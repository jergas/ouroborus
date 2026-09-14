"""CLI entry point for the controllable session loop."""
import curses
from . import runtime


def startExecutionNormal():
    from .sequence_threaded import sound, specific
    from .session import run
    control = getattr(runtime, "session_control", None)
    if control:
        control.send("phase", phase="audio", message="Opening audio output…")
    sound.startSoundServer()
    if control:
        control.send("phase", phase="genomes", message="Preparing the world and compiling genomes…")
    try:
        return curses.wrapper(run) if specific.displayType == "curses" else run(None)
    finally:
        sound.stopSoundServer()
