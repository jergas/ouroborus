# This module contains the Genome class and
# its derived classes

# It was written in Pyrex 0.9.6 on February 25th 2008
# by Jergas. Love is the Law, Love under Will!

# This Pyrex code has been compiled on an Ubuntu system
# using the gcc compiler, and run from Python 2.5 

# A Genome should contain all the information necesary
# to create an agent and animate it, as well as the
# information it needs to reproduce.

# For more information visit http://ouroborus.sf.net/


# Imported modules
####################################################################

import exceptions_birdcage as E




####################################################################



cdef class Genome:
     """Base class for the Genome of an Agent_2D"""

     def  __init__(self, object text, object table, int wordlength):
          """Create an instance of a Genome

          text       ---> a Python list of genetic symbols
          table      ---> a Python dictionary translating each word
                          into a string of executable Python code
          wordlength ---> an integer, the length of each word"""
 
          self.text = text
          self.table = table
          self.wordlength = wordlength


     cdef object pyx_readWord(self, int index):
          """Read a genetic word from the text

          index  -->> the starting point of the word in the text
          return -->> a genetic word, which is a string"""

          cdef int i
          cdef object word
          word = ""

          for i in range(self.wordlength):
              word = word + self.text[index + i]

          return word


     cdef object pyx_decode(self, object word):
          """Translate one genetic word through the table

          word   ---> a string of fixed length self.wordlength
          return -->> another string, executable Python code"""

          return self.table[word]


     def  parse(self):
          """Translate the entire text of the genome, word for word

          return -->> a Python string, a sequence of Python instructions"""

          return self.pyx_parse()


     cdef object pyx_parse(self):
          """Translate the entire text of the genome, word for word

          return -->> a Python string, a sequence of Python instructions"""

          cdef int i
          cdef object code
          code = ""

          for i in range(0,len(self.text),self.wordlength):
              code = code + self.pyx_decode(self.pyx_readWord(i)) + "\n"

          return code


     def incorporate(self, name):
         """Create a file (body) with the python code which is the parsed genome"""

         body = open(name, 'w')
         code = self.parse()
         body.write(code)
         body.close()