#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus artificial life environment.
# It includes a visual display but no sound.
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# As of today --- 10th March 2009 --- it includes the following features:
#
#	* all the AL functionality resides in the GOD module; look therein for pearls of wisdom
#	* the visual display runs on the curses library, called from GOD through a module
#	called, simply enough, visual
#	* the logic of the script differs a lot from the latest AL development, present in
#	sequence_debug...this in not really a feature, it's a warning!
#
# Read some history at EOF


import GOD
from bookentry import BookEntry
import random
import sys
import time

def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)

def startExecutionNormal():
	"""start normal execution cycle with visual display (no sound)

	return -->> 1

	Visual display through curses terminal control module"""

	print "Ready for visual execution only...commence primary ignition!"
	import curses
	global curses
	#curses.wrapper is the kosher way to fire up curses visual services; it
	#guarantees that the terminal will not be left stranded in an ocean of
	#insanity if the program terminates exceptionally
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
	topologyData = ("GridTopology", 0)
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

	# cycle through avatars to populate the automaton with some initial creatures"
	while avatars:
		# GOD.Generator will compile a module for each creature, and append
		# it to the list biblos along with its name
		mary.generateGenotypeNew(seedCode, biblos)
		avatars -= 1

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

	display = mary.generateDisplay(terra, size, stdscr)

	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		# GOD.Organizer iterates the c.a. and makes sure the world keeps revolving
		magdalen.iterateAutomaton()
		# GOD.Organizer parses the whole length of biblos
		for entry in biblos:
			magdalen.readBookOfLifeNew(entry)

		magdalen.refreshDisplay(display)


	del sys.argv[1:]
	print "Done"
	return 1


# History
#
# When the pieces of Sati's body fell to the earth after she was dismembered by Vishnu's
# battle disc, the 51 Shaktipiths came into being. Where her brow point landed hoary 
# Tarapith was raised. Kalighat, of unparalleled renown, marks the site where her little
# toe touched ground. Most revered Kamakhya crowns the spot where her very sex hit land.
# By contrast, Kankalitala, where Sati's waist fell, is a very simple little shrine where 
# families sit on the Goddess' porch without making much fuss. Similarly this script
# came into being in 9th March 2009 as a humble halfway-point between the intrincacies
# of the thread-enabled audiovisual sequence and the elegantly streamlined debug
# sequence. 




