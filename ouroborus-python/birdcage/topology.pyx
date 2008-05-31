# This module contains the topology abstract class and
# its derived classes

# It was written in Pyrex 0.9.6 on November 11th 2007
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5.
# It has also been seen to compile successfully on
# Ubuntu's GNU gcc

# The Topology object contains the information for the
# shape and dimensionality of the mundito grid. At 
# present this essentially means a finite n-dimensional 
# rectangle with possibly some or all of its edges glued
# together.

# For more information visit <ouroborus.sf.net>


# Imported modules
####################################################################

import exceptions_birdcage as E
import operator
import random




####################################################################



cdef class Topology:  
     """Abstract base class for all topologies"""

     def  __init__(self, object size, int background):
          """Create a generic Topology object
        
          size       ---> Python sequence with the integer number of cells 
                          along each axis of the grid.
          background ---> an integer, the default state for all cells."""


          self.background = background
          self.size = size
          self.dimension = len(self.size)
          self.name = "Abstract Topology"

          # check that the size of the grid fits the buffer's capacity
          for i in range(self.dimension):
              if not (size[i] < caliber):
                  raise E.SizeError(size[i],caliber)

          # multiply the number of cells along each axis yielding
          # the total number of cells in the grid
          self.cells = reduce(operator.mul, self.size, 1)

          # create an n-tuple of zeros of the correct dimension
          self.zero = (0,)*self.dimension


     def  isNormalized(self, object address):
          """Check whether a cell's address is normalised

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> True if address is normalised, False otherwise"""

          if self.pyx_isNormalized(address) == -1:
              raise E.InvalidAddressError(address, self.name)
          else:
              return self.pyx_isNormalized(address)


     cdef int pyx_isNormalized(self, object address):
          """Check whether a cell's address is normalised

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> True if address is normalised, False otherwise"""

          if self.pyx_normalize(address) == -1:
              return -1
          else:
              return address == self.pyx_normalize(address)


     def  normalize(self, object address):
          """Normalise an address (depends strongly on the topology chosen)

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> a standard coordinate value"""

          if self.pyx_normalize(address) == -1:
              raise E.InvalidAddressError(address, self.name)
          else:
              return self.pyx_normalize(address)


     cdef object pyx_normalize(self, object address):
          """Normalise an address (depends strongly on the topology chosen)

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> a standard coordinate value, or -1"""

          return -1


     def  clone(self):
          """Create a twin instantiation of the same topology

          return -->> a Topology with the same attributes as self"""

          return Topology(self.size, self.background)


     def  get(self, object address):
          """Get the state at a given address

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""

          raise NotImplementedError


     def  set(self, object address, int state):
          """Set a given address to a given state

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer
          return  -->> None"""

          raise NotImplementedError


     def  reset(self, address):
          """Reset a cell to the predefined background state

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> None"""

          self.set(address, self.background)


     def  center(self):
          """Find a cell located roughly in the center of the grid.
  
          return -->> a Python n-tuple, the address of the above cell"""

          # divide the length of each grid axis by 2 and build a tuple with
          # the resulting values
          
          address = []
          for i in range(self.dimension):
              address.append(self.size[i]/2)
          return tuple(address)

    
     def  random(self):
          """Find a random, valid address in the grid.        
  
          return -->> a Python n-tuple"""

          # find a random integer within the range of each grid axis and build
          # a tuple with the resulting values

          address = map(random.randrange, self.size)
          return tuple(address)


#################################################################################

cdef class GridTopology(Topology):
     """A two-dimensional, bounded topology consisting of a rectangular
     grid of cells, base class for 2D topologies"""



    
     def  __init__(self, object size, int background):
          """Override Topology.__init__.        

          size       ---> Python 2-tuple with the integer number of cells 
                          along the width and height of the grid.
          background ---> an integer, the default state for all cells."""


          cdef int x1, x2

          Topology.__init__(self, size, background)
          self.name = "Grid Topology"
          if not self.dimension == 2:
              raise E.DimensionError(self.name, 2, self.dimension)
          (self.width, self.height) = size
          self.border = 0

          # set up a two-dimensional array of cells at background state 

          for x1 from 0 <= x1 < self.width:
              for x2 from 0 <= x2 < self.height:
                  self.cell[x1][x2] = background


     def  clone(self):
          """Create a twin instantiation of the same topology

          return -->> a Topology with the same attributes as self"""

          return GridTopology(self.size, self.background)


     cdef object pyx_normalize(self, object address):
          """Normalise an address by invalidating address off bounds

          address ---> a grid coordinate value in the form of a Python 2-tuple
          return  -->> a standard coordinate value, or -1"""

          if len(address) > 2:
              return -1
          elif (self.normal_x1(address[0]) == -1) or (self.normal_x2(address[1]) == -1):
              return -1
          else:
              return (self.normal_x1(address[0]), self.normal_x2(address[1]))


     cdef int normal_x1(self, int x1):
          """Normalise the first coordinate
        
          x1      ---> an integer value for the first coordinate entry
          return  -->> the same value if valid, -1 otherwise"""

          if x1 < 0 or x1 >= self.width:
              return -1
          else:
              return x1


     cdef int normal_x2(self, int x2):
          """Normalise the second coordinate
        
          x2      ---> an integer value for the second coordinate entry
          return  -->> the same value if valid, -1 otherwise"""

          if x2 < 0 or x2 >= self.height:
              return -1
          else:
              return x2


     def  get(self, object address):
          """Get the state at a given address

          address ---> a grid coordinate value in the form of a Python 2-tuple
          return  -->> an integer"""

          if not len(address) == 2:
               raise E.InvalidAddressError(address,self.name)
          else:
               return self.pyx_get(address[0], address[1])          


     cdef int pyx_get(self, int x1, int x2):
          """Get the state at a given address

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> an integer, the state at this address"""

          cdef int nx1, nx2
          nx1 = self.normal_x1(x1)
          nx2 = self.normal_x2(x2)
          if nx1 == -1 or nx2 == -1:
               return self.border
          else:
               return self.cell[nx1][nx2]


     cdef int pyx_get_nosafe(self, int x1, int x2):
          """Get the state at a given address - fastest version

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> an integer, the state at this address"""

          return self.cell[x1][x2]


     def  set(self, object address, int state):
          """Set a given address to a given state

          address ---> a grid coordinate value in the form of a Python 2-tuple
          state   ---> an integer
          return  -->> None"""

          if not len(address) == 2:
               raise E.InvalidAddressError(address,self.name)
          else:
               s = self.pyx_set(address[0], address[1], state)
          if not s == 0:
               raise E.InvalidAddressError(address,self.name)


     cdef int pyx_set(self, int x1, int x2, int state):
          """Set a given address to a given state

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          state  ---> an integer
          return -->> 0 if fine, -1 otherwise"""

          cdef int nx1, nx2
          nx1 = self.normal_x1(x1)
          nx2 = self.normal_x2(x2)
          if nx1 == -1 or nx2 == -1:
               return -1
          else:
               self.cell[nx1][nx2] = state
               return 0


     cdef void pyx_set_nosafe(self, int x1, int x2, int state):
          """Set a given address to a given state - fastest version

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          state  ---> an integer
          return -->> None"""

          self.cell[x1][x2] = state


#################################################################################

cdef class ToroidTopology(GridTopology):
     """A two-dimensional, unbounded topology consisting of a rectangular
     grid of cells, where the top and bottom edges and the left and right
     edges have been 'glued together' (Pacman style)"""


     def  __init__(self, object size, int background):
          """Override Topology.__init__.        

          size       ---> Python 2-tuple with the integer number of cells 
                          along the width and height of the grid.
          background ---> an integer, the default state for all cells."""


          GridTopology.__init__(self, size, background)
          self.name = "Toroid Topology"


     def  clone(self):
          """Create a twin instantiation of the same topology

          return -->> a Topology with the same attributes as self"""

          return ToroidTopology(self.size, self.background)


     cdef object pyx_normalize(self, object address):
          """Normalise an address by finding standard coordinate values

          address ---> a grid coordinate value in the form of a Python 2-tuple
          return  -->> a standard coordinate value, or -1"""

          if len(address) > 2:
              return -1
          else:
              return (self.normal_x1(address[0]), self.normal_x2(address[1]))


     cdef int normal_x1(self, int x1):
          """Normalise the first coordinate
        
          x1      ---> an integer value for the first coordinate entry
          return  -->> x1 modulo the width of the grid"""

          while x1 < 0 or x1 >= self.width:    
              # keep adding or subtracting the width of the grid
              # until it falls into the desired range
              if x1 < 0: x1 = x1 + self.width
              elif x1 >= self.width: x1 = x1 - self.width     
          return x1


     cdef int normal_x2(self, int x2):
          """Normalise the first coordinate
        
          x2      ---> an integer value for the second coordinate entry
          return  -->> x2 modulo the width of the grid"""

          while x2 < 0 or x2 >= self.height:    
              # keep adding or subtracting the height of the grid
              # until it falls into the desired range
              if x2 < 0: x2 = x2 + self.height
              elif x2 >= self.height: x2 = x2 - self.height     
          return x2


     cdef int pyx_get(self, int x1, int x2):
          """Get the state at a given address

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> an integer, the state at this address"""

          return self.cell[self.normal_x1(x1)][self.normal_x2(x2)]


     cdef int pyx_set(self, int x1, int x2, int state):
          """Set a given address to a given state

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          state  ---> an integer
          return -->> 0 if fine, -1 otherwise"""

          self.cell[self.normal_x1(x1)][self.normal_x2(x2)] = state
          return 0
