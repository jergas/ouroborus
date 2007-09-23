# This module contains the class Ganesh, which is part of the
# controller component of Project Ouroborus, and specifically
# acts to orchestrate the mundem serialisation and deserialisation.

# At present, it simply orchestrates load and save functionalities.

# It was written in Python 2.3.4 by Sat Tara Singh  
# Khalsa on December 28 2006, when it was found to run
# successfully on Windows XP, Deg Teg Fateh!


import ouroborus.mundem.save as save
import ouroborus.mundem.load as load
import ouroborus.mundem.upload as upload
import ouroborus.mundem.download as download
import ouroborus.controller.dialogue as dial

class Ganesh:

    def __init__(self):
        """Create a mundem controller

        return -->> None"""

        self.dimension = 0
        self.size      = (0,)
        self.topologyLabel  = ""
        self.nsystemLabel   = ""
        self.ruleLabel      = ""
        self.automatonLabel = ""
        self.automaton = None
        self.allStates = 0
        self.name      = ""
        self.colors    = {}
        self.array     = None

    def archive(self,iteration):
        """Save a mundito as a .mun file

        iteration ---> an integer
        return    -->> None"""

        saver = save.Saver()
        saver.filename = self.name + str(iteration) + ".mun"
        saver.size = self.size
        saver.automaton = self.automaton

        a = saver.makeArray()
        d = saver.makeDict()

        d["dimension"] = self.dimension
        d["size"] = self.size
        d["topologyLabel"] = self.topologyLabel
        d["nsystemLabel"] = self.nsystemLabel
        d["ruleLabel"] = self.ruleLabel
        d["automatonLabel"] = self.automatonLabel
        d["allStates"] = self.allStates
        d["name"] = self.name
        d["iteration"] = iteration
        d["colors"] = self.colors

        saver.dump(d,a)
        print "mundito has been saved as file", saver.filename

    def retrieve(self):
        """Retrieve a mundito from a .mun file

        return ---> an integer, the iteration number"""

        loader = load.Loader()
        filename = dial.FilenameDialogue().cycle()[0]
        (d,a) = loader.loadPair(filename)

        self.dimension = d["dimension"]
        self.size = d["size"]
        self.topologyLabel = d["topologyLabel"]
        self.nsystemLabel = d["nsystemLabel"]
        self.ruleLabel = d["ruleLabel"] 
        self.automatonLabel = d["automatonLabel"] 
        self.allStates = d["allStates"]
        self.name = d["name"]
        iteration = d["iteration"] 
        self.colors = d["colors"]
        self.array = a

        print "mundito data has been read from file"
        return iteration

    def repopulate(self):
        """repopulate a mundito from data stored in an array

        return -->> None"""

        for x in range(self.size[0]):
            for y in range(self.size[1]):
                self.automaton.py_set2((x,y),self.array[x][y])
        print "ganesh has repopulated the mundito"

    def upload(self):
        
        uploader = upload.Uploader()
        uploader.size = self.size
        uploader.automaton = self.automaton

        uploader.makeList()
        uploader.upload()

    def clone(self):

        downloader = download.Downloader()
        downloader.automaton = self.automaton

        downloader.getList()
        downloader.setSize()
        downloader.clone()
        
#GEEK        

        
