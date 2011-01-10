## This modules is the interface between birdcage and its aural
# component. It has wrappers to the methods to  initialize csound,
# play agent sounds (at present in early development), to start the
# background sound threads, to feed them with data, and to stop
# sound altogether.

#Python's native libraries.
import threading
import sys

# Sound-related submodules.
#import background_sound as backgroundSound
import csnd_interface as csndInterface
#import sound_globals as soundGlobals

## Instantiate the sound server class.
#SoundServer = csndInterface.SoundServer()


specificity = sys.modules["__main__"].specificity
specific = __import__("specific"+specificity)



if specific.soundOn:

	# Sound-related submodules.
	import background_sound as backgroundSound
#	import csnd_interface as csndInterface
	import sound_globals as soundGlobals
	
	# Instantiate the sound server class.
	SoundServer = csndInterface.SoundServer()

	# Import the agent's sound module and methods, except when a simulation
	# lacks agents.
	if specific.simWithAgents:
		import agents_sound as agentsSound


		def agentBirth(VocalTract):
			"""Plays the birth sound.
			VocalTract	--->> an agent's voice class
			"""
			VocalTract.birthSound(SoundServer.perf)
			
			
		def eatSound(VocalTract):
			"""Plays the eating sound.
			VocalTract	--->> an agent's voice class
			"""
			VocalTract.eatSound(SoundServer.perf)
	
	
		def agentDeath(VocalTract):
			"""Plays the death sound.
			VocalTract	--->> an agent's voice class
			"""
			VocalTract.deathSound(SoundServer.perf)
	
	
	else:
		print 'If this is a simulation with agents, set simWithAgents = True in your specificXXX.py config file.'
	
	
	def setInitialData(size):
		""" Record and make global data needed for sound processing. The
		data is recorded on sound_globals.py.
		size	---> a tuple representing the automaton's width and height
		"""
		(width, height) = size
		soundGlobals.cellControlDict = backgroundSound.setControlCells(width,
											height, specific.backgroundPartials)


	def startSoundServer():
		"""Starts the sound server.
		"""
		SoundServer.initCSnd(specific.csOptions, specific.backgroundPartials)


	def backgroundVoices():
		""" Creates three threads, each running a background voice thread.
		"""
		backgroundPartials = specific.backgroundPartials
		frstInstr = 2
		frstInstrLst = range(frstInstr, (backgroundPartials + frstInstr) * 2,
							backgroundPartials)
		argsList	= [(frstInstrLst[0], -12, 3400, 0.50, 1, backgroundPartials,
							1, SoundServer.perf, SoundServer.cSnd),
						(frstInstrLst[1], -8, 3400, 0.50, 0, backgroundPartials,
							0.5, SoundServer.perf, SoundServer.cSnd),
						(frstInstrLst[2], -14, 3400, 0.50, 2, backgroundPartials,
							0, SoundServer.perf, SoundServer.cSnd)]
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
										target=backgroundSound.ctrlBckgrndSnd,
										args=(SoundServer.cSnd, ))
		return controlThread


	def inputDataControl(automaton):
		"""Updates the automaton's variables needed to control the
		background sound. These global sound-control variables 'live'
		in sound_globals.py.
		automaton	---> a birdcage cellular automaton.
		"""
		soundGlobals.backgroundUpdateList = backgroundSound.updateControlCells(automaton)


	def stopSoundServer():
		"""Stops the sound server, and changes a global within
		background_sound.py. The latter causes the iteration of the
		background sound loops (and thus its threads) to end.
		"""
		SoundServer.endCsnd()
		soundGlobals.mainIterCycle = 0


else:
	# Instantiate the sound server class.
	SoundServer = csndInterface.DummyServer()

	# Import the agent's sound module and methods, except when a simulation
	# lacks agents.

	def agentBirth(VocalTract):
		"""Plays the birth sound.
		VocalTract	--->> an agent's voice class
		"""
		pass
		
		
	def eatSound(VocalTract):
		"""Plays the eating sound.
		VocalTract	--->> an agent's voice class
		"""
		pass


	def agentDeath(VocalTract):
		"""Plays the death sound.
		VocalTract	--->> an agent's voice class
		"""
		pass


	def setInitialData(size):
		""" Record and make global data needed for sound processing. The
		data is recorded on sound_globals.py.
		size	---> a tuple representing the automaton's width and height
		"""
		pass
		

	def startSoundServer():
		"""Starts the sound server.
		"""
		SoundServer.blankInit()


	def backgroundVoices():
		""" Creates three threads, each running a background voice thread.
		"""
		voiceList	= []
		
		def dummy():
			pass

		for index in xrange(2):
			threadName = 'BackgroundVoice' + str(index)
			voice = threading.Thread(name=threadName,
										target=dummy)
			voiceList.append(voice)
		return voiceList


	def backgroundControl():
		"""Starts the background sound control thread, which modifies the
		the background sound voices.
		"""
		def dummy():
			pass
		controlThread = threading.Thread(name='backgroundVoicesControl',
										target=dummy)
		return controlThread


	def inputDataControl(automaton):
		"""Updates the automaton's variables needed to control the
		background sound. These global sound-control variables 'live'
		in sound_globals.py.
		automaton	---> a birdcage cellular automaton.
		"""
		pass


	def stopSoundServer():
		"""Stops the sound server, and changes a global within
		background_sound.py. The latter causes the iteration of the
		background sound loops (and thus its threads) to end.
		"""
		SoundServer.endCsnd()
		soundGlobals.mainIterCycle = 0
