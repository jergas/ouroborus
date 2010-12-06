""" Greetings! This script orchestrates execution for an ouroborus artificial life environment. It includes no visual display or sound, but lots of witty comments instead.

Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas

As of today --- 21st March 2010 --- it includes the following features:

	* all the AL functionality resides in the GOD module; look therein for pearls of wisdom
	* the sequence's output to terminal is a play-by-play commentary of GOD's actions
	regarding the agents populating the underlying CA
	* there's lots of inline remarks in the code itself. They could be useful if you're
	trying to understand how the code works
	* the "Old" methods of GOD have now been deprecated, for lack of Pythonic flavour

Read some history at EOF"""

# These lines need to be imported before GOD and bookentry!!! They stop
# these modules from realizing any sound processing-related activities.
import sound_globals as soundGlobals
soundGlobals.simWSound = 0

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

specificity = sys.modules["__main__"].specificity
specific = __import__("specific"+specificity)
#specificity = "Delta"
#specific = __import__("specific"+specificity)

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
	print "Specificity is " + specificity

	aset = GOD.Generator(specific.name, specificity)
	print "Instatiated a Generator called aset."
	print "If all goes well she will bear the child " + specific.name

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
	
	# taw is a dictionary which whill contain runtime information
	# essential for the agents in the form of BookEntries
	taw = {}
	print "A blank book of life exists"

	# invoke GOD.Generator's automaton creation method with the data given above
	kemet = aset.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	print " aset has created kemet"

	# now call a GOD.Organizer to oversee this automaton
	bast = GOD.Organizer(kemet, taw, specificity)
	bast.generator = aset
	(bast.width, bast.height) = (width, height)
	print "an Organizer called  has been assigned to oversee kemet"

	print "bast will now plant some seeds in kemet"
	bast.initialiseAutomaton(specific.seed)
	print "seeds have been planted in kemet"

	# populate the automaton with some initial creatures
	print "ready to populate kemet"
	while avatars:
		# GOD.Generator will write and compile a module for each creature, create
		# a BookEntry to contain it and append it to the list biblos
		aset.generateGenotype(specific.seedCode, taw)
		avatars -= 1
	else:
		print "all original genomes have been compiled"

	# prime the initial avatars for actual creation
	for key in taw.keys():
		taw[key].fatum["prayer"] = "CreateMe"
		# each BookEntry has a dictionary (called its fatum, for in a way it holds 
		# the creature's fate). The key "prayer" is linked to strings which 
		# GOD.Organizer will interpret (via Python introspection) to act in various
		# ways on the BookEntry and its attributes (i.e. the creature). The value
		# "CreateMe" identifies the BookEntry as a candidate for initalization,
		# meaning creating an agent object and placing it on the cellular automaton
		# grid

	# first sanity check: view the avatars' BookEntries before they are created
	print "the book of life's first page reads:"
	for key in taw.keys(): print taw[key]
	print "\n"

	# bast reads the BookEntries in taw and calls actual agent objects
	# into being from the code in the modules which were compiled by aset
	for key in taw.keys():	
		bast.readBookOfLife(taw[key])
		print "bast read taw and instantiated an agent from the genome"

	# second sanity check: view the initial BookEntries following initialization
	print "the book of life's prologue reads:"
	for key in taw.keys(): print taw[key]
	print "\n"

	print "the initial population phase has finished\n"
	
	# here cometh the main iteration cycle
	while bast.annum < doomsday:
		print "the time now is \t", bast.annum
		# GOD.Organizer iterates the c.a. and makes sure the world keeps revolving
		bast.iterateAutomaton()
		print "kemet has been updated"
		
		print "bast will now read the book of life"
		# GOD.Organizer parses the whole length of taw
		for key in taw.keys():
			bast.readBookOfLife(taw[key])
		print "the book has been read"
		
		# now display the BookEntries as they currently stand
		print "the book of life, taw, reads:"
		for key in taw.keys(): print taw[key]
		print "\n"
		print "there are "+str(kemet.tellPopulation())+" creatures on kemet"
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
