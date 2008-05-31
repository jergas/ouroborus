# This is a Pyrex definition file...look at the .pyx file for the full source


# Some limiting values
####################################################################
# This constant sets the maximum size for a grid along any of its axes.

cdef enum:
     caliber = 1000

#################################################################################

cdef class Topology:  
     """Abstract base class for all topologies"""

     cdef int dimension, background, cells
     cdef object size, zero, name

     cdef int pyx_isNormalized(self, object address)
     cdef object pyx_normalize(self, object address)

#################################################################################

cdef class GridTopology(Topology):
     """A two-dimensional, bounded topology consisting of a rectangular
     grid of cells, base class for 2D topologies"""

     cdef int border, width, height
     cdef int cell[caliber][caliber]

    
     cdef int pyx_isNormalized(self, object address)
     cdef object pyx_normalize(self, object address)
     cdef int normal_x1(self, int x1)
     cdef int normal_x2(self, int x2)
     cdef int pyx_get(self, int x1, int x2)
     cdef int pyx_get_nosafe(self, int x1, int x2)
     cdef int pyx_set(self, int x1, int x2, int state)
     cdef void pyx_set_nosafe(self, int x1, int x2, int state)


#################################################################################

cdef class ToroidTopology(GridTopology):
     """A two-dimensional, unbounded topology consisting of a rectangular
     grid of cells, where the top and bottom edges and the left and right
     edges have been 'glued together' (Pacman style)"""




     cdef int pyx_isNormalized(self, object address)
     cdef object pyx_normalize(self, object address)
     cdef int normal_x1(self, int x1)
     cdef int normal_x2(self, int x2)
     cdef int pyx_get(self, int x1, int x2)
     cdef int pyx_get_nosafe(self, int x1, int x2)
     cdef int pyx_set(self, int x1, int x2, int state)
     cdef void pyx_set_nosafe(self, int x1, int x2, int state)
