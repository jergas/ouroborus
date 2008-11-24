## Import the necessary built-in modules
import time, threading
from random import choice, randint
## Import the necessary user-defined modules
from Csound_Interface import initCsound, perf
import Csound_Note

## Variable to stop the threads' iterations. Changed externally (by main_sequence.py)
mainIterCycle		= 1
## Rest of global variables
downBiasedStep		= [-.03, -.02, -.01, -.03, -.02, -.01, .01, .02, .03]
upBiasedStep		= [-.03, -.02, -.01, .01, .02, .03, .01, .02, .03]
nextTotalNoOfPartials	= 6

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

## Instantiation of the counter.
globalNoOfPartialsCounter = Counter(nextTotalNoOfPartials)


class backgroundSound1(threading.Thread):
	"""Threading class for the background sound."""
	def run(self):
		fundamentalFrequency	= 165
		noOfPartials		= 2
		specType		= 0
		startDistorFact		= 0.75
		targetDistorFact	= 0.78
		overallPanning		= .75
		noteDuration		= 17
		IncrDecrHarmonics	= 1
		while mainIterCycle == 1:
			spectrum = Csound_Note.noteI2(fundamentalFrequency, noOfPartials, specType, 					startDistorFact, targetDistorFact, overallPanning, noteDuration)
			while len(spectrum) > 0:
                		partial = spectrum.pop(0)
                		perf.InputMessage(partial)
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
			if IncrDecrHarmonics == 1:
				noOfPartials = noOfPartials + 1
				globalNoOfPartialsCounter.updateCounter(1)
				if noOfPartials > 13:
					IncrDecrHarmonics = 0
			elif IncrDecrHarmonics == 0:
				noOfPartials = noOfPartials - 1
				globalNoOfPartialsCounter.updateCounter(-1)
				if noOfPartials < 3:
					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration)

class backgroundSound2(threading.Thread):
	"""Threading class for the background sound."""
	def run(self):
		fundamentalFrequency	= 110
		noOfPartials		= 2
		specType		= 2
		startDistorFact		= 0.78
		targetDistorFact	= 0.75
		overallPanning		= .5
		noteDuration		= 13
		IncrDecrHarmonics	= 1
		while mainIterCycle == 1:
			spectrum = Csound_Note.noteI2(fundamentalFrequency, noOfPartials, specType, 					startDistorFact, targetDistorFact, overallPanning, noteDuration)
			while len(spectrum) > 0:
                		partial = spectrum.pop(0)
                		perf.InputMessage(partial)
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
			if IncrDecrHarmonics == 1:
				noOfPartials = noOfPartials + 1
				globalNoOfPartialsCounter.updateCounter(1)
				if noOfPartials > 13:
					IncrDecrHarmonics = 0
			elif IncrDecrHarmonics == 0:
				noOfPartials = noOfPartials - 1
				globalNoOfPartialsCounter.updateCounter(-1)
				if noOfPartials < 3:
					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration)

class backgroundSound3(threading.Thread):
	"""Threading class for the background sound."""
	def run(self):
		fundamentalFrequency	= 137.5
		noOfPartials		= 2
		specType		= 1
		startDistorFact		= 1
		targetDistorFact	= 1
		overallPanning		= .25
		noteDuration		= 19
		IncrDecrHarmonics 	= 1
		while mainIterCycle == 1:
			spectrum = Csound_Note.noteI2(fundamentalFrequency, noOfPartials, specType, 					startDistorFact, targetDistorFact, overallPanning, noteDuration)
			while len(spectrum) > 0:
                		partial = spectrum.pop(0)
                		perf.InputMessage(partial)
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
			if IncrDecrHarmonics == 1:
				noOfPartials = noOfPartials + 1
				globalNoOfPartialsCounter.updateCounter(1)
				if noOfPartials > 13:
					IncrDecrHarmonics = 0
			elif IncrDecrHarmonics == 0:
				noOfPartials = noOfPartials - 1
				globalNoOfPartialsCounter.updateCounter(-1)
				if noOfPartials < 3:
					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration)


## Background Sound's playback method.
def playback():
	""" Background_sound's playback method"""
	backgroundSound1().start()
	backgroundSound2().start()
	backgroundSound3().start()

if __name__ == "__main__":
	initCsound()
	playback()
