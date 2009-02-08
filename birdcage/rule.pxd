# This is a Pyrex definition file...look at the .pyx file for the full source


#################################################################################
# Imported Pyrex modules


cimport topology as T
cimport neighborhood as N


####################################################################
cdef class Rule_2D:  
     """Abstract base class for all two-dimensional transition rules"""

     cdef N.Neighborhood_2D neighborhood
     cdef object param
     cdef object name

     cdef pyx_apply(self, int x1, int x2)
     cdef pyx_applyToTarget(self, int x1, int x2, T.GridTopology target)

#################################################################################

cdef class ReductionRule(Rule_2D):
     """This rule applies a binary function recursively onto a cell's
     neighbors"""

     cdef pyx_apply(self, int x1, int x2)
     cdef pyx_applyToTarget(self, int x1, int x2, T.GridTopology target)

#################################################################################

cdef class ConwayRule(Rule_2D):  
     """Conway's Game of Life rule. If the sum of a dead cell's neighbors
     is 3, the cell becomes alive.  If the sum of a live cell's neighbors
     is 2 or 3, the cell remains alive.  Otherwise, it dies."""

     cdef pyx_apply(self, int x1, int x2)
     cdef pyx_applyToTarget(self, int x1, int x2, T.GridTopology target)
