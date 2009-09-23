## This module is in charge of the agents' sound

import random
# Sound-related submodules.
import csnd_interface as csndInterface
import Csnd_notes

#Instantiate the agents' birth sound note class.
BirthNote	= Csnd_notes.BirthNote()

def birthSound():
	""" Generates the sound that represents the birth of a birdcage
	agent.
	""" 
	noteDur			= random.randint(1, 2) * 0.1
	BirthNote.dur	= noteDur
	#Feed the note to Csound.
	scoStatement = BirthNote.mkScoStrings()
	csndInterface.perf.InputMessage(scoStatement)
