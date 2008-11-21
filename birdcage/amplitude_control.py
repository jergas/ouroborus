## This module provides the methods for (sound) amplitude control within Birdcage.

##Import the necessary modules:from linear_scaler import scaleToRangefrom random import uniform

## Globals
panicAmplitude 		= 32767 # No more sound will be added until expected amps go under maxOverallAmp
maxOverallAmplitude	= 30000 # Maximum expected Amplitude
targetPrincipalAmps	= 17000 # Amplitude target for principal sound
targetBackgroundAmps	= 13000 # Amplitude target for background sound
##Generate and scale the maximum amplitudes of instrument 1 note's partialsdef spectralAmplitudesI1(distSpectrum1, limit=500):

	spectAmps	= []

	for x in distSpectrum1:        
		oneAmp = uniform(.001, 1)		spectAmps.append(oneAmp)	spectAmps.sort()	spectAmps.reverse()	scaledSpectAmps = scaleToRange(spectAmps, limit * 0.25, limit)	return scaledSpectAmps

##Generate and scale the maximum amplitudes of instrument 2 note's partials.def spectralAmplitudesI2(distSpectrum1, TotalPartialsDensity):

	spectAmps	= []
	spectralDensity	= len(distSpectrum1)
	noteTotalAmp	= targetBackgroundAmps / 3.0
	oneAmp		= noteTotalAmp / spectralDensity


	for x in distSpectrum1:		spectAmps.append(oneAmp)	return spectAmps
