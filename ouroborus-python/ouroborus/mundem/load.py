# This module works the deserialisation of static data in a .mun 
# file, to provide basic load functionality to the mundem
# component of Project Ouroborus.

# At present, it is limited to unpickling 2-dimensional automata
# instances in the form of a Numeric array with appended information

# It was written in Python 2.3.4 using birdcage 0.3.1 by Sat Tara Singh  
# Khalsa on December 14 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!

import pickle

class Loader:
    
    def __init__(self):
        """The basic object which saves a copy of an automaton's map

        return    -->> None"""

        pass

    def loadPair(self,filename):
        """Store grid data as an array

        filename ---> a string representing a readable file object
        return   -->> a Python 2-tuple (dictionary, Numeric array)"""

        file = open(filename, "r")
        pair = pickle.load(file)
        file.close()
        return pair
