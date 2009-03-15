##Import the necessary modules:from random import uniform, gauss
##Generate the attack times of the note's partials.
def attackTimes(totalDuration, distSpectrum):
    
    attacks	= []
    totalDur	= totalDuration.pop(0)
    maxDuration	= totalDur * 0.5
    minDuration	= totalDur * 0.1
    
    for x in distSpectrum:
        oneAttack = uniform(minDuration, maxDuration)
        attacks.append(oneAttack)
    return attacks
##Generate the decay times of the note's partials.
def decayTimes(totalDuration, distSpectrum):		decays		= []	totalDur	= totalDuration.pop(0)
    	maxDuration	= totalDur * 0.5
	minDuration	= totalDur * 0.1		for x in distSpectrum:		oneDecay = uniform(minDuration, maxDuration)		decays.append(oneDecay)	return decays

## Defines a list of gaussian centres for maximum amplitud to be used as maximum amplitude points in background notes.

def gaussianMidPoints(totalDuration, distSpectrum):

	midPoints	= []
	average		= totalDuration * 0.5

	for x in distSpectrum:
		oneMidPoint = gauss(average, 1)
		midPoints.append(oneMidPoint)
	return midPoints
