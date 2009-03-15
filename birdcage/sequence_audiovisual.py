#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus artificial life environment.
# It includes both a visual display and dynamic sound effects
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# As of today --- 10th March 2009 --- it includes the following features:
#
#	* all the AL functionality resides in the GOD module; look therein for pearls of wisdom
#	* the visual display runs on the curses library, called from GOD through a module
#	called, simply enough, visual
#	* there's lots of fancy stuff done with sound - this is called directly from this
#	module, using all the csound enchantments elsewhere in the package.
#	* the logic of the script differs a lot from the latest AL development, present in
#	sequence_debug...this in not really a feature, it's a warning!
#
# Read some history at EOF


import GOD
import random
import sys

def startExecutionNormal():
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
	curses.wrapper(main)

	return 1

def main(stdscr):

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
	(avatars, doomsday) = (1, 15000)
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

	sound.stopSoundServer()
	del sys.argv[1:]
	return biblos

def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)



# History
#
# Rabindranath Tagore is the local deity at Bolpur district in Bengal. His University
# of Shantiniketan looks very much like an Aldous Huxley utopia and everyone in the
# town is extremely polite, very sensitive and slightly deranged. I believe it's 
# something in the water. It was at this place, on 9th March 2009, that I finally 
# decided to turn the audiovisual execution orchestration into its own module, so
# that good old Ernesto could play around with it to his heart's desire without
# affecting the global structure of the Great Work itself.

