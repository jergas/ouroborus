## Import the necessary built-in modules
import time, threading
from random import choice, randint, sample, uniform, random
## Import the necessary user-defined modules
from Csound_Interface import initCsound, perf, csound
from csd_generator import namesChannels
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
		fundamentalFrequency	= 164.81
		noOfPartials		= 13
		specType		= 0
		startDistorFact		= 0.75
		targetDistorFact	= 0.78
		overallPanning		= .75
		noteDuration		= 13
		IncrDecrHarmonics	= 1

		while mainIterCycle == 1:
			instrumentNos = range(2, (2 + noOfPartials))
			channelNos = range(1, (1 + noOfPartials))
			spectrum = Csound_Note.noteBackground(1, fundamentalFrequency, noOfPartials,
				specType, startDistorFact, targetDistorFact, overallPanning, noteDuration)
			while len(spectrum) > 0:
                		partial = spectrum.pop(0)
				partialPlusInstr = partial.replace('i1', ('i' + str(instrumentNos.pop(0))))
				perf.InputMessage(partialPlusInstr)
				channel = channelNos.pop(0)
				csound.SetChannel('chan%s' %(channel), 1)
			startDistorFact = targetDistorFact
			noteDuration		= -13
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
#			if IncrDecrHarmonics == 1:
#				noOfPartials = noOfPartials + 1
#				globalNoOfPartialsCounter.updateCounter(1)
#				if noOfPartials > 13:
#					IncrDecrHarmonics = 0
#			elif IncrDecrHarmonics == 0:
#				noOfPartials = noOfPartials - 1
#				globalNoOfPartialsCounter.updateCounter(-1)
#				if noOfPartials < 3:
#					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration * -1)

class backgroundSound2(threading.Thread):
	"""Threading class for the background sound."""
	def run(self):
		fundamentalFrequency	= 196
		noOfPartials		= 13
		specType		= 2
		startDistorFact		= 0.78
		targetDistorFact	= 0.75
		overallPanning		= .5
		noteDuration		= 17
		IncrDecrHarmonics	= 1

		while mainIterCycle == 1:
			instrumentNos		= range(15, (15 + noOfPartials))
			channelNos = range(14, (14 + noOfPartials))
			spectrum = Csound_Note.noteBackground(1, fundamentalFrequency, noOfPartials,
				specType, startDistorFact, targetDistorFact, overallPanning, noteDuration)
			while len(spectrum) > 0:
                		partial = spectrum.pop(0)
				partialPlusInstr = partial.replace('i1', ('i' + str(instrumentNos.pop(0))))
				perf.InputMessage(partialPlusInstr)
				channel = channelNos.pop(0)
				csound.SetChannel('chan%s' %(channel), 1)
			startDistorFact = targetDistorFact
			noteDuration		= -17
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
#			if IncrDecrHarmonics == 1:
#				noOfPartials = noOfPartials + 1
#				globalNoOfPartialsCounter.updateCounter(1)
#				if noOfPartials > 13:
#					IncrDecrHarmonics = 0
#			elif IncrDecrHarmonics == 0:
#				noOfPartials = noOfPartials - 1
#				globalNoOfPartialsCounter.updateCounter(-1)
#				if noOfPartials < 3:
#					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration * -1)

class backgroundSound3(threading.Thread):
	"""Threading class for the background sound."""
	def run(self):
		instrumentNos		= range(28, 41)
		fundamentalFrequency	= 138.59
		noOfPartials		= 13
		specType		= 1
		startDistorFact		= 1
		targetDistorFact	= 1
		overallPanning		= .25
		noteDuration		= 19
		IncrDecrHarmonics 	= 1

		while mainIterCycle == 1:
			instrumentNos = range(28, (28 + noOfPartials))
			channelNos = range(27, (27 + noOfPartials))
			spectrum = Csound_Note.noteBackground(1, fundamentalFrequency, noOfPartials,
				specType, startDistorFact, targetDistorFact, overallPanning, noteDuration)
			while len(spectrum) > 0:
                		partial = spectrum.pop(0)
				partialPlusInstr = partial.replace('i1', ('i' + str(instrumentNos.pop(0))))
				perf.InputMessage(partialPlusInstr)
				channel = channelNos.pop(0)
				csound.SetChannel('chan%s' %(channel), 1)
			startDistorFact = targetDistorFact
			noteDuration		= -19
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
#			if IncrDecrHarmonics == 1:
#				noOfPartials = noOfPartials + 1
#				globalNoOfPartialsCounter.updateCounter(1)
#				if noOfPartials > 13:
#					IncrDecrHarmonics = 0
#			elif IncrDecrHarmonics == 0:
#				noOfPartials = noOfPartials - 1
#				globalNoOfPartialsCounter.updateCounter(-1)
#				if noOfPartials < 3:
#					IncrDecrHarmonics = 1
			nextTotalNoOfPartials = globalNoOfPartialsCounter.value
			Csound_Note.TotalPartialsDensity = nextTotalNoOfPartials
			while 1:
				overallPanning = (randint(-3, 3) *.05)
				if overallPanning >= 0 and overallPanning <=1:
					break
			time.sleep(noteDuration * -1)

class harmonicsGatingContol(threading.Thread):
	"""PROOF OF CONCEPT CLASS. Will be linked to the display of the simulation. Turns harmonics of the background sounds on and off"""
	def run(self):
		while backgroundSound1().isAlive() and backgroundSound2().isAlive() and backgroundSound3().isAlive():
			gatedChannels	= []
			channels1	 = backgroundSound1().run().channelNos
			channels2	 = backgroundSound2().run().channelNos
			channels3	 = backgroundSound3().run().channelNos

			del channels1[0]
			del channels2[0]
			del channels3[0]

			gateableChannels	= channels1 + channels2 + channels3
			noOfChannelsToGate	= len(gateableChannels)
			NoOfGates		= randint(1, noOfChannelsToGate)
			channelsToBeGated	= sample(gateableChannels, NoOfGates)

			while len(channelsToBeGated) > 0:
				channelToGate = channelsToBeGated.pop(0, (len(channelsToBeGated) - 1))
				gatedChannels.append(channelToBeGated)
				csound.SetChannel('chan%s' %(channelToBeGated), 0)
				


## Background Sound's playback method.
def playback():
	""" Background_sound's playback method"""
	backgroundSound1().start()
	backgroundSound2().start()
	backgroundSound3().start()
	#harmonicsGatingContol().start()

if __name__ == "__main__":
	initCsound()
	playback()
