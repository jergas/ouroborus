# This module contains the rule abstract class and
# its derived classes

# It was written in Pyrex 0.9.6 on January 7th 2008
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5.
# It has also been seen to compile successfully on
# Ubuntu's GNU gcc

# The Rule object contains the information necessary
# for calculating the state transition at each cell
# for every iteration of the automaton.

# For more information visit <ouroborus.sf.net>


# Imported modules
####################################################################

import exceptions_birdcage as E




####################################################################



cdef class Rule_2D:  
     """Abstract base class for all two-dimensional transition rules.
     It actually does nothing at all."""


     def  __init__(self, N.Neighborhood_2D neighborhood, object param=None):
          """Create a generic Rule_2D object
        
          neighborhood ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          param        ---> a Python object available for additional paramaters"""

          self.neighborhood = neighborhood
          self.param = param
          self.name = "Passive Rule 2-D"


     def  handleNeighborhood(self):
          """Return the associated neighborhood system for direct
          manipulation from Python code

          return -->> a birdcage Neighborhood_2D object"""

          return self.neighborhood


     def  apply(self, object address):
          """Apply the state transition rule at a given address

          address ---> a Python 2-tuple, the address of a cell in the grid
          return  -->> None"""

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.neighborhood.topology.name)

          self.pyx_apply(address[0], address[1])


     cdef pyx_apply(self, int x1, int x2):
          """Apply the state transition rule at a given address

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> Null"""

          pass


     def  applyToTarget(self, object address, T.GridTopology target):
          """Apply the state transition rule at a given address in a
          target cell grid different from the rule's own

          address ---> a Python 2-tuple, the address of a cell in the grid
          target ---> a birdcage GridTopology object such as a working
                      grid in a synchronous automaton
          return  -->> state"""

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.neighborhood.topology.name)

          return self.pyx_applyToTarget(address[0], address[1], target)


     cdef pyx_applyToTarget(self, int x1, int x2, T.GridTopology target):
          """Apply the state transition rule at a given address in a
          target cell grid different from the rule's own

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          target ---> a birdcage GridTopology object such as a working
                      grid in a synchronous automaton
          return -->> Null"""


          pass


#####################################################################

cdef class ReductionRule(Rule_2D):  
     """This rule applies a binary function recursively onto a cell's
     neighbors"""


     def  __init__(self, N.Neighborhood_2D neighborhood, object param):
          """Override Rule_2D.__init__
        
          neighborhood ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          param        ---> a Python 2-tuple, consisting of a
                            binary function an an initial integer value"""

          Rule_2D.__init__(self, neighborhood, param)
          self.name = "Reduction Rule"


     cdef pyx_apply(self, int x1, int x2):
          """Apply the state transition rule at a given address

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> Null"""

          cdef int state

          state = self.neighborhood.pyx_reduceStates(x1, x2, self.param[0], self.param[1])
          self.neighborhood.topology.pyx_set(x1, x2, state)


     cdef pyx_applyToTarget(self, int x1, int x2, T.GridTopology target):
          """Apply the state transition rule at a given address in a
          target cell grid different from the rule's own

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          target ---> a birdcage GridTopology object such as a working
                      grid in a synchronous automaton
          return -->> state"""

          cdef int state

          state = self.neighborhood.pyx_reduceStates(x1, x2, self.param[0], self.param[1])
          target.pyx_set(x1, x2, state)
          return state

#####################################################################

cdef class ConwayRule(Rule_2D):  
     """Conway's Game of Life rule. If the sum of a dead cell's neighbors
     is 3, the cell becomes alive.  If the sum of a live cell's neighbors
     is 2 or 3, the cell remains alive.  Otherwise, it dies."""


     def  __init__(self, N.Neighborhood_2D neighborhood, object param=None):
          """Override Rule_2D.__init__
        
          neighborhood ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          param        ---> None or nothing useful"""

          Rule_2D.__init__(self, neighborhood, param)
          self.name = "Conway Rule (3/2,3)"


     cdef pyx_apply(self, int x1, int x2):
          """Apply the state transition rule at a given address

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          return -->> Null"""

          cdef int state, sumstates, cell

          sumstates = self.neighborhood.pyx_sumStates(x1, x2)
          cell = self.neighborhood.topology.pyx_get(x1, x2)
          if (cell==0 and sumstates==3):
             state = 1
          elif (cell==1 and sumstates==2) or (cell==1 and sumstates==3):
             state = 1
          else:
             state = 0

          self.neighborhood.topology.pyx_set(x1, x2, state)


     cdef pyx_applyToTarget(self, int x1, int x2, T.GridTopology target):
          """Apply the state transition rule at a given address in a
          target cell grid different from the rule's own

          x1     ---> the first integer coordinate value
          x2     ---> the second integer coordinate value
          target ---> a birdcage GridTopology object such as a working
                      grid in a synchronous automaton
          return -->> Null"""

          cdef int state, sumstates, cell

          sumstates = self.neighborhood.pyx_sumStates(x1, x2)
          cell = self.neighborhood.topology.pyx_get(x1, x2)
          if (cell==0 and sumstates==3):
             state = 1
          elif (cell==1 and sumstates==2) or (cell==1 and sumstates==3):
             state = 1
          else:
             state = 0

          target.pyx_set(x1, x2, state)

