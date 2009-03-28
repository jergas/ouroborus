## Import the necessary built-in modules
import time, threading
from random import choice, randint, sample, uniform, random
## Import the necessary user-defined modules
from Csound_Interface import initCsound, perf, csound
from linear_scaler import scaleValueToRange
from equal_temper import pitchInCentsToFreq
import Csound_Note
import globals_background_sound as gB


## Variable to stop the threads' iterations. Changed externally (by sound.py)

## Rest of global variables
downBiasedStep		= [-.03, -.02, -.01, -.03, -.02, -.01, .01, .02, .03]
upBiasedStep		= [-.03, -.02, -.01, .01, .02, .03, .01, .02, .03]
nextTotalNoOfPartials	= 39

#class Counter(object):
#	""" A thread safe counter (by means of lock implementation)"""
#	def __init__(self, start):
#		self.lock = threading.Lock()
#		self.value = start
#	def updateCounter(self, plusOrMin):
#		self.lock.acquire()
#		try:
#			self.value = self.value + plusOrMin
#		finally:
#			self.lock.release()

def backgroundSound1Voice(firstInstr, duration, pitch, startDistorFact, specType, changeBias, panning):
	fundamentalFreq		= pitchInCentsToFreq(pitch)
	noOfPartials		= 13
	targetDistorFact	= startDistorFact + scaleValueToRange(gB.populationNorm, .001875, .31375, 0, 0.2)
	firstChannel		= firstInstr - 1
	soundDuration		= duration

	while gB.mainIterCycle == 1:
		instrumentNos	= range(firstInstr, (firstInstr + noOfPartials))
		channelNosOn	= range(firstChannel, (firstChannel + noOfPartials))
		spectrum = Csound_Note.noteBackground(1, fundamentalFreq, noOfPartials,
			specType, startDistorFact, targetDistorFact, panning, duration)
		for x in spectrum:
			partialPlusInstr = x.replace('i1', ('i' + str(instrumentNos.pop(0))))
			perf.InputMessage(partialPlusInstr)
		fundamentalFreq = pitchInCentsToFreq(pitch + randint(-50, 50))
		startDistorFact = targetDistorFact
		if changeBias == 0:
			targetDistorFact = startDistorFact + scaleValueToRange(gB.populationNorm, .001875, .31375, -0.5, 0.5)
		elif changeBias == 1:
			targetDistorFact = startDistorFact + scaleValueToRange(gB.populationNorm, .001875, .31375, 0, 0.1)
		elif changeBias == 2:
			targetDistorFact = startDistorFact + scaleValueToRange(gB.populationNorm, .001875, .31375, -.1, 0)
		if targetDistorFact > .15:
			changeBias = 2
		if targetDistorFact < .002:
			changeBias = 1
		if targetDistorFact < 0:
			targetDistorFact = 0.0001
		time.sleep(abs(duration))

def changeState(cellState, counter, controlList):
	if cellState == 1:
		controlList.append(1)
	elif cellState == 0:
		if counter == 1:
			controlList.append(0)
			counter = 0
		elif counter < 1:
			counter += 1
	return (counter, controlList)

def cellsStates(soundCellsStates):

	(gB.deadCell1Count, gB.soundControlCells) = changeState(soundCellsStates[0], gB.deadCell1Count, gB.soundControlCells)
	(gB.deadCell2Count, gB.soundControlCells) = changeState(soundCellsStates[1], gB.deadCell2Count, gB.soundControlCells)
	(gB.deadCell3Count, gB.soundControlCells) = changeState(soundCellsStates[2], gB.deadCell3Count, gB.soundControlCells)

	return gB.soundControlCells	

def controlBackgroundSound():
	
	ChannelsThread1		= range(1, 14)
	ChannelsThread2		= range(14, 27)
	ChannelsThread3		= range(27, 40)
	onChansT1		= []
	onChansT2		= []
	onChansT3		= []
	offChansT1		= ChannelsThread1
	offChansT2		= ChannelsThread2
	offChansT3		= ChannelsThread3
	annumCurrentState	= gB.annum
	annumNewState		= annumCurrentState
	wheightedGates		= [0.5]*7 + [0.25]*5 + [0.125]*3 + [0.0625]*2 + [.03125]*17
	counter			= 1.0
	#channelsCombinations	= [ChannelsThread1, ChannelsThread2, ChannelsThread3]
	#channelsUniverse	= set(ChannelsThread1 + ChannelsThread2 + ChannelsThread3)
	#currentState		= gB.soundControlCells
	#newState		= currentState

	while gB.mainIterCycle == 1:
		while annumCurrentState == annumNewState:
			annumNewState = gB.annum
		annumCurrentState = annumNewState
		allPartialsOn = []
		onChans = []
		offChans = []
		possiblePartialsOn = round(scaleValueToRange(gB.populationNorm, .001875, .31375, 1, 39))
		updatePartials = 0

		if counter % 7 == 0:
			partialsOnT1 = possiblePartialsOn // 3
			allPartialsOn.append(partialsOnT1)
			onChans.append(onChansT1)
			offChans.append(offChansT1)
			updatePartials += 1
		if counter % 5 == 0:
			partialsOnT2 = (possiblePartialsOn // 3) + (possiblePartialsOn % 3)
			allPartialsOn.append(partialsOnT2)
			onChans.append(onChansT2)
			offChans.append(offChansT2)
			updatePartials += 1
		if counter % 11 == 0:
			partialsOnT3 = possiblePartialsOn // 3
			allPartialsOn.append(partialsOnT3)
			onChans.append(onChansT3)
			offChans.append(offChansT3)
			updatePartials += 1
		if updatePartials != 0:
			for w, x, y in zip(allPartialsOn, onChans, offChans):
				if w > len(x):
					updatePartials = w - len(x)
					for z in range(0, int(updatePartials)):
						newOn = y.pop(0)
						csound.SetChannel("chan%s" %(newOn), 1)
						x.append(newOn)
				if w < len(x):
					updatePartials = len(x) - w
					for z in range(0, int(updatePartials)):
						newOff = x.pop(randint(0, len(x)-1))
						csound.SetChannel("chan%s" %(newOff), choice(wheightedGates))
						y.append(newOff)


		if gB.soundControlCells == [1, 1, 1]:
			time.sleep(0.017)
		elif gB.soundControlCells == [1, 1, 0]:
			time.sleep(0.013)
		elif gB.soundControlCells == [1, 0, 1]:
			time.sleep(0.011)
		elif gB.soundControlCells == [0, 1, 1]:
			time.sleep(0.007)
		elif gB.soundControlCells == [1, 0, 0]:
			time.sleep(0.005)
		elif gB.soundControlCells == [0, 1, 0]:
			time.sleep(0.003)
		elif gB.soundControlCells == [0, 0, 1]:
			time.sleep(0.002)
		if counter % 105 == 0:
			time.sleep(0.031)
		elif counter % 35 == 0:
			time.sleep(.029)
		elif counter % 21 == 0:
			time.sleep(.023)
		elif counter % 15 == 0:
			time.sleep(.019)
		counter += 1

		
			


#		while currentState == newState:
#			newState = cellsStates(gB.soundControlCells)
#		currentState = newState

#		for x, y in zip(newState, channelsCombinations):
#			if x ==1:
#				for z in y:
#					csound.SetChannel("chan%s" %(z), 0)
#			if x ==0:
#				for z in y:
#					csound.SetChannel("chan%s" %(z), 1)

def playback():
	""" Background_sound's playback method"""
	argsList	= [(2, -11, 3400, 0.005, 0, 1, 0.25), (15, -7, 3400, 0.003, 3, 0, 0.5), (27, -13, 3400, 0.007, 1, 2, 0.75)]
	voiceNo		= 1

	for x in argsList:
		threadName = 'BackgroundVoice' + str(voiceNo)
		voice = threading.Thread(name=threadName, target=backgroundSound1Voice, args=x)
		voice.start()
		voiceNo = voiceNo + 1

def control():
	controlThread = threading.Thread(name='backgroundVoicesControl', target=controlBackgroundSound)
	controlThread.start()

if __name__ == "__main__":
	initCsound()
	playback()
	control()
