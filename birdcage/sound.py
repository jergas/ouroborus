## This modules is the interface between birdcage and its aural
# component. It has the methods to  initialize csound, play agent
# sounds (at present in early development), to start the background
# sound threads, to feed them with data, and to stop sound altogether.

import csnd_interface as csndInterface
import background_sound as background
import sound_globals as SGlobals


def startSoundServer():
	"""Starts the sound server.
	"""
	csndInterface.initCSnd()


def playSingleNote():
	"""Plays a single note when an agent is instantiated.
	"""
	csndInterface.cSndNoteI1()


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

	sndCtrlCells	---> Three element list containing the state of
						three automaton's cells.
	populationNORM		---> The automaton's normalized cell population
	"""
	SGlobals.populNorm 	= [populNorm]
	SGlobals.sndCtrlCells = sndCtrlCells


def stopSoundServer():
	"""Stops the sound server, and changes a global within
	background_sound.py. The latter causes the iteration of the
	background sound loops (and thus its threads) to end.
	"""
	csndInterface.endCsnd()
	SGlobals.mainIterCycle = 0
