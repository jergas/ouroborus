# import all the necessary modules:
# these are the core birdcage modules:
import topology as t
import neighborhood as n
import rule as r
import operator as o
import agent as a
import automaton as u
import genome as g
from code import tabula
# these are the modules used for display
import visual as v
import curses as c
# these are the ingredients for the Pyrex compile spell
import distutils.core 
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
# anything extra goes here
import random


class Generator:
	"""This object creates a code object from a genome and appends it onto
        the list of creatures"""


	def __init__(self, obstetrix):
		"""Create a Generator instance

		obstetrix ---> a string to head all generated filenames"""
		self.obstetrics = 0
		self.obstetrix = obstetrix


	def generate(self, poeio, ode):
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
		distutils.core.setup(
			name = onoma,
			ext_modules = [Extension(onoma,[corpus])],
			cmdclass = {'build_ext':build_ext}
			) 

		# finally, append the module's name to the list of names
		ode.append(onoma)
