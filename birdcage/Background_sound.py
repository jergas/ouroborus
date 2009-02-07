## Import the necessary built-in modules
import time, threading
from random import choice, randint, sample, uniform, random
## Import the necessary user-defined modules
from Csound_Interface import initCsound, perf, csound
import Csound_Note

## Variable to stop the threads' iterations. Changed externally (by main_sequence.py)
mainIterCycle		= 1
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

def backgroundSound(noteDuration, fundamentalFrequency, specType, firstInstr, timeGate):
	noOfPartials		= 13
	startDistorFact		= 0.75
	targetDistorFact	= 0.8
	overallPanning		= .5
	IncrDecrHarmonics	= 1
	firstChannel		= firstInstr - 1
	#sleepBeforeGate		= float(noteDuration)/float(noOfPartials)

	while mainIterCycle == 1:
		instrumentNos	= range(firstInstr, (firstInstr + noOfPartials))
		channelNosOn	= range(firstChannel, (firstChannel + noOfPartials))
		channelNosOff	= channelNosOn[:]
		spectrum = Csound_Note.noteBackground(1, fundamentalFrequency, noOfPartials,
			specType, startDistorFact, targetDistorFact, overallPanning, noteDuration)
		while len(spectrum) > 0:
			partial = spectrum.pop(0)
			partialPlusInstr = partial.replace('i1', ('i' + str(instrumentNos.pop(0))))
			perf.InputMessage(partialPlusInstr)
			channelOn = channelNosOn.pop(0)
			csound.SetChannel("chan%s" %(channelOn), 1)
		while len(channelNosOff) > 0:
			time.sleep(timeGate)
			channelOff = channelNosOff.pop(0)
			csound.SetChannel("chan%s" %(channelOff), 0)
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


## Background Sound's playback method.
def playback():
	""" Background_sound's playback method"""
	argsList	= [[-11, 82.405, 3, 2, .84], [-7, 98, 2, 15, .53], [-13, 69.295, 1, 27, 1]]
	voiceNo		= 1

	for x in argsList:
		threadName = 'voice' + str(voiceNo)
		voice = threading.Thread(name=threadName, target=backgroundSound, args=(x))
		voice.start()
		voiceNo = voiceNo + 1
if __name__ == "__main__":
	initCsound()
	playback()
