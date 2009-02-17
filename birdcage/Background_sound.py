## Import the necessary built-in modules
import time, threading
from random import choice, randint, sample, uniform, random
## Import the necessary user-defined modules
from Csound_Interface import initCsound, perf, csound
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

def backgroundSound1Voice(noteDuration, fundamentalFrequency, specType, firstInstr):
	noOfPartials		= 13
	startDistorFact		= 0.75
	targetDistorFact	= 0.8
	overallPanning		= .5
	IncrDecrHarmonics	= 1
	firstChannel		= firstInstr - 1
	sleepBeforeGate		= noteDuration - 0.5

	while gB.mainIterCycle == 1:
		instrumentNos	= range(firstInstr, (firstInstr + noOfPartials))
		channelNosOn	= range(firstChannel, (firstChannel + noOfPartials))
		channelNosOff	= channelNosOn[:]
		spectrum = Csound_Note.noteBackground(1, fundamentalFrequency, noOfPartials,
			specType, startDistorFact, targetDistorFact, overallPanning, noteDuration)
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
		while 1:
			overallPanning = (randint(-3, 3) *.05)
			if overallPanning >= 0 and overallPanning <=1:
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

	(gB.deadCell1Count, gB.liveDeadCells) = changeState(soundCellsStates[0], gB.deadCell1Count, gB.liveDeadCells)
	(gB.deadCell2Count, gB.liveDeadCells) = changeState(soundCellsStates[1], gB.deadCell2Count, gB.liveDeadCells)
	(gB.deadCell3Count, gB.liveDeadCells) = changeState(soundCellsStates[2], gB.deadCell3Count, gB.liveDeadCells)

	return gB.liveDeadCells

def controlBackgroundSound():
	
	ChannelsThread1		= range(1, 14)
	ChannelsThread2		= range(14, 27)
	ChannelsThread3		= range(27, 40)
	channelsCombinations	= [ChannelsThread1, ChannelsThread2, ChannelsThread3]
	channelsUniverse	= set(ChannelsThread1 + ChannelsThread2 + ChannelsThread3)
	currentState		= gB.liveDeadCells
	newState		= currentState

	while gB.mainIterCycle == 1:
		while currentState == newState:
			newState = cellsStates(gB.liveDeadCells)
		currentState = newState

		for x, y in zip(newState, channelsCombinations):
			if x ==1:
				for z in y:
					csound.SetChannel("chan%s" %(z), 0)
			if x ==0:
				for z in y:
					csound.SetChannel("chan%s" %(z), 1)

def playback():
	""" Background_sound's playback method"""
	argsList	= [(-17, 82.405, 3, 2), (-13, 98, 2, 15), (-23, 69.295, 1, 27)]
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
