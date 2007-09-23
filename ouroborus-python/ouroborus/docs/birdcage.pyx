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


__name__ = 'birdcage'
__version__ = '0.3.1'
__author__ = 'STS Khalsa, VP Gomez <smonkey@entropia.com.mx>'
__copyright__ = 'Copyright 2005 (C) Project Ouroboros'
__license__ = 'GPL'


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
     together. Note: topologies and neighborhoods are
     used as mixins to create a map."""

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


     cdef int isNormalized(self, object address):
          """check if a cell's address is normalised.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> 1 if address is normalised, 0 otherwise"""

          return address == self.normalize(address)


     cdef object normalize(self, object address):
          """Normalise an address (depends strongly on the topology chosen).

          address ---> a grid coordinate value in the form of a Python n-tuple"""

          raise NotImplementedError


     cdef object clone(self):

          return Topology(self.size, self.dimension, self.background)


     def  py_clone(self):

          return self.clone()


     cdef int get(self, object address):
          """Get the state of an individual cell from the buffer.
          This depends strongly on the actual choice of a topology.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""

          raise NotImplementedError


     cdef int get2(self, int x, int y):
          """Override Topology.get.        

          x       ---> 
          y       --->
          return  -->> an integer, the state corresponding to the address"""

          raise NotImplementedError


     def  py_get2(self, object address):
          """A Python wrapper for the C function get.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""

          return self.get2(address[0], address[1])
     

     cdef void set(self, object address, int state):
          """Set the state of an individual cell in the buffer.
          This depends strongly on the actual choice of a topology.        

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer"""

          raise NotImplementedError


     cdef void set2(self, int x, int y, int state):
          """Override Topology.set.

          x       ---> 
          y       --->
          state   ---> an integer"""

          raise NotImplementedError


     def  py_set2(self, object address, int state):
          """A Python wrapper for the C function set.

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer"""

          self.set2(address[0], address[1], state)


     cdef void reset(self, address):
          """Reset the state of an individual cell to the background state.
       
          address ---> a grid coordinate value in the form of a Python n-tuple"""

          self.set(address, self.background)


     cdef int half(self, int n):
          """Integer division of a number by 2.

          n      ---> an integer
          return -->> an integer, the quotient of n divided by 2"""

          return operator.div(n, 2)


     cdef object center(self):
          """Find a cell located roughly in the center of the grid.
  
          return -->> a Python n-tuple, the address of the above cell"""

          cdef int i
          cdef object address          

          # divide the length of each grid axis by 2 and build a tuple with
          # the resulting values
          
          address = []
          for i from 0 <= i < self.dimension:
              address.append(self.half(self.size[i]))
          return tuple(address)

    
     def  py_center(self):
          """A Python wrapper for the C function center.

          return -->> a Python n-tuple"""

          return self.center()


     cdef object random(self):
          """Find a random, valid and normalised address in the grid.        
  
          return -->> a Python n-tuple"""

          cdef object address

          # find a random integer within the range of each grid axis and build
          # a tuple with the resulting values
          address = map(random.randrange, self.size)
          return tuple(address)


     def  py_random(self):
          """A Python wrapper for the C function random.

          return -->> a Python n-tuple"""

          return self.random()




cdef class GridTopology(Topology):
     """A two-dimensional, bounded topology consisting of a rectangular
     grid of cells."""

    
     cdef public int border, height, width
     cdef int cell[caliber][caliber]

    
     def  __init__(self, object size, int dimension, int background):
          """Override Topology.__init__.        

          size ---> a Python sequence consisting of 2 integer values."""

          assert dimension == 2
          self.border = 0

          # size is passed to Topology.__init__ which verifies
          # dimensionality and sets self.zero to (0,0)
          Topology.__init__(self, size, 2, background)
        
          # give appropriate names to each entry in the size sequence
          (self.width, self.height)= size

          # and set up a two-dimensional array of zeros where the cell
          # (x,y) corresponds to self.buffer[x][y]
          for x from 0 <= x < self.width:
              for y from 0 <= y < self.height:
                  self.cell[x][y] = background


     cdef object clone(self):

          return GridTopology(self.size, self.dimension, self.background)


     cdef int normal_x(self, int x):
          """Override Topology.normalize.
        
          x       ---> 
          return  -->> 

          the address is now a pair (a,b) and normalisation is
          accomplished by invalidating addresses which fall off
          the bounds of the rectangular grid [0,width) x [0,height)"""
 
          # check if the coordinate value is off the grid
          if x < 0 or x >= self.width:
              return -1 # and if so, the address is invalid
          return x  # otherwise it is a valid cell in the grid


     cdef int normal_y(self, int y):
          """Override Topology.normalize.
        
          y       ---> 
          return  -->> 

          the address is now a pair (a,b) and normalisation is
          accomplished by invalidating addresses which fall off
          the bounds of the rectangular grid [0,width) x [0,height)"""
 
          # check if the coordinate value is off the grid
          if y < 0 or y >= self.height:
              return -1 # and if so, the address is invalid
          return y  # otherwise it is a valid cell in the grid


     cdef int get2(self, int x, int y):
          """Override Topology.get.        

          x       ---> 
          y       --->
          return  -->> an integer, the state corresponding to the address"""


          if self.normal_x(x) == -1 or self.normal_y(y) == -1:      # if the address is invalid
              return self.border  # return the default border state

          # otherwise find the appropriate cell and return its state 
          return self.cell[x][y]# from the buffer grid


     cdef void set2(self, int x, int y, int state):
          """Override Topology.set.

          x       ---> 
          y       --->
          state   ---> an integer"""

          # if the address falls off the grid, it is a bug

          # otherwise, set the corresponding buffer list entry as desired
          self.cell[x][y] = state

    

cdef class ToroidTopology(GridTopology):
     """A two-dimensional, unbounded topology consisting of a
     rectangular grid of cells, where the 'topmost' row is adjacent
     to the 'bottommost,' and the 'leftmost' column is adjacent to the
     'rightmost.'"""

         
         
     def  __init__(self, object size, int dimension, int background ):
          """Call GridTopology.__init__.

          size ---> a Python sequence consisting of two integer values"""

          GridTopology.__init__(self, size, 2, 0)


     cdef object clone(self):

          return ToroidTopology(self.size, self.dimension, self.background)


     cdef int normal_x(self, int x):
          """Override GridTopology.normalize.

          x       ---> 
          return  -->> 

          Normalisation is performed by considering the two coordinate
          entries of the address modulo the height and width of the grid."""

          # if the address is off the normal range of the grid:
          while x < 0 or x >= self.width:    
   
              # keep adding or subtracting the height and/or width
              # until it falls into the desired range
              if x < 0: x = x + self.width
              elif x >= self.width: x = x - self.width
              
   
          return x # and then return the normalised address


     cdef int normal_y(self, int y):
          """Override GridTopology.normalize.

          y       ---> 
          return  -->> 

          Normalisation is performed by considering the two coordinate
          entries of the address modulo the height and width of the grid."""
 
          # if the address is off the normal range of the grid:
          while y < 0 or y >= self.height:    
   
              # keep adding or subtracting the height and/or width
              # until it falls into the desired range
              if y < 0: y = y + self.height
              elif y >= self.height: y = y - self.height

          return y # and then return the normalised address


     cdef int get2(self, int x, int y):
          """Override GridTopology.get.        

          x       ---> 
          y       --->
          return  -->> """


          return self.cell[self.normal_x(x)][self.normal_y(y)]   # and then find its state





# Neighborhoods
###############################################################


cdef class Neighborhood:
     """The abstraction of a neighbhourhood, or the set of cells that
     are 'adjacent' to any given cell.  Neighbourhoods are not considered
     to be inclusive by default (containing the centre cell itself) since
     the class' methods support both inclusive and exclusive neighbourhoods.
     Note: Topologies and Neighborhoods are used as mixins to create a
     map."""

     cdef Topology topology
     cdef public int neighborhood
     cdef int neigh_x[20]
     cdef int neigh_y[20]
     cdef int neigh_states[20]

     def  __init__(self, Topology topology, int neighborhood):
          """Create a general Neighborhood object."""

          cdef int i

          self.topology = topology
          self.neighborhood = neighborhood

          for i from 0 <= i < 20:
              self.neigh_x[i] = 0
              self.neigh_y[i] = 0
              self.neigh_states[i] = 0


     cdef object neighbors(self, object address):
          """Produce a list of addresses for all neighbours of a cell.

          address ---> a Python n-tuple, the address of a cell in the grid
          return  -->> a Python list of Python n-tuples, consisting of all
                       of the cell's neighbours"""
        
          raise NotImplementedError

     def  py_neighbors(self, object address):
          """Python wrapper for the C method self.neighbors

          address ---> a Python n-tuple, the address of a cell in the grid
          return  -->> a Python list of Python n-tuples, consisting of all
                       of the cell's neighbours"""

          return self.neighbors(address)



     # The following are support functions for doing computations on
     # neighborhoods; these need not be overridden for derived classes.


     cdef object states(self, object address):
          """Produce  a list of all the cell's neighbours' present state.        

          address ---> a Python n-tuple, the address of a cell in the grid
          return  -->> a Python list of integers: the states of all neighbouring
                       cells ordered according to self.neighbors

          This depends on the C function Topology.get."""

          cdef object states, neighbors
          cdef int neighbor
          neighbors = self.neighbors(address)
          states = []                              # initialise an empty list
          for neighbor from 0 <= neighbor < self.neighborhood:
              states.append(self.topology.get(neighbors[neighbor]))
          return states

     def  py_states(self, object address):
          """Python wrapper for the C method self.states

          address ---> a Python n-tuple, the address of a cell in the grid
          return  -->> a Python list of integers: the states of all neighbouring
                       cells ordered according to self.neighbors"""

          return self.states(address)




     cdef int reduce(self, object address, object function, int initial):
          """Perform a reduction operation on all neighbours' states.        

          address  ---> a Python n-tuple, the address of a cell in the grid
          function ---> a Python binary function
          initial  ---> an integer, an initial value
          return   -->> an integer

          The function is applied reccursively to all neighbour's states,
          starting at initial, to obtain a final integer value.
          This depends on the C function Topology.get.
          There is no inclusive version of this."""

          cdef object neighbors
          cdef int neighbor, reduce

          reduce = initial
          neighbors = self.neighbors(address)
          for neighbor from 0 <= neighbor < self.neighborhood:
              reduce = function(reduce, self.topology.get(neighbors[neighbor]))

          return reduce


     def  py_reduce(self, object address, object function, int initial):
          """Python wrapper for the C method self.reduce

          address  ---> a Python n-tuple, the address of a cell in the grid
          function ---> a Python binary function
          initial  ---> an integer, an initial value
          return   -->> an integer"""

          return self.reduce(address, function, initial)


     cdef int reduce2(self, int x, int y, object function, int initial):
          """Perform a reduction operation on all neighbours' states.        

          x        --->
          y        --->
          function ---> a Python binary function
          initial  ---> an integer, an initial value
          return   -->> an integer

          The function is applied reccursively to all neighbour's states,
          starting at initial, to obtain a final integer value.
          This depends on the C function Topology.get.
          There is no inclusive version of this."""

          raise NotImplementedError


     def  give_topology(self):
          return self.topology

     def  give_neighborhood(self):
          return self.neighborhood


cdef class VonNeumannNeighborhood(Neighborhood):
     """A two-dimensional neighborhood consisting of the adjoining cells
     in the 4 cardinal directions only."""

    
     def  __init__(self, GridTopology topology, int neighborhood):
          """Override Neighborhood.__init__."""
        
          assert neighborhood == 4
          Neighborhood.__init__(self, topology, neighborhood)
     
     
     cdef void neighbors2(self, int x, int y):
          """Overrride Neighborhood.neighbors.
        
          x       ---> 
          y       ---> """

          # return the four cardinal neighbours

          self.neigh_x[0] = x+1
          self.neigh_y[0] = y

          self.neigh_x[1] = x
          self.neigh_y[1] = y+1

          self.neigh_x[2] = x-1
          self.neigh_y[2] = y
              
          self.neigh_x[3] = x
          self.neigh_y[3] = y-1


     def  give_neighbors2(self, object address):
          """Python wrapper for the C method self.neighbors

          address ---> a Python n-tuple, the address of a cell in the grid
          return  -->> a Python list of Python n-tuples, consisting of all
                       of the cell's neighbours"""

          cdef int i
          cdef object neighbors

          neighbors = []

          self.neighbors2(address[0],address[1])

          for i from 0 <= i < self.neighborhood:
              neighbors.append((self.neigh_x[i], self.neigh_y[i]))

          return neighbors




     cdef void states2(self, int x, int y):
          """Produce  a list of all the cell's neighbours' present state.        

          x       ---> 
          y       ---> 

          This depends on the C function Topology.get."""


          cdef int i
          self.neighbors2(x, y)
          for i from 0 <= i < 4:
              self.neigh_states[i] = self.topology.get2(self.neigh_x[i], self.neigh_y[i])


     def  give_states2(self, object address):
          """Python wrapper for the C method self.states

          address ---> a Python n-tuple, the address of a cell in the grid
          return  -->> a Python list of integers: the states of all neighbouring
                       cells ordered according to self.neighbors"""

          cdef int i
          cdef object states

          states = []

          self.states2(address[0],address[1])

          for i from 0 <= i < 4:
              states.append(self.neigh_states[i])

          return states


     cdef int reduce2(self, int x, int y, object function, int initial):
          """Perform a reduction operation on all neighbours' states.        

          x        --->
          y        --->
          function ---> a Python binary function
          initial  ---> an integer, an initial value
          return   -->> an integer

          The function is applied reccursively to all neighbour's states,
          starting at initial, to obtain a final integer value.
          This depends on the C function Topology.get.
          There is no inclusive version of this."""

          cdef object neighbors
          cdef int neighbor, reduce

          reduce = initial

          self.neighbors2(x, y)

          for i from 0 <= i < self.neighborhood:
              reduce = function(reduce, self.topology.get2(self.neigh_x[i],self.neigh_y[i]))

          return reduce


     def  py_reduce(self, object address, object function, int initial):
          """Python wrapper for the C method self.reduce

          address  ---> a Python n-tuple, the address of a cell in the grid
          function ---> a Python binary function
          initial  ---> an integer, an initial value
          return   -->> an integer"""

          return self.reduce2(address[0], address[1], function, initial)




# Maps (Topology + Neighborhood mixins)
#######################################

cdef class Map:
     """This is a topology with a neighborhood system thrown in."""

     cdef Topology topology
     cdef Neighborhood nsystem
     cdef object size
     cdef public int dimension, background, neighborhood
     cdef public int length, height, width

     def  __init__(self, topology, nsystem):
          """Create a general Map object.

          topology ---> a birdcage Topology object
          nsystem  ---> a birdcage Neighborhood object"""

          self.topology = topology
          self.size = topology.size
          self.dimension = topology.dimension
          if self.dimension == 2:
              self.width = topology.width
              self.height = topology.height
          self.background = topology.background
          self.nsystem = nsystem
          assert nsystem.give_topology() == topology
          self.neighborhood = nsystem.neighborhood
          

     cdef object clone(self):
          """Make a morphologically identical copy of the grid.

          return -->> a birdcage Map object

          This is intended for cellular automata which require a working
          copy of themselves, such as synchronous automata (the most
          common kind)."""

          return Map(self.topology, self.nsystem)

     def  py_clone(self):

          return self.clone()


     def  py_get(self, object address):
          """A Python wrapper for the C function topology.get.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""
          
          return self.topology.get(address)


     def  py_get2(self, object address):
          """A Python wrapper for the C function topology.get.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""
          
          return self.topology.get2(address[0], address[1])



     def  py_set(self, object address, int state):
          """A Python wrapper for the C function topology.set.

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer"""

          self.topology.set(address, state)


     def  py_set2(self, object address, int state):
          """A Python wrapper for the C function topology.set.

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer"""

          self.topology.set2(address[0], address[1], state)


# Rule
########################################################################


cdef class Rule:
     """The rule is an optional mixin class (intended to be mixed in
     with an Automaton) which allows implementation of generic rules
     without reference to dimensionality, topology, neighborhood, or
     any combination thereof.  Rules, when used, include a populate
     method, and a rule method; the rule method is the same as the
     Automaton.rule method (which implements state transitions); the
     populate method is called once when the automaton is initialised
     and can, say, initialise lookup tables that the rule method relies
     upon."""

     cdef Map map
     cdef Topology topology
     cdef Neighborhood nsystem
     cdef object function


     def  __init__(self, Map map, object function):
          """Create a Rule object."""
        
          self.map = map
          self.topology = self.map.topology
          self.nsystem = self.map.nsystem
          self.function = function


     cdef void populate(self):
          """Initialise information needed to calculate rules.
          For instance: a lookup table."""
        
          pass


     cdef int rule(self, object address):
          """The main state transition function, prepackaged as a Rule."""
        
          raise NotImplementedError # purely abstract


     cdef int rule2(self, int x, int y):
          """The main state transition function, prepackaged as a Rule."""
        
          raise NotImplementedError # purely abstract



     def  py_get(self, object address):
          """A Python wrapper for the C function topology.get.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""
          
          return self.topology.get(address)


     def  py_get2(self, object address):
          """A Python wrapper for the C function topology.get.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""
          
          return self.topology.get2(address[0], address[1])


     def  py_set(self, object address, int state):
          """A Python wrapper for the C function topology.set.

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer"""

          self.topology.set(address, state)


     def  py_set2(self, object address, int state):
          """A Python wrapper for the C function topology.set.

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer"""

          self.topology.set2(address[0], address[1], state)


cdef class ReductionRule(Rule):
     """A reduction rule takes the list of states of a cell's neighbours
     and reduces them by running through the list and recursively
     applying a given binary function until a single result value is
     obtained."""



     def  __init__(self, Map map, object function):
          """Create a ReductionRule object and specify the reduction function.        
          function ---> a Python binary function"""

          Rule.__init__(self, map, function)


     cdef int rule(self, object address):
          """Apply the rule as a state transition fucntion at one cell.
        
          address ---> a Python n-tuple, an address in the grid
          return  -->> an integer, the result state at the address"""

          return self.nsystem.reduce(address, self.function, 0)


     cdef int rule2(self, int x, int y):
          """Apply the rule as a state transition fucntion at one cell.
        
          x       --->
          y       --->
          return  -->> an integer, the result state at the address"""

          return self.nsystem.reduce2(x, y, self.function, 0)


     def  py_rule(self, object address):
          """A Python wrapper for the C function rule.

          address ---> a Python n-tuple, an address in the grid
          return  -->> an integer, the result state at the address"""

          return self.rule2(address[0], address[1])


# Automata
####################################################################


cdef class Automaton:
     """An automaton joins together the map and a rule for the transition
     of one cell state to another every time unit. The number of possible
     states is held in the states attribute. The automaton also manages a
     (possibly empty) collection of agents that can move around the grid
     independently of the underlying cellular network."""

    
     cdef int possible_states, iteration
     cdef object agents
     cdef Map map
     cdef Topology topology
     cdef Neighborhood nsystem
     cdef Rule rule

    
     def  __init__(self, Map map, Rule rule):
          """Creates a new autmaton object.
          map  ---> an instance of one of the birdcage Map classes
          rule ---> an instance of the birdcage class Rule"""
        
          
          # some initial values:
          self.map = map
          self.topology = self.map.topology
          self.nsystem = self.map.nsystem
          self.rule = rule
          self.iteration = 0
          self.agents = []


     cdef int running(self):
          """Is the automaton still running?        
          return -->> 1"""
        
          return 1



     def  py_get2(self, object address):
          """A Python wrapper for the C function topology.get.

          address ---> a grid coordinate value in the form of a Python n-tuple
          return  -->> an integer"""
          
          return self.topology.get2(address[0], address[1])


     def  py_set2(self, object address, int state):
          """A Python wrapper for the C function topology.set.

          address ---> a grid coordinate value in the form of a Python n-tuple
          state   ---> an integer"""

          self.topology.set2(address[0], address[1], state)


     cdef void update(self):
          """Perform all state transitions for one time unit."""

          self.iteration = self.iteration + 1 # update the iteration counter
          for agent in self.agents:             # update all agents according
              agent.update()                   # to their own method
   

     def  py_update(self):
          """A wrapper for the C function update."""

          self.update()


     cdef void between(self):
          """Hook to run processes in-between transitions."""
        
          for agent in self.agents: # run the agents' own hook
              #agent.between()
              pass


     cdef void add(self, object agent):
          """Add a new agent to the system.        
          agent ---> an instance of the Agent class"""

          assert agent not in self.agents # check it is indeed new
          self.agents.append(agent)       # and write it in the agent list


     cdef void remove(self, object agent):
          """Remove an agent from the system.        
          agent ---> an instance of the Agent class"""
        
          assert agent in self.agents # check the agent exists
          self.agents.remove(agent)   # and remove it from the current list


# NOTE: If no Rule mixin is used, a rule for evaluating the cell transitions
# should be explicitly added here, starting as follows:
#    def rule(self, address): ...


cdef class SynchronousAutomaton(Automaton):
     """A synchronous automaton updates all cells simultaneously (that
     is, during a given update, no state transition will affect the
     transition of any other cell).  In order to accomplish this, a
     working copy of the map is generated at the beginning of the update
     process. The state transitions are then evaluated for each cell
     using the data from the original map, which doesn't change, and
     recorded on the working copy. Once all transitions have been
     computed, the original map can be discarded and the working copy
     becomes the new reality. This is probably the automaton you
     want to start from."""


     cdef Topology workMap
    
     def  __init__(self, Map map, Rule rule):
          """Create a SynchronousAutomaton object.

          map  ---> an instance of one of the birdcage Map classes
          rule ---> an instance of the birdcage Rule class"""
        
          Automaton.__init__(self, map, rule)
          self.workMap = self.topology.clone() # this is the working copy


     cdef void swap(self):
          """The working copy becomes the original map and viceversa
        
          The actual maps are identical; it is only the states of the
          cells, which are contained in the buffer lists, which need to
          be swapped."""
        
          self.topology, self.workMap = \
                         self.workMap, self.topology


     cdef void update(self):
          """Override Automaton.update."""
        
          # TODO: Generalise to n dimensions
        
          if self.map.dimension == 1: # start with 1-dimensional maps:
              pass
              #for x from 0 <= x < self.map.length: # run along the map's length
              #    address = (x,)               # picking each cell
              #    newCell = self.rule(address) # and applying the transition rule
              #    # in order to update its state in the working copy of the map
              #    self.workMap.set(address, newCell)

          elif self.map.dimension == 2: # now for 2-dimensional maps:
              for x from 0 <= x < self.map.width: # run along the width
                  for y from 0 <= y < self.map.height: # and height of the grid
                                                        # taking each cell,
                      newCell = self.rule.rule2(x, y) # apply transition rule
                      # and update its state in the working copy of the map                    
                      self.workMap.set2(x, y, newCell)

              for x from 0 <=x < self.map.width:
                  for y from 0 <= y < self.map.height:
                      state = self.workMap.get2(x, y)
                      self.topology.set2(x, y, state)

          else: # other dimensions not implemented yet

              raise NotImplementedError, "unsupported map dimensionality"

          #self.swap()            # the working copy becomes the original map
          Automaton.update(self) # update all agents and the iteration counter




cdef class TwoStateAutomaton(SynchronousAutomaton):
     """A two-state automaton is a synchronous automaton that has, not
     surprisingly, only two possible states.  They are typically
     referred to as dead and alive. NOTE: Remember if this is used without
     a Rule mixin, a self.rule(address) method must be provided."""

     def  __init__(self, Map map, Rule rule):
          """Create a TwoStateAutomaton object.

          map  ---> an instance of one of the birdcage Map classes
          rule ---> an instance of the birdcage Rule class"""
        
          Automaton.__init__(self, map, rule)
          self.possible_states = 2
          DEAD, ALIVE = range(self.possible_states)
          self.workMap = self.topology.clone() # this is the working copy
    

cdef class TwoStateReductionAutomaton(TwoStateAutomaton):
     """A two-state, synchronous automaton which evaluates cell
     transitions by means of a reduction rule."""

    
     def  __init__(self, Map map, ReductionRule rule):
          """Create a TwoStateReductionAutomaton object.

          map      ---> an instance of one of the birdcage Map classes
          rule     ---> an instance of the birdcage ReductionRule class"""
        
          TwoStateAutomaton.__init__(self, map, rule)
          #ReductionRule.__init__(self, function) # This is the Rule


cdef class Initializer:
     """An initializer simply sets up a grid with some particular starting
     conditions, prior to the beginning of the processing of the
     automaton."""

    
     def  __init__(self):
          """Create an Inizializer object."""

          pass
    

     cdef void initialize(self, Automaton automaton):
          """Initialise the grid.

          automaton ---> an instance of the birdcage Automaton class"""
        
          raise NotImplementedError


cdef class SeedInitializer(Initializer):
     """A seed initializer sets a predetermined number of cells in random
     positions in the grid in a single predetermined state."""
    

     cdef int count, state

     def  __init__(self, int count, int state):
          """Create a SeedInitializer object.

          count ---> an integer, the number of cells in the predetermined state
          state ---> an integer, the predetermined state"""
        
          Initializer.__init__(self)
          self.count = count
          self.state = state


     cdef void initialize(self, Automaton automaton):
          """Override Initializer.initialize

          automaton ---> an instance of the birdcage Automaton class"""

          cdef Map map
          cdef Topology topology
          cdef object seeds, address
        
          map = automaton.map
          topology = map.topology
          assert self.count < topology.cells # total number of cells cannot be exceeded
          seeds = [] # initialise an empty list
          for i from 0 <= i < self.count: # iterate as many times as there are seeds
              while 1:
                  address = topology.random() # pick a cell in the grid at random
                  if address in seeds:   # if it is already a seed in the list
                      continue           # then pick another cell
                  # when a new cell is found, set its state to self.state
                  topology.set2(address[0], address[1], self.state)
                  break # exit the while loop to proceed to the next seed
              # but first record the address of the last seed
              seeds.append(address)


     def  py_initialize(self, Automaton automaton):
          """A Python wrapper for the C function initialize."""

          self.initialize(automaton)      
