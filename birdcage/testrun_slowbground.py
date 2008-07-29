# import all the necessary modules:
import topology as t
import neighborhood as n
import rule as r
import operator as o
import agent as a
import automaton as u
import genome as g
from code import tabula

import visual as v
import curses as c

import distutils.core 
from distutils.extension import Extension
from Pyrex.Distutils import build_ext

import random

# set grid size and number of iterations:
size = (90,40)
(width, height) = size
iterate = 30000

# poeio is a sequence of words from tabula at module code
poeio = ['a','i','z','d','z','n','z','m','z','a','a','w','a','r','a','c','a','a','a','e']
# samskara is a genome binding poeio to tabula
samskara = g.Genome(poeio, tabula, 2)
# corpus is the relative filepath where the compiled genome will be saved
corpus = 'creatures/wanderer.pyx'
# this incantation actually writes the .pyx file with the translated poeio code
samskara.incorporate(corpus)
# create a name for the module object from the .pyx file
species = 'wanderer'

# now we invoke the pyrex compiler to create the module
distutils.core.setup(
	name = species,
	ext_modules = [Extension(species,[corpus])],
	cmdclass = {'build_ext':build_ext}
	) 

# initialise the automaton
annuvin = t.ToroidTopology(size,0)
caer = n.VonNeumannNeighborhood(annuvin)
sidhe = r.ReductionRule(caer,(o.xor,0))
prydain = u.SynchronousAutomaton_2D(sidhe)

# import the module which was dynamically created from the poeio
amatheon = __import__(species)

# create various instances of an agent class defined in poeio
amatheonwy = amatheon.beBorn(annuvin)
gwion = amatheon.beBorn(annuvin)
gwydion = amatheon.beBorn(annuvin)
bran = amatheon.beBorn(annuvin)

# manifest the agents on the grid
prydain.addAgent(bran)
prydain.addAgent(gwydion)
prydain.addAgent(amatheonwy)
prydain.addAgent(gwion)

# seed the automaton with a live cell
prydain.set((10,10),1)


def main(stdscr):
    # a little workaround to make curses work for any terminal size
    (winheight,winwidth) = stdscr.getmaxyx()
    displaywidth = (winwidth < width) and winwidth-1 or width
    displayheight = (winheight < height) and winheight-1 or height
    # run the visual display refresh cycle as initialisation
    v.updateLoop(prydain, stdscr, displaywidth, displayheight)
    stdscr.refresh()

    # this is an iteration counter
    t = 0
    #print "t = %i\r" % (t)
    
    # the main iteration cycle
    for i in range(iterate):
        # update the automaton
        if i%17 == 0: prydain.update()
        t = t+1
        # call a method from the dynamically compiled peoio to update the agents
        amatheon.wander(amatheonwy)
	amatheon.wander(gwion)
	amatheon.wander(gwydion)
	amatheon.wander(bran)

        # run the visual display refresh cycle
    	v.updateLoop(prydain, stdscr, displaywidth, displayheight)
        stdscr.refresh()
        #print "t = %i" % (t)
    raw_input("Done")

# call the generic curses wrapper to maintain terminal sanity in all events
if __name__ == '__main__': c.wrapper(main)
