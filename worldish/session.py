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
        while sequence.bast.annum < sequence.doomsday:
            if control and not control.before_tick(sequence):
                break
            sequence.bast.iterateAutomaton()
            render = sequence.bast.annum % sequence.simulationToAudiovisual == 0
            for entry in list(sequence.taw.values()):
                prayer = entry.fatum["prayer"]
                sequence.bast.readBookOfLife(entry)
                if render:
                    sequence.showAgent(entry, prayer)
            if render:
                sequence.showBackground()
            if control:
                control.after_tick(sequence)
            else:
                time.sleep(specific.annumDelay)
            if sound.SoundServer.perf.status():
                raise RuntimeError("Audio performance ended before the simulation completed")
    finally:
        soundGlobals.mainIterCycle = 0
        soundGlobals.stop_event.set()
        for voice in started:
            voice.join()
        sound.stopSoundServer()
    return runtime.report_result(sequence.bast, sequence.bast.generator)
