# This module contains the class Hare, which is part of the
# controller component of Project Ouroborus, and specifically
# acts to sustain a mundito

# At present, it runs finite iteration sequences with a number
# of different display modes

# It was written in Python 2.3.4 by Sat Tara Singh  
# Khalsa on December 18 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import ouroborus.controller.dialogue as dial

class Hare:
    """The provider aspect of the Hindu Trinity"""

    def __init__(self):
        """Create a mundito sustainment controller

        return -->> None"""

        self.brahm      = None
        self.ganesh     = None
        self.status     = "NIRGUNA"
        self.iterations = 0
        self.display    = "SNAPSHOT"
        self.frequency  = 0
        self.chrono     = None

    def sustain(self):
        """Operate a mundito automaton

        return -->> None"""

        while self.status == "JUGJUGA":
            self.interpretSetIterationsDialogue()
            if self.status != "NIRGUNA":
                self.interpretSetDisplayDialogue()
                self.prepareDisplay()
                self.iterate()
            self.interpretGoAtItAgainDialogue()
        return

    def pauseAtEndOfTime(self):
        """Perform world-shattering decisions after iteration

        return -->> None"""
        
        assert self.status is "NIRGUNA"
        self.interpretEndOfTimeDialogue()
     
    def interpretSetIterationsDialogue(self):
        """User chooses number of iterations to perform

        return -->> None"""

        user = dial.SetIterationsDialogue().cycle()
        if user[0] == 0:
            self.status = "NIRGUNA"
            return
        else:
            self.iterations = user[0]
            print "ready to calculate", self.iterations, "iterations"

    def interpretSetDisplayDialogue(self):
        """User defines a display mode

        return    -->> None"""

        user = dial.SetDisplayDialogue().cycle()

        if user == "snap":
            self.display = "SNAPSHOT"
        elif user == "strobe":
            self.display = "STROBOSCOPIC"
            self.frequency = dial.SetFrequencyDialogue().cycle()[0]
        elif user == "flick":
            self.display = "ANIMATION"

    def interpretGoAtItAgainDialogue(self):
        """User may end the cycle of sustainment

        return -->> None"""

        user = dial.GoAtItAgainDialogue().cycle()

        if user == "continue":
            self.status = "JUGJUGA"
        elif user == "conclude":
            self.status = "NIRGUNA"

    def prepareDisplay(self):
        """Prime the view for display

        return -->> None"""

        self.brahm.saraswati.renewView()

    def iterate(self):
        """Perform the specified number of iterations

        return -->> None"""

        for t in range(self.iterations):

            t = t+1
            self.chrono += 1
            print "time:", self.chrono

            self.brahm.automaton.py_update()

            if self.display == "SNAPSHOT":
                continue

            elif self.display == "ANIMATION":
                self.brahm.saraswati.updateView()

            elif self.display == "STROBOSCOPIC" and t%self.frequency == 0:
                self.brahm.saraswati.updateView()

        if self.display == "SNAPSHOT":
            self.brahm.saraswati.renewView()

        print "sequence of iterations completed"

    def interpretEndOfTimeDialogue(self):
        """User decides next operation to perform

        return -->> None"""

        user = dial.EndOfTimeDialogue().cycle()

        if user == "iterate":
            self.status = "JUGJUGA"
        elif user == "save":
            self.ganesh.archive(self.chrono)
            self.interpretEndOfTimeDialogue()
        elif user == "upload":
            self.ganesh.upload()
            self.interpretEndOfTimeDialogue()
        elif user == "clone":
            self.ganesh.clone()
            self.interpretEndOfTimeDialogue()
        elif user == "annihilate":
            return

                

