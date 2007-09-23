# This module downloads a list and uses it to populate a mundito

# At present, it is limited to 2-dimensional automata
# instances created by the birdcage engine, at a given iteration.

# It was written in Python 2.3.4 using birdcage 0.3.1 by Sat Tara Singh  
# Khalsa on January 12th 2007, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import xmlrpclib

class Downloader:

    def __init__(self):

        self.server = xmlrpclib.ServerProxy("http://linux.ajusco.upn.mx:8080")
        self.automaton = None
        self.size  = (0,)
        self.list  = []

    def getList(self):

        self.list = self.server.getGrid()

    def setSize(self):
        y = len(self.list)
        x = len(self.list[0])
        self.size = (x,y)

    def clone(self):

        for y in range(self.size[1]):
            for x in range(self.size[0]):
                self.automaton.py_set2((x,y),self.list[y][x])

                
