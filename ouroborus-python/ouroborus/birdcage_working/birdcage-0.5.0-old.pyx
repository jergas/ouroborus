# This is an optimization of Erik Max Francis' generic
# cellular automata generation engine Cage, and is based
# on his Python code.

# It was written in Pyrex 0.9.3 and built from Cage 1.1.3
# on May 10th 2005 by Sat Tara Singh Khalsa and Vian 
# Patricio Gomez. Deg Teg Fateh!

# This is an entirely new version of the engine, with the 
# algorithms written in pure Pyrex as far as possible.  

# Extension types and C methods are used extensively. Python
# wrappers to access the C methods from Python code are
# provided occassionally. The main difference with the original 
# cage is that the buffer grid is now a C array of integers, and
# all references to addresses in the form of Python tuples have
# been replaced by C integers.

# This version is highly unstable, and provides just enough 
# functionality to run a two-state, reduction rule, 
# two-dimensional automaton.

# This version can be run with a visual display using the
# accompanying bc03_parity automaton.


__name__ = 'birdcageNew'
__version__ = '0.5.0'
__author__ = 'STS Khalsa <smonkey@entropia.com.mx>'
__copyright__ = 'Copyright 2005 (C) Project Ouroboros'
__license__ = 'GPL v3'


import operator
import random



# Some limiting values
####################################################################
# These define the maximum size for a grid along any of its axes.

cdef enum:
     caliber = 1000
####################################################################



# Topologies
##################################################################


cdef class Topology:  
     """A topology is the encapsulation of the shape and dimensionality
     of a cellular network.  This essentially means a finite n-dimensional
     rectangular grid where some or all of the edges might be glued
     together."""

     cdef public int dimension, background, cells
     cdef public object size, zero

     def  __init__(self, object size, int dimension, int background):
          """Create a generic Topology object.
        
          size       ---> Python sequence with the integer number of cells 
                          along each axis of the grid.
          dimension  ---> an integer, the number of axes in the grid.
          background ---> an integer, the default state for all cells."""

          self.dimension = dimension
          self.background = background
          self.size = size

          # check that the dimensionality of the size sequence is correct
          assert len(size) == self.dimension

          # check that the size of the grid fits the buffer's capacity
          for i in range(self.dimension):
              assert size[i] < caliber

          # multiply the number of cells along each axis yielding
          # the total number of cells in the grid
          self.cells = reduce(operator.mul, self.size, 1)

          # create an n-tuple of zeros of the correct dimension
          self.zero = (0,)*self.dimension

