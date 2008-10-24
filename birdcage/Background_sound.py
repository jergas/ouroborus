## Import the necessary built-in modules
import time, threading
## Import the necessary user-defined modules
from Csound_Interface import csoundNote, initCsound, perf
from Csound_Note import note

## Variable to stop the threads' iterations. Will be changed externally (by main_sequence.py)
mainIterCycle = 1

## Threading class for the background sound.
class backgroundSound1(threading.Thread):

## Thread's run method.
	def run(self):
		while mainIterCycle == 1:
			spectrum1 = note(110, 5, 0, .5, 1, 13)
			while len(spectrum1) > 0:
                		partial1 = spectrum1.pop(0)
                		perf.InputMessage(partial1)
			time.sleep(13)

## Another threading class for background sound.
class backgroundSound2(threading.Thread):

	def run(self):
		while mainIterCycle == 1:
			spectrum2 = note(165, 5, 3, 1.3, 0, 17)
			while len(spectrum2) > 0:
                		partial2 = spectrum2.pop(0)
                		perf.InputMessage(partial2)
			time.sleep(17)

## Background Sound's playback method.
def playback():
	backgroundSound1().start()
	backgroundSound2().start()

if __name__ == "__main__":
    playback()
