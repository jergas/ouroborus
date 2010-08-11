## Default reference pitch (i.e. pitch 0) is C2, 

import math


def centsToFreq(pitchNo, modulo=1200, reference=32.70):
	""" Converts a pitch number into a frequency. A difference of 12
	between pitch numbers is equivalent to an octave. With the defaults,
	a difference of .01 is equivalent to a cent. Pitch 0 is C2
	(assuming central C to be C5
	pitchNo		---> a pitch number to be converted into a frequency
	modulo		---> number of steps into which the octave is divided
					(optional)
	reference	---> the frequency of pitch 0 (optional)
	return		-->  the frequency of the pitch number.
	"""
	step = math.pow(math.e, math.log(2) / modulo)
	frequency = reference * math.pow(step, pitchNo)
	return frequency
