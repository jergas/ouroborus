## Contains the background sound generation and control methods, which
# are converted into threads by playbak() and control(), respectively.

# Python's native libraries
import time
import threading
import random
# User-defined submodules
import Numeric_utils as NU
from equal_temper import centsToFreq
from Csnd_notes import BckgrndNote
import sound_globals as soundGlobals

# Instantiate the numeric scaling class. 
Scaling = NU.Scaling()
Series	= NU.Series(0)

#logging = open("log.txt", 'w')

def oneBckgrndVox(frstInstr, dur, ptch, strtDistr, specType, numOfPartls, pan,
					perf, cSnd):
	"""Starts a note-generating loop which -parting from initial
	parameters- is modified via the simulation (and some randomness).

	frstInstr	---> First csound instrument that this voice will use
	dur			---> Time that each note of the voice will last
	ptch		---> Initial ptch of the fundamental frecuency
	strtDistr	---> The initial spectral-distortion factor
	specType	---> Spectrum type (odd, even, fibonacci or prime)
	numOfPartls	---> Number of partials in the harmonic spectrum
	pan			---> Note's panning
	perf		---> a Csound performance thread
	cSnd		---> a Csound instance
	"""
	fundFreq		= centsToFreq(ptch)
	endDistrFact	= strtDistr + (.01 * random.randint(-10, 10))
	instrNos 		= range(frstInstr, (frstInstr + numOfPartls))
	# Instantiate the background sound note class.
	bckgrndNote = BckgrndNote(instrNos, fundFreq, numOfPartls, specType,
								strtDistr, endDistrFact, pan, dur)

	spectrum	= bckgrndNote.mkScoStrings()
	for x, y in zip(spectrum, instrNos):
		perf.InputMessage(x)
		cSnd.SetChannel("chan%s" %(y-1), .5)

	while soundGlobals.mainIterCycle == 1:
		time.sleep(abs(dur) - 1)
		# Change the parameters for the next note.
		freqDeviation	= random.randint(-50, 50)
		fundFreq = centsToFreq(ptch + freqDeviation)
		bckgrndNote.fundFreq = fundFreq
		strtDistr = endDistrFact
		bckgrndNote.distor = strtDistr
		endDistrFact	= strtDistr + (.01 * random.randint(-5, 5))
		bckgrndNote.distor2 = endDistrFact
		spectrum	= bckgrndNote.mkScoStrings()
		# Feed the partials to Csound.
		for x, y in zip(spectrum, instrNos):
			perf.InputMessage(x)

		
		
def ctrlBckgrndSnd(cSnd):
	"""Uses parameters from the automaton (stored by sound.py in
	sound_globals.py) to control the background sound after the notes
	have started. Changes at note-start times are handled by
	oneBckgrndVox().
	cSnd		---> a Csound instance
	"""	
	wheightedGates	= [0.5]*2 + [0.25]*3 + [0.125]*5 + [0.0625]*7 + [.03125]*11
	wheightedAmps	= [4]*2 + [2]*4 + [1]*8
	oldAutomatonState	= soundGlobals.backgroundUpdateList
	
	while soundGlobals and soundGlobals.mainIterCycle:
		# Wait until number of the automaton's live cells has varied.
		newAutomatonState = soundGlobals.backgroundUpdateList
		# Attenuate or boost the relevant partials
		if oldAutomatonState != newAutomatonState:
			for x in newAutomatonState:
				if x[1] == 1:
					cSnd.SetChannel("chan%s" %(x[0]),
									random.choice(wheightedAmps))
				else:
					cSnd.SetChannel("chan%s" %(x[0]),
									random.choice(wheightedGates))
		oldAutomatonState = soundGlobals.backgroundUpdateList
		time.sleep(.01)




def setControlCells(width, height, backgroundPartials):
	""" Randomly chooses a list of cells which will control whether an
	individual background (harmonic) partial will be on or off.
	width				---> the cellular automaton's width
	height				---> the cellular automaton's height
	backgroundPartials	---> number or partials per voice
	return				-->> a dictionary for background-sound control
	"""
	# Construct a list of tuples representing the cells of the
	# automaton.
	sampleSize = (backgroundPartials * 3)
	cellList = []
	for x in range(width):
		for y in range(height):
			cell = (x, y)
			cellList.append(cell)
	# Take a random sample, which will serve as the background-sound
	# control cells.
	cellSample = random.sample(cellList, sampleSize)
	# Construct a dictionary with the control channels as keys, and a
	# 3-tuple with cell, oldCellState, onOffRate  and a counter 2-tuple.
	controlChannels = range(1, sampleSize + 1)
	primes = Series.prime(backgroundPartials)
	primesSet = set(primes)
	naturals = range(1, backgroundPartials + 1)
	dictList = []
	for channel, cell in zip (controlChannels, cellSample):
		mod = (channel - 1) % backgroundPartials
		if mod in primesSet:
			onOffRate = primes[mod - 2]
		else:
			onOffRate =  random.choice([1, 2])
		keyValue = (str(channel), (cell, 0, onOffRate, (0, 0)))
		dictList.append(keyValue)
	cellControlDict = dict(dictList)
	return cellControlDict
	
	
def updateControlCells(automaton):
	""" Updates the state of the automaton's sound-controll cells.
	automaton	---> a birdcage cellular automaton
	return		-->> a list of channel-number new-state 2-tuples
	"""
	backgroundUpdateList = []
	for channel, entry in soundGlobals.cellControlDict.iteritems():
		cell			= entry[0]
		oldCellState	= entry[1]
		onOffRate		= entry[2]
		counters		= entry[3]
		counterOn		= counters[0]
		counterOff		= counters[1]
		newCellState	= automaton.get(cell)
		if oldCellState != newCellState:
			if newCellState:
				if not counterOff:
					if  not counterOn:
						counterOn += 1
					elif counterOn % onOffRate:
						counterOn += 1
					else:
						backgroundUpdateList.append((channel, 1))
						counterOn = 0
			else:
				if not counterOn:
					if not counterOff:
						counterOff += 1
					elif counterOff % onOffRate:
						counterOff += 1
					else:
						backgroundUpdateList.append((channel, 0))
						counterOff = 0

			soundGlobals.cellControlDict[channel] = (cell, newCellState,
														onOffRate,
														(counterOn, counterOff))
	return backgroundUpdateList
