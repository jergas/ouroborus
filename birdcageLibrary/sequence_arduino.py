#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus
# artificial life environment.
# The module is based in sequence_audiovisual.py, and sequence_new.py,
# with the novelty that it implements threads and input from an arduino chip.
#
# Coded by Jergas Apwith and Diego Trujillo


# Python's native libraries
import curses
import operator
import random
import sys
import threading
import time

# These lines need to be read before GOD and bookentry!!!
import sound_globals as soundGlobals
soundGlobals.simWSound = 1

# Ouroborus libraries
import GOD
from bookentry import BookEntry
import sound

## Debug temporary lines:
logging = open('logging.txt', 'w')
##

specificity = "Environment"
specific = __import__("specific"+specificity)
if specific.logging:
	pass

def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)


def startExecutionBeta():
    """changes specificity to Beta and then calls the Normal submode

    return -->>1"""
    global specific
    specificity = "Beta"
    specific = __import__("specific"+specificity)
    
    startExecutionNormal()


def startExecutionNormal():
	"""Start normal execution cycle with sound and visual display

	return -->> 1

	Visual display through curses terminal control module
	Sonorization through csound courtesy of Ernesto Illescas
	"""
	print "Ready for full audiovisual execution...commence primary ignition!"
	# Start-up Csound (should be done here so Csound's start-up and
	#compilation messages are kept away from the simulation by
	#curses.wrapper().
	sound.startSoundServer()
	# curses.wrapper is the kosher way to fire up curses visual services; it
	#guarantees that the terminal will not be left stranded in an ocean of
	#insanity if the program terminates exceptionally.
	curses.wrapper(main)
#	sound.stopSoundServer()
	return 1


def main(stdscr):
	"""Runs the simulation initialization methods, converts the
	simulation and audiovisual methods into threads and starts these
	threads.
	stdscr	---> a curses standard screen object
	"""
	# Instantiate the class ThreadedSequence, which contains the
	# needed attributes and methods for the execution.
	Sequence = ThreadedSequence(stdscr)
	# Instantiate two threads with target methods simulationLoop() and
	#audiovisualLoop().
	simulation	= threading.Thread(name='Simulation',
									target=Sequence.simulationLoop)
	background	= threading.Thread(name='Background',
									target=Sequence.backgroundLoop)
	
	# Create the background-sound threads.
	voices = sound.backgroundVoices()
	voicesControl = sound.backgroundControl()
	# Start the thread instances, and then wait until they've finished,
	# so they don't interfere with curses' clean-up.
	for x in voices:
		x.start()
	voicesControl.start()
	simulation.start()
	background.start()
#	voicesControl.join()
	sound.stopSoundServer()
	logging.write('you have reached line 122!\n')
#	simulation.join()
#	background.join()
#	agents.join()

	del sys.argv[1:]
	print "Done"


class ThreadedSequence(object):
	""" The initialization method sets up the attributes needed for the
	(threaded) execution of the rest of the class' methods:
	simulationLoop() and audioVisualLoop(). Shared variables are
	implemented as class attributes, and their data is kept thread-safe
	and synchronized via the threading.Lock() and threading.Condition()
	methods.
	"""
	def __init__(self, stdscr):
		"""Instantiates GOD's automaton-generator and automaton-
		organizer classes. Populates the automaton with some
		initial creatures (broken). Generates a display, and
		starts Csound.
		stdscr	---> a curses standard screen object
		"""
		# Instantiate a generator.
		mary = GOD.Generator("kristos")
		# The following lines contain all the data to build a complete
		# cellular automaton.
		self.size = specific.size
		(width, height) = self.size
		topologyData = specific.topology
		neighborData = specific.neighborhood
		ruleData = specific.rule
		automatonData = specific.automaton
		# biblos is a list which whill contain essential runtime information.
		self.biblos = []
		# Invoke GOD.Generator's automaton creation method with the data
		# given above.
		self.terra = mary.generateAutomaton(self.size, topologyData,
											neighborData, ruleData, 
											automatonData)
		# Call a GOD.Organizer to oversee this automaton.
		self.magdalen = GOD.Organizer(self.terra, self.biblos, specificity)
		self.magdalen.generator = mary
		(self.magdalen.width, self.magdalen.height) = (width, height)
          # Initialize an attribute to hold the automaton's population.
		self.population = 0
		self.currentEntry = None
		# Generate a display, and start the sound threads.
		setCursesColors()
		self.display = mary.generateDisplay(self.terra, self.size, stdscr)
		sound.setInitialData(self.magdalen.width)
#		sound.startBackground()
#		sound.startBackgroundControl()
		# Create a thread-condition object to keep the simulation and
		# audiovisual threads synchronized.
		self.bckgrndThreadCondition	= threading.Condition()
		logging.write('you have reached line 198!\n')


	def simulationLoop(self):
		"""The simulation's main iteration cycle happens here.
		"""	
		# Main iteration cycle
		while self.magdalen.annum < self.doomsday:
			# Aquire the thread-synchronizing condition.
			self.bckgrndThreadCondition.acquire()
			# Iterate the c.a., while updating the population attribute. Parse
			# the whole length of biblos.
			self.population = self.magdalen.iterateAutomaton()
			# Notify the audiovisual loop, so it continues its course.
			self.bckgrndThreadCondition.notify()
			# Wait for a notification from the audiovisual loop.
			self.bckgrndThreadCondition.wait()
			# Release the thread-synchronizing condition.
			self.bckgrndThreadCondition.release()
			logging.write('you have reached line 231!\n')
#		sound.stopSoundServer()
		# This last part makes sure that, if this thread finishes before
		# the audiovisual one, the latter does not remain locked.
		self.bckgrndThreadCondition.acquire()
		self.bckgrndThreadCondition.notify()
		self.bckgrndThreadCondition.release()

	def backgroundLoop(self):
		""" Refreshing of the curses background happens here.
		"""
		(width, height)	= self.size

		while self.magdalen.annum < self.doomsday:
			# Aquire a thread-synchronizing condition.
			self.bckgrndThreadCondition.acquire()
			# Update the data needed by the background sound engine.
			populNorm = float(self.population) / operator.mul(width,height)
			sndCtrlCells = [self.terra.get((22,18)), self.terra.get((40,18)),
							self.terra.get((64,18))]
			# Update the display
			self.magdalen.refreshDisplay(self.display)
			# Update the audio
			sound.inputDataControl(sndCtrlCells, populNorm)
			# Notify the simulation loop, so it continues its course.
			self.bckgrndThreadCondition.notify()
			# Wait for a notification from the simulation loop.
			self.bckgrndThreadCondition.wait()
			# Release the thread-synchronizing condition.
			self.bckgrndThreadCondition.release()
			logging.write('you have reached line 262!\n')
		# This last part makes sure that, if this thread finishes before
		# the simulation one, the latter does not remain locked.
		self.bckgrndThreadCondition.acquire()
		self.bckgrndThreadCondition.notify()
		self.bckgrndThreadCondition.release()	
#		sound.stopSoundServer()

