#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus
# artificial life environment.
# The module is based in sequence_auidovisual.py, and sequence_new.py,
# with the novelty that it implements threads
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# This module is a work in progress. Things still lacking are:
#
#	* A sweet spot between the simulation's speed and the audiovisual's
#		lack of it has yet to be found
#	* The terminal window is not re-established if the application is
#		terminated via ctrl^c
#	* Background sound algorithms must be updated to accomodate the
#		threaded execution
#
# It includes the following features:
#
#	* Execution of the simulation proper, and the audiovisual
#		representation occur on different threads
#	* All the AL functionality resides in the GOD module; look therein
#		for pearls of wisdom
#	* If your'e trying to understand how the code works, refer to
#		sequence_new.py and sequence_auidovisual.py


# Python's native libraries
import curses
import operator
import random
import sys
import threading
# Ouroborus libraries
import GOD
from bookentry import BookEntry
import sound

specificity = "Alpha"
specific = __import__("specific"+specificity)

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
	simulation = threading.Thread(name='Simulation',
									target=Sequence.simulationLoop)
	audiovisual = threading.Thread(name='Audiovisual',
									target=Sequence.audioVisualLoop)
	# Start the thread instances, and then wait until they've finished,
	# so they don't interfere with curses' clean-up.
	simulation.start()
	audiovisual.start()
	simulation.join()
	audiovisual.join()

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
		starts sound.
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
		# avatars is the number of initial creatures, and doomsday is the number
		# of iterations.
		(avatars, self.doomsday) = (specific.avatars, specific.doomsday)
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
		self.initialAgents = 0
		# Cycle through avatars to populate the automaton with some initial
		# creatures.
		while avatars:
			# Compile a module for each creature, and append it to the list
			# biblos along with its name.
			mary.generateGenotypeNew(specific.seedCode, self.biblos)
			avatars -= 1
			self.initialAgents += 1
		# prime the initial avatars for actual creation
		for entry in self.biblos:
			entry.fatum["prayer"] = "CreateMe"
		# magdalen reads the data in biblos and calls actual agent objects.
		for entry in self.biblos:	
			self.magdalen.readBookOfLifeNew(entry)
		# Initialize an attribute to hold the automaton's population.
		self.population = 0

		# Generate a display, and start the sound threads.
		setCursesColors()
		self.display = mary.generateDisplay(self.terra, self.size, stdscr)
		sound.setInitialData(self.magdalen.width)
		sound.startBackground()
		sound.startBackgroundControl()
		# Create a thread-condition object to keep the simulation and
		# audiovisual threads synchronized.
		self.lock				= threading.Lock()
		self.threadCondition	= threading.Condition(self.lock)


	def simulationLoop(self):
		"""The simulation's main iteration cycle happens here.
		"""	
		loopsPerVisual	= 1
		counter			= 1

		# Main iteration cycle
		while self.magdalen.annum < self.doomsday:
			# Aquire a thread-synchronizing condition.
			self.threadCondition.acquire()
			# Iterate the c.a., while updating the population attribute. Parse
			# the whole length of biblos.
			# If loopsPerVisual loops of the simulation have transcurred,
			# notify the audiovisual thread, so that it loops once. Otherwise,
			# only iterate the simulation.		
			if loopsPerVisual == counter:
				self.population = self.magdalen.iterateAutomaton()
				for entry in self.biblos:
					self.births = []
					# Birth sound for new-born agents
					if entry.fatum["prayer"] == "BeBirthed":
						sound.agentBirth(entry.fatum["voice"])
					self.magdalen.readBookOfLifeNew(entry)
				# Notify the audiovisual loop, so it continues its course.
				self.threadCondition.notify()
				# Wait for a notification from the audiovisual loop.
				self.threadCondition.wait()
				counter = 1
			else:
				self.population = self.magdalen.iterateAutomaton()
				for entry in self.biblos:
					self.magdalen.readBookOfLifeNew(entry)
				counter += 1
			# Release the thread-synchronizing condition.
			self.threadCondition.release()
		# This last part makes sure that, if this thread finishes before
		# the audiovisual one, the latter does not remain locked.
		self.threadCondition.acquire()
		self.threadCondition.notify()
		self.threadCondition.release()	


	def audioVisualLoop(self):
		""" The audiovisual loop happens here.
		"""
		(width, height)	= self.size

		while self.magdalen.annum < self.doomsday:
			# Aquire a thread-synchronizing condition.
			self.threadCondition.acquire()
			# Update the data needed by the background sound engine.
			populNorm = float(self.population) / operator.mul(width,height)
			sndCtrlCells = [self.terra.get((22,18)), self.terra.get((40,18)),
							self.terra.get((64,18))]
			# Update the display
			self.magdalen.refreshDisplay(self.display)
			# Update the audio
			sound.inputDataControl(sndCtrlCells, populNorm)
			# Notify the simulation loop, so it continues its course.
			self.threadCondition.notify()
			# Wait for a notification from the simulation loop.
			self.threadCondition.wait()
			# Release the thread-synchronizing condition.
			self.threadCondition.release()
		# This last part makes sure that, if this thread finishes before
		# the simulation one, the latter does not remain locked.
		self.threadCondition.acquire()
		self.threadCondition.notify()
		self.threadCondition.release()	
		sound.stopSoundServer()
