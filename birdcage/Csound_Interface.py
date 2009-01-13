from random import choice, randint, random
## Import Python's Csound library
import csnd
## Import user defined methods.
from Csound_Note import noteI1
import csd_generator

## Instantiate Csound's API, and it's performance class.
csound = csnd.CppSound()
perf = csnd.CsoundPerformanceThread(csound)

def initCsound():
	"""Makes an instance of the Csound Api, sets a string that works as a CSD file with the appropriate
	options, exports it to csound, compiles the CSD, starts a performance thread, and starts playing."""
	
	#csound.setPythonMessageCallback()
	csound.setCSD(csd_generator.makeCSD(39))
	csound.exportForPerformance()
	csound.compile()
	perf.Play()

def csoundNoteI1():
	""" Generates the sound that derives from the instantiation of a birdcage agent.""" 
	specType	= [0, 1, 2, 3]
	distFactor	= [.5, .55, .60, .65, .70, .75, .80, .85, .90, .95, 1,
			1.05, 1.15, 1.20, 1.25, 1.30, 1.35, 1.40, 1.45, 1.50]
	noteDur		= random() + 0.5
	try:
		spectrum = noteI1(randint(440, 880), randint(10, 150), choice(specType),
					choice(distFactor), random(), noteDur)
		while len(spectrum) > 0:
			partial = spectrum.pop(0)
			perf.InputMessage(partial)   
	except:
		print """
CsoundModulesError...

Applying the GIGO (garbag in garbage out) rule.'

"""
		perf.Stop()
		perf.Join()
if __name__ == "__main__":
	initCsound()
