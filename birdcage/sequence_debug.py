#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus artificial life environment.
# It includes no visual display or sound, but lots of witty comments instead.
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# As of today --- 11th May 2009 --- it includes the following features:
#
#	* all the AL functionality resides in the GOD module; look therein for pearls of wisdom
#	* the sequence's output to terminal is a play-by-play commentary of GOD's actions
#	regarding the agents populating the underlying CA
#	* there's lots of inline remarks in the code itself. They could be useful if you're
#	trying to understand how the code works
#	* the code here uses only the "New" methods of GOD, for more Pythonic flavour
#
# Read some history at EOF


import GOD
from bookentry import BookEntry


import random
import sys
import time

specificity = "Alpha"
specific = __import__("specific"+specificity)

def startExecutionNormal():
	"""start verbose execution cycle with no visual display or sound

	return -->> 1"""

	print "Ready for execution. Warning: DEBUG MODE: no sound or visual effects"

	mary = GOD.Generator("kristos")
	print "Instatiated a Generator called mary"

	# the following lines contain all the data to build a complete cellular automaton
	size = specific.size
	(width, height) = size
	topologyData = specific.topology
	neighborData = specific.neighborhood
	ruleData = specific.rule
	automatonData = specific.automaton
	
	# avatars is the number of initial creatures, and doomsday the number of iterations	
	(avatars, doomsday) = (specific.avatars, specific.doomsday)
	# biblos is a list which whill contain essential runtime information
	biblos = []

	# invoke GOD.Generator's automaton creation method with the data given above
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	print "mary has created terra"

	# now call a GOD.Organizer to oversee this automaton
	magdalen = GOD.Organizer(terra, biblos, specificity)
	magdalen.generator = mary
	(magdalen.width, magdalen.height) = (width, height)
	print "an Organizer called magdalen has been assigned to oversee terra"

	# cycle through avatars to populate the automaton with some initial creatures"
	print "ready to populate terra"
	while avatars:
		# GOD.Generator will compile a module for each creature, and append
		# it to the list biblos along with its name
		mary.generateGenotypeNew(specific.seedCode, biblos)
		print "mary compiled a genome and wrote it in biblos"
		avatars -= 1
	# prime the initial avatars for actual creation
	for entry in biblos:
		entry.fatum["prayer"] = "CreateMe"

	# first sanity check: view the avatars before they are created
	print "the book of life's first page reads:"
	for entry in biblos: print entry
	print "\n"

	# magdalen reads the data in biblos and calls actual agent objects
	# into being from the code in the modules compiled by mary
	for entry in biblos:	
		magdalen.readBookOfLifeNew(entry)
		print "magdalen read biblos and instantiated an agent from the genome"

	print "the book of life's prologue reads:"
	for entry in biblos: print entry
	print "\n"

	print "the initial population phase has finished\n"
	
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		print "the time now is \t", magdalen.annum
		# GOD.Organizer iterates the c.a. and makes sure the world keeps revolving
		if magdalen.annum == 3:
			magdalen.annum += 1
			terra.set((40,10),1)
			print "soil altered"
		else:
			magdalen.iterateAutomaton()
		print "terra has been updated"
		print "magdalen will now read the book of life"
		# GOD.Organizer parses the whole length of biblos
		for entry in biblos:
			magdalen.readBookOfLifeNew(entry)
		print "the book has been read"
		print "the book of life, biblos, reads:"
		for entry in biblos: print entry
		print "\n"

	del sys.argv[1:]
	print "Done"
	return 1


# History
#
# This module came into existence as a rather simple script. My intention was to keep it as
# straight and elegant as possible, so that the flow of execution could be followed clearly,
# with all the messy details tucked away by GOD. Then along came Jergas and Ernesto
# tampering with my pretty code until it was no longer so easy to read - albeit adding
# such nice features as sound effects and creature reproduction. Ultimately it was the
# sheer awkardness of Neanderthaloid debugging (hacking at my own code to kill sound and
# visual, invoking it from the interpreter and then decommenting it back to original form)
# which drove me to write out 3 distinct scripts, intended for different needs. 
# Incidentally, these scripts were completed while riding an Indian Railways express train
# from Ajmer in the scorching desert of Rajasthan, close to the sacred pool of Pushkar, back
# to good, old, smelly and loud Delhi. As the train journey proceeded at an agonisingly 
# slow speed towards the banks of the holy Ganga in Haridwar, I debugged the Debug script
# and finally obtained some insight as to who does what to whom. For all those interested
# in understanding the workings of GOD I suggest running this and following the runtime
# comments.
#
# Soon afterwards I took things a step further and turned the old module, which was called
# main_sequence, into 3 different sequence_audiovisual, sequence_visual and sequence_debug
# scripts. I continued working in sequence_debug and its evil twin sequence_new, streamlining
# the relationship between agents and their GOD and introducing BookEntry instances in the 
# book of life.
#

