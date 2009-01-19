# import all the necessary modules:
# these are the core birdcage modules:
import topology
import neighborhood
import rule
import agent as a
import automaton
import genome as g
from code import tabula
# these are the modules used for display
import visual as v
import curses as c
# these are the ingredients for the Pyrex compile spell
import sys
import distutils.core 
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
# anything extra goes here
import random


class Generator:
	"""This object creates a code object from a genome and appends it onto
        the list of creatures. It also performs other creation-related functions
	such as generating a fully-functioning cellular automaton"""


	def __init__(self, obstetrix):
		"""Create a Generator instance

		obstetrix ---> a string to head all generated filenames"""
		
		self.obstetrics = 0
		self.obstetrix = obstetrix


	def generateAutomaton(self, size, tdata, ndata, rdata, adata):
		"""Create an instance of a birdcage automaton class

		size   ---> a Python tuple of integers
		tdata  ---> a Python tuple commencing with a string
		ndata  ---> a Python tuple commencing with a string
		rdata  ---> a Python tuple commencing with a string
                adata  ---> a Python tuple commencing with a string
		return -->> an Automaton object"""

		topologyClass = getattr(topology, tdata[0])
		topologyInstance = topologyClass(size, tdata[1])

		neighborhoodClass = getattr(neighborhood, ndata[0])
		neighborhoodInstance = neighborhoodClass(topologyInstance)

		ruleClass = getattr(rule, rdata[0])
		ruleInstance = ruleClass(neighborhoodInstance, rdata[1])

		automatonClass = getattr(automaton, adata[0])
		automatonInstance = automatonClass(ruleInstance)

		return automatonInstance


	def generateGenotype(self, poeio, ode):
		"""Write and compile a file from a genome

		poeio  ---> a list of characters
		ode    ---> a list of names
		return -->> 1"""

		self.obstetrics += 1
		# samskara is a genome binding poeio to tabula
		samskara = g.Genome(poeio, tabula, 2)
		# create a name for the module object
		onoma = self.obstetrix+str(self.obstetrics)
		# corpus is the relative filepath where the compiled genome will be saved
		corpus = 'creatures/'+onoma+'.pyx'
		# this incantation actually writes the .pyx file with the translated poeio code
		samskara.incorporate(corpus)

		# now we invoke the pyrex compiler to create the module
		# this is a hack to do away with the command line arguments Pyrex expects
		commandLineArgs = ['build_ext', '--inplace']
		sys.argv.extend(commandLineArgs)
		# and the actual call to the compiler using the Pyrex build_ext command
		distutils.core.setup(
			name = onoma,
			ext_modules = [Extension(onoma,[corpus])],
			cmdclass = {'build_ext':build_ext}
			) 

		# finally, append the module's name to the list of names and return
		ode.append(onoma)
		return 1


	def generateDisplay(self, earth, size, stdscr):
		"""Initialise a curses display for the automaton and its agents
		earth  ---> a birdcage automaton
		size   ---> a 2-tuple with the grid's dimensions
		stdscr ---> a curses standard screen object
		return -->> a 3-tuple of values useful for display"""

		# a little workaround to make curses work for any terminal size
		(width, height) = size
		(winheight,winwidth) = stdscr.getmaxyx()
		displaywidth = (winwidth < width) and winwidth-1 or width
		displayheight = (winheight < height) and winheight-1 or height
		# run the visual display refresh cycle as initialisation
		earth.set((40,10),1)
		v.updateLoop(earth, stdscr, displaywidth, displayheight)
		stdscr.refresh()
		# return a 3-tuple useful for further display
		return (stdscr, displaywidth, displayheight)


class Organizer:
	"""This object coordinates the iteration-per-iteration functioning of the
	automata and its agents. It calls on the Organizer and Destroyer when
	necessary."""


	def __init__(self, earth, book):
		"""Create an Organizer instance

		earth ---> some complete birdcage Automaton instance
		book  ---> a list of agent code objects (genotypes)"""

		self.earth = earth
		self.book = book
		self.annum = 0


	def iterateAutomaton(self):
		"""Iterate the birdcage automaton associated to the Organizer

		return -->> 1"""

		self.earth.update()
		self.annum = self.annum + 1
		return 1


        def readBookOfLife(self, index, code, prana, mana, address):
		"""Dynamically import the modules compiled by the Generator

		This will also cause actual agent instances to be created
		index   ---> an integer, the module's order in self.book
		code    ---> a string with the genome's code
		prana   ---> an integer with the agent's initial prana
		mana    ---> an integer, a special state of the ca from the agent's viewpoint
		address ---> a 2-tuple, the agent's birthplace
		return  -->> 1 """

		if type(self.book[index]) == type("string"):
			module = __import__(self.book[index])
			agent = module.birth(self.earth, code, prana, mana, address)
			self.earth.addAgent(agent)
			self.book[index] = (self.book[index], module, agent)

			return 1

	def iterateAgents(self):
		"""Go through the list of agents and let them perform their actions

		return -->> 1 """

		for entity in self.book:
			entity[1].live(entity[2])

		return 1


	def refreshDisplay(self, display):
		"""Refresh the display on a curses terminal

		display       ---> a 3-tuple as follows:
		                   (stdscr, displaywidth, displayheight)
		stdscr        ---> a curses standard screen object
		displaywidth  ---> the integer width of the curses terminal
		displayheight ---> the integer height of the curses terminal
		return        -->> 1"""

		v.updateLoop(self.earth, display[0], display[1], display[2])
		display[0].refresh()
		
		

