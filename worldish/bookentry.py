#!/usr/bin/python

# This neat little module contains the BookEntry class for the book of life.
# 
# Coded by Sat Tara Singh, Jergas Apwith and Ernesto Illescas
#
# As of today --- 8th May 2009 --- it includes the following features:
#
#	* each instance of BookEntry will stand for one of the creatures which are
#	referred to in the Book of Life
#	* there are 4 objects which belong in the BookEntry as attributes - its name,
#	an actual imported module object with the code which is the creature's informational
#	soul, the agent object which is an instance of a birdcage class and a dictionary
#	called fatum which contains various data, as follows:
#	* the creature's code is written as a string on its fatum, so that it may be
#	copied onto the book of life when a descendant is to be generated
#	* the value for the creature's mana is also written here
#	* the creature's prana and address also appear here, and are dynamically
#	updated every round of the creture's life
#
# Read some history at EOF

import string
import sound_globals as soundGlobals


class BookEntry:
	"""An entry into the book of life, comprising of:

	name  ---> a string,
	module ---> a module object with the compiled genome,
	agent  ---> a birdcage agent object, and
	fatum  ---> a dictionary with data written by the agent"""

	def __init__(self, name, modulename):
		self.name = name
		self.modulename = modulename
		self.module = None
		self.agent = None
		self.fatum = {"prayer":"BeBirthed"}
		self.automaton = None


	def __str__(self):
		display = [self.name+", of strain "+self.modulename+" has the following fatum:"]
		display.extend(["\t"+str(key)+":\t"+str(value) for key,value in self.fatum.items()])
		return string.join(display, "\n")


	def callModule(self):
		"""Dynamically import the module with the agent into the runtime namespace"""
		self.module = __import__(self.modulename)


	def instantiateAgent(self, automaton):
		"""Call an instance of the appropriate agent class by invoking the birth 
		method in its module, and using the parameters in the bookentry

		automaton ---> a birdcage automaton object"""

		code = self.fatum["code"]
		prana = self.fatum["prana"]
		mana = self.fatum["mana"]		
		address = self.fatum["address"]
		self.agent = self.module.birth(automaton, code, prana, mana, address)
		self.automaton = automaton


	def agentLive(self):
		"""Call on the agent to perform its live method

		return -->> 1"""

		self.fatum["prayer"] = self.module.live(self.agent) #this is deep magic!
		self.fatum["prana"] = self.agent.tellPrana() # simply update some data now
		self.fatum["address"] = self.agent.tellAddress()
		# if an agent just ate, record it in VocalTract (when running
		# simulations with sound)
		if soundGlobals.simWSound == 1:
			if self.agent.hasEaten():
				self.fatum["voice"].ate = 1
		return 1


        def terminateAgent(self):
                """Terminate the agent at its life's end
                
                return -->> 1"""
                
                del self.agent
                del self.module
                return 1


# History
#
# This module came into being as a tool to send information between GOD and its creatures,
# via the Book of Life, in a systematic and pythonic fashion.
#
# As I meditate on the Lord Buddha's life on this Full Moon in the House of Scorpio, I
# wonder if the turning of the wheel of dharma is accessible through our own effort of
# will, or only through the grace of an enlightened being, or if there is even a 
# difference between these two.

