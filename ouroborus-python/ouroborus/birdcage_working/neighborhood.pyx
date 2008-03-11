# This module contains the neighborhood abstract class and
# its derived classes.

# It was written in Pyrex 0.9.6 on November 16th 2007
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5.
# It has also been seen to compile successfully on
# Ubuntu's GNU gcc

# A neighborhood system defines the set of cells which are considered
# to be 'adjacent' to any given cell. These may be inclusive
# or exclusive depending on whether they contain the centre
# cell itself. A neighborhood contains a topology, complete with 
# its map of cells and states, as an attribute.

# For more information visit <ouroborus.sf.net>


# Imported modules
####################################################################

import exceptions_birdcage as E
import operator


####################################################################


cdef class Neighborhood_2D:
     """Base class for all two-dimensional neighborhoods"""

     def  __init__(self, T.GridTopology topology):
          """Create a generic Neighborhood_2D object.

          topology ---> a birdcage GridTopology object"""

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


     def  handleTopology(self):
          """Return the underlying topology, for direct
          manipulation from Python code

          return -->> a GridTopology object"""

          return self.topology


     def  clone(self):
          """Make a morphologically identical copy of the grid.

          return -->> a birdcage Neighborhood object

          This is intended for cellular automata which require a working
          copy of themselves, such as synchronous automata (the most
          common kind)."""

          return self.pyx_clone()          


     cdef Neighborhood_2D pyx_clone(self):
          """Make a morphologically identical copy of the grid.

          return -->> a birdcage Neighborhood_2D object"""

          cdef T.Topology topology_copy
          topology_copy = self.topology.clone()
          return Neighborhood_2D(topology_copy)


     def  listNeighbors(self, object address):
          """List all of a given cell's neighbors

          address ---> a Python 2-tuple, the address of a cell in the grid
          return  -->> a Python list of coordinates, consisting of all
                       of the cell's neighbours"""

          cdef int i, x1, x2
          cdef object coordinates

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.topology.name)

          coordinates = []

          self.pyx_calculateNeighbors(address[0], address[1])

          for i from 0 <= i < self.neighbors:
              x1 = self.topology.normal_x1(self.neighbors_x1[i])
              x2 = self.topology.normal_x2(self.neighbors_x2[i])
              coordinates.append((x1, x2))

          return coordinates


     cdef void pyx_calculateNeighbors(self, int x1, int x2):
          """Calculate the coordinates of a cell's neighbors
          and store the information in the self.neighbors variables
        
          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> Null"""

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
          x2     ---> the second integer coordinate value
          return -->> Null"""

          cdef int i
          self.pyx_calculateNeighbors(x1, x2)
          for i from 0 <= i < self.neighbors:
              self.neighbors_st[i] = self.topology.pyx_get(self.neighbors_x1[i], self.neighbors_x2[i])


     def  reduceStates(self, object address, object function, int initialv):
          """Iterate a binary function recursively on all of a cell's
          neighbours' states

          address  ---> a Python 2-tuple, the address of a cell in the grid
          function ---> a Python binary function
          initialv ---> an initial integer value
          return   -->> an integer value"""

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.topology.name)

          return self.pyx_reduceStates(address[0], address[1], function, initialv)


     cdef int pyx_reduceStates(self, int x1, int x2, object function, int initialv):
          """Iterate a binary function recursively on all of a cell's
          neighbours' states

          x1       ---> the first integer coordinate value
          x2       ---> the second integer coordinate value
          function ---> a Python binary function
          initialv ---> an initial integer value
          return   -->> an integer value"""

          cdef int i, reducing

          self.pyx_calculateStates(x1, x2)
          reducing = initialv
          
          for i from 0 <= i < self.neighbors:
               reducing = function(reducing, self.neighbors_st[i])

          return reducing


     def  sumStates(self, object address):
          """Sum all the neighbouring states

          address  ---> a Python 2-tuple, the address of a cell in the grid
          return -->> an integer value"""

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.topology.name)

          return self.pyx_sumStates(address[0], address[1])


     cdef int pyx_sumStates(self, int x1, int x2):
          """Sum all the neighbouring states

          x1     ---> the first integer coordinate value 
          x2     ---> the second integer coordinate value
          return -->> an integer value"""

          return self.pyx_reduceStates(x1, x2, operator.add, 0)          

####################################################################
# The following methods are Python handlers to access the embedded
# Topology methods:

     def  isNormalized(self, object address):
          """Check whether a cell's address is normalised

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> True if address is normalised, False otherwise"""

          return self.topology.isNormalized(address)


     def  normalize(self, object address):
          """Normalise an address (depends strongly on the topology chosen)

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> a standard coordinate value"""

          return self.topology.normalize(address)


     def  get(self, object address):
          """Get the state at a given address

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""

          return self.topology.get(address)


     def  set(self, object address, int state):
          """Set a given address to a given state

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer
          return  -->> None"""

          self.topology.set(address, state)


     def  reset(self, address):
          """Reset a cell to the predefined background state

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> None"""

          self.topology.reset(address)


     def  center(self):
          """Find a cell located roughly in the center of the grid.
  
          return -->> a Python n-tuple, the address of the above cell"""

          return self.topology.center()          
          
    
     def  random(self):
          """Find a random, valid address in the grid.        
  
          return -->> a Python n-tuple"""

          return self.topology.random()

####################################################################

cdef class VonNeumannNeighborhood(Neighborhood_2D):
     """A 2-D neighborhood system which only looks at the adjacent
     cells in the 4 cardinal directions"""

     def  __init__(self, T.GridTopology topology):
          """A two-dimensional neighborhood consisting of the adjoining
          cells in the 4 cardinal directions only.

          topology ---> a birdcage GridTopology object"""


          Neighborhood_2D.__init__(self, topology)
          self.neighbors = 4
          self.name = "Von Neumann neighborhood system"
          

     cdef Neighborhood_2D pyx_clone(self):
          """Make a morphologically identical copy of the grid.

          return -->> a birdcage VonNeumannNeighborhood object"""

          cdef T.Topology topology_copy
          topology_copy = self.topology.clone()
          return VonNeumannNeighborhood(topology_copy)


     cdef void pyx_calculateNeighbors(self, int x1, int x2):
          """Calculate the coordinates of a cell's neighbors
          and store the information in the self.neighbors variables
        
          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> Null"""

          self.neighbors_x1[0] = x1
          self.neighbors_x2[0] = x2-1

          self.neighbors_x1[1] = x1+1
          self.neighbors_x2[1] = x2

          self.neighbors_x1[2] = x1
          self.neighbors_x2[2] = x2+1
              
          self.neighbors_x1[3] = x1-1
          self.neighbors_x2[3] = x2


