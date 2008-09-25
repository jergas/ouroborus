## Method to generate a Distorted Harmonic Spectrum note.
import csnd

from Csound_Note import note
from random import choice, randint

csound = csnd.CppSound()
perf = csnd.CsoundPerformanceThread(csound)

## It makes an instance of the Csound Api, sets a string that works as a
#CSD file with the appropriate options, exports it to csound, compiles
#the CSD, starts a performance thread, and
#starts playing.
def initCsound():
    
    csound.setPythonMessageCallback()
    csound.setCSD('''
<CsoundSynthesizer>
<CsOptions>
csound -odac -+rtaudio=alsa -b8192 -B8192 -m0 -d temp.orc temp.sco
</CsOptions>

<CsInstruments>
sr = 44100	; sample rate
kr = 4410	; control rate
ksmps = 10	; sr/kr
nchnls = 2	; # de canales


; instrument 1: Stereo sinusoidal oscilator with linear envelope 

    instr 1
ileft = sqrt(p6)
iright = sqrt (1-p6)
kctrl	linen p4, p7, p3, p8
asig	oscili kctrl,p5,1
    outs asig * ileft, asig * iright
    endin

; p1 instrument n.
; p2 start time
; p3 duration
; p4 amplitude (0-32767)
; p5 frquency (en hz)
; p6 panning (0-1, 1 es izquierda)
; p7 attack time
; p8 decay time

</CsInstruments>
<CsScore>
f1 0 4096 10 1       ; use GEN10 to compute a sine wave

; ten hours of silence:
i1	0	36000	0	3000	0	0	0
e ; end of the score
</CsScore>
</CsoundSynthesizer>

    ''')
    csound.exportForPerformance()
    csound.compile()

    perf.Play()
##Displays options for the next set of partials to be used in the next
#note, waits for the user's instructions and sends the selected parameters
#to Csound. These instructions are repeated while the user choses a valid
#option.
def csoundNote():
    specType    = [0, 1, 2, 3]
    distFactor  = [.5, .55, .60, .65, .70, .75, .80, .85, .90, .95, 1,
                1.05, 1.15, 1.20, 1.25, 1.30, 1.35, 1.40, 1.45, 1.50]
    noteDur     = [2, 3, 5, 7, 11, 13]
    try:
            spectrum = note(randint(200, 800), randint(10, 150), choice(specType),
                    choice(distFactor), 0, choice(noteDur))
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
    HelloWorld()
