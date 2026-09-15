"""Linux session worker: curses on the PTY, control on a separate socket."""
import argparse
import curses
import fcntl
import json
import os
from pathlib import Path
import select
import socket
import termios
import time
import traceback

from .config import SimulationConfig
from .protocol import Decoder, encode


class SessionControl:
    def __init__(self, channel, run_id, config):
        self.channel = channel
        self.run_id = run_id
        self.config = config
        self.decoder = Decoder()
        self.paused = False
        self.stopped = False
        self.step_pending = 0
        self.interval = config.interval
        self.volume = config.volume
        self.muted = False
        self.next_tick = 0
        self.last_frame = 0
        self.send("state", state="preparing")

    def send(self, kind, **values):
        # The GUI drains this channel continuously. A stalled/disconnected GUI
        # must end the worker instead of blocking indefinitely.
        self.channel.sendall(encode({"type": kind, "run_id": self.run_id, **values}))

    def gain(self):
        from .sequence_threaded import sound, specific
        if specific.soundOn:
            sound.SoundServer.cSnd.setControlChannel("worldish_attenuation", 1 if self.paused or self.muted else 1 - self.volume)

    def ready(self, sequence):
        self.sequence = sequence
        self.gain()
        self.send("state", state="running")
        self.snapshot(sequence)

    def snapshot(self, sequence):
        width, height = sequence.size
        from .observation import MAX_AGENT_CHOICES
        observer = sequence.bast.generator.observation
        living = (entry for entry in sequence.taw.values()
                  if getattr(entry, "agent", None) is not None)
        from itertools import islice
        organisms = [{"id": entry.name, "position": list(entry.agent.tellAddress())}
                     for entry in islice(living, MAX_AGENT_CHOICES)]
        self.send("snapshot", tick=sequence.bast.annum,
                  organisms=organisms, organisms_truncated=sequence.kemet.tellPopulation() > len(organisms),
                  inspection=observer.inspection(sequence.taw),
                  ledger=observer.ledger(sequence.kemet.tellAgents()), trace=observer.trace.summary(),
                  population=sequence.kemet.tellPopulation(), births=sequence.bast.births,
                  deaths=sequence.bast.deaths, width=width, height=height,
                  cells=[int(bool(sequence.kemet.get((x, y)))) for y in range(height) for x in range(width)],
                  agents=[list(p) for p in sorted({tuple(p) for a in sequence.kemet.tellAgents()
                                                    for p in a.tellCorporality()})])
        self.last_frame = time.monotonic()

    def commands(self, timeout):
        if not select.select([self.channel], [], [], timeout)[0]:
            return
        data = self.channel.recv(65536)
        if not data:
            self.stopped = True
            return
        for command in self.decoder.feed(data):
            request = command.get("request_id")
            if command.get("run_id") != self.run_id:
                continue
            action = command.get("action")
            try:
                if action == "stop":
                    self.stopped = True
                elif action == "pause":
                    self.paused = True
                    self.step_pending = 0
                    self.gain()
                elif action == "resume":
                    self.paused = False
                    self.step_pending = 0
                    self.gain()
                elif action == "step" and self.paused:
                    self.step_pending += 1
                elif action == "inspect":
                    agent_id = command["agent_id"]
                    if not isinstance(agent_id, str) or len(agent_id) > 256:
                        raise ValueError("Invalid agent ID")
                    self.sequence.bast.generator.observation.select(agent_id, self.sequence.taw)
                    self.snapshot(self.sequence)
                elif action == "pace":
                    value = float(command["value"])
                    if not 0.01 <= value <= 5:
                        raise ValueError("Invalid pace")
                    self.interval = value
                    self.next_tick = time.monotonic()
                elif action == "volume":
                    value = float(command["value"])
                    if not 0 <= value <= 1:
                        raise ValueError("Invalid volume")
                    self.volume = value
                    self.gain()
                elif action == "mute":
                    self.muted = bool(command["value"])
                    self.gain()
                else:
                    raise ValueError("Command unavailable in this state")
                self.send("ack", request_id=request, action=action)
                self.send("state", state="stopping" if self.stopped else "paused" if self.paused else "running")
                if action == "pause":
                    self.snapshot(self.sequence)
            except (ValueError, KeyError, TypeError) as error:
                self.send("error", request_id=request, message=str(error))

    def resize(self, sequence):
        display = sequence.display
        if not isinstance(display, tuple):
            return
        stdscr = display[0]
        size = os.get_terminal_size(0)
        dimensions = (min(sequence.size[0], max(0, size.columns - 1)),
                      min(sequence.size[1], max(0, size.lines - 1)))
        if stdscr.getmaxyx() != (size.lines, size.columns) or display[1:] != dimensions:
            curses.resizeterm(size.lines, size.columns)
            stdscr.erase()
            sequence.display = (stdscr, *dimensions)
            sequence.showBackground()
        # Consume resize/key events so ncurses processes its resize notification.
        while stdscr.getch() != -1:
            pass

    def before_tick(self, sequence):
        while True:
            self.commands(0)
            self.resize(sequence)
            if self.stopped:
                return False
            if self.paused and self.step_pending:
                self.step_pending -= 1
                return True
            if not self.paused and time.monotonic() >= self.next_tick:
                return True
            self.commands(0.03)

    def after_tick(self, sequence):
        if self.paused or sequence.bast.annum == sequence.doomsday or time.monotonic() - self.last_frame >= 0.05:
            self.snapshot(sequence)
        self.next_tick = time.monotonic() + self.interval


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--channel", type=int, required=True)
    parser.add_argument("--run-id", required=True)
    parser.add_argument("--config", type=Path, required=True)
    args = parser.parse_args()
    channel = socket.socket(fileno=args.channel)
    channel.settimeout(2)
    control = None
    try:
        fcntl.ioctl(0, termios.TIOCSCTTY, 0)
        config = SimulationConfig(**json.loads(args.config.read_text()))
        control = SessionControl(channel, args.run_id, config)
        from . import runtime
        from .start import main as launch
        runtime.session_control = control
        # Configuration is applied before any execution module imports GOD/audio.
        runtime.specificity = config.preset.capitalize()
        specific = runtime.get_specific()
        specific.annumDelay = specific.agentsDelay = 0
        specific.desktopVolume = config.volume
        if config.audio == "speakers":
            runtime_dir = Path(os.environ.get("XDG_RUNTIME_DIR", f"/run/user/{os.getuid()}"))
            backend = os.environ.get("WORLDISH_AUDIO_BACKEND", "pulse" if (runtime_dir / "pulse/native").exists() else "pa")
            if backend not in ("pulse", "pa", "alsa", "jack"):
                raise ValueError("Unsupported WORLDISH_AUDIO_BACKEND")
            specific.csOptions = f"<CsoundSynthesizer>\n<CsOptions>\n-odac -+rtaudio={backend} -b1024 -B2048 -d -m0\n</CsOptions>"
        launch_args = ["--mode", "session", "--specificity", config.preset, "--display", "curses",
                       "--seed", str(config.seed), "--steps", str(config.steps),
                       "--output-dir", str(args.config.parent),
                       "--execution-method", config.execution_method,
                       "--instructions-per-tick", str(config.instructions_per_tick),
                       "--energy-policy", config.energy_policy,
                       "--instructions-per-prana", str(config.instructions_per_prana),
                       "--trace-mode", config.trace_mode, "--trace-limit", str(config.trace_limit)]
        if config.audio == "off":
            launch_args.append("--no-sound")
        elif config.audio == "silent":
            launch_args.append("--silent-audio")
        launch(launch_args)
        result = json.loads((args.config.parent / "result.json").read_text())
        control.send("finished", state="stopped" if control.stopped else "finished", result=result)
        return 0
    except BaseException as error:
        traceback.print_exc()
        if control:
            try:
                control.send("failed", message=str(error) or type(error).__name__)
            except OSError:
                pass
        return 1
    finally:
        channel.close()


if __name__ == "__main__":
    raise SystemExit(main())
