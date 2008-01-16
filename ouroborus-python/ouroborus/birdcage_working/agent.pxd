# This is a Pyrex definition file...look at the .pyx file for the full source


#################################################################################
# Imported Pyrex modules


cimport topology as T
cimport neighborhood as N


####################################################################
cdef class Agent:  
     """Abstract base class for all agents"""

     cdef N.Neighborhood_2D corporality
     cdef N.Neighborhood_2D sensoriality
     cdef T.Topology topology
     cdef int prana
     cdef object foot, name

     cdef int pyx_isAlive(self)
     cdef int pyx_tellPrana(self)
     cdef void pyx_gainPrana(self, int amount)
     cdef void pyx_losePrana(self, int amount)
     cdef void pyx_zeroPrana(self)
     cdef void pyx_update(self)


#################################################################################

cdef class Agent_2D(Agent):  
     """Base class for all agents based on a two-dimensional automaton."""

     cdef int pyx_isAlive(self)
     cdef int pyx_tellPrana(self)
     cdef void pyx_gainPrana(self, int amount)
     cdef void pyx_losePrana(self, int amount)
     cdef void pyx_zeroPrana(self)
     cdef void pyx_update(self)
