## Defines the amplitudes for the partials of an additive synthesis note. Since
#amplitudes add to each other, the maximum total amplitud is 32767, and there are,
#at the moment three species, the maximum amplitude of a note is 10000. If the
#maximum amp. is exceded, the sound waves will be truncated in the digital to
#analogue converter.
##Import the necessary modules:from linear_scaler import scaleToRangefrom random import gammavariate##Generate and scale the maximum amplitudes of the note's partials
def amplitudes(distSpectrum, limit=10000):
    spectAmps	= []
    for x in distSpectrum:
        
        oneAmp = gammavariate(.04, 1)	####Play with the beta value when
                                        #there's sound.        spectAmps.append(oneAmp)    spectAmps.sort()    spectAmps.reverse()    scaledSpectAmps = scaleToRange(spectAmps, 10, limit)    return scaledSpectAmps	