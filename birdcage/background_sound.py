## Contains the background sound generation and control methods, which
# are converted into threads by playbak() and control(), respectively.

# Python's native libraries
import time
import threading
import random
# Sound-related submodules
from csnd_interface import initCSnd, perf, cSnd
import Numeric_utils as NU
from equal_temper import centsToFreq
from Csnd_notes import BckgrndNote
import sound_globals as soundGlobals

# Instantiate the numeric scaling class. 
Scaling = NU.Scaling()

#logging = open("log.txt", 'w')

def oneBckgrndVox(frstInstr, dur, ptch, strtDistr, specType, numOfPartls, pan):
	"""Starts a note-generating loop which -parting from initial
	parameters- is modified via the simulation (and some randomness).

	frstInstr	---> First csound instrument that this voice will use
	dur			---> Time that each note of the voice will last
	ptch		---> Initial ptch of the fundamental frecuency
	strtDistr	---> The initial spectral-distortion factor
	specType	---> Spectrum type (odd, even, fibonacci or prime)
	numOfPartls	---> Number of partials in the harmonic spectrum
	pan			---> Note's panning
	"""
	fundFreq		= centsToFreq(ptch)
	endDistrFact	= strtDistr + (.01 * random.randint(-10, 10))
	instrNos 		= range(frstInstr, (frstInstr + numOfPartls))
	# Instantiate the background sound note class.
	bckgrndNote = BckgrndNote(instrNos, fundFreq, numOfPartls, specType,
								strtDistr, endDistrFact, pan, dur)

	while soundGlobals.mainIterCycle == 1:
		spectrum	= bckgrndNote.mkScoStrings()
		# Feed the partials to Csound.
#		print 'Voice Update'
		for x in spectrum:
			perf.InputMessage(x)
		# Change the parameters for the next note.
		fundFreq = centsToFreq(ptch + random.randint(-50, 50))
		bckgrndNote.fundFreq = fundFreq
		strtDistr = endDistrFact
		bckgrndNote.distor = strtDistr
		endDistrFact	= strtDistr + (.01 * random.randint(-10, 10))
		bckgrndNote.distor2 = endDistrFact
		#if not distrBias:
		#	endDistrFact = strtDistr+Scaling.valToRng(soundGlobals.populNorm[0],
		#												soundGlobals.populMin[0],
		#												soundGlobals.populMax[0],
		#												-0.1, 0.1)
		#	bckgrndNote.distor2 = endDistrFact
		#elif distrBias is 1:
		#	endDistrFact = strtDistr+Scaling.valToRng(soundGlobals.populNorm[0],
		#												soundGlobals.populMin[0],
		#												soundGlobals.populMax[0],
		#												0, 0.2)
		#	bckgrndNote.distor2 = endDistrFact
		#elif distrBias is 2:
		#	endDistrFact = strtDistr+Scaling.valToRng(soundGlobals.populNorm[0],
		#												soundGlobals.populMin[0],
		#												soundGlobals.populMax[0],
		#												-.2, 0)
		#	bckgrndNote.distor2 = endDistrFact
		#if endDistrFact > .75:
		#	distrBias = 2
		#if endDistrFact < .25:
		#	distrBias = 1
		time.sleep(abs(dur))

		
		
def ctrlBckgrndSnd():
	"""Uses parameters from the automaton (stored by sound.py in
	sound_globals.py) to control the background sound after the notes
	have started. Changes at note-start times are handled by
	oneBckgrndVox().
	"""	
	wheightedGates	= [0.5]*2 + [0.25]*3 + [0.125]*5 + [0.0625]*7 + [.03125]*11
	oldAutomatonState	= soundGlobals.backgroundUpdateList
	
	while soundGlobals and soundGlobals.mainIterCycle:
		# Wait until number of the automaton's live cells has varied.
		newAutomatonState = soundGlobals.backgroundUpdateList
#		while oldAutomatonState == newAutomatonState:
#			time.sleep(.1)
#			break
		# Attenuate or boost the relevant partials
		if oldAutomatonState != newAutomatonState:
			for x in newAutomatonState:
				if x[1] == 1:
					mod13 = (int(x[0]) % 13) + 1
					if not x[2] % mod13:
						cSnd.SetChannel("chan%s" %(x[0]), 1)
				else:
					cSnd.SetChannel("chan%s" %(x[0]),
									random.choice(wheightedGates))
#									random.choice(wheightedGates))
		oldAutomatonState = soundGlobals.backgroundUpdateList
		time.sleep(.1)




def setControlCells(width, height, backgroundPartials):
	""" Randomly chooses a list of cells which will control whether an
	individual background (harmonic) partial will be on or off.
	width	---> the cellular automaton's width
	height	---> the cellular automaton's height
	return	-->> a dictionary key=controlChannel value=(cell, state)
	"""
	# Construct a list of tuples representing the cells of the
	# automaton.
	backgroundPartials = (backgroundPartials * 3) + 1
	controlChannels = range(1, backgroundPartials)
	cellList = []
	for x in range(width):
		for y in range(height):
			cell = (x, y)
			cellList.append(cell)
	# Take a random sample, which will serve as the background-sound
	# control cells.
	cellSample = random.sample(cellList, backgroundPartials)
	# Construct a dictionary with the control channels as keys, and a
	# 3-tuple with cell-address, cell-state as values and a counter.
	dictList = []
	for channel, cell in zip (controlChannels, cellSample):
		keyValue = (str(channel), (cell, 0, 0))
		dictList.append(keyValue)
	cellControlDict = dict(dictList)
	return cellControlDict
	
	
def updateControlCells(automaton):
	""" Updates the state of the automaton's sound-controll cells.
	automaton	---> a birdcage cellular automaton
	return		-->> a list of channel-number new-state 2-tuples
	"""
	backgroundUpdateList = []
	for channel, cellAndCellState in soundGlobals.cellControlDict.iteritems():
		oldCellState = soundGlobals.cellControlDict[channel][1]
		cellState = automaton.get(cellAndCellState[0])
		if oldCellState != cellState:
			counter = soundGlobals.cellControlDict[channel][2]
			if cellState:
				counter += 1
			soundGlobals.cellControlDict[channel] = (cellAndCellState[0],
														cellState,
														counter)
			backgroundUpdateList.append((channel, cellState, counter))
	return backgroundUpdateList
