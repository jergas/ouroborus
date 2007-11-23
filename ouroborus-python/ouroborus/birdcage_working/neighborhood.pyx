# This module contains the neighborhood abstract class and
# its derived classes.

# It was written in Pyrex 0.9.3 on November 16th 2007
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5 

# A neighborhood defines the set of cells which are considered
# to be 'adjacent' to any given cell. These may be inclusive
# or exclusive depending on whether they contain the centre
# cell itself.

# For more information visit <ouroborus.sf.net>


# Imported modules
####################################################################

import exceptions_birdcage as E

cimport topology as T


# Some limiting values
####################################################################
# This constant sets the maximum number of neighbors in a
# neighborhood

cdef enum:
     capacity = 20

####################################################################


cdef class Neighborhood_2D:
     """Base class for all two-dimensional neighborhoods"""

     cdef T.GridTopology topology
     cdef int neighbors
     cdef object name
     cdef int neighbors_x1[capacity]
     cdef int neighbors_x2[capacity]
     cdef int neighbors_st[capacity]


     def  __init__(self, T.GridTopology topology):
          """Create a generic Neighborhood_2D object."""

          cdef int i
          self.topology = topology
          self.neighbors = 0
          self.name = "Abstract 2D neighborhood system"

          if not (self.topology.dimension == 2):
               raise E.DimensionError(self.name, 2, self.topology.dimension)

          for i from 0 <= i < capacity:
              self.neighbors_x1[i] = 0
              self.neighbors_x2[i] = 0
              self.neighbors_st[i] = 0


     def  listNeighbors(self, object address):
          """List all of a given cell's neighbors

          address ---> a Python 2-tuple, the address of a cell in the grid
          return  -->> a Python list of coordinates, consisting of all
                       of the cell's neighbours"""

          cdef int i
          cdef object coordinates

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.topology.name)

          coordinates = []

          self.pyx_calculateNeighbors(address[0], address[1])

          for i from 0 <= i < self.neighbors:
              coordinates.append((self.neighbors_x1[i], self.neighbors_x2[i]))

          return coordinates


     cdef void pyx_calculateNeighbors(self, int x1, int x2):
          """Calculate the coordinates of a cell's neighbors
          and store the information in the self.neighbors variables
        
          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value"""

          pass


     def  listStates(self, object address):
          """List the states of all of a given cell's neighbors

          address ---> a Python 2-tuple, the address of a cell in the grid
          return  -->> a Python list of integers, consisting of all
                       of the cell's neighbours' states"""

          cdef int i
          cdef object states

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.topology.name)

          states = []

          self.pyx_calculateStates(address[0], address[1])

          for i from 0 <= i < self.neighbors:
              states.append(self.neighbors_st[i])

          return states



     cdef void pyx_calculateStates(self, int x1, int x2):
          """Calculate the statess of a cell's neighbors and store
          the information in the self.neighbors_st variables

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value"""

          cdef int i
          self.pyx_calculateNeighbors(x1, x2)
          for i from 0 <= i < self.neighbors:
              self.neighbors_st[i] = self.topology.pyx_get(self.neighbors_x1[i], self.neighbors_x2[i])


####################################################################

cdef class VonNeumannNeighborhood(Neighborhood_2D):
     """Base class for all two-dimensional neighborhoods,
     still abstract"""

     def  __init__(self, T.GridTopology topology):
          """A two-dimensional neighborhood consisting of the adjoining
          cells in the 4 cardinal directions only."""


          Neighborhood_2D.__init__(self, topology)
          self.neighbors = 4
          self.name = "Von Neumann neighborhood system"
          

     cdef void pyx_calculateNeighbors(self, int x1, int x2):
          """Calculate the coordinates of a cell's neighbors
          and store the information in the self.neighbors variables
        
          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value"""

          self.neighbors_x1[0] = x1+1
          self.neighbors_x2[0] = x2

          self.neighbors_x1[1] = x1
          self.neighbors_x2[1] = x2+1

          self.neighbors_x1[2] = x1-1
          self.neighbors_x2[2] = x2
              
          self.neighbors_x1[3] = x1
          self.neighbors_x2[3] = x2-1
