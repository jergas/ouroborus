# This provides a rudimentary, text-driven user interface for the
# controller component of Project Ouroborus

# At present, it is based on sequential dialogues which orchestrate
# a linear flow of execution

# It was written in Python 2.3.4 by Sat Tara Singh  
# Khalsa on December 16 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


class OptionsDialogue:
    """A generic menu options dialogue"""

    heading  = ""
    options  = -1
    captions = []
    values   = []

    def __init__(self):
        """Verify data coherence

        return -->> None"""
        
        self.options = len(self.captions)
        assert self.options == len(self.values)
        
    def present(self):
        """Present the dialogue options on screen

        return -->> None"""

        assert self.options > 0
        print "\n"
        print "*** " + self.heading + " ***"
        print "\n"
        print "Choose one option and type Enter: \n"
        for i in range(self.options):
            print "\t" + str(i+1) + ". " + self.captions[i]

    def query(self):
        """Receive input from user

        return -->> an integer or None"""

        raw_reply = raw_input("->")

        try:
            reply = int(raw_reply)
        except:
            return 

        if reply < 0 or reply >= self.options + 1:
            return
        else:
            return self.values[reply-1]

    def cycle(self):
        """Orchestrate the dialogue's performance

        return -->> a Python object"""

        choice = None

        while choice is None:
            self.present()
            choice = self.query()

        return choice


class ValuesDialogue:
    """A generic direct input dialogue"""

    heading  = ""
    queries  = -1
    captions = []
    choice   = []

    def __init__(self):
        """Verify data coherence
        
        return    -->> None"""
        
        assert self.queries == len(self.captions)

    def present(self):
        """Present the dialogue options on screen

        return -->> None"""

        assert self.queries > 0
        print "\n"
        print "*** " + self.heading + " ***"
        print "\n"
        print "Type an answer followed by Enter: \n"
        
    def query(self):
        """Receive input from user

        return -->> a string or number"""

        reply = raw_input("->")

        return reply

    def cycle(self):
        """Orchestrate the dialogue's performance

        return -->> a Python list"""

        self.choice = []
        for i in range(self.queries):
            self.choice.append(-1)

        self.present()

        for i in range(self.queries):
            while self.choice[i] == -1:
                print self.captions[i]
                self.choice[i]=self.query()

        return self.choice
   

### Narayan's dialogues:

class MainDialogue(OptionsDialogue):
    """Main start-up dialogue"""

    heading  = "Welcome to Ouroborus"
    captions = ["Create a new mundito","Load an existing mundito","Exit program"]
    values   = ["creation","retrieval","exit"]


### Brahm's dialogues:

class ChooseDimensionDialogue(OptionsDialogue):
    """Choose a dimension for the grid"""

    heading  = "Choose a dimension for the mundito grid"
    captions = ["Two"]
    values   = [2]

class ChooseTopologyDialogue(OptionsDialogue):
    """Choose a topology for the mundito grid"""

    heading  = "Which topology would you like?"
    captions = ["Toroid Topology"]
    values   = ["2dToroid"]

    def __init__(self,dimension):
        """Override generic __init__

        dimension ---> an integer
        return    -->> None"""

        assert dimension == 2
        OptionsDialogue.__init__(self)

class ChooseNSystemDialogue(OptionsDialogue):
    """Choose a neighborhood for the mundito grid"""

    heading  = "Which neighborhood system shall we use?"
    captions = ["Von Neumann Neighborhood"]
    values   = ["2dVonNeumann"]

    def __init__(self,dimension):
        """Override generic __init__

        dimension ---> an integer
        return    -->> None"""

        assert dimension == 2
        OptionsDialogue.__init__(self)

class ChooseAutomatonDialogue(OptionsDialogue):
    """Choose a birdcage automaton class"""

    heading  = "Choose a type of cellular automaton"
    captions = ["2-state synchronous automaton with reduction rule"]
    values   = ["2stateReduction"]

class ChooseReductionRuleDialogue(OptionsDialogue):
    """Choose a specific reduction rule"""

    heading  = "Select which function to use as a reduction rule"
    captions = ["Parity (exclusive \"or\")"]
    values   = ["xor"]

class ChooseInitializationMethodDialogue(OptionsDialogue):
    """Choose a method to initialise the automaton"""

    heading  = "How shall we initialise the automaton?"
    captions = ["Animate one specific cell","Animate a random set of cells","Remain inanimate"]
    values   = ["singleSpecific","nRandom","blank"]

class ChooseSizeDialogue(ValuesDialogue):
    """Choose a size for the grid"""

    heading  = "Choose the size of the mundito grid"

    def __init__(self,dimension):
        """Override generic __init__

        dimension ---> an integer
        return    -->> None"""

        self.queries = dimension
        self.captions = []
        for i in range(dimension):
            self.captions.append("Size of grid along axis "+str(i+1)+":")
        ValuesDialogue.__init__(self)

    def query(self):
        """Override generic query

        return -->> a positive integer"""

        try:
            reply = int(raw_input("->"))
        except:
            return -1

        if reply < 1: return -1
        else: return reply
        
class PickCellDialogue(ValuesDialogue): 
    """Pick an individual address from the grid"""

    heading  = "Pick an individual cell from the map"

    def __init__(self,size):
        """Override generic __init__

        dimension ---> an n-tuple
        return    -->> None"""

        self.queries = len(size)
        self.size    = size
        self.captions = []
        for i in range(len(size)):
            self.captions.append("Coordinate along axis "+str(i+1)+":")
        ValuesDialogue.__init__(self)

    def query(self,axis):
        """Override generic query

        axis   ---> an integer, the order along the coordinate tuple
        return -->> a valid integer, the projection onto the ith axis"""

        try:
            reply = int(raw_input("->"))
        except:
            return -1

        if reply < 0 or reply >= self.size[axis]: return -1
        else: return reply

    def cycle(self):
        """Override generic cycle

        return -->> a Python list"""

        self.choice = []
        for i in range(self.queries):
            self.choice.append(-1)

        self.present()

        for i in range(self.queries):
            while self.choice[i] == -1:
                print self.captions[i]
                self.choice[i]=self.query(i)

        return self.choice

class PickIntegerDialogue(ValuesDialogue):
    """Choose a positive integer"""

    heading  = "Pick the number of cells to animate:"
    queries  = 1
    captions = ["Enter a positive integer"]

    def query(self):
        """Override generic query

        return -->> a positive integer"""

        try:
            reply = int(raw_input("->"))
        except:
            return -1

        if reply < 1: return -1
        else: return reply


class PickNameDialogue(ValuesDialogue):
    """Choose a name for the mundito"""

    heading  = "Creation is almost over..."
    queries  = 1
    captions = ["Choose a name for your mundito"]

class ChooseColorsDialogue(ValuesDialogue):
    """Choose rgb values for each state of the automaton grid"""

    heading  = "Choose RGB colours for the automaton's states"

    def __init__(self,allStates):
        """Override generic __init__

        allStates ---> an integer
        return    -->> None"""

        self.queries = allStates
        self.captions = []
        for i in range(self.queries):
            self.captions.append("\nRGB value for state "+str(i)+":")
        ValuesDialogue.__init__(self)

    def query(self):
        """Override generic query

        return -->> a 3-tuple, an rgb value"""

        reply = [None,None,None]

        try:
            reply[0] = int(raw_input("Red value (0 to 255) "))
            reply[1] = int(raw_input("Green value (0 to 255) "))
            reply[2] = int(raw_input("Blue value (0 to 255) "))            
        except:
            return (-1,)

        for i in range(3):
            if reply[i] < 0 or reply[i] >= 256: return (-1,)
        else: return reply

    def cycle(self):
        """Orchestrate the dialogue's performance

        return -->> a Python list"""

        self.choice = []
        for i in range(self.queries):
            self.choice.append((-1,))

        self.present()

        for i in range(self.queries):
            while self.choice[i] == (-1,):
                print self.captions[i]
                self.choice[i]=tuple(self.query())

        return self.choice
    

### Hare's dialogues:

class SetDisplayDialogue(OptionsDialogue):
    """Choose a display mode for the view"""

    heading  = "Select a display mode"
    captions = ["snapshot at end of sequence","animated frames movie","stroboscopic images"]
    values   = ["snap","flick","strobe"]

class GoAtItAgainDialogue(OptionsDialogue):
    """Choose to terminate the sustainment cycle"""

    heading  = "The requested number of iterations has been performed"
    captions = ["Compute more iterations","See more options"]
    values   = ["continue","conclude"]

class EndOfTimeDialogue(OptionsDialogue):
    """Decide whether to continue or terminate"""

    heading  = "What shall be the future of this mundito?"
    captions = ["Perform some more iterations","Save it","Upload an image of the grid","Clone a foreign mundito","Blow it to smithereens"]
    values   = ["iterate","save","upload","clone","annihilate"]

class SetIterationsDialogue(ValuesDialogue):
    """Choose a number of iterations to perform"""

    heading  = "Choose a number of iterations to perform:"
    queries  = 1
    captions = ["Enter a positive integer"]

    def query(self):
        """Override generic query

        return -->> a positive integer"""

        try:
            reply = int(raw_input("->"))
        except:
            return -1

        if reply < 0: return -1
        else: return reply

class SetFrequencyDialogue(ValuesDialogue):
    """Choose a frequency for the display"""

    heading  = "Choose a frequency for the strobe:"
    queries  = 1
    captions = ["Enter a positive integer"]

    def query(self):
        """Override generic query

        return -->> a positive integer"""

        try:
            reply = int(raw_input("->"))
        except:
            return -1

        if reply < 2: return -1
        else: return reply

    
### Ganesh's dialogues:

class FilenameDialogue(ValuesDialogue):
    """Write the name of the .mun file to load from"""

    heading  = "Where shall the mundito be retrieved from?"
    queries  = 1
    captions = ["Write the name of the file"]

    
