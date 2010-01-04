## Contains the background sound generation and control methods, which
# are converted into threads by playbak() and control(), respectively.

# Python's native libraries
import time
import threading
from random import choice, randint, uniform
# Sound-related submodules
from csnd_interface import initCSnd, perf, cSnd
import Numeric_utils as NU
from equal_temper import centsToFreq
from Csnd_notes import BckgrndNote
import sound_globals as sGlobals

# Instantiate the numeric scaling class. 
Scaling = NU.Scaling()


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
	numOfPartls		= 12
	endDistrFact	= strtDistr + Scaling.valToRng(sGlobals.populNorm[0],
													sGlobals.populMin[0],
													sGlobals.populMax[0],
													-0.1, 0.1)
	instrNos 		= range(frstInstr, (frstInstr + numOfPartls))
	# Instantiate the background sound note class.
	bckgrndNote = BckgrndNote(instrNos, fundFreq, numOfPartls, specType,
								strtDistr, endDistrFact, pan, dur)

	while sGlobals.mainIterCycle == 1:
		spectrum	= bckgrndNote.mkScoStrings()
		# Feed the partials to Csound.
		for x in spectrum:
			perf.InputMessage(x)
		# Change the parameters for the next note.
		fundFreq = centsToFreq(ptch + randint(-50, 50))
		bckgrndNote.fundFreq = fundFreq
		strtDistr = endDistrFact
		bckgrndNote.distor = strtDistr
		if not distrBias:
			endDistrFact = strtDistr + Scaling.valToRng(sGlobals.populNorm[0],
														sGlobals.populMin[0],
														sGlobals.populMax[0],
														-0.1, 0.1)
			bckgrndNote.distor2 = endDistrFact
		elif distrBias is 1:
			endDistrFact = strtDistr + Scaling.valToRng(sGlobals.populNorm[0],
														sGlobals.populMin[0],
														sGlobals.populMax[0],
														0, 0.2)
			bckgrndNote.distor2 = endDistrFact
		elif distrBias is 2:
			endDistrFact = strtDistr + Scaling.valToRng(sGlobals.populNorm[0],
														sGlobals.populMin[0],
														sGlobals.populMax[0],
														-.2, 0)
			bckgrndNote.distor2 = endDistrFact
		if endDistrFact > .75:
			distrBias = 2
		if endDistrFact < .25:
			distrBias = 1
		time.sleep(abs(dur) - 2)	


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
	oldPartialsOn	=	0

	while sGlobals and sGlobals.mainIterCycle:
		allpartlsOn			= []
		onChans				= []
		offChans			= []
		updatepartls 		= 0
		possiblePartlsOn	= round(Scaling.valToRng(sGlobals.populNorm[0],
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
							newOff = x.pop(randint(0, len(x)-1))
							cSnd.SetChannel("chan%s" %(newOff),
											choice(wheightedGates))
							y.append(newOff)
		# Introduces (slight) discontinuity to the update of partial's
		# intencity.		
#		if sGlobals.sndCtrlCells == [1, 1, 1]:
#			time.sleep(0.017)
#		elif sGlobals.sndCtrlCells == [1, 1, 0]:
#			time.sleep(0.013)
#		elif sGlobals.sndCtrlCells == [1, 0, 1]:
#			time.sleep(0.011)
#		elif sGlobals.sndCtrlCells == [0, 1, 1]:
#			time.sleep(0.007)
#		elif sGlobals.sndCtrlCells == [1, 0, 0]:
#			time.sleep(0.005)
#		elif sGlobals.sndCtrlCells == [0, 1, 0]:
#			time.sleep(0.003)
#		elif sGlobals.sndCtrlCells == [0, 0, 1]:
#			time.sleep(0.002)
#		if counter % 105 == 0:
#			time.sleep(0.031)
#		elif counter % 35 == 0:
#			time.sleep(.029)
#		elif counter % 21 == 0:
#			time.sleep(.023)
#		elif counter % 15== 0:
#			time.sleep(.019)
		if sGlobals.populNorm[0] > sGlobals.populMax[0]:
			sGlobals.populMax[0] = sGlobals.populNorm[0]
		counter += 1
		time.sleep(.01)


voiceList	= []

def playback():
	""" Creates three threads, each running a background voice thread.
	"""
	argsList	= [(2, -12, 3400, 0.8, 0, 1, 0.25),
					(15, -8, 3400, 0.5, 3, 0, 0.5),
					(27, -14, 3400, 0.2, 1, 2, 0.75)]
	voiceNo		= 1
#	voiceList	= []

	for x in argsList:
		threadName = 'BackgroundVoice' + str(voiceNo)
		voice = threading.Thread(name=threadName, target=oneBckgrndVox, args=x)
		voice.start()
		voiceList.append(voice)
		voiceNo = voiceNo + 1
#	for x in voiceList:
#		x.join()


def control():
	"""Starts the background sound control thread, which modifies the
	the background sound voices.
	"""
	controlThread = threading.Thread(name='backgroundVoicesControl',
									target=ctrlBckgrndSnd)
	controlThread.start()
	voiceList.append(controlThread)
#	controlThread.join()

def joinThreads():
	for x in voiceList:
		x.join()

# This was used for debugging, and may become handy again.
if __name__ == "__main__":
	initCSnd()
	playback()
	control()
