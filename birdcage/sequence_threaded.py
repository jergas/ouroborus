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
#	* Creatures haven't made it into the display yet
#	* The automaton should only be iterated in the simulation.
#	* Lock implementation (to keep data thread-safe) are missing
#	* A sweet spot between the simulation's speed and the audiovisual's
#		lack of it has yet to be found
#	* The terminal is not cleaned after the execution ends
#
# It includes the following features:
#
#	* All the AL functionality resides in the GOD module; look therein
#		for pearls of wisdom
#	* The sequence's visualization (still under construction)
#	* If your'e trying to understand how the code works, refere to
#		sequence_new.py


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
	curses.wrapper(main)
	return 1


def main(stdscr):
	"""Runs the simulation initialization methods, converts the
	simulation and audiovisual methods into threads and starts these
	threads.
	stdscr	---> a curses standard screen object
	"""
	(magdalen, doomsday, terra, display, size) = initSimulation(stdscr)

	simulation = threading.Thread(name='Simulation', target=simulationLoop,
								args=(magdalen, doomsday))
	audiovisual = threading.Thread(name='Audiovisual', target=audioVisualLoop,
								args=(magdalen, doomsday, terra, display,
										size))

	simulation.start()
	audiovisual.start()


def initSimulation(stdscr):
	"""Instantiates GOD's automaton-generator and automaton-
	organizer classes. Populates the automaton with some
	initial creatures (broken). Generates a display, and
	starts sound.
	stdscr	---> a curses standard screen object
	return	--> a tuple containing: instances of GOD.organizer,
				doomsday (number of iterations the simulation will
				last), a c.a., a display, and ths c.a.'s size
	"""
	# Instantiate a generator.
	mary = GOD.Generator("kristos")
	# The following lines contain all the data to build a complete
	# cellular automaton.
	size = (width, height) = (80,20)
	topologyData = ("GridTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )
	seedCode = "Y i Y c Y s C b C d C r T l T p T e T c T r T g T o R d R l"
	(avatars, doomsday) = (1, 15000)
	biblos = []
	# Invoke GOD.Generator's automaton creation method with the data
	# given above.
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData,
									automatonData)
	# Call a GOD.Organizer to oversee this automaton.
	magdalen = GOD.Organizer(terra, biblos)
	magdalen.generator = mary
	(magdalen.width, magdalen.height) = (width, height)
	# Cycle through avatars to populate the automaton with some initial
	# creatures.
	while avatars:
		# Compile a module for each creature, and append it to the list
		# biblos along with its name.
		mary.generateGenotypeNew(seedCode.split(" "), biblos)
		avatars -= 1
	# magdalen reads the data in biblos and calls actual agent objects.
	for entry in biblos:
		# set some initial parameters in each entry's fatum
		entry.fatum["code"] = seedCode
		entry.fatum["prana"] = 7
		entry.fatum["mana"] = 1
		(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
		entry.fatum["address"] = (x, y)
		magdalen.readBookOfLifeNew(entry)
	# Generate a display, and start the sound server and threads.
	setCursesColors()
	display = mary.generateDisplay(terra, size, stdscr)
	sound.startSoundServer()
	sound.startBackground()
	sound.startBackgroundControl()
	return (magdalen, doomsday, terra, display, size)


def simulationLoop(magdalen, doomsday):
	"""The simulation's main iteration cycle happens here.
	magdalen	---> a GOD.organizer's instance
	doomsday	---> the number of iterations that the simulation
					will undergo
	return		--> 1
	"""	
	# Main iteration cycle
	while magdalen.annum < doomsday:
		# GOD.Organizer iterates the c.a.
		magdalen.iterateAutomaton()


def audioVisualLoop(magdalen, doomsday, terra, display, size):
	""" The audiovisual loop happens here.
	magdalen	---> a GOD.organizer's instance
	doomsday	---> the number of iterations that the simulation
					will undergo
	terra		---> A birdcage cellular automaton's instance
	display		---> A GOD.generator display instance
	size		---> A tuple representing the c.a.'s size
	"""
	(width, height)	= size
	
	### First get background going, then deal with this.
	#for i in range(avatars):
	#	mary.generateGenotype(seedCode.split(" "), biblos) # NO MARY!!!
	#	sound.agentBirth()
	###
	while magdalen.annum < doomsday:
		# Update sound-control data
		population = magdalen.iterateAutomaton() ##!!! extra c.a. iter.
		populNorm = float(population) / operator.mul(width,height)
		sndCtrlCells = [terra.get((22,18)), terra.get((40,18)),
						terra.get((64,18))]
		sound.inputDataControl(sndCtrlCells, populNorm)
		# Update the display
		magdalen.refreshDisplay(display)
	sound.stopSoundServer()
	del sys.argv[1:]
	print "Done"



def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)
