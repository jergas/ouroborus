import time
import Csound_Interface
import Background_sound

def startSoundServer():
	"""Starts the sound server"""
	Csound_Interface.initCsound()

def playSingleNote():
	"""Plays a single note when an agent is instantiated.

	Some latency issues have still to be dealt with."""
       	Csound_Interface.csoundNoteI1()

def startBackground():
	"""Starts the background sound threads."""
	Background_sound.playback()

def stopSoundServer():
	"""Stop all sound.

	Stops the sound server, and changes a global within Background_sound.py. 
	This causes the iteration of the background sound loops 
	(and thus its threads) to end."""
	Csound_Interface.perf.Stop()
	Background_sound.mainIterCycle = 0







