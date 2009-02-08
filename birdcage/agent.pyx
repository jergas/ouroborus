# This module contains the agent abstract class and
# its derived classes

# It was written in Pyrex 0.9.6 on January 8th 2008
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5.
# It has also been seen to compile successfully on
# Ubuntu's GNU gcc

# An Agent object is an autonomous virtual entity which
# roams on top of the underlying automaton and interacts
# with it, as well as with other agents, without being
# actually part of the cell grid.

# For more information visit <ouroborus.sf.net>


# Imported modules
####################################################################

import exceptions_birdcage as E




####################################################################



cdef class Agent:
     """Abstract base class for all agents"""


     def  __init__(self, object code, N.Neighborhood_2D corporality, N.Neighborhood_2D sensoriality, int prana, int mana, object address):
          """Create a generic Agent_2D object
        
          code         ---> a string which will bind with a birdcage Genome object
          corporality  ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          sensoriality ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          prana        ---> an integer
          mana         ---> an integer, a state of the automaton
          address      ---> a Python tuple, the address of a cell in the grid"""

          self.code = code
          self.corporality = corporality
          self.sensoriality = sensoriality

          if self.corporality.topology != self.sensoriality.topology:
             raise E.ConflictingTopologyError(self.corporality.topology.name, self.sensoriality.topology.name)

          self.topology = self.corporality.topology

          self.moira = None

          self.prana = prana
          self.mana = mana
          self.name = "Abstract Agent"


     def  isAlive(self):
          """Return True if agent has positive prana, False otherwise

          return -->> Boolean"""
          
          return self.prana > 0


     cdef int pyx_isAlive(self):
          """Return True if agent has positive prana, False otherwise

          return -->> 1 or 0"""

          return self.prana > 0


     def  tellCode(self):
          """Return the Agent's code string

          return -->> the Agent's code as a string"""

          return self.code


     def  tellPrana(self):
          """Return the amount of prana the Agent has

          return -->> the Agent's prana as an integer value"""

          return self.pyx_tellPrana()


     cdef int pyx_tellPrana(self):
          """Return the amount of prana the Agent has

          return -->> the Agent's prana as an integer value"""

          return self.prana


     def gainPrana(self, int amount):
          """Increase Agent's prana by a given amount)

          amount ---> the integer increase of prana
          return -->> None"""

          self.pyx_gainPrana(amount)


     cdef void pyx_gainPrana(self, int amount):
          """Increase Agent's prana by a given amount)

          amount ---> the integer increase of prana
          return -->> None"""

          self.prana = self.prana + amount


     def  losePrana(self, int amount):
          """Decrease Agent's prana by a given amount)

          amount ---> the integer decrease of prana
          return -->> None"""

          self.pyx_losePrana(amount)


     cdef void pyx_losePrana(self, int amount):
          """Decrease Agent's prana by a given amount)

          amount ---> the integer decrease of prana
          return -->> None"""

          self.prana = self.prana - amount
          if self.prana < 0:
             self.prana = 0


     def  zeroPrana(self):
          """Lose all prana; set it to zero

          return -->> None"""

          self.pyx_zeroPrana()


     cdef void pyx_zeroPrana(self):
          """Lose all prana; set it to zero

          return -->> None"""

          self.prana = 0


     def  update(self):
          """The agent does its thing, whatever it is

          return -->> None"""

          self.pyx_update()

    
     cdef void pyx_update(self):
          """The agent does its thing, whatever it is

          return -->> None"""

          self.prana = self.prana - 1

####################################################################


cdef class Agent_2D(Agent):  
     """Base class for all agents based on a two-dimensional automaton."""


     def  __init__(self, object code, N.Neighborhood_2D corporality, N.Neighborhood_2D sensoriality, int prana, int mana, object address):
          """Create a generic Agent_2D object
        
          code         ---> a string which will bind with a birdcage Genome object
          corporality  ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          sensoriality ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          prana        ---> an integer
          mana         ---> an integer, a state of the automaton
          address      ---> a Python 2-tuple, the address of a cell in the grid"""

          Agent.__init__(self, code, corporality, sensoriality, prana, mana, address)
          
          address = self.topology.normalize(address) 
          (self.x1, self.x2) = (address[0], address[1])
          self.directions = self.sensoriality.neighbors + 1
          self.facing = 0
          self.name = "Agent 2-D"


     def  tellAddress(self):
          """Return the agent's address on the grid

          return -->> a Python 2-tuple"""

          return (self.x1, self.x2) 


     def  tellCorporality(self):
          """Return a list with the grid addresses covered
          by the agent's corporality

          return -->> a Python list of 2-tuples"""

          cdef object address, addresses, neighbor, neighbors

          address = (self.x1, self.x2) 
          addresses = []
          neighbors = self.corporality.listNeighbors(address)
          if address not in neighbors:
              addresses.append(address)
          for neighbor in neighbors:
              addresses.append(neighbor)
          return addresses

     
     def  move(self, object address):
          """Move the agent to a new address

          address ---> a Python 2-tuple, an address on the grid"""

          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.topology.name)

          address = self.topology.normalize(address)
          self.pyx_move(address[0], address[1])


     cdef void pyx_move(self, int y1, int y2):
          """Move the agent to a new address

          x1 ---> the first integer coordinate value
          x2 ---> the second integer coordinate value"""

          self.x1 = self.topology.normal_x1(y1)
          self.x2 = self.topology.normal_x2(y2)


     def  tellDirections(self):
          """Return all the cells in the agent's sensoriality

          return -->> a Python list of addresses"""

          cdef int i
          cdef object directions

          directions = [(self.x1, self.x2)]
          for i from 0 <= i < (self.directions-1):
              directions.append(self.sensoriality.listNeighbors((self.x1, self.x2))[i])
          return directions


     def  tellFacing(self):
          """Return the cell which the agent is facing

          return -->> a Python 2-tuple"""

          cdef object facing

          facing = self.tellDirections()[self.facing]
          return self.topology.normalize(facing)


     def  changeFacing(self, int facing):
          """Change the direction in which the agent faces

          facing ---> an integer
          return -->> 1 if successful"""

          if self.pyx_changeFacing(facing) == -1:
              raise E.NotInNeighborhoodError(facing, self.sensoriality.name)
          return 1


     cdef int pyx_changeFacing(self, int facing):
          """Change the direction in which the agent faces

          facing ---> an integer
          return -->> 1 if successful, -1 otherwise"""

          if facing < 0 or facing >= self.directions:
              return -1
          else:
              self.facing = facing


     def  advance(self):
          """Move the agent in the direction it's facing

          return -->> True if the agent moved, False otherwise"""

          if self.facing == 0:
              return False
          else:
              self.pyx_advance()
              return True


     cdef int pyx_advance(self):
          """Move the agent in the direction it's facing"""

          cdef int y1, y2

          if self.facing == 0:
              return 0
          else:
              self.sensoriality.pyx_calculateNeighbors(self.x1, self.x2)
              y1 = self.sensoriality.neighbors_x1[self.facing-1] 
              y2 = self.sensoriality.neighbors_x2[self.facing-1] 
              self.pyx_move(y1, y2)
              return 1


     def  eatMana(self):
          """Eat prana from the underlying cell

          return -->> True if successful, False otherwise"""

          if self.pyx_eatMana() == 0:
              return False
          else:
              return True


     cdef int pyx_eatMana(self):
          """Eat prana from the underlying cell

          return -->> 1 if successful, 0 otherwise"""

          if self.topology.pyx_get(self.x1, self.x2) == self.mana:
              self.pyx_gainPrana(1)
              self.topology.pyx_set(self.x1, self.x2, self.topology.background)
              return 1
          else:
              return 0
