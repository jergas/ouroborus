## Contains the different elements to construct a (csound) csd. 

csOptions	= """<CsoundSynthesizer>
<CsOptions>
csound -odac -+rtaudio=alsa -b8192 -B8192 -d -m0 temp.orc temp.sco
</CsOptions>"""
orchestraHeader	= """<CsInstruments>
sr = 44100	; sample rate
kr = 4410	; control rate
ksmps = 10	; sr/kr
nchnls = 2	; # of channels
"""
## instrument 1: Stereo filtered pink noise with amplitude envelope.
instrument1	= """
    instr 1
idur		= p3		; in seconds
iamp		= p4		; 0-32767
icntrfreq	= p5		; in hz
ileft		= sqrt(p6)	; between 0-1, 1 is hard left
iright		= sqrt(1-p6)	; ibidem
iattkt		= p7		; in seconds
idcyt		= p8		; ibidem
imaxampdur	= idur - (iattkt + idcyt)
kampenv	envlpx iamp, .0001, idur, 1, 2, 0.1, .001
apink	pinkish kampenv, 0
ares	reson apink, icntrfreq, 20		
    outs ares * ileft, ares * iright
    endin
"""
## instrument 2: Stereo sinusoidal oscilator with linear envelope, and glissando pitch.
instrument2	= """
    instr 2
kchan	chnget "chan1"

idur			= abs(p3)	; in seconds
iamp			= p4		; 0-32767
iamp1			= iamp * 0.5
ifreq1			= p5		; in hz
ifreq2			= p6		; in hz
idurtoenvmax		= p8 - .02
idurback		= idur - idurtoenvmax - .02
ileft			= sqrt(p7)	; between 0-1, 1 is hard left
iright			= sqrt(1-p7)	; ibidem
kgate			= kchan

kampenv		expseg 0.001, .02, iamp1, idurtoenvmax, iamp, idurback, iamp1, .02, 0.001
kfreqgliss	expseg ifreq1, idur * .1, ifreq1, idur * .8, ifreq2, idur *.1, ifreq2
asig		oscili kampenv * kgate, kfreqgliss, 1
    outs asig * ileft, asig * iright
    endin
"""
csScore		= """</CsInstruments>
<CsScore>
f1 0 4096 10 1       ; a sine wave
f2 0 129 -7 0 128 1

; ten hours of silence:
i1	0	36000	0	3000	0	0	0
e ; end of the score
</CsScore>
</CsoundSynthesizer>"""
