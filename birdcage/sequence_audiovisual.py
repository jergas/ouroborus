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

import random
import sys

from bookentry import BookEntry
import GOD


def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)


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
	# start the sound server
	sound.startSoundServer()
	curses.wrapper(main)

	return 1

def main(stdscr):

	mary = GOD.Generator("kristos")

	# setting the curses colour pairs
	setCursesColors()

	# the following lines contain all the data to build a complete automaton
	# size = (width, height) = (int(sys.argv[-4]),int(sys.argv[-3]))
	size = (width, height) = (80,20)
	# del sys.argv[-4:-2]
	topologyData = ("ToroidTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	import operator
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )

	# the seedCode is the genetic code given to the initial creatures
	# look at the module code for meaning of the genome; tamper with this
	# at your own peril!
	seedCode = "Yi Yc Ys Cb Cd Cr Tl Tp Em Tc Tr Tg Tx Ty To Rd Rl"

	# avatars is the number of initial creatures, and doomsday the number of iterations
	(avatars, doomsday) = (1, 570)
	# biblos is a list which whill contain essential runtime information
	biblos = []
	# invoke GOD.Generator's automaton creation method with the data given above
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)

	# now call a GOD.Organizer to oversee this automaton
	magdalen = GOD.Organizer(terra, biblos)
	magdalen.generator = mary
	(magdalen.width, magdalen.height) = (width, height)
	initialAgents = 0
	initialAddresses = []

	# cycle through avatars to populate the automaton with some initial creatures"
	while avatars:
		# GOD.Generator will compile a module for each creature, and append
		# it to the list biblos along with its name
		mary.generateGenotypeNew(seedCode, biblos)
		avatars -= 1
		initialAgents += 1

	# magdalen reads the data in biblos and calls actual agent objects
	# into being from the code in the modules compiled by mary
	for entry in biblos:	
		# set some initial parameters in each entry's fatum
		entry.fatum["code"] = seedCode
		entry.fatum["prana"] = 7
		entry.fatum["mana"] = 1
		(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
		entry.fatum["address"] = (x, y)
		magdalen.readBookOfLifeNew(entry)
		initialAddresses.append((x, y))
	
	display = mary.generateDisplay(terra, size, stdscr)

	# start the background sound and its control thread
	sound.setInitialData(magdalen.width)
	sound.startBackground()
	sound.startBackgroundControl()
	# birth sound of the initial agents
	for x in initialAddresses:
		sound.agentBirth(x[0])

	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		# GOD.Organizer iterates the c.a. and makes sure the world keeps revolving. Also, populationNorm is calculated in order to determine (sound) spectral density.
		population = magdalen.iterateAutomaton()
		populNorm = float(population) / operator.mul(width,height)
		# GOD.Organizer parses the whole length of biblos
		for entry in biblos:
			birth = 0
			agentAddress = entry.fatum["address"]
			if entry.fatum["prayer"] == "BeBirthed":
				birth = 1
			magdalen.readBookOfLifeNew(entry)
			if birth == 1:
				sound.agentBirth(agentAddress[0])
		# The display and the sound control data are updated.
		magdalen.refreshDisplay(display)
		sndCtrlCells = [terra.get((22,18)), terra.get((40,18)),
						terra.get((64,18))]
		sound.inputDataControl(sndCtrlCells, populNorm)

	sound.stopSoundServer()
	del sys.argv[1:]
	print "Done"
	return 1



# History
#
# Rabindranath Tagore is the local deity at Bolpur district in Bengal. His University
# of Shantiniketan looks very much like an Aldous Huxley utopia and everyone in the
# town is extremely polite, very sensitive and slightly deranged. I believe it's 
# something in the water. It was at this place, on 9th March 2009, that I finally 
# decided to turn the audiovisual execution orchestration into its own module, so
# that good old Ernesto could play around with it to his heart's desire without
# affecting the global structure of the Great Work itself.

