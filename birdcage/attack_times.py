## Defines the time it takes for each partial to reach its maximum amplitude
#(peak).
##Import the necessary modules:from random import uniform
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
