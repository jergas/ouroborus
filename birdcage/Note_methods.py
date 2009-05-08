## Contains the classes and methods to generate data for the note
# classes.

import random

import numeric_series as numSer


class Spctrm:
	""" Contains the methods to generate harmonic-based notes.
	"""
	def mkPartls(self, spectType, numOfPartls):
		""" Generates a list of partials that will be used to generate
		spectra.
		spectType	---> type of spectrum (0=odd partls, 1=even partls,
					2=fibonacci partls and 3=prime partls)
		numOfPartls	---> number of partials to generate
		return		--> a partial-series list
		"""
		kinds			= [numSer.odd, numSer.even, numSer.fibo, numSer.prime]
		kindChoice		= kinds.pop(spectType)
		partls			= kindChoice(numOfPartls)		return partls


	def dSpect(self, fundFreq, partls, distor):		""" Constructs a distorted harmonic spectrum based on the 
		iteration of the function "s = f*p to the d", where s is the
		spectrum, f is de fundamental frequency, p is the partial
		number, and d is a distortion factor.
		fundFreq	---> the fundamental frequency
		partls		---> the partials present in the spectrum
		distor		---> the distortion factor
		return		---> a distorted-harmonic-spectrum list
		"""
		spect	= []
		for x in xrange(len(partls)):			onePartl = partls.pop(0)			distorPartl = pow(onePartl, distor)			onePartlFreq = fundFreq * distorPartl
			# Control that harmonics over the audible range are not
			#generated.			if  onePartlFreq < 20000 :
				onePartlFreq = round(onePartlFreq, 3)
				spect.append(onePartlFreq)			else:				break		return spect


class StrtTms:
	""" Contains start time methods.
	"""
	def expoSpct(self, dSpect, limit=.3):		"""Makes exponential start times. The start times are ordered,
		so that lower partials start earlier.
		dSpect	---> a distorted-harmonic-spectrum list
		return	--> a list of start times
		limit=.3
		"""		strts	= [0]		
		for x in xrange(len(dSpect) - 1):			oneStrt = random.expovariate(2)			if oneStrt <= limit and oneStrt >= .001:				strts.append(oneStrt)		strts.sort()		return strts


class Durs:
	""" Contains duration methods.
	"""
	def spectDurs(self, strts, dur):		""" Generates spectral durations, by substracting corresponding
		start times to a total duration.
		strts	---> a list of start times
		dur		---> a total duration
		return	--> a list of durations
		"""		durs	= []				for x in strts:			partlDur = dur - x			durs.append(partlDur)		return durs


class Amps:
	""" Contains amplitude methods.
	"""
	def __init__(self):
		""" The totAgntAmp initialization parameter is the total to
		which the partials parameters add up to.
		"""
		self.trgtAgntAmps		= 17000.0
		self.trgtBckgrndAmps	= 15000.0


	def spectEqlAmpsPnk(self, dSpect):
		"""Gives equal amplitude values to a note's partials so that
		its total amplitude equals trgtAgntAmps minus an attenuation
		factor (due to pinkish opcode's unstable amplitude output).
		dSpect	---> a distorted-harmonic-spectrum list
		return	--> a list of amplitude values
		"""
		spectAmps	= []
		spectDens	= len(dSpect)
		pnkAmpAtten	= self.trgtAgntAmps - (self.trgtAgntAmps * 0.9)
		oneAmp		= pnkAmpAtten / spectDens

		for x in xrange(len(dSpect)):			spectAmps.append(oneAmp)		return spectAmps


	def spectUnifrmAmps(self, dSpect):
		""" Makes uniformlly distributed amplitudes to a note's partials,
		so that they add up to trgtBckgrndAmps
		dSpect	---> a distorted-harmonic-spectrum list
		return	--> a list of amplitude values
		"""
		spectAmps	= []

		for x in xrange(len(dSpect)):        
			oneAmp = random.uniform(.001, 1)			spectAmps.append(oneAmp)		spectAmps.sort()		spectAmps.reverse()		scaledSpectAmps = numSer.scaling(spectAmps, self.trgtBckgrndAmps)		return scaledSpectAmps


class Pan:
	""" Contains panning methods.
	"""
	def spctrlPans(self, pan, dSpect):		""" Gives a stereophonic range to a spectreal note. While
		close by, each partial has a deviation from the fundamental's
		position.
		pan		---> a number between 0-1 to indicate panning (1 is
						hard left.)
		dSpect	---> a distorted-harmonic-spectrum list
		return	--> a list of spectral panning positions
		"""		spat 	= [pan]
		for x in xrange(len(dSpect) - 1):			onePan = random.gauss(pan, .01)			if 0 < onePan < 1:				spat.append(onePan)		return spat


class Env:
	""" Contains envelope methods.
	"""
	def attckTs(self, dur, dSpect):
	    """ Generates attack times for the spectrum partials. Each
		attack time lasts between 10 and 50% of the notes duration.
		dur		---> a total duration
		dSpect	---> a distorted-harmonic-spectrum list
		return	--> a list of attack times
		"""
	    attcks	= []
	    totDur	= dur.pop(0)
	    maxDur	= totDur * 0.5
	    minDur	= totDur * 0.1
	    
	    for x in xrange(len(dSpect)):
	        oneAttck = random.uniform(minDur, maxDur)
	        attcks.append(oneAttck)
	    return attcks


	def decTs(self, dur, dSpect):		""" Generates decay times for the spectrum partials. Each
		decay time lasts between 10 and 50 of the notes duration.
		dur		---> a total duration
		dSpect	---> a distorted-harmonic-spectrum list
		return	--> a list of attack times
		"""		decs	= []		totDur	= dur.pop(0)
		maxDur	= totDur * 0.5
		minDur	= totDur * 0.1				for x in xrange(len(dSpect)):			oneDec = random.uniform(minDur, maxDur)			decs.append(oneDec)		return decs


	def gaussMaxAmp(self, dur, dSpect):
		""" Generates a list of gaussian points. These are used as the
		peak amplitude points of the background notes.
		dur		---> a total duration
		dSpect	---> a distorted-harmonic-spectrum list
		return	--> a list of gaussian points
		"""
		midPnts	= []
		average		= dur * 0.5

		for x in xrange(len(dSpect)):
			oneMidPnt = random.gauss(average, 1)
			midPnts.append(oneMidPnt)
		return midPnts
