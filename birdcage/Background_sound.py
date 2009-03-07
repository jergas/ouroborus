## Import the necessary built-in modules
import time, threading
from random import choice, randint, sample, uniform, random
## Import the necessary user-defined modules
from Csound_Interface import initCsound, perf, csound
from linear_scaler import scaleValueToRange
import Csound_Note
import globals_background_sound as gB

## Variable to stop the threads' iterations. Changed externally (by sound.py)

## Rest of global variables
downBiasedStep		= [-.03, -.02, -.01, -.03, -.02, -.01, .01, .02, .03]
upBiasedStep		= [-.03, -.02, -.01, .01, .02, .03, .01, .02, .03]
nextTotalNoOfPartials	= 39

class Counter(object):
	""" A thread safe counter (by means of lock implementation)"""
	def __init__(self, start):
		self.lock = threading.Lock()
		self.value = start
	def updateCounter(self, plusOrMin):
		self.lock.acquire()
		try:
			self.value = self.value + plusOrMin
		finally:
			self.lock.release()

def backgroundSound1Voice(noteDuration, fundamentalFrequency, panning, specType, firstInstr):
	noOfPartials		= 13
	startDistorFact		= 0.75
	targetDistorFact	= 0.8
	IncrDecrHarmonics	= 1
	firstChannel		= firstInstr - 1
	sleepBeforeGate		= noteDuration - 0.5

	while gB.mainIterCycle == 1:
		instrumentNos	= range(firstInstr, (firstInstr + noOfPartials))
		channelNosOn	= range(firstChannel, (firstChannel + noOfPartials))
		channelNosOff	= channelNosOn[:]
		spectrum = Csound_Note.noteBackground(1, fundamentalFrequency, noOfPartials,
			specType, startDistorFact, targetDistorFact, panning, noteDuration)
		for x in spectrum:
			partialPlusInstr = x.replace('i1', ('i' + str(instrumentNos.pop(0))))
			perf.InputMessage(partialPlusInstr)
		startDistorFact = targetDistorFact
		while 1:
			newValue = targetDistorFact
			if newValue > 0.6 and newValue < 1.15:
				newValue = newValue + (randint(-3, 3) *.01)
			elif newValue >= 1.15:
				newValue = newValue + choice(downBiasedStep)
			elif newValue <= 0.6:
				newValue = newValue + choice(upBiasedStep)
			if newValue >= 0.5 and newValue <= 1.25:
				targetDistorFact = newValue
				break
		time.sleep(abs(sleepBeforeGate))

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
	#channelsCombinations	= [ChannelsThread1, ChannelsThread2, ChannelsThread3]
	#channelsUniverse	= set(ChannelsThread1 + ChannelsThread2 + ChannelsThread3)
	#currentState		= gB.soundControlCells
	#newState		= currentState
	iterText = open('iterText.txt', 'w')

	while gB.mainIterCycle == 1:
		while annumCurrentState == annumNewState:
			annumNewState = gB.annum
		annumCurrentState = annumNewState
		iterText.write('\nannum = ' + str(gB.annum) + '\npopulationNorm=' + str(gB.populationNorm))
		allPartialsOn = []
		onChans = []
		offChans = []
		possiblePartialsOn = round(scaleValueToRange(gB.populationNorm, .001875, .31375, 1, 39))

		if annumNewState % 5 == 0:
			partialsOnT1 = possiblePartialsOn // 3
			allPartialsOn.append(partialsOnT1)
			onChans.append(onChansT1)
			offChans.append(offChansT1)
		if annumNewState % 3 == 0:
			partialsOnT2 = (possiblePartialsOn // 3) + (possiblePartialsOn % 3)
			allPartialsOn.append(partialsOnT2)
			onChans.append(onChansT2)
			offChans.append(offChansT2)
		if annumNewState % 7 == 0:
			partialsOnT3 = possiblePartialsOn // 3
			allPartialsOn.append(partialsOnT3)
			onChans.append(onChansT3)
			offChans.append(offChansT3)
		
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
					csound.SetChannel("chan%s" %(newOff), 0.125)
					y.append(newOff)
		if annumNewState % 105 == 0:
			time.sleep(.11)
			iterText.write('\nannum divisible by 105!!!!')
		elif annumNewState % 35 == 0:
			time.sleep(.07)
			iterText.write('\nannum divisible by 35!!!!')
		elif annumNewState % 15 == 0:
			time.sleep(.05)
			iterText.write('\nannum divisible by 15!!!!')

		
			


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
	argsList	= [(-17, 150, 0.25, 0, 2), (-13, 100, 0.5, 3, 15), (-23, 125, 0.75, 1, 27)]
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
