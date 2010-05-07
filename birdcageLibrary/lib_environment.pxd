# This is a Pyrex definition file...look at the .pyx file for the full source


#################################################################################
# Imported Pyrex modules


cimport topology as T
cimport neighborhood as N
from neighborhood cimport MooreNeighborhood
cimport rule
from rule cimport Rule_2D

#################################################################################

cdef class EnvironmentRule(Rule_2D):  
     """Conway's Game of Life rule. If the sum of a dead cell's neighbors
     is 3, the cell becomes alive.  If the sum of a live cell's neighbors
     is 2 or 3, the cell remains alive.  Otherwise, it dies."""
     

cdef class MooreNeighborhoodPlus(MooreNeighborhood):
     """Pyrex would not compile without this line (nutzzz isn't it?)"""