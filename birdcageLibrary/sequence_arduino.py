#!/usr/bin/python

# Greetings! This script orchestrates execution for an ouroborus
# artificial life environment.
# The module is based in sequence_threaded.py, and sequence_new.py,
# with the novelty that it implements threads and input from an arduino chip.
#
# Coded by Jergas Apwith, Diego Trujillo and Ernesto Illescas


# Python's native libraries
import curses
import operator
import random
import sys
import threading
import time

# These lines need to be read before GOD and bookentry!!!
import sound_globals as soundGlobals
soundGlobals.simWSound = 1

# Ouroborus libraries
import GOD
import sound

# This refers to a configuration file which stores information such as
# automaton self.size, number of iterations, etc. Feel free to write
# your own.
specificity = "Environment"
specific = __import__("specific"+specificity)

def setCursesColors():
	""" Set the curses colours.
	"""
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)



# A specificBeta.py file must be written if this function is to be used.
def startExecutionBeta():
    """Changes specificity to Beta and then calls the Normal submode
	
    return -->>1
    """
    global specific
    specificity = "Beta"
    specific = __import__("specific"+specificity)
    
    startExecutionNormal()


def startExecutionNormal():
	""" Start normal execution cycle with sound and visual display.

	return	-->> 1
	"""
	# Start the sound server.
	sound.startSoundServer(specificity)
	# curses.wrapper is the kosher way to fire up curses visual
	# services; it guarantees that the terminal will not be left
	# stranded in an ocean of insanity if the program terminates
	# exceptionally.
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
	
	# Instantiate two threads with target methods simulationLoop() and
	#audiovisualLoop().
	simulation	= threading.Thread(name='Simulation',
									target=Sequence.simulationLoop)
	background	= threading.Thread(name='Background',
									target=Sequence.backgroundLoop)
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
	voicesControl.start()
	simulation.start()
	background.start()
	
	# Wait until the simulation thread has finished.
	try:
		simulation.join()
	except KeyboardInterrupt:
		Sequence.interrupt = True
		sound.stopSoundServer()
		
	# Do some clean-up
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
		organizer classes. Generates a display.
		stdscr	---> a curses standard screen object
		"""
		# Instantiate a generator.
		aset = GOD.Generator(specific.name)
		# The following lines contain all the data to build a complete
		# cellular automaton.
		self.size = specific.size
		(width, height) = self.size
		topologyData = specific.topology
		neighborData = specific.neighborhood
		ruleData = specific.rule
		automatonData = specific.automaton
		# Doomsday is the number of iterations.
		self.doomsday = specific.doomsday
		 # taw is not used in this sequence, but is required by the
		 # syntax of GOD.Organizer()
		self.taw = []
		
		# Invoke GOD.Generator's automaton creation method with the data
		# given above.
		self.kemet = aset.generateAutomaton(self.size, topologyData,
											neighborData, ruleData, 
											automatonData)
		# Call a GOD.Organizer to oversee this automaton.
		self.bast = GOD.Organizer(self.kemet, self.taw, specificity)
		self.bast.generator = aset
		(self.bast.width, self.bast.height) = (width, height)
		
		# The bast organizer will now plant some seeds in kemet.
		self.bast.initialiseAutomaton(specific.seed)
		
		# Set the curses colour pairs.
		setCursesColors()
		# Generate a curses display.
		self.display = aset.generateDisplay(self.kemet, self.size, stdscr)
		# Set some initial data for sound control.
		sound.setInitialData(self.bast.width)

		# Create a thread-condition object to keep the simulation and
		# audiovisual threads synchronized.
		self.bckgrndThreadCondition	= threading.Condition()
		self.simulationOn	= True
		self.interrupt		= False

	def simulationLoop(self):
		"""The simulation's main iteration cycle happens here.
		"""	
		# Main iteration cycle
		while self.bast.annum < self.doomsday and not self.interrupt:
			self.bckgrndThreadCondition.acquire()
			# GOD.Organizer iterates the c.a.
			self.population = self.bast.iterateAutomaton()
			self.bckgrndThreadCondition.notify()
			self.bckgrndThreadCondition.wait()
			self.bckgrndThreadCondition.release()
		self.simulationOn = False
		sound.stopSoundServer()

	def backgroundLoop(self):
		""" Refreshing of the curses screen happens here
		"""
		(width, height)	= self.size

		while self.simulationOn and not self.interrupt:
			self.bckgrndThreadCondition.acquire()
			# Update the data needed by the background sound engine.
			populNorm = float(self.population) / operator.mul(width,height)
			sndCtrlCells = [self.kemet.get((22,18)), self.kemet.get((40,18)),
							self.kemet.get((64,18))]
			# Update the display
			self.bast.refreshDisplay(self.display)
			# Update the audio
			sound.inputDataControl(sndCtrlCells, populNorm)
			self.bckgrndThreadCondition.notify()
			self.bckgrndThreadCondition.wait()
			self.bckgrndThreadCondition.release()