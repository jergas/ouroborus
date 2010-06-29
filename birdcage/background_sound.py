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

def oneBckgrndVox(frstInstr, dur, ptch, strtDistr, specType, distrBias, pan):
	"""Starts a note-generating loop which -parting from initial
	parameters- is modified via the simulation (and some randomness).

	frstInstr	---> First csound instrument that this voice will use
	dur			---> Time that each note of the voice will last
	ptch		---> Initial ptch of the fundamental frecuency
	strtDistr	---> The initial spectral-distortion factor
	specType	---> Spectrum type (odd, even, fibonacci or prime)
	distrBias	---> A bias for how the spectrum will tend to vary
	pan			---> Note's panning
	"""
	fundFreq		= centsToFreq(ptch)
	numOfPartls		= 13
	endDistrFact	= strtDistr + Scaling.valToRng(soundGlobals.populNorm[0],
													soundGlobals.populMin[0],
													soundGlobals.populMax[0],
													-0.1, 0.1)
	instrNos 		= range(frstInstr, (frstInstr + numOfPartls))
	# Instantiate the background sound note class.
	bckgrndNote = BckgrndNote(instrNos, fundFreq, numOfPartls, specType,
								strtDistr, endDistrFact, pan, dur)

	while soundGlobals.mainIterCycle == 1:
		spectrum	= bckgrndNote.mkScoStrings()
#		logging.write ('\n' + str(len(spectrum)))
		# Feed the partials to Csound.
		for x in spectrum:
			perf.InputMessage(x)
		# Change the parameters for the next note.
		#fundFreq = centsToFreq(ptch + random.randint(-50, 50))
		#bckgrndNote.fundFreq = fundFreq
		#strtDistr = endDistrFact
		#bckgrndNote.distor = strtDistr
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
#		logging.write('\nsleeping' + str(counter))
		time.sleep(abs(dur))
#		logging.write ('\nwaking' + str(counter))


def ctrlBckgrndSndOLD():
	"""Uses parameters from the automaton (stored by sound.py in
	sound_globals.py) to control the background sound after the notes
	have started. Changes at note-start times are handled by
	oneBckgrndVox().
	"""	
	chansT1			= range(1, 14)
	chansT2			= range(14, 27)
	chansT3			= range(27, 40)
	onChansT1		= []
	onChansT2		= []
	onChansT3		= []
	offChansT1		= chansT1
	offChansT2		= chansT2
	offChansT3		= chansT3
	wheightedGates	= [0.5]*7 + [0.25]*5 + [0.125]*3 + [0.0625]*2 + [.03125]*17
	counter			= 1.0
	oldPartialsOn	=	0

	while soundGlobals and soundGlobals.mainIterCycle:
		allpartlsOn			= []
		onChans				= []
		offChans			= []
		updatepartls 		= 0
		possiblePartlsOn	= round(Scaling.valToRng(soundGlobals.populNorm[0],
											.001875, .31375, 1, 39))
	# Wait until number of the automaton's live cells has varied.
	# (needed when running the threaded version of the threaded
	# execution).
		while oldPartialsOn == possiblePartlsOn:
			time.sleep(.01)
			break
		oldPartialsOn = possiblePartlsOn
		# Test how many partials will be attenuated or boosted, and
		# prepares the lists that do the trick.
		if counter % 7 == 0:
			partlsOnT1 = possiblePartlsOn // 3
			allpartlsOn.append(partlsOnT1)
			onChans.append(onChansT1)
			offChans.append(offChansT1)
			updatepartls += 1
		if counter % 5 == 0:
			partlsOnT2 = (possiblePartlsOn // 3) + (possiblePartlsOn % 3)
			allpartlsOn.append(partlsOnT2)
			onChans.append(onChansT2)
			offChans.append(offChansT2)
			updatepartls += 1
		if counter % 11 == 0:
			partlsOnT3 = possiblePartlsOn // 3
			allpartlsOn.append(partlsOnT3)
			onChans.append(onChansT3)
			offChans.append(offChansT3)
			updatepartls += 1
		## Attenuate or boost the relevant partials
		if updatepartls:
			for w, x, y in zip(allpartlsOn, onChans, offChans):
				if w > len(x):
					updatepartls = w - len(x)
					for z in range(0, int(updatepartls)):
						if len(y):
							newOn = y.pop(0)
							cSnd.SetChannel("chan%s" %(newOn), 1)
							x.append(newOn)
				if w < len(x):
					updatepartls = len(x) - w
					for z in range(0, int(updatepartls)):
						if len(x):
							newOff = x.pop(random.randint(0, len(x)-1))
							cSnd.SetChannel("chan%s" %(newOff),
											random.choice(wheightedGates))
							y.append(newOff)

		if soundGlobals.populNorm[0] > soundGlobals.populMax[0]:
			soundGlobals.populMax[0] = soundGlobals.populNorm[0]
		counter += 1
		time.sleep(.01)
		
		
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
					cSnd.SetChannel("chan%s" %(x[0]), 1)
				else:
					cSnd.SetChannel("chan%s" %(x[0]), 0)
#									random.choice(wheightedGates))
		oldAutomatonState = soundGlobals.backgroundUpdateList
		time.sleep(.1)




def setControlCells(width, height, controlChannels=range(1,40)):
	""" Randomly chooses a list of cells which will control whether an
	individual background (harmonic) partial will be on or off.
	width	---> the cellular automaton's width
	height	---> the cellular automaton's height
	return	-->> a dictionary key=controlChannel value=(cell, state)
	"""
	# Construct a list of tuples representing the cells of the
	# automaton.
	cellList = []
	for x in range(width):
		for y in range(height):
			cell = (x, y)
			cellList.append(cell)
	# Take a random sample, which will serve as the background-sound
	# control cells.
	cellSample = random.sample(cellList, 39)
	# Construct a dictionary with the control channels as keys, and a
	# 2-tuple with cell-address and cell-state as values.
	dictList = []
	for channel, cell in zip (controlChannels, cellSample):
		keyValue = (str(channel), (cell, 0))
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
			soundGlobals.cellControlDict[channel] = (cellAndCellState[0],
														cellState)
			backgroundUpdateList.append((channel, cellState))
	return backgroundUpdateList
