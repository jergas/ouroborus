# This is a Pyrex definition file...look at the .pyx file for the full source

####################################################################

# Imported Pyrex modules


cimport topology as T
cimport neighborhood as N
cimport rule as R
cimport agent as A


####################################################################

cdef class Automaton_2D:  
     """Abstract base class for all two-dimensional automata"""
 
     cdef T.GridTopology topology
     cdef N.Neighborhood_2D neighborhood
     cdef R.Rule_2D rule
     cdef int states
     cdef object agents, name

     cdef void pyx_addAgent(self, A.Agent_2D agent)
     cdef void pyx_removeAgent(self, A.Agent_2D agent)
     cdef int pyx_update(self)

####################################################################

cdef class AsynchronousAutomaton_2D(Automaton_2D):  
     """A 2-D automaton in which the state transitions are applied
     at the same time as they are calculated, on a cell per cell
     basis"""

     cdef void pyx_addAgent(self, A.Agent_2D agent)
     cdef void pyx_removeAgent(self, A.Agent_2D agent)
     cdef int pyx_update(self)

####################################################################

cdef class SynchronousAutomaton_2D(Automaton_2D):  
     """A 2-D automaton in which the state transitions are applied
     simultaneously throughout the grid"""

     cdef T.GridTopology workgrid

     cdef void pyx_addAgent(self, A.Agent_2D agent)
     cdef void pyx_removeAgent(self, A.Agent_2D agent)
     cdef int pyx_update(self)
