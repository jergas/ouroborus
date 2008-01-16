# This module contains the agent abstract class and
# its derived classes

# It was written in Pyrex 0.9.3 on January 8th 2008
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5 

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


     def  __init__(self, N.Neighborhood_2D corporality, N.Neighborhood_2D sensoriality, int prana, object address):
          """Create a generic Agent_2D object
        
          corporality  ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          sensoriality ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          prana        ---> an integer
          foot         ---> a Python tuple, the address of a cell in the grid"""

          self.corporality = corporality
          self.sensoriality = sensoriality

          if self.corporality.topology != self.sensoriality.topology:
             raise E.ConflictingTopologyError(self.corporality.topology.name, self.sensoriality.topology.name)

          self.topology = self.corporality.topology
          self.prana = prana       
          self.name = "Abstract Agent"


     def  isAlive(self):
          """Return True if agent has positive prana, False otherwise

          return -->> Boolean"""
          
          return self.prana > 0


     cdef int pyx_isAlive(self):
          """Return True if agent has positive prana, False otherwise

          return -->> 1 or 0"""

          return self.prana > 0


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

          pass


####################################################################


cdef class Agent_2D(Agent):  
     """Base class for all agents based on a two-dimensional automaton."""


     def  __init__(self, N.Neighborhood_2D corporality, N.Neighborhood_2D sensoriality, int prana, object address):
          """Create a generic Agent_2D object
        
          corporality  ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          sensoriality ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          prana        ---> an integer
          foot         ---> a Python 2-tuple, the address of a cell in the grid"""

          Agent.__init__(self, corporality, sensoriality, prana, address)
          
          if self.topology.pyx_normalize(address) == -1:
               raise E.InvalidAddressError(address, self.topology.name)
 
          self.foot = address         
          self.name = "Agent 2-D"

