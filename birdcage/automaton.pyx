# This module contains the automaton abstract class and
# its derived classes

# It was written in Pyrex 0.9.6 on January 8th 2008
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5.
# It has also been seen to compile successfully on
# Ubuntu's GNU gcc

# An Automaton is the highest level working object of the
# birdcage engine. It includes a neighborhood system with
# a topology, a transition rule for updates, and a collection
# of free-roaming agents.

# For more information visit <ouroborus.sf.net>


# Imported modules
####################################################################

import exceptions_birdcage as E




####################################################################



cdef class Automaton_2D:  
     """Abstract base class for all two-dimensional automata"""


     def  __init__(self, R.Rule_2D rule):
          """Create a generic Automaton_2D object
        
          rule  ---> a birdcage Rule_2d object with its respective
                     two-dimensional neighborhood system and topology"""

          self.rule = rule
          self.neighborhood = rule.neighborhood
          self.topology = rule.neighborhood.topology
          self.agents = []
          self.states = 0
          self.name = "Abstract Automaton 2-D"


     def  returnTopology(self):
          """Return the automaton's underlying topology object

          return -->> a birdcage topology instance"""

          return self.topology


     def  addAgent(self, A.Agent_2D agent):
          """Add an agent to the running list of agents

          agent  ---> a birdcage Agent_2D object
          return -->> None"""

          self.pyx_addAgent(agent)


     cdef void pyx_addAgent(self, A.Agent_2D agent):
          """Add an agent to the running list of agents

          agent  ---> a birdcage Agent_2D object
          return -->> Null"""

          if agent.topology != self.topology:
              raise E.ConflictingTopologyError(agent.topology.name, self.topology.name)

          self.agents.append(agent)


     def  removeAgent(self, A.Agent_2D agent):
          """Remove an agent from the running list of agents

          agent  ---> a birdcage Agent_2D object
          return -->> Null"""

          self.pyx_removeAgent(agent)


     cdef void pyx_removeAgent(self, A.Agent_2D agent):
          """Remove an agent from the running list of agents

          agent  ---> a birdcage Agent_2D object
          return -->> Null"""

          if agent in self.agents:
              self.agents.remove(agent)


     def  update(self):
          """Perform an entire state transition cycle

          return -->> population"""

          return self.pyx_update()


     cdef int pyx_update(self):
          """Perform an entire state transition cycle

          return -->> Null"""

          pass


     def  setStates(self, states):
          """Set the number of states in the automaton

          states ---> an integer
          return -->> None"""

          self.states = states


     def  tellPopulation(self):
          """Return the number of live agents

          return -->> an integer"""

          return len(self.agents)


     def  tellAgents(self):
          """Return the list of agents on the automaton

          return -->> a Pythoh list of Agent_2D's"""

          return self.agents


     def  tellAgentAddresses(self):
          """Return all agent's addresses as a list

          return -->> a Python list of 2-tuples"""

          cdef object addresses 
          cdef A.Agent_2D agent

          addresses = []

          for agent in self.agents:
              addresses.append(agent.tellAddress())

          return addresses


     def  get(self, object address):
          
          return self.topology.get(address)


     def  set(self, object address, int state):

          self.topology.set(address, state)

####################################################################


cdef class AsynchronousAutomaton_2D(Automaton_2D):  
     """A 2-D automaton in which the state transitions are applied
     at the same time as they are calculated, on a cell per cell
     basis"""


     def  __init__(self, R.Rule_2D rule):
          """Create an AsynchronousAutomaton_2D object
        
          rule  ---> a birdcage Rule_2d object with its respective
                     two-dimensional neighborhood system and topology"""

          Automaton_2D.__init__(self, rule)
          self.name = "Asynchronous Automaton 2-D"


     cdef int pyx_update(self):
          """Override Automaton.pyx__update

          return -->> Null"""

          cdef int x1, x2
          cdef int population
          population = 0

          for  0 <= x1 < self.topology.size[0]:
              for  0 <= x2 < self.topology.size[1]:
                  population = population + self.rule.pyx_apply(x1, x2)

          Automaton_2D.pyx_update(self)

          return population

####################################################################


cdef class SynchronousAutomaton_2D(Automaton_2D):  
     """A 2-D automaton in which the state transitions are applied
     simultaneously throughout the grid"""


     def  __init__(self, R.Rule_2D rule):
          """Create an SynchronousAutomaton_2D object
        
          rule  ---> a birdcage Rule_2d object with its respective
                     two-dimensional neighborhood system and topology"""

          Automaton_2D.__init__(self, rule)
          self.name = "Synchronous Automaton 2-D"
          self.workgrid = self.topology.clone()


     cdef int pyx_update(self):
          """Override Automaton_2D.pyx__update

          return -->> population"""

          cdef int x1, x2
          cdef int population
          population = 0

          for 0 <= x1 < self.topology.size[0]:
              for 0 <= x2 < self.topology.size[1]:
                  population = population + self.rule.pyx_applyToTarget(x1, x2, self.workgrid)

          (self.topology, self.workgrid) = (self.workgrid, self.topology)
          self.neighborhood.topology = self.topology
          self.rule.neighborhood.topology = self.topology

          Automaton_2D.pyx_update(self)

          return population
