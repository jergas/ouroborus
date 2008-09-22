# This is a Pyrex definition file...look at the .pyx file for the full source


#################################################################################
# Imported Pyrex modules


cimport topology as T
cimport neighborhood as N
cimport genome as G


####################################################################
cdef class Agent:  
     """Abstract base class for all agents"""

     cdef N.Neighborhood_2D corporality
     cdef N.Neighborhood_2D sensoriality
     cdef T.GridTopology topology
     cdef int prana, mana
     cdef object code, name, moira

     cdef int pyx_isAlive(self)
     cdef int pyx_tellPrana(self)
     cdef void pyx_gainPrana(self, int amount)
     cdef void pyx_losePrana(self, int amount)
     cdef void pyx_zeroPrana(self)
     cdef void pyx_update(self)


#################################################################################

cdef class Agent_2D(Agent):  
     """Base class for all agents based on a two-dimensional automaton."""

     cdef int directions, facing, x1, x2

     cdef int pyx_isAlive(self)
     cdef int pyx_tellPrana(self)
     cdef void pyx_gainPrana(self, int amount)
     cdef void pyx_losePrana(self, int amount)
     cdef void pyx_zeroPrana(self)
     cdef void pyx_update(self)
     cdef void pyx_move(self, int y1, int y2)
     cdef int pyx_changeFacing(self, int facing)
     cdef int pyx_advance(self)
     cdef int pyx_eatMana(self)
