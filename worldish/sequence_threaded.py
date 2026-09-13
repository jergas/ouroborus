from . import runtime
# This script orchestrates execution for an ouroborus artificial life
# environment. The module is based on sequence_audiovisual.py, with the
# novelty that it implements threads.
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# It includes the following features:
#
#       * Execution of the simulation proper, background audiovisuals and
#         the agents audiovisuals occur in separate threads
#       * All the AL functionality resides in the GOD module; look therein
#               for pearls of wisdom
#       * If you're trying to understand how the code works, refer to
#               sequence_debug.py and sequence_auidovisual.py


# Python's native libraries
import curses
import operator
import os
import random
import signal
import sys
import threading
import queue
from concurrent.futures import Future, TimeoutError
import time

# These lines need to be read before GOD and bookentry!!!
from . import sound_globals as soundGlobals
soundGlobals.simWSound = int(runtime.get_specific().soundOn)

# Ouroborus libraries
from . import GOD
from .bookentry import BookEntry
from . import sound


# __main__.specificity is (part of) a filename for a config file which
# stores information such as the cellular aoutomaton's parameters, the seed
# genome for agents, and so forth. This is name is passed down from the
# command line and used here to actually import the config file.
specificity = runtime.specificity
specific = runtime.get_specific(specificity)


# If instructed by the configuration file, enable system output to be
# printed to file.
if specific.sysOutToFile:
        sys.stdout = specific.debugFile
        sys.stderr = specific.debugFile


def startExecutionNormal():
    """Run simulation work in a worker and keep terminal/GUI updates on the main thread."""
    sound.startSoundServer()
    try:
        if specific.displayType == 'curses':
            curses.wrapper(main)
        else:
            main(None)
    finally:
        sound.stopSoundServer()
    return 1


def main(stdscr, sequence_class=None):
    sequence = (sequence_class or ThreadedSequence)(stdscr)
    sound.beginPerformance()
    voices = sound.backgroundVoices() + [sound.backgroundControl()]
    simulation = threading.Thread(target=sequence.simulationLoop, name='Simulation')
    for voice in voices:
        voice.start()
    simulation.start()
    try:
        while simulation.is_alive() or not sequence.requests.empty():
            try:
                callback, result = sequence.requests.get(timeout=0.05)
            except queue.Empty:
                continue
            try:
                result.set_result(callback())
            except BaseException as error:
                result.set_exception(error)
        simulation.join()
        if sequence.error is not None:
            raise sequence.error
    finally:
        sequence.stop.set()
        simulation.join()
        soundGlobals.mainIterCycle = 0
        soundGlobals.stop_event.set()
        for voice in voices:
            voice.join()
        sound.stopSoundServer()
    runtime.report_result(sequence.bast, sequence.bast.generator)
    print(f"Completed {sequence.bast.annum} iterations; {sequence.kemet.tellPopulation()} agents alive.")
    return 1


class ThreadedSequence(object):
        """ The initialization method sets up the attributes needed for the
        (threaded) execution of the rest of the class' methods. Shared
        variables are implemented as class attributes, and their data is
        kept thread-safe and synchronized via the threading.Lock() and
        threading.Condition() methods.
        """
        def __init__(self, stdscr):
                """Instantiates GOD's automaton-generator and automaton-
                organizer classes. Populates the automaton with some
                initial creatures. Generates a display.

                stdscr  ---> a curses standard screen object
                """
                # Instantiate a generator.
                aset = GOD.Generator(specific.name, specificity)
                # The following lines contain all the data to build a complete
                # cellular automaton.
                self.size = specific.size
                (width, height) = self.size
                topologyData = specific.topology
                neighborData = specific.neighborhood
                ruleData = specific.rule
                automatonData = specific.automaton
                # avatars is the number of initial creatures, and doomsday the
                # number of iterations.
                (avatars, self.doomsday) = (specific.avatars, specific.doomsday)
                # self.taw is a dictionary which whill contain runtime
                # information essential for the agents in the form of
                # BookEntries.
                self.taw = {}

                # Invoke GOD.Generator's automaton creation method with the data
                # given above.
                self.kemet = aset.generateAutomaton(self.size, topologyData,
                                                                                        neighborData, ruleData,
                                                                                        automatonData)
                # Now call a GOD.Organizer to oversee this automaton.
                self.bast = GOD.Organizer(self.kemet, self.taw, specificity)
                self.bast.generator = aset
                (self.bast.width, self.bast.height) = (width, height)


                # The bast organizer will now plant some seeds in kemet.
                self.bast.initialiseAutomaton(specific.seed)
                # Populate the automaton with some initial creatures.
                while avatars:
                        # GOD.Generator will write and compile a module for each
                        # creature, create a BookEntry to contain it and append it
                        # to the list taw
                        aset.generateGenotype(specific.seedCode, self.taw)
                        avatars -= 1

                # Prime the initial avatars for actual creation.
                for key in list(self.taw.keys()):
                        self.taw[key].fatum["prayer"] = "CreateMe"
                        # Each BookEntry has a dictionary called its fatum. The key
                        # "prayer" is linked to strings which GOD.Organizer will
                        # interpret (via Python introspection) to act in various
                        # ways on  the BookEntry and its attributes (i.e. the
                        # creature). The value "CreateMe" identifies the BookEntry
                        # as a candidate for initalization, meaning creating an
                        # agent object and placing it on the cellular automaton
                        # grid.

                # bast reads the BookEntries in taw and calls actual agent
                # objects into being from the code in the modules which were
                # compiled by aset.
                for key in list(self.taw.keys()):
                        self.bast.readBookOfLife(self.taw[key])

                # Decide whether to use a Curses or Pygame display
                if stdscr:
                        # Generate a curses display.
                        self.display = aset.generateDisplay(self.kemet, self.size, stdscr)
                else:
                        self.display = aset.generateDisplay(self.kemet, self.size, self.taw)

                # Set some initial data for sound control.
                sound.setInitialData(self.size)

                # Initialize variables for agent-related inter-thread
                # communication.
                self.currentEntry = None
                self.birth      = 0
                self.death      = 0

                # Number of simulation loops per audiovisual loop.
                self.simulationToAudiovisual = specific.simulationToAudiovisual
                self.requests = queue.Queue()
                self.stop = threading.Event()
                self.error = None

        def on_display_thread(self, callback):
                result = Future()
                self.requests.put((callback, result))
                while not self.stop.is_set():
                        try:
                                return result.result(timeout=0.05)
                        except TimeoutError:
                                pass
                raise InterruptedError("Simulation stopped")

        def simulationLoop(self):
                """Advance the original automaton/agent lifecycle and await each display update."""
                try:
                        while self.bast.annum < self.doomsday and not self.stop.is_set():
                                self.bast.iterateAutomaton()
                                render = self.bast.annum % self.simulationToAudiovisual == 0
                                for entry in list(self.taw.values()):
                                        if self.stop.is_set():
                                                break
                                        prayer = entry.fatum["prayer"]
                                        self.bast.readBookOfLife(entry)
                                        if render:
                                                self.on_display_thread(lambda entry=entry, prayer=prayer: self.showAgent(entry, prayer))
                                if render:
                                        self.on_display_thread(self.showBackground)
                                if sound.SoundServer.perf.status():
                                        break
                                self.stop.wait(specific.annumDelay)
                except BaseException as error:
                        self.error = error

        def showBackground(self):
                self.bast.refreshDisplay(self.display)
                sound.inputDataControl(self.kemet)

        def showAgent(self, entry, prayer):
                if prayer != "KillMe":
                        self.bast.refreshAgent(entry, self.display)
                if specific.soundOn:
                        if prayer == "KillMe":
                                sound.agentDeath(entry.fatum["voice"])
                        elif prayer == "BeBirthed":
                                sound.agentBirth(entry.fatum["voice"])
                        elif entry.fatum["voice"].ate:
                                sound.eatSound(entry.fatum["voice"])
                                entry.fatum["voice"].ate = 0
