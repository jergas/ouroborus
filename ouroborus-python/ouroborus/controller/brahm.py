# This module contains the class Brahm, which is part of the
# controller component of Project Ouroborus, and specifically
# acts to create a mundito

# At present, it is limited to a test automaton with a few
# initialization options

# It was written in Python 2.3.4 by Sat Tara Singh  
# Khalsa on December 17 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import ouroborus.birdcage as ca
import ouroborus.controller.dialogue as dial
import ouroborus.controller.saraswati
import operator

class Brahm:

    def __init__(self):
        """Create a mundito creation controller

        return -->> None"""

        self.ganesh    = None
        self.dimension = 0
        self.size      = (0,)
        self.topology  = None
        self.topologyLabel = ""
        self.nsystem   = None
        self.nsystemLabel = ""
        self.map       = None
        self.rule      = None
        self.ruleLabel = ""
        self.automaton = None
        self.automatonLabel = ""
        self.allStates = 0
        self.name      = ""
        self.saraswati = None

    def create(self):
        """Create a mundito automaton

        return -->> None"""

        self.interpretChooseDimensionDialogue()
        self.interpretChooseSizeDialogue()
        self.interpretChooseTopologyDialogue()
        self.interpretChooseNSystemDialogue()
        self.makeMap()
        self.interpretChooseAutomatonDialogue()
        self.interpretChooseInitializationMethodDialogue()
        self.interpretPickNameDialogue()
        self.invokeGanesh()
        self.invokeSaraswati()
        self.saraswati.ganesh = self.ganesh
        self.saraswati.createView()

    def recreate(self):
        """Recreate a mundito automaton from stored data

        return -->> None"""

        self.recreateDimension()
        self.recreateSize()
        self.recreateTopology()
        self.recreateNSystem()
        self.makeMap()
        self.recreateAutomaton()
        self.recreateName()
        
        self.invokeSaraswati()
        self.saraswati.ganesh = self.ganesh
        self.saraswati.recreateView()
        self.invokeGanesh()

     
    def interpretChooseDimensionDialogue(self):
        """User chooses the grid dimension

        return -->> None"""

        user = dial.ChooseDimensionDialogue().cycle()
        self.dimension = user
        print "dimension", self.dimension, "established"

    def recreateDimension(self):
        """Set the dimension from stored data

        return -->> None"""

        shabd = self.ganesh.dimension
        self.dimension = shabd
        print "dimension", self.dimension, "established"

    def interpretChooseSizeDialogue(self):
        """User chooses the grid size
        
        return    -->> None"""

        user = dial.ChooseSizeDialogue(self.dimension).cycle()
        self.size = tuple(user)
        print "size", self.size, "established"

    def recreateSize(self):
        """Set the size from stored data
        
        return    -->> None"""

        shabd = self.ganesh.size
        self.size = shabd
        print "size", self.size, "established"

    def interpretChooseTopologyDialogue(self):
        """User defines a topology for the mundito grid

        return    -->> None"""

        user = dial.ChooseTopologyDialogue(self.dimension).cycle()

        if user == "2dToroid":
            assert len(self.size) == 2
            self.topology = ca.ToroidTopology(self.size,2,0)
            self.topologyLabel = "2dToroid"
            print "Toroid grid created"

    def recreateTopology(self):
        """Set the topology from stored data

        return    -->> None"""

        shabd = self.ganesh.topologyLabel

        if shabd == "2dToroid":
            assert len(self.size) == 2
            self.topology = ca.ToroidTopology(self.size,2,0)
            self.topologyLabel = "2dToroid"
            print "Toroid grid created"

    def interpretChooseNSystemDialogue(self):
        """User defines a neighborhood system for the mundito grid

        return    -->> None"""

        user = dial.ChooseNSystemDialogue(self.dimension).cycle()

        if user == "2dVonNeumann":
            assert self.dimension == 2
            self.nsystem = ca.VonNeumannNeighborhood(self.topology,4)
            self.nsystemLabel = "2dVonNeumann"
            print "Von Neumann neighborhoods selected"

    def recreateNSystem(self):
        """Set the neighborhood system from stored data

        return    -->> None"""

        shabd = self.ganesh.nsystemLabel

        if shabd == "2dVonNeumann":
            assert self.dimension == 2
            self.nsystem = ca.VonNeumannNeighborhood(self.topology,4)
            self.nsystemLabel = "2dVonNeumann"
            print "Von Neumann neighborhoods selected"

    def makeMap(self):
        """Create a mundito map

        return   -->> None"""

        self.map = ca.Map(self.topology,self.nsystem)
        print "map of size",
        for i in range(self.dimension - 1):
            print self.size[i],"by",
        print self.size[self.dimension - 1], "created"

    def interpretChooseAutomatonDialogue(self):
        """User defines an automaton class

        return -->> None"""

        user = dial.ChooseAutomatonDialogue().cycle()

        if user == "2stateReduction":
            self.interpretChooseReductionRuleDialogue()
            self.automaton = ca.TwoStateReductionAutomaton(self.map,self.rule)
            self.automatonLabel = "2stateReduction"
            self.allStates = 2
            print "2-state reduction rule synchronous automaton created"

    def recreateAutomaton(self):
        """Recreate the automaton from stored data

        return -->> None"""

        shabd = self.ganesh.automatonLabel

        if shabd == "2stateReduction":
            self.recreateReductionRule()
            self.automaton = ca.TwoStateReductionAutomaton(self.map,self.rule)
            self.automatonLabel = "2stateReduction"
            assert self.ganesh.allStates is 2
            self.allStates = 2
            print "2-state reduction rule synchronous automaton created"


    def interpretChooseReductionRuleDialogue(self):
        """User defines a reduction rule

        return -->> None"""

        user = dial.ChooseReductionRuleDialogue().cycle()

        if user == "xor":
            self.rule = ca.ReductionRule(self.map,operator.xor)
            self.ruleLabel = "xor"
            print "Parity reduction rule selected"

    def recreateReductionRule(self):
        """Recreate a reduction rule from stored data

        return -->> None"""

        shabd = self.ganesh.ruleLabel

        if shabd == "xor":
            self.rule = ca.ReductionRule(self.map,operator.xor)
            self.ruleLabel = "xor"
            print "Parity reduction rule selected"

    def interpretChooseInitializationMethodDialogue(self):
        """User defines a method to initialise the automaton

        return -->> None"""
 
        user = dial.ChooseInitializationMethodDialogue().cycle()

        if user == "singleSpecific":
            address = tuple(dial.PickCellDialogue(self.size).cycle())
            self.automaton.py_set2(address,1)
            print "cell at address", address, "animated"

        elif user == "nRandom":
            seed = dial.PickIntegerDialogue().cycle()[0]
            ca.SeedInitializer(seed,1).py_initialize(self.automaton)
            print seed, "random cells animated"

        elif user == "blank":
            print "automaton remains homogenously dead"

    def interpretPickNameDialogue(self):
        """User chooses a name for the mundito

        return -->> None"""

        user = dial.PickNameDialogue().cycle()
        self.name = user[0]
        print "mundito", self.name, "is ready to run"

    def recreateName(self):
        """Recreate name from stored data

        return -->> None"""

        self.name = self.ganesh.name
        print "mundito", self.name, "is ready to run"

    def invokeGanesh(self):
        """Let Ganesh record relevant mundito data

        return -->> None"""

        self.ganesh.dimension = self.dimension
        self.ganesh.size = self.size
        self.ganesh.topologyLabel = self.topologyLabel
        self.ganesh.nsystemLabel = self.nsystemLabel
        self.ganesh.ruleLabel = self.ruleLabel
        self.ganesh.automatonLabel = self.automatonLabel
        self.ganesh.automaton = self.automaton
        self.ganesh.allStates = self.allStates
        self.ganesh.name = self.name
        print "ganesh has taken note of this creation"   

    def invokeSaraswati(self):
        """Create a controller for the view

        return -->> None"""

        if self.saraswati is None:
            self.saraswati = ouroborus.controller.saraswati.Saraswati()
            print "saraswati comes into existence"
        self.saraswati.dimension = self.dimension
        self.saraswati.size = self.size
        self.saraswati.automaton = self.automaton
        self.saraswati.allStates = self.allStates
        self.saraswati.name = self.name
        print "saraswati acknowledges creation"

    
