# This script orchestrates execution for an ouroborus artificial life
# environment. The module is based on sequence_audiovisual.py, with the
# novelty that it implements threads.
#
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# It includes the following features:
#
#	* Execution of the simulation proper, background audiovisuals and
#	  the agents audiovisuals occur in separate threads
#	* All the AL functionality resides in the GOD module; look therein
#		for pearls of wisdom
#	* If you're trying to understand how the code works, refer to
#		sequence_debug.py and sequence_auidovisual.py


# Python's native libraries
import curses
import operator
import os
import random
import sys
import threading
import time

# These lines need to be read before GOD and bookentry!!!
import sound_globals as soundGlobals
soundGlobals.simWSound = 1

# Ouroborus libraries
import GOD
from bookentry import BookEntry
import sound


# This refers to a configuration file which stores information such as
# automaton self.size, seed genome, number of iterations, etc. Feel free to
# write your own.
specificity = sys.modules["__main__"].specificity
specific = __import__("specific"+specificity)

# If logging is enabled, then open a log file.
if specific.logging:
	logging = open(specific.logFile, 'w')


def startExecutionNormal():
	""" Start normal execution cycle with sound and visual display.

	return	-->> 1
	"""
	# Start the sound server.
	sound.startSoundServer()
	# curses.wrapper is the kosher way to fire up curses visual
	# services; it guarantees that the terminal will not be left
	# stranded in an ocean of insanity if the program terminates
	# exceptionally. If Pygame or debug are used, the curses.wrapper
	# hides the output, so it is not used.
	if specific.displayType == 'pygame' or specific.displayType == 'debug':
		main(None)
	elif specific.displayType == 'curses':
		curses.wrapper(main)
	return 1


def main(stdscr):
	"""Runs the simulation initialization methods, converts the
	simulation and audiovisual methods into threads and starts these
	threads.
	stdscr	---> a curses standard screen object
	return	-->> 1
	"""
	# Instantiate the class ThreadedSequence, which contains the
	# needed attributes and methods for the execution.
	Sequence = ThreadedSequence(stdscr)

	# Instantiate three threads with target methods: the simulation
	# loop, the backgroud audiovisual loop and the agent's loop.
	simulation	= threading.Thread(name='Simulation',
									target=Sequence.simulationLoop)
	background	= threading.Thread(name='Background',
									target=Sequence.backgroundLoop)
	agents		= threading.Thread(name='Agents',
									target=Sequence.agentsLoop)

	# Create the background-sound threads.
	voices = sound.backgroundVoices()
	voicesControl = sound.backgroundControl()

	# Make all non-simulation threads daemonic, so that they won't
	#prevent the simulation from exciting. Also start them.
	for x in voices:
		x.setDaemon(True)
		x.start()
	voicesControl.setDaemon(True)
	background.setDaemon(True)
	agents.setDaemon(True)
	voicesControl.start()
	simulation.start()
	background.start()
	agents.start()

	# Wait until the simulation thread has finished.
	try:
		simulation.join()
	except KeyboardInterrupt:
		sound.stopSoundServer()
	finally:
		if specific.debugOutputToFile == True and specific.displayType == 'debug':
			os.system("nano " + specific.debugFileName)

	# Do some cleaunup.
	sound.stopSoundServer()
	del sys.argv[1:]
	print "Done"
	return 1


class ThreadedSequence(object):
	""" The initialization method sets up the attributes needed for the
	(threaded) execution of the rest of the class' methods. Shared
	variables are implemented as class attributes, and their data is
	kept thread-safe and synchronized via the threading.Lock() and
	threading.Condition() methods.
	"""
	def __init__(self, stdscr):
		"""Instantiates GOD's automaton-generator and automaton-
		organizer classes. Populates the automaton with some
		initial creatures. Generates a display.

		stdscr	---> a curses standard screen object
		"""
		# Instantiate a generator.
		aset = GOD.Generator(specific.name, specificity)
		# The following lines contain all the data to build a complete
		# cellular automaton.
		self.size = specific.size
		(width, height) = self.size
		topologyData = specific.topology
		neighborData = specific.neighborhood
		ruleData = specific.rule
		automatonData = specific.automaton
		# avatars is the number of initial creatures, and doomsday the
		# number of iterations.	
		(avatars, self.doomsday) = (specific.avatars, specific.doomsday)
		# self.taw is a dictionary which whill contain runtime
		# information essential for the agents in the form of
		# BookEntries.
		self.taw = {}

		# Invoke GOD.Generator's automaton creation method with the data
		# given above.
		self.kemet = aset.generateAutomaton(self.size, topologyData,
											neighborData, ruleData,
											automatonData)
		# Now call a GOD.Organizer to oversee this automaton.
		self.bast = GOD.Organizer(self.kemet, self.taw, specificity)
		self.bast.generator = aset
		(self.bast.width, self.bast.height) = (width, height)


		# The bast organizer will now plant some seeds in kemet.
		self.bast.initialiseAutomaton(specific.seed)
		# Populate the automaton with some initial creatures.
		while avatars:
			# GOD.Generator will write and compile a module for each
			# creature, create a BookEntry to contain it and append it
			# to the list taw
			aset.generateGenotype(specific.seedCode, self.taw)
			avatars -= 1

		# Prime the initial avatars for actual creation.
		for key in self.taw.keys():
			self.taw[key].fatum["prayer"] = "CreateMe"
			# Each BookEntry has a dictionary called its fatum. The key
			# "prayer" is linked to strings which GOD.Organizer will
			# interpret (via Python introspection) to act in various
			# ways on  the BookEntry and its attributes (i.e. the
			# creature). The value "CreateMe" identifies the BookEntry
			# as a candidate for initalization, meaning creating an
			# agent object and placing it on the cellular automaton
			# grid.

		# bast reads the BookEntries in taw and calls actual agent
		# objects into being from the code in the modules which were
		# compiled by aset.
		for key in self.taw.keys():
			self.bast.readBookOfLife(self.taw[key])

		# Decide whether to use a Curses or Pygame display
		if stdscr:
			# Generate a curses display.
			self.display = aset.generateDisplay(self.kemet, self.size, stdscr)
		else:
			self.display = aset.generateDisplay(self.kemet, self.size, self.taw)

		# Set some initial data for sound control.
		sound.setInitialData(self.size)

		# Initialize variables for agent-related inter-thread
		# communication.
		self.currentEntry = None
		self.birth	= 0
		self.death	= 0

		# Number of simulation loops per audiovisual loop.
		self.simulationToAudiovisual = specific.simulationToAudiovisual
		# Create a thread-condition object to keep the simulation and
		# audiovisual threads synchronized.
		self.bckgrndThreadCondition	= threading.Condition()
		self.agentThreadCondition	= threading.Condition()
		# Control variable to stop secondary threads.
		self.simulationOn	= True


	def simulationLoop(self):
		"""The simulation's main iteration cycle happens here.
		"""
		# Main iteration cycle
		while self.bast.annum < self.doomsday:
			self.bckgrndThreadCondition.acquire()
			# GOD.Organizer iterates the c.a.
			self.bast.iterateAutomaton()
			# Only do an audiovisual loop every simulationToAudiovisual
			# iterations.
			if not self.bast.annum % self.simulationToAudiovisual:
				self.bckgrndThreadCondition.notify()
			# GOD.Organizer parses the whole length of taw
			for key in self.taw.keys():
				self.agentThreadCondition.acquire()
				self.birth	= 0
				self.death	= 0
				self.currentEntry = self.taw[key]
				# If the agent is about to be born or to die, then record
				# it.
				if self.currentEntry.fatum["prayer"] == "BeBirthed":
					self.birth = 1
				if self.currentEntry.fatum["prayer"] == "KillMe":
					self.death = 1
				self.bast.readBookOfLife(self.currentEntry)
				# Only do an audiovisual loop every simulationToAudiovisual
				# iterations.
				if not self.bast.annum % self.simulationToAudiovisual:
					self.agentThreadCondition.notify()
					self.agentThreadCondition.wait()
				self.agentThreadCondition.release()
			# Only do an audiovisual loop every simulationToAudiovisual
			# iterations.
			if not self.bast.annum % self.simulationToAudiovisual:
				self.bckgrndThreadCondition.wait()
			self.bckgrndThreadCondition.release()
			# Test if the Csound performance-thread is still running, and
			# break the simulation loop if not (solves the interruption
			# bug).
			if sound.SoundServer.perf.GetStatus():
				break
		self.simulationOn = False
		sound.stopSoundServer()

	def backgroundLoop(self):
		""" Refreshing of the curses background happens here
		(the agents are also re-drawn so that they don't disappear).
		"""
		(width, height)	= self.size

		while self.simulationOn:
			self.bckgrndThreadCondition.acquire()
			self.bckgrndThreadCondition.notify()
			self.bckgrndThreadCondition.wait()
			# Update the display
			self.bast.refreshDisplay(self.display)
			# Update the audio
			sound.inputDataControl(self.kemet)
			self.bckgrndThreadCondition.release()


	def agentsLoop(self):
		""" Deals with drawing of agents and with their sound.
		"""
		# Make sure that simulationLoop() runs before this thread.
		while self.bast.annum < 1:
			time.sleep(.01)
		while self.simulationOn:
			self.agentThreadCondition.acquire()
			self.agentThreadCondition.notify()
			# If the current agent died, make the appropriate sound.
			if self.death:
				sound.agentDeath(self.currentEntry.fatum["voice"])
				time.sleep(random.uniform(0.2, 0.4))
			# Else refresh the agent's display and (possibly) make the
			# appropriate sound.
			else:
				# Update the agent in the display.
				self.bast.refreshAgent(self.currentEntry, self.display)
				# If the agent is born or eats, then make the appropriate
				# sound.
				if self.birth == 1:
					sound.agentBirth(self.currentEntry.fatum["voice"])
					time.sleep(random.uniform(0.2, 0.4))
				elif self.currentEntry.fatum["voice"].ate == 1:
					sound.eatSound(self.currentEntry.fatum["voice"])
					self.currentEntry.fatum["voice"].ate = 0
					time.sleep(random.uniform(0.1, 0.2))
			self.agentThreadCondition.wait()
			self.agentThreadCondition.release()
