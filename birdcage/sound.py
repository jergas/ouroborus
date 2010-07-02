## This modules is the interface between birdcage and its aural
# component. It has wrappers to the methods to  initialize csound,
# play agent sounds (at present in early development), to start the
# background sound threads, to feed them with data, and to stop
# sound altogether.

#Python's native libraries.
import threading
import sys

# Sound-related submodules.
import background_sound as backgroundSound
import csnd_interface as csndInterface
import sound_globals as soundGlobals

specificity = sys.modules["__main__"].specificity
specific = __import__("specific"+specificity)

# Import the agent's sound module and methods, except when a simulation
# lacks agents.
if specific.simWithAgents:
	import agents_sound as agentsSound


	def agentBirth(VocalTract):
		"""Plays the birth sound.
		"""
		VocalTract.birthSound()
		
		
	def eatSound(VocalTract):
		"""Plays the eating sound.
		"""
		VocalTract.eatSound()
else:
	print 'If this is a simulation with agents, set simWithAgents to True in your specificXXX.py module.'


def setInitialData(size):
	""" Record and make global data needed for sound processing. The
	data is recorded on sound_globals.py.
	size	---> a tuple representing the automaton's width and height
	"""
	(width, height) = size
	soundGlobals.cellControlDict = backgroundSound.setControlCells(width, height, specific.backgroundPartials)


def startSoundServer():
	"""Starts the sound server.
	"""
	csndInterface.initCSnd(specific.csOptions,
							specific.backgroundPartials)


def backgroundVoices():
	""" Creates three threads, each running a background voice thread.
	"""
	backgroundPartials = specific.backgroundPartials
	frstInstr = 2
	frstInstrLst = range(frstInstr, (backgroundPartials + frstInstr) * 2,
						backgroundPartials)
	argsList	= [(frstInstrLst[0], -12, 3400, 0.50, 1, backgroundPartials,
						1),
					(frstInstrLst[1], -8, 3400, 0.50, 0, backgroundPartials,
						0.5),
					(frstInstrLst[2], -14, 3400, 0.50, 2, backgroundPartials,
						0)]
	voiceList	= []

	for index, item in enumerate(argsList):
		threadName = 'BackgroundVoice' + str(index)
		voice = threading.Thread(name=threadName,
									target=backgroundSound.oneBckgrndVox,
									args=item)
		voiceList.append(voice)
	return voiceList


def backgroundControl():
	"""Starts the background sound control thread, which modifies the
	the background sound voices.
	"""
	controlThread = threading.Thread(name='backgroundVoicesControl',
										target=backgroundSound.ctrlBckgrndSnd)
	return controlThread


def inputDataControl(automaton, populNorm):
	"""Updates the automaton's variables needed to control the
	background sound. These global sound-control variables 'live'
	in sound_globals.py.

	automaton	---> a birdcage cellular automaton.
	"""
	soundGlobals.backgroundUpdateList = backgroundSound.updateControlCells(automaton)
	soundGlobals.populNorm = [populNorm] 


def stopSoundServer():
	"""Stops the sound server, and changes a global within
	background_sound.py. The latter causes the iteration of the
	background sound loops (and thus its threads) to end.
	"""
	csndInterface.endCsnd()
	soundGlobals.mainIterCycle = 0
