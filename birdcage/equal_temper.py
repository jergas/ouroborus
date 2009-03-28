#Default reference pith (i.e. pitch 0) is C2, assuming middle C to be C5.

import math as m

def pitchInCentsToFreq(pitchNo, modulo=1200, reference=32.70):
	step = m.pow(m.e, m.log(2) / modulo)
	pitch = reference * m.pow(step, pitchNo)
	return pitch
