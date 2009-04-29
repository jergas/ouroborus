## This module is destined to be obsolete. It was a proof-of-concept
# dating from the beginning of sound implementation. It plays a
# spectral note for every instance of an agent present at the beginning
# of the simulation.

from random import random, randint, choice
# Sound-related submodules.
from csnd_interface import perf
from csnd_notes import birthNote


def birthSound():
	""" Generates the sound that represents the birth of a birdcage
	agent at the beginning of the simulation.
	""" 
	specType	= [0, 1, 2, 3]
	distFactor	= [.5, .55, .60, .65, .70, .75, .80, .85, .90, .95, 1, 1.05,
					1.15, 1.20, 1.25, 1.30, 1.35, 1.40, 1.45, 1.50]
	noteDur		= random() + 0.5
	spectrum	= birthNote(randint(440, 880), randint(10, 150),
							choice(specType), choice(distFactor), random(),
							noteDur)
	#Feed the spectrum (i.e. the note) to the Csound.
	while len(spectrum) > 0:
		partial = spectrum.pop(0)
		perf.InputMessage(partial)
