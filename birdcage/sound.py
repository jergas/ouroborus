## This modules is the interface between birdcage and its aural
# component. It has wrappers to the methods to  initialize csound,
# play agent sounds (at present in early development), to start the
# background sound threads, to feed them with data, and to stop
# sound altogether.

#Python's native libraries.
import threading

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


def backgroundVoices():
	""" Creates three threads, each running a background voice thread.
	"""
	argsList	= [(2, -12, 3400, 0.8, 0, 1, 0.25),
					(15, -8, 3400, 0.5, 3, 0, 0.5),
					(27, -14, 3400, 0.2, 1, 2, 0.75)]
	voiceNo		= 1
	voiceList	= []

	for x in argsList:
		threadName = 'BackgroundVoice' + str(voiceNo)
		voice = threading.Thread(name=threadName,
									target=background.oneBckgrndVox, args=x)
#		voice.start()
		voiceList.append(voice)
		voiceNo = voiceNo + 1
	return voiceList


def backgroundControl():
	"""Starts the background sound control thread, which modifies the
	the background sound voices.
	"""
	controlThread = threading.Thread(name='backgroundVoicesControl',
									target=background.ctrlBckgrndSnd)
#	controlThread.start()
#	voiceList.append(controlThread)
	return controlThread


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
#	logging = open('logging.txt', 'w')
#	logging.write('you have reached here!')
#	logging.close()
	background.joinThreads()
	csndInterface.endCsnd()
	sGlobals.mainIterCycle = 0
