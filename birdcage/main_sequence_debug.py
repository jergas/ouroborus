import GOD
import random
import sys

def main(stdscr):
	mary = GOD.Generator("kristos")
	#sound.startSoundServer()

	# setting the curses colour pairs
	#setCursesColors()

	# the following lines contain all the data to build a complete automaton
	# size = (width, height) = (int(sys.argv[-4]),int(sys.argv[-3]))
	size = (width, height) = (80,20)
	# del sys.argv[-4:-2]
	topologyData = ("GridTopology", 0)
	neighborData = ("VonNeumannNeighborhood", )
	import operator
	ruleData = ("ReductionRule", (operator.xor, 0))
	automatonData = ("SynchronousAutomaton_2D", )
	seedCode = "Y i Y c Y s C b C d C r T l T e T r R d R p R c R l"

	# invoke God.Generator's automaton creation method with the data given above
	# (avatars, doomsday)= sys.argv[-2:]
	(avatars, doomsday)= (1, 5)
	# del sys.argv[-2:]
	avatars = int(avatars)
	doomsday = int(doomsday)
	biblos = []
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	magdalen = GOD.Organizer(terra, biblos)


	for i in range(avatars):
		mary.generateGenotype(seedCode.split(" "), biblos)
		print "generated agent", i # debugging
		#sound.playSingleNote()
		print "biblos is", biblos # debugging
		(x, y) = (30, 8)		
		#(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
		magdalen.readBookOfLife(i, seedCode, 7, 1, (x, y), mary)
		print "biblos is", biblos # debugging

	
	#for i in range(avatars):
	#	mary.generateGenotype(seedCode.split(" "), biblos)
	#	print "generated agent", i # debugging
	#	sound.playSingleNote()
	#	print "biblos is", biblos # debugging
	#	(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
	#	magdalen.readBookOfLife(i, seedCode, 7, 1, (x, y))
	#	print "biblos is", biblos # debugging

	#display = mary.generateDisplay(terra, size, stdscr)
	#sound.startBackground()
	# here cometh the main iteration cycle
	while magdalen.annum < doomsday:
		print "time is", magdalen.annum
		print "biblos is", biblos
		magdalen.iterateAutomaton()
		for i in range(len(biblos)): 
			magdalen.readBookOfLife(i, "a", 0, 0, (50,8), mary)
			if magdalen.annum == 10:
				biblos[0][3].gainPrana(5)
		#magdalen.iterateAgents()
		#magdalen.refreshDisplay(display)


	#sound.stopSoundServer()
	return biblos

def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)


# call the generic curses wrapper to maintain terminal sanity in all events
if __name__ == '__main__': curses.wrapper(main)


