"""A controlled tick loop reusing the legacy Worldish lifecycle.

The existing CLI modes remain unchanged. This session is also available through
``worldish --mode session``; a desktop worker supplies its optional control hook.
"""
import curses
import time

from . import runtime


def run(stdscr):
    from .sequence_threaded import ThreadedSequence, sound, soundGlobals, specific

    control = getattr(runtime, "session_control", None)
    sequence = ThreadedSequence(stdscr)
    from .run_limits import RunLimits, RunMonitor
    monitor = RunMonitor(sequence.bast, RunLimits.from_specificity(specific))
    sequence.bast.run_monitor = monitor
    if stdscr is not None:
        stdscr.nodelay(True)
        curses.curs_set(0)
    voices = sound.backgroundVoices() + [sound.backgroundControl()]
    started = []
    try:
        sound.beginPerformance()
        for voice in voices:
            voice.start()
            started.append(voice)
        if control:
            control.ready(sequence)
        monitor.check()
        while sequence.bast.annum < sequence.doomsday and not monitor.reached:
            if control and not control.before_tick(sequence):
                monitor.reason = "stopped"
                break
            sequence.bast.iterateAutomaton()
            render = sequence.bast.annum % sequence.simulationToAudiovisual == 0
            entries = list(sequence.taw.values())
            for index, entry in enumerate(entries):
                prayer = entry.fatum["prayer"]
                sequence.bast.readBookOfLife(entry)
                monitor.visits += 1
                monitor.tick_complete = index == len(entries) - 1
                if render:
                    sequence.showAgent(entry, prayer)
                if monitor.check():
                    break
            if not entries:
                monitor.tick_complete = True
            if render:
                sequence.showBackground()
            if control:
                if monitor.reached:
                    control.snapshot(sequence)
                else:
                    control.after_tick(sequence)
            else:
                time.sleep(specific.annumDelay)
            if monitor.reached:
                break
            if sound.SoundServer.perf.status():
                raise RuntimeError("Audio performance ended before the simulation completed")
    finally:
        soundGlobals.mainIterCycle = 0
        soundGlobals.stop_event.set()
        for voice in started:
            voice.join()
        sound.stopSoundServer()
    return runtime.report_result(sequence.bast, sequence.bast.generator)
