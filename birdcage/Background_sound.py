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
	def __init__(self, start):
		self.lock = threading.Lock()
		self.value = start
	def updateCounter(self, plusOrMin, threadNo):
		self.lock.acquire()
		try:
			self.value = self.value + plusOrMin
		finally:
			self.lock.release()

globalNoOfPartialsCounter = Counter(nextTotalNoOfPartials)

## Threading class for the background sound.
class backgroundSound1(threading.Thread):

	def run(self):
		fundamentalFrequency	= 165
		noOfPartials		= 2
		specType		= 0
		startDistorFact		= 0.75
		targetDistorFact	= 0.78
		overallPanning		= .75
		noteDuration		= 17
		IncrDecrHarmonics	= 1
		counter			= Counter(noOfPartials)
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
				globalNoOfPartialsCounter.updateCounter(1, 0)
				counter.updateCounter(1, 1)
				if noOfPartials > 13:
					IncrDecrHarmonics = 0
			elif IncrDecrHarmonics == 0:
				noOfPartials = noOfPartials - 1
				globalNoOfPartialsCounter.updateCounter(-1, 0)
				counter.updateCounter(-1, 1)
				if noOfPartials < 3:
					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			nextNoOfPartialsT1 = counter.value
			Csound_Note.PartialsDensityT1 = nextNoOfPartialsT1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			print 'Next number of Partials T1', nextNoOfPartialsT1, 'nextTotalNoOfPartials', nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration)


## Another threading class for background sound. Same as above, but with new parameters.
class backgroundSound2(threading.Thread):

	def run(self):
		fundamentalFrequency	= 110
		noOfPartials		= 2
		specType		= 2
		startDistorFact		= 0.78
		targetDistorFact	= 0.75
		overallPanning		= .5
		noteDuration		= 13
		IncrDecrHarmonics	= 1
		counter 		= Counter(noOfPartials)
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
				globalNoOfPartialsCounter.updateCounter(1, 0)
				counter.updateCounter(1, 2)
				if noOfPartials > 13:
					IncrDecrHarmonics = 0
			elif IncrDecrHarmonics == 0:
				noOfPartials = noOfPartials - 1
				globalNoOfPartialsCounter.updateCounter(-1, 0)
				counter.updateCounter(-1, 2)
				if noOfPartials < 3:
					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			nextNoOfPartialsT2 = counter.value
			Csound_Note.PartialsDensityT2 = nextNoOfPartialsT2
			print 'Next number of Partials T2', nextNoOfPartialsT2, 'nextTotalNoOfPartials', nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration)

class backgroundSound3(threading.Thread):

	def run(self):
		fundamentalFrequency	= 137.5
		noOfPartials		= 2
		specType		= 1
		startDistorFact		= 1
		targetDistorFact	= 1
		overallPanning		= .25
		noteDuration		= 19
		IncrDecrHarmonics 	= 1
		counter 		= Counter(noOfPartials)
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
				globalNoOfPartialsCounter.updateCounter(1, 0)
				counter.updateCounter(1, 3)
				if noOfPartials > 13:
					IncrDecrHarmonics = 0
			elif IncrDecrHarmonics == 0:
				noOfPartials = noOfPartials - 1
				globalNoOfPartialsCounter.updateCounter(-1, 0)
				counter.updateCounter(-1, 3)
				if noOfPartials < 3:
					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			nextNoOfPartialsT3 = counter.value
			Csound_Note.PartialsDensityT3 = nextNoOfPartialsT3
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			print 'Next number of Partials T3', nextNoOfPartialsT3, 'nextTotalNoOfPartials', nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration)


## Background Sound's playback method.
def playback():
	backgroundSound1().start()
	backgroundSound2().start()
	backgroundSound3().start()

if __name__ == "__main__":
	initCsound()
	playback()
