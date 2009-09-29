## This module is in charge of the agents' sound

import random
# Sound-related submodules.
import csnd_interface as csndInterface
import Csnd_notes

#Instantiate the agents' birth sound note class.
BirthNote	= Csnd_notes.BirthNote()

def birthSound(panning):
	""" Generates the sound that represents the birth of a birdcage
	agent.
	""" 
	BirthNote.dur	= random.randint(1, 2) * 0.1
	BirthNote.pan	= panning
	#Feed the note to Csound.
	scoStatement = BirthNote.mkScoStrings()
	csndInterface.perf.InputMessage(scoStatement)
