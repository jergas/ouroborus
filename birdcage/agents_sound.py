## This module is in charge of the agents' sound

# Python modules.
import random
# Sound-related sub-modules.
import csnd_interface as csndInterface
import Csnd_notes
# Other sub-modules
import Numeric_utils as NumericUtils

#Instantiate the agents' birth sound note class and a scaling class.
AgentNote	= Csnd_notes.AgentNote()
Scaling = NumericUtils.Scaling()


class VocalTract(object):
	""" Contains the attributes that define an agent's voice quality and
	the methods to produce diffetent sounds.
	"""
	def __init__(self, agentXAxis, width):
		"""
		ADeviation	---> a deviation constant of the "a" formants
		IDeviation	---> a deviation constant of the "i" formants
		IDeviation	---> a deviation constant of the "o" formants
		panning		---> the agent's normalized x-axis position
		"""
		self.ptch1		= random.randint(5, 35)
		self.ptch2 		= random.randint(45, 400)
		self.vibr		= random.randint(1, 50)
		self.ADeviation = random.uniform(-250, 250)
		self.IDeviation = random.uniform(-250, 250)
		self.ODeviation = random.uniform(-250, 250)
		self.panning	= Scaling.valToRng(agentXAxis, 0, width, 1, 0)
		self.ate		= 0


	def birthSound(self):
		""" Generates the sound that an agent does at birth.
		"""
		# Set the relevant parameters in the AgentNote class.
		AgentNote.dur			= random.uniform(.05, .2)
		AgentNote.ptch1			= self.ptch1
		AgentNote.ptch2 		= self.ptch2
		AgentNote.vibr			= self.vibr
		AgentNote.IDeviation	= self.IDeviation
		AgentNote.ADeviation	= self.ADeviation	
		AgentNote.pan			= self.panning
		# Make a score-statement string and feed it to Csound.
		scoStatement = AgentNote.mkBirthString()
		csndInterface.perf.InputMessage(scoStatement)

	def eatSound(self):
		""" Generates the sound that an agent does while eating.
		"""
        # Set the relevant parameters in the AgentNote class.
		AgentNote.dur			= .1
		AgentNote.ptch1			= self.ptch1
		AgentNote.ptch2 		= self.ptch2
		AgentNote.ODeviation	= self.ODeviation
		AgentNote.pan			= self.panning
		# Make a score-statement string and feed it to Csound.
		scoStatement = AgentNote.mkEatString()
		csndInterface.perf.InputMessage(scoStatement)
