# This is a Pyrex definition file...look at the .pyx file for the full source


#################################################################################
# Imported Pyrex modules





####################################################################
cdef class Genome:
     """Base class for the Genome of an Agent_2D"""

     cdef object text, table
     cdef int wordlength

     cdef object pyx_readWord(self, int index)
     cdef object pyx_decode(self, object word)
     cdef object pyx_parse(self)
     