#!/usr/bin/python
import GOD
import curses
import sound
import random
import sys

def main(stdscr):
	mary = GOD.Generator("kristos")
	sound.startSoundServer()

	# setting the curses colour pairs
	setCursesColors()

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
	(avatars, doomsday)= (1, 1500)
	# del sys.argv[-2:]
	avatars = int(avatars)
	doomsday = int(doomsday)
	biblos = []
	terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
	magdalen = GOD.Organizer(terra, biblos)


	for i in range(avatars):
		mary.generateGenotype(seedCode.split(" "), biblos)
		#print "generated agent", i # debugging
		sound.playSingleNote()
		#print "biblos is", biblos # debugging
		(x, y) = (30, 8)		
		#(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
		magdalen.readBookOfLife(i, seedCode, 7, 1, (x, y), mary)
		#print "biblos is", biblos # debugging

	
	#for i in range(avatars):
	#	mary.generateGenotype(seedCode.split(" "), biblos)
	#	print "generated agent", i # debugging
	#	sound.playSingleNote()
	#	print "biblos is", biblos # debugging
	#	(x, y) = (random.randint(0, width-1), random.randint(0, height-1))
	#	magdalen.readBookOfLife(i, seedCode, 7, 1, (x, y))
	#	print "biblos is", biblos # debugging

	display = mary.generateDisplay(terra, size, stdscr)
	sound.startBackground()
	sound.startBackgroundControl()
	# here cometh the main iteration cycle
	iterText = open('iterText.txt', 'w')
	maxPop = 0
	minPop = 1
	while magdalen.annum < doomsday:

		population = magdalen.iterateAutomaton()
		populationNorm = float(population) / operator.mul(width,height)
		iterText.write('\nMaximumPopulation = ' + str(populationNorm))
		if populationNorm > maxPop:
			maxPop = populationNorm
		if populationNorm < minPop:
			minPop = populationNorm
		#print "time is", magdalen.annum
		#print "biblos is", biblos
		#iterText.write('\n------' + '\nannum=' + str(magdalen.annum) + '\n' + str(biblos))
		#iterText.write('\npopulation=' + str(float(population) / operator.mul(width,height)))
		#iterText.write('\nstate(5,5)=' + str(terra.get((40,10))))
		for i in range(len(biblos)): 
			newbirth = magdalen.readBookOfLife(i, "a", 0, 0, (50,8), mary)
			if magdalen.annum == 750:
				biblos[0][3].gainPrana(5)
#			if magdalen.annum == 760 and i == 1:
#				biblos[i][3].gainPrana(12)
#			#iterText.write('\nagent=' + str(biblos[i][0]) + 'births? ' + str(newbirth))
			#iterText.write('   prana=' + str(biblos[i][3].tellPrana()))
		#magdalen.iterateAgents()
		magdalen.refreshDisplay(display)
		soundControlCells = [terra.get((22,18)), terra.get((40,19)), terra.get((64,17))]
		sound.inputDataControl(soundControlCells, populationNorm)

	iterText.write('MaximumPopulation = ' + str(maxPop) + '\nMinimumPopulation = ' + str(minPop))
	sound.stopSoundServer()
	return biblos

def setCursesColors():
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
	curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)


# call the generic curses wrapper to maintain terminal sanity in all events
if __name__ == '__main__': curses.wrapper(main)


