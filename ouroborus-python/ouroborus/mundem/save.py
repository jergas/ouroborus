# This module deals with the serialisation of static data on 
# a mundito grid which is a basic functionality of the mundem
# component of Project Ouroborus.

# At present, it is limited to pickling 2-dimensional automata
# instances created by the birdcage engine, at a given iteration.

# It was written in Python 2.3.4 using birdcage 0.3.1 by Sat Tara Singh  
# Khalsa on December 12 2006, Day of Guadalupe, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import Numeric
import pickle

class Saver:
    
    def __init__(self):
        """The basic object which saves a copy of an automaton's map

        sustainer ---> a hare controller object"""

        self.iteration = None
        self.filename  = ""
        self.size      = (0,)
        self.automaton = None

    def makeArray(self):
        """Store grid data as an array

        return -->> a Numeric array"""
        #TODO: Add flexibility to this function: allow subspaces to be saved

        array = Numeric.zeros(self.size)
        for y in range(self.size[1]):
            for x in range(self.size[0]):
                array[x,y] = self.automaton.py_get2((x,y))
        return array

    def makeDict(self):
        """Store additional information in a dictionary

        return -->> a Python dictionary"""

        dict = {}
        return dict

    def dump(self, dict, array):
        """Pickle a dictionary and array into a predetermined file

        dict   ---> a Python dictionary
        array  ---> a Numeric array
        return -->> None""" 

        pair = (dict,array)
        file = open(self.filename,"w")
        pickle.dump(pair,file)
        file.close()

