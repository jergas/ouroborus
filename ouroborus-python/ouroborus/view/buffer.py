# This module contains the class Buffer, which is basically a
# matrix which buffers a mundito grid for the purpose of feeding
# the display with relevant information.

# At present, it is limited to 2-state, 2-dimensional birdcage
# cellular automata.

# The Numeric library is no longer being maintained, and should
# be replaced by numarray.

# It was written in Python 2.3.4 using the module Numeric 24.2
# by Sat Tara Singh Khalsa on December 18 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import Numeric as N

class Buffer:
    """Stores the grid's information needed for visual display"""

    def __init__(self,size,automaton,colors):
        """Create a buffering Array

        size      ---> an n-tuple
        automaton ---> a birdcage automaton
        colors    ---> a dictionary linking automaton states to rpg 3-tuples
        return    -->> None"""

        assert len(size) <= 3
        order = []
        for i in range(len(size)):
            order.append(size[i])
        order.append(3)

        self.size = size
        (self.width,self.height) = self.size
        self.array = N.zeros(tuple(order))
        self.automaton = automaton
        self.colors = colors
        
    def update(self):
        """Update the buffer

        return -->> None"""

        for x in range(self.width):
            for y in range(self.height):
                self.array[x,y] = self.colors[self.automaton.py_get2((x,y))]
