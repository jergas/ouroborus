import GOD
import curses
import sound

def main(stdscr):
	mary = GOD.Generator("kristos")
	sound.startSoundServer()

	# setting the curses colour pairs
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)

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
	doomsday = 1000	
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	magdalen = GOD.Organizer(terra, biblos)
	

	for i in range(avatars):
		mary.generateGenotype(seedCode.split(" "), biblos)
		sound.playSingleNote()
	magdalen.readBookOfLife(i, seedCode, 7, 1, (10,10))

	display = mary.generateDisplay(terra, size, stdscr)
	sound.startBackground()
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		magdalen.iterateAutomaton()
		magdalen.iterateAgents()
		magdalen.refreshDisplay(display)

	sound.stopSoundServer()
	return 1
	

# call the generic curses wrapper to maintain terminal sanity in all events
if __name__ == '__main__': end = curses.wrapper(main)
print end

