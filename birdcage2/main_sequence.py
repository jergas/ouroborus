#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus artificial life environment
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# As of today --- 23 February 2009 --- it includes the following features:
#
#	* all the AL functionality resides in the GOD module; look therein for pearls of wisdom
#	* there are 3 callable functions in this module: 
#		startExecutionAudioVisual - runs with curses and csound
#		startExecutionVisual - runs with curses and no sound
#		startExecutionDebug - no visual output, plenty of witty comments, though!
#	* these functions are called from start.py, although you may invoke them from the
#	interpreter or elsewhere, if you should choose to do so
#	* or you may build your own function to suit your particular needs of execution, once
#	again you may need to take a closer look at GOD (have GOD's darshan!) in order to do this.
#	* there are lots of inline comments below, they may also prove useful
#
# History
#
# This module came into existence as a rather simple script. My intention was to keep it as
# straight and elegant as possible, so that the flow of execution could be followed clearly,
# with all the messy details tucked away by GOD. Then along came Jergas and Ernesto
# tampering with my pretty code until it was no longer so easy to read - albeit adding
# such nice features as sound effects and creature reproduction. Ultimately it was the
# sheer awkardness of Neanderthaloid debugging (hacking at my own code to kill sound and
# visual, invoking it from the interpreter and then decommenting it back to original form)
# which drove me to writing out 3 distinct scripts, intended for different needs. 
# Incidentally, these scripts were completed while riding an Indian Railways express train
# from Ajmer in the scorching desert of Rajasthan, close to the sacred pool of Pushkar, back
# to good, old, smelly and loud Delhi. As the train journey proceeded at an agonisingly 
# slow speed towards the banks of the holy Ganga in Haridwar, I debugged the Debug script
# and finally obtained some insight as to who does what to whom. For all those interested
# in understanding the workings of GOD I suggest running this and following the runtime
# comments.

import GOD
import random
import sys
import time

def startExecutionAudiovisual():
	"""start normal execution cycle with sound and visual display

	return -->> 1

	Visual display through curses terminal control module
	Sound effectus through csound courtesy of Ernesto Illescas"""

	print "Ready for full audiovisual execution...commence primary ignition!"

	import curses, sound
	global curses, sound
	#curses.wrapper is the kosher way to fire up curses visual services; it
	#guarantees that the terminal will not be left stranded in an ocean of
	#insanity if the program terminates exceptionally
	curses.wrapper(mainAudiovisual)

	return 1

def mainAudiovisual(stdscr):

	mary = GOD.Generator("kristos")
	sound.startSoundServer()

	# setting the curses colour pairs
	setCursesColors()

	# the following lines contain all the data to build a complete automaton
	# size = (width, height) = (int(sys.argv[-4]),int(sys.argv[-3]))
	size = (width, height) = (80,20)
	# del sys.argv[-4:-2]
	topologyData = ("GridTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	import operator
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )
	seedCode = "Y i Y c Y s C b C d C r T l T e T r R d R p R c R l"

	# invoke God.Generator's automaton creation method with the data given above
	# (avatars, doomsday)= sys.argv[-2:]
	(avatars, doomsday) = (1, 1500)
	# del sys.argv[-2:]
	avatars = int(avatars)
	doomsday = int(doomsday)
	biblos = []
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	magdalen = GOD.Organizer(terra, biblos)


	for i in range(avatars):
		mary.generateGenotype(seedCode.split(" "), biblos)
		#print "generated agent", i # debugging
		sound.playSingleNote()
		#print "biblos is", biblos # debugging
		(x, y) = (30, 8)		
		#(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
		magdalen.readBookOfLife(i, seedCode, 7, 1, (x, y), mary)
		#print "biblos is", biblos # debugging

	
	display = mary.generateDisplay(terra, size, stdscr)
	sound.startBackground()
	sound.startBackgroundControl()
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		#print "time is", magdalen.annum
		#print "biblos is", biblos
		population = magdalen.iterateAutomaton()
		populationNorm = float(population) / operator.mul(width,height)
		for i in range(len(biblos)): 
			magdalen.readBookOfLife(i, "a", 0, 0, (50,8), mary)
			if magdalen.annum == 750:
				biblos[0][3].gainPrana(5)
		#magdalen.iterateAgents()
		magdalen.refreshDisplay(display)
		soundControlCells = [terra.get((22,18)), terra.get((40,19)), terra.get((64,17))]
		sound.inputDataControl(soundControlCells, populationNorm, magdalen.annum)
		time.sleep(0.0001)

	sound.stopSoundServer()
	del sys.argv[1:]
	return biblos

def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)

def startExecutionVisual():
	"""start normal execution cycle with visual display (no sound)

	return -->> 1

	Visual display through curses terminal control module"""

	print "Ready for visual execution only...commence primary ignition!"

	import curses
	global curses
	#curses.wrapper is the kosher way to fire up curses visual services; it
	#guarantees that the terminal will not be left stranded in an ocean of
	#insanity if the program terminates exceptionally
	curses.wrapper(mainVisual)

	return 1


def mainVisual(stdscr):

	mary = GOD.Generator("kristos")


	# setting the curses colour pairs
	setCursesColors()

	# the following lines contain all the data to build a complete automaton
	# size = (width, height) = (int(sys.argv[-4]),int(sys.argv[-3]))
	size = (width, height) = (80,20)
	# del sys.argv[-4:-2]
	topologyData = ("GridTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	import operator
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )
	seedCode = "Y i Y c Y s C b C d C r T l T e T r R d R p R c R l"

	# invoke God.Generator's automaton creation method with the data given above
	# (avatars, doomsday)= sys.argv[-2:]
	(avatars, doomsday) = (1, 1500)
	# del sys.argv[-2:]
	avatars = int(avatars)
	doomsday = int(doomsday)
	biblos = []
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	magdalen = GOD.Organizer(terra, biblos)


	for i in range(avatars):
		mary.generateGenotype(seedCode.split(" "), biblos)
		#print "generated agent", i # debugging

		#print "biblos is", biblos # debugging
		(x, y) = (30, 8)		
		#(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
		magdalen.readBookOfLife(i, seedCode, 7, 1, (x, y), mary)
		#print "biblos is", biblos # debugging

	
	display = mary.generateDisplay(terra, size, stdscr)

	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		#print "time is", magdalen.annum
		#print "biblos is", biblos
		magdalen.iterateAutomaton()
		for i in range(len(biblos)): 
			magdalen.readBookOfLife(i, "a", 0, 0, (50,8), mary)
			if magdalen.annum == 750:
				biblos[0][3].gainPrana(5)
		#magdalen.iterateAgents()
		magdalen.refreshDisplay(display)


	del sys.argv[1:]
	return biblos




def startExecutionDebug():
	"""start verbose execution cycle with no visual display or sound

	return -->> 1"""

	print "Ready for execution. Warning: DEBUG MODE: no sound our visual effects"

	mary = GOD.Generator("kristos")
	print "Instatiated a Generator called mary"

	# the following lines contain all the data to build a complete cellular automaton
	size = (width, height) = (80,20)
	topologyData = ("GridTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	import operator
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )
	
	# the seedCode is the genetic code given to the initial creatures
	# look at the module code for meaning of the genome; tamper with this
	# at your own peril!
	seedCode = "Y i Y c Y s C b C d C r T l T e T r R d R p R c R l"

	# avatars is the number of initial creatures, and doomsday the number of iterations	
	(avatars, doomsday) = (2, 7)
	# biblos is a list which whill contain essential runtime information
	biblos = []

	# invoke GOD.Generator's automaton creation method with the data given above
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	print "mary has created terra"

	# now call a GOD.Organizer to oversee this automaton
	magdalen = GOD.Organizer(terra, biblos)
	print "an Organizer called magdalen has been assigned to oversee terra"

	# cycle through avatars to populate the automaton with some initial creatures"
	print "ready to populate terra"
	for i in range(avatars):
		# GOD.Generator will compile a module for each creature, and append
		# it to the list biblos along with its name
		mary.generateGenotype(seedCode.split(" "), biblos)
		print "mary compiled a genome and wrote it in biblos"
		print "the book of life, biblos, reads:\t", biblos
		print "\n"

		# GOD.Organizer reads the data in biblos and calls actual agent objects
		# into being from the code in the modules compiled by mary
		(x, y) = (random.randint(0, width-1), random.randint(0, height-1))	
		magdalen.readBookOfLife(i, seedCode, random.randint(1,7), 1, (x, y), mary)
		print "magdalen read biblos and instantiated an agent from the genome"
		print "the book of life, biblos, reads:\t", biblos
	print "the initial population phase has finished\n"

	
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		print "the time now is \t", magdalen.annum
		print "the book of life, biblos, reads:\t", biblos
		# GOD.Organizer iterates the c.a. and makes sure the world keeps revolving
		magdalen.iterateAutomaton()
		print "terra has been updated"
		print "magdalen will now read the book of life"
		# GOD.Organizer parses the whole length of biblos
		for i in range(len(biblos)): 
			magdalen.readBookOfLife(i, "a", 0, 0, (50,8), mary)
		print "the book has been read"

		# this is an arbitrary intervention to artificially augment a creature's prana
		if magdalen.annum == 3:
			biblos[0][3].gainPrana(12)
			print "a creature's prana has been increased by divine gift"
		
		print "\n"

	del sys.argv[1:]
	print "Done"
	return 1



