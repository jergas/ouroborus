# This module transforms a grid into a list and uploads it to a server

# At present, it is limited to 2-dimensional automata
# instances created by the birdcage engine, at a given iteration.

# It was written in Python 2.3.4 using birdcage 0.3.1 by Sat Tara Singh  
# Khalsa on January 12th 2007, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import xmlrpclib

class Uploader:

    def __init__(self):

        self.server = xmlrpclib.ServerProxy("http://linux.ajusco.upn.mx:8080")
        self.automaton = None
        self.size  = (0,)
        self.list  = []

    def makeList(self):

        list = []
        for y in range(self.size[1]):
            list.append([])
            for x in range(self.size[0]):
                list[y].append(self.automaton.py_get2((x,y)))
        self.list = list

    def upload(self):

        self.server.setGrid(self.list)
