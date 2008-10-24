## Method to generate a Distorted Harmonic Spectrum note.
import csnd

from Csound_Note import note
from random import choice, randint, random

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
idur		= p3		; in seconds
iamp		= p4		; 0-32767
ifreq		= p5		; in hz
ileft		= sqrt(p6)	; between 0-1, 1 is hard left
iright		= sqrt(1-p6)	; ibidem
iattkt		= p7		; in seconds
idcyt		= p8		; ibidem
imaxampdur	= idur - (iattkt + idcyt)
klinenv	linseg 0, iattkt, iamp, imaxampdur, iamp, idcyt, 0
asig	oscili klinenv,ifreq,1
    outs asig * ileft, asig * iright
    endin

    instr 2
idur		= p3		; in seconds
iamp		= p4		; 0-32767
ifreq		= p5		; in hz
ileft		= sqrt(p6)	; between 0-1, 1 is hard left
iright		= sqrt(1-p6)	; ibidem
iattkt		= p7		; in seconds
idcyt		= p8		; ibidem
imaxampdur	= idur - (iattkt + idcyt)
kexpenv	expseg 0.001, iattkt, iamp, imaxampdur, iamp, idcyt, 0.001
asig	oscili kexpenv,ifreq,1
    outs asig * ileft, asig * iright
    endin

</CsInstruments>
<CsScore>
f1 0 4096 10 1       ; a sine wave

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
                    choice(distFactor), random(), choice(noteDur))
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
