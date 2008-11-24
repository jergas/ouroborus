## Constructs the parameters for an additive-synthesis note. Each evaluation of
#the method "nota" yields a single additive-synthesis note, composed of several
#csound notes. Note that each string in the returned list is a csound score
#line for.
##Import the necessary modules:from random import random, choice, randint, uniformfrom numeric_series import *from distorted_spectrum import distortedSpectrumfrom start_times import startTimes
from partials_durations import partialsDurationsfrom amplitude_control import spectralAmplitudesI1, spectralAmplitudesI2from spectral_pan import spectralPanfrom attack_times import attackTimesfrom decay_times import decayTimes

# Global variables for amplitude control. Changed by Background_sound.py.
PartialsDensityT1	= 2
PartialsDensityT2	= 2
PartialsDensityT3	= 2
TotalPartialsDensity	= 6

## Method for a single note from the Distorted Harmonic Spectrum Model, with instrument 1.def noteI1(fundamental, noOfHarmonics, spectrumType, distortion, overallPanning,
		totalDuration):
## Which kind of partials will be present in a note.
	species		= [evenPartials, oddPartials,
				fibonacciPartials, primePartials]
	spectrumChoice	= species.pop(spectrumType)
	partials	= spectrumChoice(noOfHarmonics)	distSpectrum	= distortedSpectrum(fundamental, partials,
				distortion)## Csound instrument no.	instrumentCSD	= 1## Defines the start times of the partials. In seconds	startTimesCSD	= startTimes(distSpectrum)## Defines the durations of the partials. In seconds	durationsCSD	= partialsDurations(startTimesCSD, totalDuration)## Defines the amplitudes of the partials. Between (0-32767)	amplitudesCSD	= spectralAmplitudesI1(distSpectrum)##Gives a little "space" to the note. Just like when humans speak: low tones
#resonate towards the chest and high ones towrds the forehead.	spectralPanCSD	= spectralPan(overallPanning, distSpectrum)## Attack time of the partials. In seconds.	attacksCSD	= attackTimes(durationsCSD[:1], distSpectrum)	## Decay time  of the partials. In seconds.	decaysCSD	= decayTimes(durationsCSD[:1], distSpectrum)## Contains the csound notes that integrate an additive synthesis note.	partialsCSD	= []								## Constructs the csound score lines (each string is a line) for an additive
#synthesis note.	while len(distSpectrum) > 0:		noteCSD = ("i%s %s %s %s %s %s %s %s" %(instrumentCSD,
				startTimesCSD.pop(0), durationsCSD.pop(0),
				amplitudesCSD.pop(0), distSpectrum.pop(0),				spectralPanCSD.pop(0), attacksCSD.pop(0),
				decaysCSD.pop(0)))		partialsCSD.append(noteCSD)	return partialsCSD

## Method for a single note from the Distorted Harmonic Spectrum Model, with instrument 2.def noteI2(fundamental, noOfHarmonics, spectrumType, distortion1, distortion2,
	overallPanning, totalDuration):
## Partials at the beginning of the note.
	species			= [evenPartials, oddPartials,
					fibonacciPartials, primePartials]
	spectrumChoice		= species.pop(spectrumType)
	partials		= spectrumChoice(noOfHarmonics)	distSpectrum1		= distortedSpectrum(fundamental, partials,
					distortion1)
## Partials half way through the note.
	species1		= [evenPartials, oddPartials,
					fibonacciPartials, primePartials]
	spectrumChoice1		= species1.pop(spectrumType)
	partials1		= spectrumChoice1(noOfHarmonics)
	distSpectrum2		= distortedSpectrum(fundamental, partials1,
					distortion2)## Csound instrument no.	instrumentCSD		= 2## Defines the start times of the partials. In seconds	startTimesCSD		= startTimes(distSpectrum1)## Defines the durations of the partials. In seconds	durationsCSD		= partialsDurations(startTimesCSD, totalDuration)## Defines the amplitudes of the partials. Between (0-32767)	amplitudesCSD		= spectralAmplitudesI2(distSpectrum1)##Gives a little "space" to the note. Just like when humans speak: low tones
#resonate towards the chest and high ones towrds the forehead.	spectralPanCSD		= spectralPan(overallPanning, distSpectrum1)## Attack time of the partials. In seconds.	attacksCSD		= attackTimes(durationsCSD[:1], distSpectrum1)	## Decay time  of the partials. In seconds.	decaysCSD		= decayTimes(durationsCSD[:1], distSpectrum1)## Contains the csound notes that integrate an additive synthesis note.	partialsCSD		= []								## Constructs the csound score lines (each string is a line) for an additive
#synthesis note.	while len(distSpectrum1) > 0:		noteCSD = ("i%s %s %s %s %s %s %s %s %s" %(instrumentCSD,
				startTimesCSD.pop(0), durationsCSD.pop(0),
				amplitudesCSD.pop(0), distSpectrum1.pop(0),
				distSpectrum2.pop(0), spectralPanCSD.pop(0),
				attacksCSD.pop(0), decaysCSD.pop(0)))		partialsCSD.append(noteCSD)	return partialsCSD
