## This modules is the interface between birdcage and its aural
# component. It has wrappers to the methods to  initialize csound,
# play agent sounds (at present in early development), to start the
# background sound threads, to feed them with data, and to stop
# sound altogether.

# Sound-related submodules.
import agents_sound as agentsSound
import background_sound as background
import csnd_interface as csndInterface
import sound_globals as sGlobals


def setInitialData(automatonWidth):
	sGlobals.automatonWidth = automatonWidth


def startSoundServer():
	"""Starts the sound server.
	"""
	csndInterface.initCSnd()


def agentBirth(VocalTract):
	"""Plays the birth sound.
	"""
	VocalTract.birthSound()
	
	
def eatSound(VocalTract):
	"""Plays the eating sound.
	"""
	VocalTract.eatSound()


def startBackground():
	"""Starts the background-sound threads.
	"""
	background.playback()


def startBackgroundControl():
	"""Starts the background-sound control thread.
	"""
	background.control()


def inputDataControl(sndCtrlCells, populNorm):
	"""Updates the automaton's variables needed to control the
	background sound. These global sound-control variables 'live'
	in sound_globals.py.

	sndCtrlCells	---> three element list containing the state of
						three automaton's cells.
	populationNORM	---> the automaton's normalized cell population
	"""
	sGlobals.populNorm 	= [populNorm]
	sGlobals.sndCtrlCells = sndCtrlCells


def stopSoundServer():
	"""Stops the sound server, and changes a global within
	background_sound.py. The latter causes the iteration of the
	background sound loops (and thus its threads) to end.
	"""
	background.joinThreads()
	csndInterface.endCsnd()
	sGlobals.mainIterCycle = 0
