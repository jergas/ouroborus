#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus
# artificial life environment. It includes visual display.
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# As of today --- 10th March 2009 --- it includes the following
# features:
#
#	* all the AL functionality resides in the GOD module; look therein
#	  for pearls of wisdom
#	* the visual display runs on the curses library, called from GOD
#	  through a module called, simply enough, visual
#
# Read some history at EOF



import curses
import operator
import random
import sys

# These lines need to be imported before GOD and bookentry!!! They stop
# these modules from realizing any sound processing-related activities.
import sound_globals as soundGlobals
soundGlobals.simWSound = 0

from bookentry import BookEntry
import GOD

# This refers to a configuration file which stores information such as
# automaton size, seed genome, number of iterations, etc. Feel free to
# write your own.
specificity = "Alpha"
specific = __import__("specific"+specificity)


def setCursesColors():
	""" Set the curses colours.
	"""
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)


def startExecutionBeta():
    """ Changes specificity to Beta and then calls the Normal submode.

    return	-->> 1
	"""
    global specific
    specificity = "Beta"
    specific = __import__("specific"+specificity)
    
    startExecutionNormal()


def startExecutionDelta():
    """ Changes specificity to Delta and then calls the Normal submode.

    return	-->> 1
	"""
    global specific
    specificity = "Delta"
    specific = __import__("specific"+specificity)
    
    startExecutionNormal()


def startExecutionNormal():
	""" Start normal execution cycle with visual display only.

	return	-->> 1
	"""
	# curses.wrapper is the kosher way to fire up curses visual
	# services; it guarantees that the terminal will not be left
	# stranded in an ocean of insanity if the program terminates
	# exceptionally.
	curses.wrapper(main)

	return 1


def main(stdscr):
	""" Start execution cycle with visual display only.

	stdscr	--->> a standard curses display
	return	-->> 1
	"""
	# Instatiate a Generator called aset.
	aset = GOD.Generator(specific.name, specificity)
	# The following lines read (from the config file) all the data
	#needed to build. a complete cellular automaton
	size = specific.size
	(width, height) = size
	topologyData = specific.topology
	neighborData = specific.neighborhood
	ruleData = specific.rule
	automatonData = specific.automaton
	# avatars is the number of initial creatures, and doomsday the
	# number of iterations.	
	(avatars, doomsday) = (specific.avatars, specific.doomsday)
	# taw is a list which whill contain runtime information essential
	# for the agents in the form of BookEntries.
	taw = []

	# Invoke GOD.Generator's automaton creation method with the data
	# given above.
	kemet = aset.generateAutomaton(size, topologyData, neighborData, ruleData,
									automatonData)
	# Now call a GOD.Organizer to oversee this automaton.
	bast = GOD.Organizer(kemet, taw, specificity)
	bast.generator = aset
	(bast.width, bast.height) = (width, height)

	# The bast organizer will now plant some seeds in kemet.
	bast.initialiseAutomaton(specific.seed)
	# Populate the automaton with some initial creatures.
	while avatars:
		# GOD.Generator will write and compile a module for each
		# creature, create a BookEntry to contain it and append it to
		# the list biblos
		aset.generateGenotype(specific.seedCode, taw)
		avatars -= 1

	# Prime the initial avatars for actual creation.
	for entry in taw:
		entry.fatum["prayer"] = "CreateMe"
		# Each BookEntry has a dictionary called its fatum. The key
		# "prayer" is linked to strings which GOD.Organizer will
		# interpret (via Python introspection) to act in various ways on
		# the BookEntry and its attributes (i.e. the creature). The
		# value "CreateMe" identifies the BookEntry as a candidate for
		# initalization, meaning creating an agent object and placing it
		# on the cellular automaton grid.

	# bast reads the BookEntries in taw and calls actual agent objects
	# into being from the code in the modules which were compiled by
	# aset.
	for entry in taw:	
		bast.readBookOfLife(entry)

	# Set the curses colour pairs.
	setCursesColors()
	# Generate a curses display.
	display = aset.generateDisplay(kemet, size, stdscr)

	# Main iteration cycle.
	while bast.annum < doomsday:
		# GOD.Organizer iterates the c.a.
		bast.iterateAutomaton()

		# GOD.Organizer parses the whole length of taw
		for entry in taw:
			# Read the fatum of the current agent.
			bast.readBookOfLife(entry)

		# The display is updated.
		bast.refreshDisplay(display)
	# Do some cleanup and return.

	del sys.argv[1:]
	print "Done."
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

