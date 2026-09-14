## This module intantiates the Csound API and its performance class.
# It also contains the methods for preparing Csound for performance,
# and to end the performance.

# Python native libraries.
import time
import threading

# Csound API library.
# ctcsound is imported only when audio is enabled.
# Sound-related submodules.
from . import Csnd_data as CsndData

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
                dummyPerf.daemon = True
                dummyPerf.start()


        def status(self):
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
                import ctcsound
                self.cSnd = ctcsound.Csound()
                self.perf = None
                self._ctcsound = ctcsound



        def initCSnd(self, csOptions, backgroundPartials):
                """Generates a single-file Csound Structured Data (.csd) string,
                sets it in the Csound API, exports it for performance, compiles it,
                and prepares a paused performance. Call play after genome builds.
                csOptions                       ---> the command-line csound options
                backgroundPartials      ---> the number of per voice spectral partials
                """
                #cSnd.setPythonMessageCallback() # useful for debugging.
                totalPartials   = backgroundPartials * 3
                CsdGenerator    = CsndData.CsdGenerator(totalPartials, csOptions)
                csd = CsdGenerator.csd
                if self.cSnd.compileCsdText(csd) != 0:
                        raise RuntimeError("Csound could not compile the Worldish orchestra")
                from . import runtime
                self.cSnd.setControlChannel("worldish_attenuation", 1 - getattr(runtime.get_specific(), "desktopVolume", 1.0))
                if self.cSnd.start() != 0:
                        raise RuntimeError("Csound could not start its audio output")
                self.perf = self._ctcsound.CsoundPerformanceThread(self.cSnd.csound())

        def play(self):
                """Begin playback once the simulation is ready."""
                self.perf.play()



        def endCsnd(self):
                """ Stops playback (Stop()). Releases any resources associated with
                the performance thread(Join()). Prints information about the end of
                a performance, and closes the audio device (cleanup()).
                """
                if self.perf is not None:
                        self.perf.stop()
                        self.perf.join()
                        self.perf = None



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
