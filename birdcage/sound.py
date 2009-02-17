import time
import Csound_Interface
import Background_sound as background
import globals_background_sound as gB

def startSoundServer():
	"""Starts the sound server"""
	Csound_Interface.initCsound()

def playSingleNote():
	"""Plays a single note when an agent is instantiated.

	Some latency issues have still to be dealt with."""
       	Csound_Interface.csoundNoteI1()

def startBackground():
	"""Starts the background sound threads."""
	background.playback()

def startBackgroundControl():
	"""Starts the background sound control thread"""
	background.control()

def inputDataControl(cell1, cell2, cell3):
	gB.liveDeadCells = [cell1, cell2, cell3]

def stopSoundServer():
	"""Stop all sound.

	Stops the sound server, and changes a global within Background_sound.py. 
	This causes the iteration of the background sound loops 
	(and thus its threads) to end."""
	Csound_Interface.endCsound()
	gB.mainIterCycle = 0







