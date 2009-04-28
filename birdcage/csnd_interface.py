## This module intantiates the Csound API and its performance class.
# It also contains the methods for preparing Csound for performance,
# and to end the performance.

from random import choice, randint, random
# Csound API library.
import csnd
# Sound-related submodules.
import csd_generator as csdGenerator

## Instantiate Csound's API, and it's performance class.
cSnd	= csnd.CppSound()
perf	= csnd.CsoundPerformanceThread(cSnd)


def initCSnd():
	"""Generates a single-file Csound structured data (CSD) string,
	sets it in the Csound API, exports it for performance, compiles it,
	and starts the 	performance.
	"""
	#cSnd.setPythonMessageCallback() # useful for debugging.
	csd = csdGenerator.makeCSD(39) # the (hard-wired) number of csound
									# background instruments is 39.
	cSnd.setCSD(csd)
	cSnd.exportForPerformance()
	cSnd.compile()
	perf.Play()

def endCsnd():
	""" Stops playback (Top()). Releases any resources associated with
	the performance thread(Join()). Prints information about the end of
	a performance, and closes the audio device (cleanup()).
	"""
	perf.Stop()
	perf.Join()
	cSnd.cleanup()
