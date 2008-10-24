import GOD
import curses

#### Ernesto's edit
## Module(s) imported for sound purposes
import time
import Csound_Interface
import Background_sound
print "Imported sound engine"
## Starts the sound server
Csound_Interface.initCsound()
#### End Ernesto's edit

def main(stdscr):
	mary = GOD.Generator("kristos")

	# the following lines contain all the data to build a complete automaton
	size = (90,40)
	topologyData = ("GridTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	import operator
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )
        seedCode = "Y i Y c Y s C b C d C r T l T p"

	# invoke God.Generator's automaton creation method with the data given above
	biblos = []
	avatars = 1
	doomsday = 30000	
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	magdalen = GOD.Organizer(terra, biblos)
	

	for i in range(avatars):
		mary.generateGenotype(seedCode.split(" "), biblos)
#### Ernesto's edit
## Plays a single note when an agent is instantiated.
#### Some latency issues have still to be dealt with.
        	Csound_Interface.csoundNote()
#### End Ernesto's edit
        magdalen.readBookOfLife(i, seedCode, 7, 1, (10,10))

	display = mary.generateDisplay(terra, size, stdscr)
#### Ernesto's edit
## Starts the background sound threads.
	Background_sound.playback()
#### End Ernesto's edit
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		magdalen.iterateAutomaton()
		magdalen.iterateAgents()
		magdalen.refreshDisplay(display)
#### Ernesto's edit
## Changes a global within Background_sound.py. This causes the iteration of the background sound
# loops (and thus its threads) to end.
	Background_sound.mainIterCycle = 0
####End Ernesto's edit

	return 1
	

# call the generic curses wrapper to maintain terminal sanity in all events
if __name__ == '__main__': end = curses.wrapper(main)
print end

