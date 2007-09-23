# Narayan is the background controller for all other processes;
# it coordinates the other classes which together comprise the
# controller component of Project Ouroborus

# At present, it only launches and reads the main dialogue

# It was written in Python 2.3.4 by Sat Tara Singh  
# Khalsa on December 16 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import ouroborus.controller.brahm
import ouroborus.controller.hare
import ouroborus.controller.shiv
import ouroborus.controller.ganesh 
import ouroborus.controller.dialogue as dial


class Narayan:
    """The Lord of the Universe, the Trascendent One"""

    def originateCosmos(self):
        """Primitive function: call the main dialogue

        return -->> None"""

        print "Prepare to originate cosmos..."
        self.brahm = ouroborus.controller.brahm.Brahm()
        print "brahm comes into existence"
        self.hare = ouroborus.controller.hare.Hare()
        print "hare comes into existence"
        self.shiv = ouroborus.controller.shiv.Shiv()
        print "shiv comes into existence"
        self.ganesh = ouroborus.controller.ganesh.Ganesh()
        print "ganesh comes into existence"
        self.brahm.ganesh = self.ganesh
        self.hare.ganesh  = self.ganesh

        self.interpretMainDialogue()

    def interpretMainDialogue(self):
        """Accept user input from MainDialogue

        return -->> None"""

        while 1:
            user = dial.MainDialogue().cycle()

            if user == "creation":
                self.causeCreation()
                print "creation process finished...brahm enters contemplation"
                self.hare.brahm = self.brahm
                print "in fact, brahm becomes an attribute of hare"
                self.hare.chrono = 0
                self.hare.status = "JUGJUGA"
                self.causeSustainment()
                print "the lord hare chooses to step outside"
                self.shiv.brahm = self.brahm
                self.shiv.hare = self.hare
                print "control handed over to shiv"
                self.causeAnnihilation()

            elif user == "retrieval":
                iteration = self.causeRetrieval()
                self.causeRecreation()
                self.causeRepopulation()
                self.hare.brahm = self.brahm
                print "recreation process is finished, hare comes into action"
                self.hare.prepareDisplay()
                self.hare.chrono = iteration
                print "times come into play again at t =",iteration
                self.hare.status = "JUGJUGA"
                self.causeSustainment()
                print "hare no longer sustains brahm's creation"
                self.shiv.brahm = self.brahm
                self.shiv.hare = self.hare
                print "control handed over to shiv"
                self.causeAnnihilation()

            elif user == "exit":
                self.terminateCosmos()
                break

        print "cosmos terminated"
        return

    def causeCreation(self):
        """Order brahm to create a mundito

        return -->> None"""

        self.brahm.create()

    def causeRecreation(self):
        """Order brahm to recreate a mundito from data stored by ganesh

        return -->> None"""

        self.brahm.recreate()


    def causeSustainment(self):
        """Order hare to iterate a mundito

        return -->> None"""

        while self.hare.status == "JUGJUGA":
            self.hare.sustain()
            self.hare.pauseAtEndOfTime()


    def causeRetrieval(self):
        """Order ganesh to retrieve a mundito archive

        return -->> an integer, the iteration number"""

        return self.ganesh.retrieve()

    def causeRepopulation(self):
        """Order ganesh to repopulate a mundito from stored data

        return -->> None"""

        self.ganesh.repopulate()

    def causeAnnihilation(self):
        """Order shiv to annihilate a mundito

        return -->> None"""

        self.shiv.annihilate()

    def terminateCosmos(self):
        """End program

        return -->> None"""
        
        del self.brahm.saraswati; print "saraswati deleted"
        del self.brahm; print "brahm deleted"
        del self.hare; print "hare deleted"
        del self.shiv; print "shiv deleted"
        del self.ganesh; print "ganesh deleted"
        
        return


