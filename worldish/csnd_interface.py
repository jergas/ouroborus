## This module intantiates the Csound API and its performance class.
# It also contains the methods for preparing Csound for performance,
# and to end the performance.

# Python native libraries.
import time
import threading

# Csound API library.
import csnd
# Sound-related submodules.
import Csnd_data as CsndData

class DummyPerf(object):
	""" This class deals with ctrl^c when simulations lack sound.
	"""
	def __init__(self):
		"""
		"""
		self.keyInterrupt = False


	def sigIntCatcher(self):
		""" Start a loop that catches a ctrl^c signal.
		"""
		while not self.keyInterrupt:
			try:
				time.sleep(0.1)
			except KeyboardInterrupt:
				break
		self.keyInterrupt = True


	def start(self):
		""" Stop the ctrl^c signal catcher.
		"""
		dummyPerf = threading.Thread(target=self.sigIntCatcher)
		dummyPerf.setDaemon(True)
		dummyPerf.start()


	def GetStatus(self):
		if self.keyInterrupt:
			exit = 1
		else:
			exit = 0
		return exit
		



	def stop(self):
		""" Stop the ctrl^c signal catcher.
		"""
		self.keyInterrupt = True



class SoundServer(object):
	"""This class functions as a Csound sound server.
	"""
	def __init__(self):
		"""Instantiate Csound's API and it's performance class.
		"""
		self.cSnd			= csnd.CppSound()
		self.perf			= csnd.CsoundPerformanceThread(self.cSnd)


	def initCSnd(self, csOptions, backgroundPartials):
		"""Generates a single-file Csound Structured Data (.csd) string,
		sets it in the Csound API, exports it for performance, compiles it,
		and starts the 	performance.
		csOptions			---> the command-line csound options
		backgroundPartials	---> the number of per voice spectral partials
		"""
		#cSnd.setPythonMessageCallback() # useful for debugging.
		totalPartials	= backgroundPartials * 3
		CsdGenerator	= CsndData.CsdGenerator(totalPartials, csOptions)
		csd = CsdGenerator.csd
		self.cSnd.setCSD(csd)
		self.cSnd.exportForPerformance()
		self.cSnd.compile()
		self.perf.Play()


	def endCsnd(self):
		""" Stops playback (Stop()). Releases any resources associated with
		the performance thread(Join()). Prints information about the end of
		a performance, and closes the audio device (cleanup()).
		"""
		self.perf.Stop()
		self.perf.Join()
		self.cSnd.cleanup()


class DummyServer(object):
	"""This class substitutes SoundServer() when the simulation lacks
	sound.
	"""
	def __init__(self):
		"""This does nothing.
		"""
		self.perf = DummyPerf()


	def start(self):
		"""This does nothing.
		"""
		self.perf.start()


	def stop(self):
		"""This does nothing.
		"""
		self.perf.stop()
