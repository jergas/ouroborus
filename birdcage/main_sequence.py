import GOD
import curses

def main(stdscr):
	mary = GOD.Generator("kristos")

	# the following lines contain all the data to build a complete automaton
	size = (90,40)
	topologyData = ("GridTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	import operator
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )
        seedCode = "Y i Y c Y s C b C d C r T f T p"

	# invoke God.Generator's automaton creation method with the data given above
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	biblos = []
	magdalen = GOD.Organizer(terra, biblos)
	avatars = 1
	doomsday = 200

	for i in range(avatars):
		mary.generateGenotype(seedCode.split(" "), biblos)
                magdalen.readBookOfLife(i, seedCode, 7, 1, (10,10))

	display = mary.generateDisplay(terra, size, stdscr)
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		magdalen.iterateAutomaton()
		magdalen.refreshDisplay(display)
	return 1
	

# call the generic curses wrapper to maintain terminal sanity in all events
if __name__ == '__main__': end = curses.wrapper(main)
print end

