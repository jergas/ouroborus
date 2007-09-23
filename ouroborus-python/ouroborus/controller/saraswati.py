# This module contains the class Saraswati, which is part of the
# controller component of Project Ouroborus, and specifically
# acts to orchestrate the view

# At present, it simply creates and calls the screen and buffer
# objects of view

# It was written in Python 2.3.4 by Sat Tara Singh  
# Khalsa on December 18 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import ouroborus.view.buffer as buffer
import ouroborus.view.screen as screen
import ouroborus.controller.dialogue as dial

class Saraswati:
    """The Shakti aspect of Brahm, the Goddess of Arts"""

    def __init__(self):
        """Create a view controller

        return -->> None"""

        self.ganesh    = None
        self.dimension = 0
        self.size      = (0,)
        self.automaton = None
        self.allStates = 0
        self.name      = ""
        self.buffer    = None
        self.colors    = {}
        self.view      = None
        
    def createView(self):
        """Create a visual display

        return -->> None"""

        colors = self.interpretChooseColorsDialogue()
        self.ganesh.colors = self.colors
        print "choice of colors recorded by ganesh"
        self.buffer = buffer.Buffer(self.size,self.automaton,self.colors)
        print "display buffer is ready for operation"

    def recreateView(self):
        """Recreate a visual display from stored data

        return -->> None"""

        self.colors = self.ganesh.colors
        print "choice of colors remembered by ganesh"
        self.buffer = buffer.Buffer(self.size,self.automaton,self.colors)
        print "display buffer is ready for operation"

    def renewView(self):
        """Renew the display, leaving it ready to run

        return -->> None"""

        if self.view: del self.view
        self.view = screen.Screen(self.size,self.buffer,self.name)
        self.updateView()

    def updateView(self):
        """Update the visual display

        return -->> None"""

        self.buffer.update()
        self.view.update()       

    def interpretChooseColorsDialogue(self):
        """User chooses colors for the automaton's states

        return -->> a dictionary linking automaton states to rpg 3-tuples"""

        user = dial.ChooseColorsDialogue(self.allStates).cycle()
        colors = {}
        for i in range(self.allStates):
            colors[i] = user[i]
        self.colors = colors
        print "rgb colours for automaton determined"

        
