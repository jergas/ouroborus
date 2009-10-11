## This module is in charge of the agents' sound

# Python modules.
import random
# Sound-related sub-modules.
import csnd_interface as csndInterface
import Csnd_notes
# Other sub-modules
import Numeric_utils as NumericUtils

#Instantiate the agents' birth sound note class and a scaling class.
BirthNote	= Csnd_notes.BirthNote()
Scaling = NumericUtils.Scaling()


class VocalTract(object):
	""" Contains the attributes that define an agent's voice quality and
	the methods to produce diffetent sounds.
	"""
	def __init__(self, agentXAxis, width):
		"""
		ADeviation	---> a deviation constant of the "a" formants
		IDeviation	---> a deviation constant of the "i" formants
		panning		---> the agent's normalized x-axis position
		"""
		self.ADeviation = random.uniform(-250, 250)
		self.IDeviation = random.uniform(-250, 250)
		self.panning	= Scaling.valToRng(agentXAxis, 0, width, 1, 0)


	def birthSound(self):
		""" Generates the sound that represents the birth of a birdcage
		agent.
		""" 
		BirthNote.dur			= random.uniform(.5, 2) * 0.1
		BirthNote.pan			= self.panning
		BirthNote.IDeviation	= self.IDeviation
		BirthNote.ADeviation	= self.ADeviation	
		#Feed the note to Csound.
		scoStatement = BirthNote.mkScoStrings()
		csndInterface.perf.InputMessage(scoStatement)
