from . import runtime
"""GOD stands for Generator, Organizer and Destroyer. This module contains
3 classes whose methods and attributes relate to the execution and
orchestration of the various components of an Ouroborus AL world, such as
the backdrop cellular automaton, the agents who inhabit it, and the sound
and visual display through which humans perceive it."""

"""The actual execution flow is defined in a different module called
sequence_threaded, sequence_experimental, or in general sequence_x. Such
a module calls the objects defined in GOD. GOD lies therefore at the very
crux of the matter, as it puts together relatively low level objects of
many different sorts, and defines ways to handle them from a high level
perspective."""

"""GOD was created by a list of creatures including Ernesto Illescas,
Jergas Apwith and Sat Tara Singh."""

# import all the necessary modules, starting with some from the standard library
import sys
import random

# specificity is a module containing parameters which define many aspects
# of the AL world, i.e. it acts like a config file. There can be any
# number of specificity files, and the choice of which one to use is
# made at the sequence_x module. It is imported here under the variable
# name specific
specificity = runtime.specificity
specific = runtime.get_specific(specificity)

# the following are the core birdcage modules which are necessary to
# setup the backdrop cellular automaton, and the agents which
# populate the AL world:
import birdcage.topology as topology
import birdcage.agent as a
import birdcage.automaton as automaton
import birdcage.genome as g
# the following modules' location is configured in the specificity file.
# The standard versions can be found in the birdcage directory and
# have names like birdcage.neighborhood, alternate verions  of these
# modules can be found in the circadian directory under the same
# filenames; others may exist in the future.
neighborhood = __import__(specific.neighborhood[2], fromlist=[''])
rule = __import__(specific.rule[2], fromlist=[''])
# WARNING: This use of the fromlist argument is a hack,
# it depends on some weird behaviour in the api,
# and thus might break unexpectedly in the future

# These modules live in the local directory
from . import visual as v # the visual representation of the world
from .code import tabula # encoding the agent's genetics

# Add a fixed header-like section to the tabula encoding the
# worlds' genetics and therefore the agents' genomes. This is taken
# from the specificity file and contains a list of imports.
if hasattr(specific, 'boilerplate'):
        tabula['boilerplate'] = specific.boilerplate

# The following suite of imports is pretty high-level and directly related
# to the worldish simulation implemented mainly through this module

try:
        # an encapsulation module to facilitate handling of agents
        from .bookentry import BookEntry
        # these are the modules used for display
        import curses as c
        # these are the modules used for sound
        from . import sound_globals as soundGlobals
        # only load modules if running sound enabled simulations
        if soundGlobals.simWSound == 1:
                from . import agents_sound as agentsSound
except ImportError:
        print("WARNING: agent management, display or sound may not function correctly")

# Genomes are compiled outside the simulation process so setuptools cannot
# consume its arguments or replace its logging configuration.
import importlib
from pathlib import Path
import subprocess


def compile_genome(name, source):
    with open("build.log", "a") as log:
        result = subprocess.run(
            [sys.executable, str(Path(__file__).with_name("_compile.py")), name, source],
            stdout=log, stderr=subprocess.STDOUT,
        )
    if result.returncode:
        raise RuntimeError(f"Genome {name} failed to compile; see {Path('build.log').resolve()}")
    importlib.invalidate_caches()


# the debugOutputToFile flag is by default set to True on specificity files.
# It redirects all output to a logfile
if specific.debugOutputToFile:
        sys.stdout = specific.debugFile
        sys.stderr = specific.debugFile




class Generator:
        """This object creates a code object from a genome and appends it onto
        the dictionary of creatures. It also performs other creation-related functions
        such as generating a fully-functioning cellular automaton"""


        def __init__(self, obstetrix, specificity):
                """Create a Generator instance

                obstetrix ---> a string to head all generated filenames"""

                self.specific = runtime.get_specific(specificity)
                self.obstetrics = 0
                self.obstetrix = obstetrix
                self.scions = [] # this is a list of strains used for MassCompiling

                # Set the compile mode using getattr
                self.generateGenotype = getattr(self, "generateGenotype"+self.specific.compiling, self.generateGenotypeIndividualCompile)

                # set the display functions using getattr
                self.displayType = self.specific.displayType.capitalize()
                self.generateDisplay = getattr(self, "generateDisplay" + self.displayType)

                # set the library in which the criterion funtion is located, then set
                # the criterion function for deciding which cells are displayed
                self.criterionLocation = globals()[self.specific.criterionLocation]
                self.criterion = getattr(self.criterionLocation, specific.criterion)




        def generateAutomaton(self, size, tdata, ndata, rdata, adata):
                """Create an instance of a birdcage automaton class

                size   ---> a Python tuple of integers
                tdata  ---> a Python tuple commencing with a string
                ndata  ---> a Python tuple commencing with a string
                rdata  ---> a Python tuple commencing with a string
                adata  ---> a Python tuple commencing with a string
                return -->> an Automaton object"""

                topologyClass = getattr(topology, tdata[0])
                topologyInstance = topologyClass(size, tdata[1])
                print(topology, neighborhood)

                neighborhoodClass = getattr(neighborhood, ndata[0])
                neighborhoodInstance = neighborhoodClass(topologyInstance)

                ruleClass = getattr(rule, rdata[0])
                ruleInstance = ruleClass(neighborhoodInstance, rdata[1])

                automatonClass = getattr(automaton, adata[0])
                automatonInstance = automatonClass(ruleInstance)

                return automatonInstance


        def generateGenotype(self, poeio, ode):
                """Write and compile a file from a genome

                poeio  ---> a list of characters
                ode    ---> a dictionary of names (the Book of Life)
                return -->> 1, None or onoma (the new agents name)

                this is actually a general handle for various specific genotype
                generation methods, which are defined, sensibly enough, in the
                Specific file."""

                # This function is a placeholder, the actual function is assigned to
                # this name in Generator.__init__(). The following line is a failsafe.
                print("A failsafe generateGenotype has been used. This should not happen!")
                return getattr(self, "generateGenotype"+self.specific.compiling, self.generateGenotypeIndividualCompile)(poeio, ode)


        def generateGenotypeVoid(self, poeio, ode):
                """Compile nothing, no agents

                poeio  ---> a list of characters
                ode    ---> a list of names
                return -->> None"""

                print("blank genome - no compilation required!")
                return None


        def generateGenotypeIndividualCompile(self, poeio, ode):
                """Write and compile a file from a genome

                poeio  ---> a list of characters
                ode    ---> a dictionary of names (the book of life)
                return -->> the new agents name (onoma)

                New version compatible with the new BookEntry class"""

                # samskara is a genome binding poeio to tabula
                samskara = g.Genome(poeio, tabula, 2)
                # create a name for the module object
                onoma = self.obstetrix+str(self.obstetrics)
                # corpus is the relative filepath where the Pyrex genome code will be saved
                Path('creatures').mkdir(exist_ok=True)
                corpus = 'creatures/'+onoma+'.pyx'
                # this incantation actually writes the .pyx file with the translated poeio code
                samskara.incorporate(corpus)

                compile_genome(onoma, corpus)

#               # finally, append the module's name to the list of names,
#               #ode.append(BookEntry(onoma, onoma))
                # finally, add the module's BookEntry to the Book of Life
                # (dictionary of names) using its name as a key
                ode[onoma] = BookEntry(onoma, onoma)
                self.obstetrics += 1
                return onoma


        def generateGenotypeMassCompile(self, poeio, ode):
                """Write and compile a file from a genome

                poeio  ---> a list of characters
                ode    ---> a dictionary of names (the Book of Life)
                return -->> the new agent's name (onoma)

                New version compatible with the new BookEntry class"""

                # create a name for the new bookentry object
                onoma = self.obstetrix+"clone"+str(self.obstetrics)
                # first check whether the genome has already been compiled
                if poeio in self.scions:

                        # identify the genome in the dictionary of compiled strains
                        strain = self.obstetrix+str(self.scions.index(poeio))
                        ode[onoma]=(BookEntry(onoma, strain))

                else:
                        # if it hasn't, proceed to compile the new genome
                        # samskara is a genome binding poeio to tabula
                        samskara = g.Genome(poeio, tabula, 2)
                        # create a name for the module object
                        strain = self.obstetrix+str(len(self.scions))
                        # corpus is the relative filepath where the Pyrex genome code will be saved
                        Path('creatures').mkdir(exist_ok=True)
                        corpus = 'creatures/'+strain+'.pyx'
                        # this incantation actually writes the .pyx file with the translated poeio code
                        samskara.incorporate(corpus)

                        compile_genome(strain, corpus)
                        self.scions.append(poeio)

                        # finally, add the module's BookEntry to the Book of Life
                        # (dictionary of names) using its name as a key
                        ode[onoma] = BookEntry(onoma, strain)

                self.obstetrics += 1
                return onoma


        def generateDisplayCurses(self, earth, size, stdscr):
                """Initialise a curses display for the automaton and its agents
                earth  ---> a birdcage automaton
                size   ---> a 2-tuple with the grid's dimensions
                stdscr ---> a curses standard screen object
                return -->> a 3-tuple of values useful for display"""

                # a little workaround to make curses work for any terminal size
                (width, height) = size
                (winheight,winwidth) = stdscr.getmaxyx()
                displaywidth = (winwidth < width) and winwidth-1 or width
                displayheight = (winheight < height) and winheight-1 or height

                # run the visual display refresh cycle as initialisation
                seed = earth.returnTopology().random()
                earth.set(seed,1)

                # Set the curses colours.
                v.setCursesColors(self.specific.manaColour,
                                        self.specific.agentsColour,
                                        self.specific.backgroundColour)

                v.updateLoop(earth, stdscr, displaywidth, displayheight)
                stdscr.refresh()
                # return a 3-tuple useful for further display
                return (stdscr, displaywidth, displayheight)


        def generateDisplayPygame(self, earth, size, stdscr):
                """Initialise a curses display for the automaton and its agents
                earth  ---> a birdcage automaton
                size   ---> a 2-tuple with the grid's dimensions
                stdscr ---> a curses standard screen object
                return -->> a 3-tuple of values useful for display"""

                # run the visual display refresh cycle as initialisation
                seed = earth.returnTopology().random()
                earth.set(seed,1)

                screen = v.pygGenerateDisplay(size, "birdcage reloaded")
                v.pygUpdateBackground(earth, self.criterion, size)


        def generateDisplayDebug(self, earth, size, book):
                """Initialise a debug display.
                earth  ---> a birdcage automaton
                """
                # run the display refresh cycle as initialisation
                seed = earth.returnTopology().random()
                earth.set(seed,1)
                v.debugUpdateDisplay(1, book, specific.debugFile)



class Organizer:
        """This object coordinates the iteration-per-iteration functioning of the
        automata and its agents. It calls on the Organizer and Destroyer when
        necessary."""


        def __init__(self, earth, book, specificity):
                """Create an Organizer instance

                earth       ---> some complete birdcage Automaton instance
                book        ---> a dictionary of agent code objects (genotypes)
                specificity ---> the suffix of a configuration module
                """
                self.specific = runtime.get_specific(specificity)
                self.earth = earth
                self.generator = None
                self.destroyer = None
                self.book = book
                self.annum = 0
                self.births = 0
                self.deaths = 0
                self.size = self.specific.size
                (self.width, self.height) = self.size

                # set the display functions using getattr
                self.displayType = self.specific.displayType.capitalize()
                self.refreshDisplay = getattr(self, "refreshDisplay" + self.displayType)
                self.refreshBackground = getattr(self, "refreshBackground"+self.displayType)
                self.refreshAgent = getattr(self, "refreshAgent" + self.displayType)

                # set the library in which the criterion funtion is located, then set
                # the criterion function for deciding which cells are displayed
                self.criterionLocation = globals()[self.specific.criterionLocation]
                self.criterion = getattr(self.criterionLocation, specific.criterion)


        def initialiseAutomaton(self, seed):
                """Initialise cellular automaton from data in specs file

                seed   ---> a tuple
                return -->> 1"""

                getattr(self, "seedAutomaton"+seed[0])(seed)
                return 1


        def seedAutomatonVoid(self, seed):
                """Does nothing, just testing

                seed   ---> a tuple
                return ---> 1"""

                print("The automaton's cells have all been initialised to the background's value")
                return 1


        def seedAutomatonRandom(self, seed):
                """Randomly set some points to one in the c.a.

                seed   ---> a tuple
                return -->> 1"""

                for i in range(seed[1]):
                        self.earth.set(self.earth.returnTopology().random(),1)
                return 1


        def iterateAutomaton(self):
                """Iterate the birdcage automaton associated to the Organizer

                return -->> population"""

                self.annum = self.annum + 1
                return self.earth.update()


        def readBookOfLife(self, bookentry):
                """New and more pythonic version of this core function

                bookentry ---> a BookEntry object
                return    -->> 1

                in essence this function redirects to various methods
                aptly named according to the entity's prayer type"""

                # look for the entity's prayer
                prayer = bookentry.fatum["prayer"]
                default = self.grantPrayerLive
                # call the appropriate grantPrayer method by prayer type
                return getattr(self, "grantPrayer"+prayer, default)(bookentry)


        def grantPrayerCreateMe(self, bookentry):
                """Setup the fatum for a new BookEntry, for creature created by
                divine mandate.

                bookentry ---> a BookEntry object
                return    -->> 1"""

                # set some initial parameters in the creature's fatum
                bookentry.fatum["code"] = self.specific.seedCode
                bookentry.fatum["prana"] = self.specific.prana
                bookentry.fatum["mana"] = self.specific.mana
                (x, y) = (random.randint(0, self.width-1), random.randint(0, self.height-1))
                bookentry.fatum["address"] = (x, y)
                bookentry.fatum["prayer"] = "BeBirthed"
                # Instantiate the class that contains the agent's sound
                # attributes and methods (in case of sound-enabled simulation).
                if soundGlobals.simWSound == 1:
                        bookentry.fatum["voice"] = agentsSound.VocalTract(x, self.width)
                return 1



        def grantPrayerBeBirthed(self, bookentry):
                """Populate an agent's BookEntry and place it on the c.a.

                bookentry ---> a BookEntry object
                return    -->> 1"""

                # import the module (compiled by the generator) and place it in bookentry
                bookentry.callModule()
                # call the module's birth function to instantiate an agent object
                bookentry.instantiateAgent(self.earth)
                # add the agent to the c.a.'s list of agents
                self.earth.addAgent(bookentry.agent)
                self.births += 1
                # set the agent's prayer back to its default state
                bookentry.fatum["prayer"] = "Live"
                return 1


        def grantPrayerLive(self, bookentry):
                """Allow an agent to perform its standard live method

                return -->> 1"""

                bookentry.agentLive()
                return 1


        def grantPrayerGrantChild(self, bookentry):
                """Make a new entry for an agent which has reproduced

                return -->> a string, the agent child's name
                """
                # the Generator compiles the new module and writes it in the book
                code = bookentry.fatum["code"]
                child = self.book[self.generator.generateGenotype(code, self.book)]
                # add some necessary data to the new entry
                child.fatum["code"] = bookentry.fatum["code"]
                child.fatum["prana"] = self.specific.prana
                child.fatum["mana"] = self.specific.mana
                (x, y) = (random.randint(0, self.width-1), random.randint(0, self.height-1))
                child.fatum["address"] = (x, y)
                # This appears to do nothing...investigate!!!
                child.fatum["prayer"] = "BeBirthed"
                # Instantiate the class that contains the agent's sound
                # attributes and methods (if sound is enabled).
                if soundGlobals.simWSound == 1:
                        child.fatum["voice"] = agentsSound.VocalTract(x, self.width)
                # set the agent's prayer back to live
                bookentry.fatum["prayer"] = "Live"
                return child.name


        def grantPrayerKillMe(self, bookentry):
                """Delete an agent and strike its entry from the book

                return -->> 1"""

                self.earth.removeAgent(bookentry.agent)
                self.deaths += 1
                bookentry.terminateAgent()
                del self.book[bookentry.name]
                return 1


        def readBookOfLifeOld(self, index, code, prana, mana, address, generator):
                """Dynamically import the modules compiled by the Generator

                This will also cause actual agent instances to be created
                index     ---> an integer, the module's order in self.book
                code      ---> a string with the genome's code
                prana     ---> an integer with the agent's initial prana
                mana      ---> an integer, a special state of the ca from the agent's viewpoint
                address   ---> a 2-tuple, the agent's birthplace
                generator ---> an instance of GOD.Generator
                return    -->> 1 """

                if self.book[index][4]["prayer"] == "BE_BIRTHED":
                        #print self.book[index][1], "prays to be birthed"
                        module = __import__(self.book[index][1])
                        agent = module.birth(self.earth, code, prana, mana, address)
                        self.earth.addAgent(agent)
                        self.book[index][2] = module
                        self.book[index][3] = agent
                        self.book[index][4]["prayer"] = "LIVE"

                        return 1

                elif self.book[index][4]["prayer"] == "LIVE":
                        self.book[index][2].live(self.book[index][3],self.book,self.book[index][0])

                        return 1

                elif self.book[index][4]["prayer"] == "GRANT_CHILD":
                        generator.generateGenotype(self.book[index][4]["code"], self.book)
                        self.book[index][4]["prayer"] = "LIVE"
                        del self.book[index][4]["code"]

                        return 1


        def iterateAgents(self):
                """Go through the dictionary of agents and let them perform their actions

                return -->> 1 """

                for entity in self.book:
                        entity[1].live(entity[2])

                return 1


        def refreshDisplayCurses(self, display):
                """Refresh the display on a curses terminal

                display       ---> a 3-tuple as follows:
                                                (stdscr, displaywidth, displayheight)
                stdscr        ---> a curses standard screen object
                displaywidth  ---> the integer width of the curses terminal
                displayheight ---> the integer height of the curses terminal
                return        -->> 1"""
                v.updateLoop(self.earth, display[0], display[1], display[2])
                display[0].refresh()


        def refreshDisplayPygame(self, display):
                """Refresh the display on a curses terminal"""

                v.pygUpdateBackground(self.earth, self.criterion, self.size)


        def refreshDisplayDebug(self, display):
                """ Display the automaton and agents data after a whole
                self.earth iteration.
                display ---> the input is syntactically needed, but not used
                """
                v.debugUpdateDisplay(self.annum, self.book, specific.debugFile)


        def refreshBackgroundCurses(self, display):
                """Refresh the background of a display on a curses terminal

                display       ---> a 3-tuple as follows:
                                                (stdscr, displaywidth, displayheight)
                stdscr        ---> a curses standard screen object
                displaywidth  ---> the integer width of the curses terminal
                displayheight ---> the integer height of the curses terminal
                return        -->> 1
                """
                v.updateBackground(self.earth, display[0], display[1], display[2])
                display[0].refresh()


        def refreshBackgroundPygame(self, display):
                """Refresh the background of a display on a curses terminal

                display       ---> a 3-tuple as follows:
                                                (stdscr, displaywidth, displayheight)
                stdscr        ---> a curses standard screen object
                displaywidth  ---> the integer width of the curses terminal
                displayheight ---> the integer height of the curses terminal
                return        -->> 1
                """
                v.pygUpdateBackground(self.earth, self.criterion, self.size)


        def refreshBackgroundDebug(self, display=None):
                """ Display the automaton data after a whole self.earth
                iteration.
                """
                v.debugUpdateBackground(self.annum, specific.debugFile)


        def refreshAgentCurses(self, entry, display):
                """Refresh the image of an agent on a curses terminal

                display       ---> a 3-tuple as follows:
                                                (stdscr, displaywidth, displayheight)
                stdscr        ---> a curses standard screen object
                displaywidth  ---> the integer width of the curses terminal
                displayheight ---> the integer height of the curses terminal
                return        -->> 1"""
                agent = entry.agent
                v.updateAgent(agent, display[0], display[1], display[2])
                display[0].refresh()


        def refreshAgentPygame(self, entry, display):
                """Refresh the image of an agent on in the pygame viewer

                display       ---> a 3-tuple as follows:
                                                (stdscr, displaywidth, displayheight)
                stdscr        ---> a curses standard screen object
                displaywidth  ---> the integer width of the curses terminal
                displayheight ---> the integer height of the curses terminal
                return        -->> 1"""
                agent = entry.agent
                v.pygDrawAgent(agent)


        def refreshAgentDebug(self, entry, display):
                """Report the status of an agent in the debug viewer mode.
                entry   ---> a bookOfLife entry
                display ---> the input is syntactically needed, but not used
                """
                v.debugUpdateAgent(entry, specific.debugFile)
