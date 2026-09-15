"""Own a worker process group, terminal and private control connection."""
import errno
import fcntl
import json
import os
from pathlib import Path
import pty
import signal
import socket
import struct
import subprocess
import sys
import termios
import time
import uuid

from PySide6.QtCore import QObject, Property, Signal, Slot, QTimer, QUrl
from PySide6.QtGui import QDesktopServices

from worldish.config import SimulationConfig
from worldish.protocol import Decoder, encode


class Controller(QObject):
    changed = Signal()
    terminalData = Signal(bytes)
    terminalReset = Signal()
    snapshotChanged = Signal(dict)
    completed = Signal()

    def __init__(self, parent=None, output_root=None):
        super().__init__(parent)
        self._state = "idle"
        self._message = "Choose a specificity and bring a world to life."
        self._metrics = "No active simulation"
        self._audio = "Audio stopped"
        self._run_path = ""
        self.process = None
        self.master = None
        self.channel = None
        self.log = None
        self.columns, self.rows = 80, 30
        self.decoder = Decoder()
        self.outgoing = b""
        self.request_id = 0
        self.run_id = ""
        self.stop_at = None
        self.sent_interrupt = False
        self.final_state = None
        self.audio_started_at = None
        self.failure_reason = None
        self.config = None
        self.output_root = Path(output_root or Path.cwd() / ".worldish" / "desktop")
        self.timer = QTimer(self)
        self.timer.setInterval(20)
        self.timer.timeout.connect(self.poll)

    state = Property(str, lambda self: self._state, notify=changed)
    message = Property(str, lambda self: self._message, notify=changed)
    metrics = Property(str, lambda self: self._metrics, notify=changed)
    audioStatus = Property(str, lambda self: self._audio, notify=changed)
    runPath = Property(str, lambda self: self._run_path, notify=changed)
    runSummary = Property(str, lambda self: f"{self.config.preset.title()} · seed {self.config.seed} · {self.config.steps} iterations" if self.config else "", notify=changed)
    busy = Property(bool, lambda self: self.process is not None, notify=changed)

    @Slot(str, int, int, float, str, float)
    @Slot(str, int, int, float, str, float, str, int, str, int)
    def start(self, preset, steps, seed, interval, audio, volume,
              execution_method="compiled", instructions_per_tick=6,
              energy_policy="maintenance", instructions_per_prana=6):
        if self.process:
            return
        try:
            self.config = SimulationConfig(preset.lower(), steps, seed, interval, audio, volume,
                                           execution_method, instructions_per_tick,
                                           energy_policy, instructions_per_prana)
            self.output_root.mkdir(parents=True, exist_ok=True)
            self.run_id = uuid.uuid4().hex
            output = self.output_root / self.run_id
            output.mkdir()
            self._run_path = str(output.resolve())
            config_path = output / "config.json"
            config_path.write_text(json.dumps(self.config.to_dict(), indent=2) + "\n")
            self.master, slave = pty.openpty()
            parent, child = socket.socketpair()
            self.channel = parent
            try:
                fcntl.ioctl(slave, termios.TIOCSWINSZ, struct.pack("HHHH", self.rows, self.columns, 0, 0))
                env = os.environ.copy()
                env["TERM"] = "xterm-256color"
                env["PYTHONUNBUFFERED"] = "1"
                root = Path(__file__).resolve().parents[2]
                env["PYTHONPATH"] = str(root) + os.pathsep + env.get("PYTHONPATH", "")
                native = root / ".deps/native/usr/lib"
                if native.is_dir():
                    env["LD_LIBRARY_PATH"] = str(native) + os.pathsep + env.get("LD_LIBRARY_PATH", "")
                    env.setdefault("OPCODE6DIR64", str(native / "csound/plugins64-6.0"))
                self.log = (output / "worker.log").open("wb")
                self.process = subprocess.Popen(
                    [sys.executable, "-m", "worldish.worker", "--channel", str(child.fileno()),
                     "--run-id", self.run_id, "--config", str(config_path.resolve())],
                    stdin=slave, stdout=slave, stderr=self.log, env=env,
                    pass_fds=(child.fileno(),), start_new_session=True)
            finally:
                os.close(slave)
                child.close()
            os.set_blocking(self.master, False)
            parent.setblocking(False)
            self.decoder = Decoder()
            self.outgoing = b""
            self.stop_at = None
            self.sent_interrupt = False
            self.final_state = None
            self.failure_reason = None
            self.audio_started_at = None
            self._state = "preparing"
            action = "Preparing interpreted programs." if execution_method == "interpreted" else "Compiling genomes may take a moment."
            self._message = f"Preparing {preset.title()} · seed {seed}. {action}"
            self._metrics = "Initializing world"
            self._audio = "Audio preparing" if audio != "off" else "Audio off"
            self.terminalReset.emit()
            self.timer.start()
        except (OSError, ValueError) as error:
            self._message = str(error)
            if self.process:
                self._kill_group(signal.SIGKILL)
                self.process.wait()
            self._release()
            self._state = "failed"
        self.changed.emit()

    @Slot(str)
    def command(self, action):
        self.send_command(action)

    def send_command(self, action, **values):
        if not self.process or self._state == "stopping":
            return
        self.request_id += 1
        self.outgoing += encode({"run_id": self.run_id, "request_id": self.request_id,
                                 "action": action, **values})

    @Slot(float)
    def setPace(self, value):
        self.send_command("pace", value=value)

    @Slot(float)
    def setVolume(self, value):
        self.send_command("volume", value=value)

    @Slot(bool)
    def setMuted(self, value):
        self.send_command("mute", value=value)

    @Slot()
    def stop(self):
        if self.process and self.stop_at is None:
            self.send_command("stop")
            self.stop_at = time.monotonic()
            self._state = "stopping"
            self._message = "Stopping simulation and audio…"
            self.changed.emit()

    @Slot(int, int)
    def resize(self, columns, rows):
        self.columns = max(2, min(columns, 400))
        self.rows = max(2, min(rows, 200))
        if self.master is not None:
            try:
                fcntl.ioctl(self.master, termios.TIOCSWINSZ, struct.pack("HHHH", self.rows, self.columns, 0, 0))
                self._kill_group(signal.SIGWINCH)
            except OSError:
                pass

    def terminal_input(self, data):
        if data == b"\x03":
            self.stop()
            return
        if self.master is not None:
            try:
                os.write(self.master, data)
            except (BlockingIOError, OSError):
                pass

    def _event(self, event):
        if event.get("run_id") != self.run_id:
            return
        kind = event["type"]
        if kind == "phase" and self.stop_at is None:
            self.audio_started_at = time.monotonic() if event["phase"] == "audio" else None
            self._message = event["message"]
        elif kind == "state" and self.stop_at is None:
            self._state = event["state"]
            if self._state in ("running", "paused"):
                self._message = "World alive." if self._state == "running" else "Paused · Step advances one tick. Audio is muted while paused."
                self._audio = "Audio off" if self.config.audio == "off" else "Audio muted (paused)" if self._state == "paused" else "Audio active" if self.config.audio == "speakers" else "Audio running without output"
        elif kind == "snapshot":
            self._metrics = f"Tick {event['tick']} · Agents {event['population']} · Births {event['births']} · Deaths {event['deaths']}"
            self.snapshotChanged.emit(event)
        elif kind == "finished":
            self.final_state = event["state"]
            result = event["result"]
            self._metrics = f"Tick {result['iterations']} · Agents {result['population']} · Births {result['births']} · Deaths {result['deaths']}"
        elif kind == "failed":
            self.final_state = "failed"
            self._message = event["message"] + " · See run logs."
        elif kind == "error":
            self._message = event["message"]
        self.changed.emit()

    def _kill_group(self, sig):
        if self.process:
            try:
                os.killpg(self.process.pid, sig)
            except ProcessLookupError:
                pass

    def poll(self):
        if not self.process:
            return
        try:
            # Bounded reads keep the UI responsive even during heavy output.
            for _ in range(8):
                try:
                    data = os.read(self.master, 65536)
                except OSError as error:
                    if error.errno in (errno.EIO, errno.EAGAIN):
                        break
                    raise
                if not data:
                    break
                self.terminalData.emit(data)
            if self.outgoing:
                try:
                    count = self.channel.send(self.outgoing)
                    self.outgoing = self.outgoing[count:]
                except BlockingIOError:
                    pass
            latest = None
            for _ in range(16):
                try:
                    data = self.channel.recv(65536)
                except BlockingIOError:
                    break
                if not data:
                    break
                for event in self.decoder.feed(data):
                    if event.get("type") == "snapshot":
                        latest = event
                    else:
                        if latest:
                            self._event(latest)
                            latest = None
                        self._event(event)
            if latest:
                self._event(latest)
        except (OSError, ValueError, KeyError) as error:
            if self.stop_at is None:
                self._message = f"Worker connection ended: {error}"
                self.stop()
        if self.audio_started_at is not None and time.monotonic() - self.audio_started_at > 20 and self.stop_at is None:
            self.failure_reason = "Audio device did not respond. Try Audio output: Off, or check your audio service."
            self.stop()
            self._message = self.failure_reason
            self.changed.emit()
        if self.stop_at is not None:
            elapsed = time.monotonic() - self.stop_at
            if elapsed > 1 and not self.sent_interrupt:
                self._kill_group(signal.SIGINT)
                self.sent_interrupt = True
            if elapsed > 3:
                self._kill_group(signal.SIGKILL)
        code = self.process.poll()
        if code is not None:
            # Also reap compiler descendants if initialization was interrupted.
            self._kill_group(signal.SIGKILL)
            self._state = "failed" if self.failure_reason else "stopped" if self.stop_at is not None else self.final_state or "failed"
            if self._state != "failed":
                self._message = "Run finished." if self._state == "finished" else "Run stopped."
            elif self.failure_reason:
                self._message = self.failure_reason
            elif not self.final_state:
                self._message = f"Worker exited ({code}). See worker.log in the run folder."
            self._audio = "Audio stopped"
            self._release()
            self.changed.emit()
            self.completed.emit()

    def _release(self):
        self.timer.stop()
        if self.master is not None:
            os.close(self.master)
            self.master = None
        if self.channel:
            self.channel.close()
            self.channel = None
        if self.log:
            self.log.close()
            self.log = None
        self.process = None

    @Slot()
    def openLogs(self):
        if self._run_path:
            QDesktopServices.openUrl(QUrl.fromLocalFile(self._run_path))

    @Slot(QUrl, "QVariantMap")
    def savePreset(self, url, values):
        try:
            config = SimulationConfig(**values)
            path = Path(url.toLocalFile())
            path.write_text(json.dumps({"version": 1, "simulation": config.to_dict()}, indent=2) + "\n")
            self._message = f"Saved settings to {path.name}."
        except (OSError, ValueError, TypeError) as error:
            self._message = f"Could not save settings: {error}"
        self.changed.emit()

    @Slot(QUrl, result="QVariantMap")
    def loadPreset(self, url):
        try:
            path = Path(url.toLocalFile())
            if path.stat().st_size > 65536:
                raise ValueError("Settings file is too large")
            data = json.loads(path.read_text())
            if not isinstance(data, dict) or data.get("version") != 1:
                raise ValueError("Unsupported settings file version")
            config = SimulationConfig(**data["simulation"])
            self._message = f"Loaded {path.name}. Settings apply on the next run."
            self.changed.emit()
            return config.to_dict()
        except (OSError, ValueError, TypeError, KeyError) as error:
            self._message = f"Could not load settings: {error}"
            self.changed.emit()
            return {}

    def shutdown(self):
        if self.process:
            self._kill_group(signal.SIGINT)
            try:
                self.process.wait(timeout=2)
            except subprocess.TimeoutExpired:
                self._kill_group(signal.SIGKILL)
                self.process.wait(timeout=2)
            self._kill_group(signal.SIGKILL)
            self._release()
