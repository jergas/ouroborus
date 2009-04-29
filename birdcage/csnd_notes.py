##
from random import random, choice, randint, uniformfrom numeric_series import *from distorted_spectrum import distortedSpectrumfrom start_times import startTimes
from partials_durations import partialsDurationsfrom amplitude_control import spectralAmplitudesI1, spectralAmplitudesI2from spectral_pan import spectralPanfrom envelope_methods import attackTimes, decayTimes, gaussianMidPoints

def birthNote(fundamental, noOfHarmonics, spectrumType, distortion,
				overallPanning, totalDuration):
	"""
	"""
	species			= [evenPartials, oddPartials, fibonacciPartials,
						primePartials]
	spectrumChoice	= species.pop(spectrumType)
	partials		= spectrumChoice(noOfHarmonics)	distSpectrum	= distortedSpectrum(fundamental, partials, distortion)	instrumentCSD	= 1	startTimesCSD	= startTimes(distSpectrum)	durationsCSD	= partialsDurations(startTimesCSD, totalDuration)	amplitudesCSD	= spectralAmplitudesI1(distSpectrum)	spectralPanCSD	= spectralPan(overallPanning, distSpectrum)	attacksCSD		= attackTimes(durationsCSD[:1], distSpectrum)	decaysCSD		= decayTimes(durationsCSD[:1], distSpectrum)	partialsCSD		= []	while len(distSpectrum) > 0:		noteCSD = ("i%s %s %s %s %s %s %s %s" %(instrumentCSD,
				startTimesCSD.pop(0), durationsCSD.pop(0),
				amplitudesCSD.pop(0), distSpectrum.pop(0),				spectralPanCSD.pop(0), attacksCSD.pop(0),
				decaysCSD.pop(0)))		partialsCSD.append(noteCSD)	return partialsCSD

def bckgrndNote(instrument, fundamental, noOfHarmonics, spectrumType,
				distortion1, distortion2, panning, totalDuration):
	"""
	"""
	species			= [evenPartials, oddPartials, fibonacciPartials,
						primePartials]
	spectrumChoice	= species.pop(spectrumType)
	partials		= spectrumChoice(noOfHarmonics)	distSpectrum1	= distortedSpectrum(fundamental, partials, distortion1)

	species1		= [evenPartials, oddPartials, fibonacciPartials,
						primePartials]
	spectrumChoice1	= species1.pop(spectrumType)
	partials1		= spectrumChoice1(noOfHarmonics)
	distSpectrum2	= distortedSpectrum(fundamental, partials1, distortion2)

	if len(distSpectrum1) > len(distSpectrum2):
		extra = distSpectrum1[-1]
		distSpectrum2.append(extra)
	if len(distSpectrum1) < len(distSpectrum2):
		extra = distSpectrum2[-1]
		distSpectrum1.append(extra)
	startTimesCSD	= startTimes(distSpectrum1)	durationsCSD	= partialsDurations(startTimesCSD, totalDuration)	amplitudesCSD	= spectralAmplitudesI2(distSpectrum1)
	durToEnvMaxCSD	= gaussianMidPoints(durationsCSD[0], distSpectrum1)	partialsCSD		= []									while len(distSpectrum1) > 0:		noteCSD = ("i%s %s %s %s %s %s %s %s" %(instrument,
				startTimesCSD.pop(0), durationsCSD.pop(0),
				amplitudesCSD.pop(0), distSpectrum1.pop(0),
				distSpectrum2.pop(0), panning, durToEnvMaxCSD.pop(0)))		partialsCSD.append(noteCSD)	return partialsCSD
