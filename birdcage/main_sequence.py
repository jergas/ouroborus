import GOD
import curses

####Ernesto's edit
##Module(s) imported for sound purposes
import time
import Csound_Interface
print "Imported sound engine"
Csound_Interface.initCsound()
####End Ernesto's edit

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
####Ernesto's edit
        Csound_Interface.csoundNote()
####End Ernesto's edit
        magdalen.readBookOfLife(i, seedCode, 7, 1, (10,10))

	display = mary.generateDisplay(terra, size, stdscr)
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		magdalen.iterateAutomaton()
		magdalen.iterateAgents()
		magdalen.refreshDisplay(display)

	return 1
	

# call the generic curses wrapper to maintain terminal sanity in all events
if __name__ == '__main__': end = curses.wrapper(main)
print end

