## This module intantiates the Csound API and its performance class.
# It also contains the methods for preparing Csound for performance,
# and to end the performance.

from random import choice, randint, random
# Csound API library.
import csnd
# Sound-related submodules.
import Csnd_data as CsndData

## Instantiate Csound's API, it's performance class and a .csd
#generator.
#cSnd			= csnd.CppSound()
#perf			= csnd.CsoundPerformanceThread(cSnd)
CsdGenerator	= CsndData.CsdGenerator(39) # the (hard-wired) number
											#of csound background
											#instruments is 39.


def initCSnd():
	"""Generates a single-file Csound Structured Data (.csd) string,
	sets it in the Csound API, exports it for performance, compiles it,
	and starts the 	performance.
	"""
	cSnd			= csnd.CppSound()
	perf			= csnd.CsoundPerformanceThread(cSnd)
	global perf
	#cSnd.setPythonMessageCallback() # useful for debugging.
	csd = CsdGenerator.csd
	cSnd.setCSD(csd)
	cSnd.exportForPerformance()
	cSnd.compile()
	perf.Play()

def endCsnd():
	""" Stops playback (Stop()). Releases any resources associated with
	the performance thread(Join()). Prints information about the end of
	a performance, and closes the audio device (cleanup()).
	"""
	perf.Stop()
	perf.Join()
	cSnd.cleanup()
