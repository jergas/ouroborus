## Defines the time it takes for each partial to reach its maximum amplitude
#(peak).
##Import the necessary modules:from random import uniform
##Generate the attack times of the note's partials.
def attackTimes(totalDuration, distSpectrum, minDurationAT=.001):
    
    attacks	= []
    maxDuration	= totalDuration.pop(0) * 0.5
    
    for x in distSpectrum:
        oneAttack = uniform(minDurationAT, maxDuration)
        attacks.append(oneAttack)
    return attacks