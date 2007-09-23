# This module contains the class Shiv, which is part of the
# controller component of Project Ouroborus, and specifically
# acts to destroy a mundito

# At present, it simply wipes out a whole 2-dimensional mundito
# leaving no trace.

# It was written in Python 2.3.4 by Sat Tara Singh  
# Khalsa on December 29 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


class Shiv:
    """The destroyer aspect of the Hindu Trinity"""

    def __init__(self):
        """Create a mundito destruction controller

        return -->> None"""

        self.hare = None

    def annihilate(self):
        """Utterly destroy a mundito automaton

        return -->> None"""

        print "ready to commence destruction"
        automaton = self.brahm.automaton
        size = self.brahm.size
        self.brahm.saraswati.colors[0]=(120,40,0)
        for x in range(size[0]):
            for y in range(size[1]):
                automaton.py_set2((x,y),0)
        self.brahm.saraswati.renewView()
        del self.brahm.automaton
        del self.brahm.saraswati.buffer
        print "destruction complete"
        
