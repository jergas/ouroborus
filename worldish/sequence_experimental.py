"""Experimental independent clocks for the automaton and agent workers.

Original experiment by Sat Tara Singh, Jergas Apwith and Ernesto Illescas.
The Python 3 implementation shares lifecycle/display handling with the
threaded sequence and serializes access to the shared cellular automaton.
"""
import curses
import threading

from . import runtime, sound_globals
sound_globals.simWSound = int(runtime.get_specific().soundOn)
from . import sequence_threaded as threaded
from . import sound

specific = runtime.get_specific()


def startExecutionNormal():
    sound.startSoundServer()
    try:
        if specific.displayType == "curses":
            curses.wrapper(lambda screen: threaded.main(screen, ExperimentalSequence))
        else:
            threaded.main(None, ExperimentalSequence)
    finally:
        sound.stopSoundServer()
    return 1


class ExperimentalSequence(threaded.ThreadedSequence):
    """Keep independent agent clocks while protecting the shared agent registry."""

    def __init__(self, screen):
        super().__init__(screen)
        self.world_lock = threading.RLock()
        self.started = threading.Event()
        self.workers = []
        self.assignments = {}
        self.worker_count = specific.agentThreadsNumber if specific.agentThreads == "custom" else 1
        if self.worker_count < 1:
            raise ValueError("agentThreadsNumber must be positive")
        self.per_agent = specific.agentThreads == "onePerAgent"
        if specific.agentThreads not in ("custom", "one", "onePerAgent"):
            raise ValueError(f"Unknown agentThreads setting: {specific.agentThreads}")

    def add_worker(self, key):
        worker = threading.Thread(target=self.agentLoop, args=(key,), name=f"Agents-{key}")
        self.workers.append(worker)
        worker.start()

    def simulationLoop(self):
        try:
            if self.per_agent:
                for key in list(self.taw):
                    self.add_worker(key)
            else:
                for index in range(self.worker_count):
                    self.add_worker(index)
            while self.bast.annum < self.doomsday and not self.stop.is_set():
                with self.world_lock:
                    self.bast.iterateAutomaton()
                    self.started.set()
                    if self.bast.annum % self.simulationToAudiovisual == 0:
                        self.on_display_thread(self.showBackground)
                if sound.SoundServer.perf.status():
                    break
                self.stop.wait(max(specific.annumDelay, 0.001))
        except BaseException as error:
            self.error = error
        finally:
            self.stop.set()
            self.started.set()
            # Workers may have added descendants; after the stop signal no
            # further workers are admitted, and all outstanding ones are joined.
            with self.world_lock:
                workers = list(self.workers)
            for worker in workers:
                worker.join()

    def agentLoop(self, worker_key):
        self.started.wait()
        try:
            while not self.stop.is_set():
                with self.world_lock:
                    if self.stop.is_set():
                        return
                    if self.per_agent:
                        keys = [worker_key] if worker_key in self.taw else []
                        if not keys:
                            return
                    else:
                        for key in self.taw:
                            if key not in self.assignments:
                                self.assignments[key] = len(self.assignments) % self.worker_count
                        keys = [key for key in self.taw if self.assignments[key] == worker_key]
                    for key in keys:
                        if self.stop.is_set():
                            return
                        entry = self.taw[key]
                        prayer = entry.fatum["prayer"]
                        child = self.bast.readBookOfLife(entry)
                        if self.per_agent and isinstance(child, str) and not self.stop.is_set():
                            self.add_worker(child)
                        self.on_display_thread(lambda entry=entry, prayer=prayer: self.showAgent(entry, prayer))
                self.stop.wait(max(specific.agentsDelay, 0.001))
        except BaseException as error:
            if not self.stop.is_set():
                self.error = error
                self.stop.set()
