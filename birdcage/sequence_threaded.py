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
#	* Background sound algorithms must be updated to accomodate the
#		threaded execution.
#
# It includes the following features:
#
#	* Execution of the simulation proper, and the audiovisual
#		representation occur on different threads
#	* All the AL functionality resides in the GOD module; look therein
#		for pearls of wisdom
#	* If your'e trying to understand how the code works, refere to
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


def startExecutionNormal():
	"""Start normal execution cycle with sound and visual display

	return -->> 1

	Visual display through curses terminal control module
	Sonorization through csound courtesy of Ernesto Illescas
	"""
	print "Ready for full audiovisual execution...commence primary ignition!"
	# Start-up Csound (should be done here so Csound's start-up and
	#compilation messages are kept away from the simulation by
	#curses.wrapper()
	sound.startSoundServer()
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
		return	--> a tuple containing: instances of GOD.organizer,
					doomsday (number of iterations the simulation will
					last), a c.a., a display, ths c.a.'s size, and biblos
					(a list with essential runtime information).
		"""
		# Instantiate a generator.
		mary = GOD.Generator("kristos")
		# The following lines contain all the data to build a complete
		# cellular automaton.
		self.size = (width, height) = (80, 570)
		topologyData = ("GridTopology", 0)
		neighborData = ("VonNeumannNeighborhood", )
		ruleData = ("ReductionRule", (operator.xor, 0))
		automatonData = ("SynchronousAutomaton_2D", )
		seedCode = "Y i Y c Y s C b C d C r T l T p T e T c T r T g T o R d R l"
		(avatars, self.doomsday) = (1, 50)
		self.biblos = []
		# Invoke GOD.Generator's automaton creation method with the data
		# given above.
		self.terra = mary.generateAutomaton(self.size, topologyData, neighborData, ruleData,
										automatonData)
		# Call a GOD.Organizer to oversee this automaton.
		self.magdalen = GOD.Organizer(self.terra, self.biblos)
		self.magdalen.generator = mary
		(self.magdalen.width, self.magdalen.height) = (width, height)
		# Cycle through avatars to populate the automaton with some initial
		# creatures.
		while avatars:
			# Compile a module for each creature, and append it to the list
			# biblos along with its name.
			mary.generateGenotypeNew(seedCode.split(" "), self.biblos)
			avatars -= 1
		# magdalen reads the data in biblos and calls actual agent objects.
		for entry in self.biblos:
			# set some initial parameters in each entry's fatum
			entry.fatum["code"] = seedCode
			entry.fatum["prana"] = 7
			entry.fatum["mana"] = 1
			(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
			entry.fatum["address"] = (x, y)
			self.magdalen.readBookOfLifeNew(entry)
		# Initialize an attribute to hold the automaton's population.
		self.population = 0

		# Generate a display, and start the sound threads.
		setCursesColors()
		self.display = mary.generateDisplay(self.terra, self.size, stdscr)
		sound.startBackground()
		sound.startBackgroundControl()
		# Create a thread-condition object to keep the simulation and
		# audiovisual threads synchronized.
		self.lock				= threading.Lock()
		self.threadCondition	= threading.Condition(self.lock)


	def simulationLoop(self):
		"""The simulation's main iteration cycle happens here.
		magdalen	---> a GOD.organizer's instance
		doomsday	---> the number of iterations that the simulation
						will undergo
		return		--> 1
		"""	
		loopsPerVisual	= 2
		counter			= 2

		# Main iteration cycle
		while self.magdalen.annum < self.doomsday:

			# GOD.Organizer iterates the c.a., while updating the population
			# attribute.
			# If loopsPerVisual loops of the simulation have transcurred,
			# notify the audiovisual thread, so that it loops once.
			self.threadCondition.acquire()		
			if loopsPerVisual == counter:
				self.population = self.magdalen.iterateAutomaton()
				self.threadCondition.notify()
				self.threadCondition.wait()
				counter = 1
			else:
				self.population = self.magdalen.iterateAutomaton()
				counter += 1
			self.threadCondition.release()
		# This last part makes sure that, if this thread finishes before
		# the audiovisual one, the latter does not remain locked.
		self.threadCondition.acquire()
		self.threadCondition.notify()
		self.threadCondition.release()	


	def audioVisualLoop(self):
		""" The audiovisual loop happens here.
		magdalen	---> a GOD.organizer's instance
		doomsday	---> the number of iterations that the simulation
						will undergo
		terra		---> A birdcage cellular automaton's instance
		display		---> A GOD.generator display instance
		size		---> A tuple representing the c.a.'s size
		biblos		---> A list with essential runtime information
		"""
		(width, height)	= self.size
		
		while self.magdalen.annum < self.doomsday:

			self.threadCondition.acquire()
			
			# GOD.Organizer parses the whole length of biblos
			for entry in self.biblos:
				self.magdalen.readBookOfLifeNew(entry)
			# Update the data needed by the background sound engine.
			populNorm = float(self.population) / operator.mul(width,height)
			sndCtrlCells = [self.terra.get((22,18)), self.terra.get((40,18)),
							self.terra.get((64,18))]
			# Update the display
			self.magdalen.refreshDisplay(self.display)
			# Update the audio
			sound.inputDataControl(sndCtrlCells, populNorm)

			self.threadCondition.notify()
			self.threadCondition.wait()
			self.threadCondition.release()
		# This last part makes sure that, if this thread finishes before
		# the simulation one, the latter does not remain locked.
		self.threadCondition.acquire()
		self.threadCondition.notify()
		self.threadCondition.release()	
		sound.stopSoundServer()



def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)
