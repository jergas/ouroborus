 

import time, threading
from random import choice, randint, uniform

from csnd_interface import initCSnd, perf, cSnd
from linear_scaler import scaleValToRng
from equal_temper import centsToFreq
import csnd_note as csndNote
import sound_globals as SGlobals


def oneBckgrndVox(frstInstr, dur, ptch, strtDistr, specType, distrBias, pan):
	"""Starts a note-generating loop which -parting from initial
	parameters- is modified via the simulation (and some randomness).

	frstInstr	---> First csound instrument that this voice will use
	dur			---> Time that each note of the voice will last
	ptch		---> Initial ptch of the fundamental frecuency
	strtDistr	---> The initial spectral-distortion factor
	specType	---> Spectrum type (all, even, fibonacci or prime)
	distrBias	---> A bias for how the spectrum will tend to vary
	pan			---> Note's panning
	"""
	fundFrec		= centsToFreq(ptch)
	numOfPartls		= 13
	endDistrFact	= strtDistr + scaleValToRng(SGlobals.populNorm[0],
												.001875, .31375, 0, 0.2)

	while SGlobals.mainIterCycle == 1:
		# Generate instrument nos. (for each partial) and a spectrum.
		instrNos = range(frstInstr, (frstInstr + numOfPartls))
		spectrum = csndNote.bckgrndNote(1, fundFrec, numOfPartls, specType,
									strtDistr, endDistrFact, pan, dur)
		# Assign the spectrum's partial an intrument no., and feed them
		# to csound.
		for x in spectrum:
			partialInstrNo = x.replace('i1', ('i' + str(instrNos.pop(0))))
			perf.InputMessage(partialInstrNo)
		# Change the parameters for the next note.
		fundFrec = centsToFreq(ptch + randint(-50, 50))
		strtDistr = endDistrFact
		if not distrBias:
			endDistrFact = strtDistr + scaleValToRng(SGlobals.populNorm[0],
													.001875, .31375, -0.04,
													0.004)
		elif distrBias is 1:
			endDistrFact = strtDistr + scaleValToRng(SGlobals.populNorm[0],
													.001875, .31375, 0, 0.08)
		elif distrBias is 2:
			endDistrFact = strtDistr + scaleValToRng(SGlobals.populNorm[0],
													.001875, .31375, -.08, 0)
		if endDistrFact > .15:
			distrBias = 2
		if endDistrFact < .0001:
			distrBias = 1
		if endDistrFact < 0:
			endDistrFact = 0.0001
		time.sleep(abs(dur) - 1)	


def ctrlBckgrndSnd():
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

	while SGlobals.mainIterCycle == 1:
		allpartlsOn		= []
		onChans				= []
		offChans			= []
		possiblepartlsOn 	= round(scaleValToRng(SGlobals.populNorm[0],
												.001875, .31375, 1, 39))
		updatepartls = 0
		# Test how many partials will be attenuated or boosted, and
		# prepares the lists that do the trick.
		if counter % 7 == 0:
			partlsOnT1 = possiblepartlsOn // 3
			allpartlsOn.append(partlsOnT1)
			onChans.append(onChansT1)
			offChans.append(offChansT1)
			updatepartls += 1
		if counter % 5 == 0:
			partlsOnT2 = (possiblepartlsOn // 3) + (possiblepartlsOn % 3)
			allpartlsOn.append(partlsOnT2)
			onChans.append(onChansT2)
			offChans.append(offChansT2)
			updatepartls += 1
		if counter % 11 == 0:
			partlsOnT3 = possiblepartlsOn // 3
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
						newOn = y.pop(0)
						cSnd.SetChannel("chan%s" %(newOn), 1)
						x.append(newOn)
				if w < len(x):
					updatepartls = len(x) - w
					for z in range(0, int(updatepartls)):
						newOff = x.pop(randint(0, len(x)-1))
						cSnd.SetChannel("chan%s" %(newOff),
										choice(wheightedGates))
						y.append(newOff)
		# Introduces (slight) discontinuity to the update of partial's
		# intencity.		
		if SGlobals.sndCtrlCells == [1, 1, 1]:
			time.sleep(0.017)
		elif SGlobals.sndCtrlCells == [1, 1, 0]:
			time.sleep(0.013)
		elif SGlobals.sndCtrlCells == [1, 0, 1]:
			time.sleep(0.011)
		elif SGlobals.sndCtrlCells == [0, 1, 1]:
			time.sleep(0.007)
		elif SGlobals.sndCtrlCells == [1, 0, 0]:
			time.sleep(0.005)
		elif SGlobals.sndCtrlCells == [0, 1, 0]:
			time.sleep(0.003)
		elif SGlobals.sndCtrlCells == [0, 0, 1]:
			time.sleep(0.002)
		if counter % 105 == 0:
			time.sleep(0.031)
		elif counter % 35 == 0:
			time.sleep(.029)
		elif counter % 21 == 0:
			time.sleep(.023)
		elif counter % 15== 0:
			time.sleep(.019)
		counter += 1


def playback():
	""" Creates three threads, each running a background voice thread.
	"""
	argsList	= [(2, -24, 3400, 0.005, 0, 1, 0.25),
					(15, -20, 3400, 0.003, 3, 0, 0.5),
					(27, -30, 3400, 0.007, 1, 2, 0.75)]
	voiceNo		= 1

	for x in argsList:
		threadName = 'BackgroundVoice' + str(voiceNo)
		voice = threading.Thread(name=threadName, target=oneBckgrndVox, args=x)
		voice.start()
		voiceNo = voiceNo + 1


def control():
	"""Starts the background sound control thread, which modifies the
	the background sound voices.
	"""
	controlThread = threading.Thread(name='backgroundVoicesControl',
									target=ctrlBckgrndSnd)
	controlThread.start()

if __name__ == "__main__":
# This was used for debugging, and may become handy again.
	initCSnd()
	playback()
	control()
