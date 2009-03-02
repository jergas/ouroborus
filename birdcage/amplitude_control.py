## This module provides the methods for (sound) amplitude control within Birdcage.

##Import the necessary modules:from linear_scaler import scaleToRangefrom random import uniform

## Globals
panicAmplitude 		= 32767 # No more sound will be added until expected amps go under maxOverallAmp
maxOverallAmplitude	= 30000 # Maximum expected Amplitude
targetPrincipalAmps	= 17000.0 # Amplitude target for principal sound
targetBackgroundAmps	= 13000.0 # Amplitude target for background sound

def scaling(aList, newTotal):
	"""Scales the values in aList so they add up to newTotal"""
	inAmpTotal	= 0.0
	newAmps		= []

	for x in aList:
		inAmpTotal = inAmpTotal + x
	scaleFactor = newTotal / inAmpTotal
	for x in aList:
		newAmp = x * scaleFactor
		newAmps.append(newAmp)
	return newAmps
def spectralAmplitudesI1(distSpectrum):
	"""Gives equal amplitude values to a note's partials so that its total amplitude equals
	targetPrincipalAmps minus an attenuation factor (due to pinkish's unstable amplitude output)."""
	spectAmps		= []
	spectralDensity		= len(distSpectrum)
	pinkAmpAtenuation	= targetPrincipalAmps - (targetPrincipalAmps * 0.8)
	oneAmp			= pinkAmpAtenuation / spectralDensity

	for x in distSpectrum:		spectAmps.append(oneAmp)	return spectAmps
def spectralAmplitudesI2(distSpectrum1):
	""" Makes uniformlly distributed amplitudes to a note's partials, so that they add up to
	targetBackgroundAmps"""
	spectAmps	= []
	noteTotalAmp	= targetBackgroundAmps / 3.0

	for x in distSpectrum1:        
		oneAmp = uniform(.001, 1)		spectAmps.append(oneAmp)	spectAmps.sort()	spectAmps.reverse()	scaledSpectAmps = scaling(spectAmps, noteTotalAmp)	return scaledSpectAmps	return spectAmps
