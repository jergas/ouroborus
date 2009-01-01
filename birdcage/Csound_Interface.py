from random import choice, randint, random
## Import Python's Csound library
import csnd
## Import user defined method.
from Csound_Note import noteI1

## Instantiate Csound's API, and it's performance class.
csound = csnd.CppSound()
perf = csnd.CsoundPerformanceThread(csound)

def initCsound():
	"""Makes an instance of the Csound Api, sets a string that works as a CSD file with the appropriate
	options, exports it to csound, compiles the CSD, starts a performance thread, and starts playing."""
	#csound.setPythonMessageCallback()
	csound.setCSD('''
<CsoundSynthesizer>
<CsOptions>
csound -odac -+rtaudio=alsa -b512 -B16384 -m0 -d temp.orc temp.sco
</CsOptions>

<CsInstruments>
sr = 44100	; sample rate
kr = 4410	; control rate
ksmps = 10	; sr/kr
nchnls = 2	; # de canales


; instrument 1: Stereo filtered pink noise with amplitude envelope.
    instr 1
idur			= p3		; in seconds
iamp			= p4		; 0-32767
icntrfreq		= p5		; in hz
ileft			= sqrt(p6)	; between 0-1, 1 is hard left
iright			= sqrt(1-p6)	; ibidem
iattkt			= p7		; in seconds
idcyt			= p8		; ibidem
imaxampdur		= idur - (iattkt + idcyt)
kampenv		envlpx iamp, .0001, idur, 1, 2, 0.1, .001
apink		pinkish kampenv, 0
ares		reson apink, icntrfreq, 20		
    outs ares * ileft, ares * iright
    endin

; instrument 1: Stereo sinusoidal oscilator with linear envelope, and glissando pitch.
    instr 2
idur			= p3		; in seconds
iamp			= p4		; 0-32767
ifreq1			= p5		; in hz
ifreq2			= p6		; in hz
ileft			= sqrt(p7)	; between 0-1, 1 is hard left
iright			= sqrt(1-p7)	; ibidem
iattkt			= p8		; in seconds
idcyt			= p9		; ibidem
imaxampdur		= idur - (iattkt + idcyt)
iglissdur1		= p3 * 0.5
iglisssust		= p3 * 0.25
iglissdur2		= p3 * 0.25
kampenv		linseg 0, iattkt, iamp, imaxampdur, iamp, idcyt, 0
kfreqgliss	expseg ifreq1, iglissdur1, ifreq2, iglisssust, ifreq2, iglissdur2, ifreq1
asig		oscili kampenv, kfreqgliss, 1
    outs asig * ileft, asig * iright
    endin

</CsInstruments>
<CsScore>
f1 0 4096 10 1       ; a sine wave
f2 0 129 -7 0 128 1

; ten hours of silence:
i1	0	36000	0	3000	0	0	0
e ; end of the score
</CsScore>
</CsoundSynthesizer>

	''')
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
