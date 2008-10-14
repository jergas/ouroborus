## Defines the decay times for the partials of an additive synthesis note.##Import the necessary modules:from random import uniform##Generate the decay times of the note's partials.
def decayTimes(totalDuration, distSpectrum):		decays		= []	totalDur	= totalDuration.pop(0)
    	maxDuration	= totalDur * 0.5
	minDuration	= totalDur * 0.1		for x in distSpectrum:		oneDecay = uniform(minDuration, maxDuration)		decays.append(oneDecay)	return decays
