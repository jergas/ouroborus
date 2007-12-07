# This is a Pyrex definition file...look at the .pyx file for the full source


# Some limiting values
####################################################################
# This constant sets the maximum number of neighbors in a
# neighborhood

cdef enum:
     capacity = 20

####################################################################
# Imported Pyrex modules


cimport topology as T


####################################################################

cdef class Neighborhood_2D:
     """Base class for all two-dimensional neighborhoods"""

     cdef T.GridTopology topology
     cdef int neighbors
     cdef object name
     cdef int neighbors_x1[capacity]
     cdef int neighbors_x2[capacity]
     cdef int neighbors_st[capacity]


     cdef void pyx_calculateNeighbors(self, int x1, int x2)
     cdef void pyx_calculateStates(self, int x1, int x2)
     cdef int pyx_reduceStates(self, int x1, int x2, object function, int initialv)


####################################################################

cdef class VonNeumannNeighborhood(Neighborhood_2D):
     """Base class for all two-dimensional neighborhoods,
     still abstract"""


     cdef void pyx_calculateNeighbors(self, int x1, int x2)
     cdef void pyx_calculateStates(self, int x1, int x2)
     cdef int pyx_reduceStates(self, int x1, int x2, object function, int initialv)
