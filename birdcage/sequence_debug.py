#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus artificial life environment.
# It includes no visual display or sound, but lots of witty comments instead.
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# As of today --- 21st March 2010 --- it includes the following features:
#
#	* all the AL functionality resides in the GOD module; look therein for pearls of wisdom
#	* the sequence's output to terminal is a play-by-play commentary of GOD's actions
#	regarding the agents populating the underlying CA
#	* there's lots of inline remarks in the code itself. They could be useful if you're
#	trying to understand how the code works
#	* the "Old" methods of GOD have now been deprecated, for lack of Pythonic flavour
#
# Read some history at EOF


import GOD
from bookentry import BookEntry
# BookEntries are modified dictionary objects which store all the information which an agent 
# (creature) object needs to execute (live) as well as metainformation which it will use to
# self-replicate (reproduce) and pass on to its descendants. GOD contains various objects
# which control execution flow by acting on the BookEntries as well as the underlying automaton
# and the various user interfaces (visualization and sound, if enabled).


import random
import sys
import time

specificity = "Delta"
specific = __import__("specific"+specificity)
# This refers to a configuration file which stores information such as automaton size, seed 
# genome, number of iterations, etc. feel free to write your own

def startExecutionBeta():# I wonder what this is for
    """changes specificity to Beta and then calls the Normal submode. 

    return -->>1"""
    global specific
    specificity = "Beta"
    specific = __import__("specific"+specificity)
    
    startExecutionNormal()


def startExecutionNormal():
	"""start verbose execution cycle with no visual display or sound

	return -->> 1"""

	print "Ready for execution. Warning: DEBUG MODE! no sound or visual effects"

	mary = GOD.Generator("kristos")
	print "Instatiated a Generator called mary."
	print "If all goes well she will bear the child Kristos"

	# the following lines read (from the config file) all the data needed to build 
	# a complete cellular automaton
	size = specific.size
	(width, height) = size
	topologyData = specific.topology
	neighborData = specific.neighborhood
	ruleData = specific.rule
	automatonData = specific.automaton
	
	# avatars is the number of initial creatures, and doomsday the number of iterations	
	(avatars, doomsday) = (specific.avatars, specific.doomsday)
	
	# biblos is a list which whill contain runtime information essential for the agents
	# in the form of BookEntries
	biblos = []
	print "A blank book of life exists"

	# invoke GOD.Generator's automaton creation method with the data given above
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	print "mary has created terra"
	# i'm trying to systematise ca initialisation here, this code is temporary
	# and should be in GOD instead
	assert specific.seed[1] == "random"
	for i in range(specific.seed[0]):
		terra.set(terra.returnTopology().random(),1)
	print "seeds have been planted in terra"

	# now call a GOD.Organizer to oversee this automaton
	magdalen = GOD.Organizer(terra, biblos, specificity)
	magdalen.generator = mary
	(magdalen.width, magdalen.height) = (width, height)
	print "an Organizer called magdalen has been assigned to oversee terra"

	# populate the automaton with some initial creatures
	print "ready to populate terra"
	while avatars:
		# GOD.Generator will write and compile a module for each creature, create
		# a BookEntry to contain it and append it to the list biblos
		mary.generateGenotype(specific.seedCode, biblos)
		print "mary compiled a genome and wrote it in biblos"
		avatars -= 1

	# prime the initial avatars for actual creation
	for entry in biblos:
		entry.fatum["prayer"] = "CreateMe"
		# each BookEntry has a dictionary (called its fatum, for in a way it holds 
		# the creature's fate). The key "prayer" is linked to strings which 
		# GOD.Organizer will interpret (via Python introspection) to act in various
		# ways on the BookEntry and its attributes (i.e. the creature). The value
		# "CreateMe" identifies the BookEntry as a candidate for initalization,
		# meaning creating an agent object and placing it on the cellular automaton
		# grid

	# first sanity check: view the avatars' BookEntries before they are created
	print "the book of life's first page reads:"
	for entry in biblos: print entry
	print "\n"

	# magdalen reads the BookEntries in biblos and calls actual agent objects
	# into being from the code in the modules which were compiled by mary
	for entry in biblos:	
		magdalen.readBookOfLife(entry)
		print "magdalen read biblos and instantiated an agent from the genome"

	# second sanity check: view the initial BookEntries following initialization
	print "the book of life's prologue reads:"
	for entry in biblos: print entry
	print "\n"

	print "the initial population phase has finished\n"
	
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		print "the time now is \t", magdalen.annum
		# GOD.Organizer iterates the c.a. and makes sure the world keeps revolving
		magdalen.iterateAutomaton()
		print "terra has been updated"
		
		print "magdalen will now read the book of life"
		# GOD.Organizer parses the whole length of biblos
		for entry in biblos:
			magdalen.readBookOfLife(entry)
		print "the book has been read"
		
		# now display the BookEntries as they currently stand
		print "the book of life, biblos, reads:"
		for entry in biblos: print entry
		print "\n"

	del sys.argv[1:]
	print "Done. Thanks for watching creation unfold ^_^ \n"
	return 1


# History
#
# This module came into existence as a rather simple script. My intention was to keep it as
# straight and elegant as possible, so that the flow of execution could be followed clearly,
# with all the messy details tucked away by GOD. Then along came Jergas and Ernesto
# tampering with my pretty code until it was no longer so easy to read - albeit adding
# nice features such as sound effects and creature reproduction. Ultimately it was the
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

