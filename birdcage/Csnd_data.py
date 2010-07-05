## Contains a class who's attributes are needed to construct a .csd,
#and a class that constructs a .csd. For information on .csd file
#types, and Csound command-line options, look at The Cannonical Csound
#Reference Manual.


class CsdStrings(object):
	""" Contains the strings needed to construct a .csd file.
	while the class contains methods, these are only ment to set the
	class's attributes, while keeping an ordered way to comment on each
	attribute (the methods).
	"""
	def __init__(self, csOptions):
		""" Runs the methods in the class in order to set the classe's
		attributes. For information on the attributes, read its method
		doc-string.
		"""
		self.csOptions	= csOptions
		self.opts		= self.dfltOpts()
		self.orchHead	= self.dfltOrchHead()
		self.instrs		= self.dfltInstrs()
		self.sco		= self.dfltSco()


	def dfltOpts(self):
		""" Sets csound's command line flags. The flags employed are as
		follows:
		-o dac				---> 'write' audio to the host audio output
								device.
		-+rtaudio=alsa		---> specify alsa as the audio driver
								interface
		-b 8192				---> sample-frames per software buffer
		-B 8192				---> sample-frames held in the hardware
								buffer
		-d					---> don't show any displays
		-m0					---> don't show messages during the
								performance
		temp.orc temp.sco	---> name of the temporary output files
		return 				--> the csOtions string
		"""
		csOptions	= self.csOptions
		return csOptions

	def dfltOrchHead(self):
		""" The header, this is the beginning of the .csd's
		CsInstruments Section. Comments are included within the string
		(preceeded by a semicolon).
		return --> the orchestra-header string
		"""
		orchestraHeader	= """
<CsInstruments>
sr = 44100	; sample rate
kr = 4410	; control rate
ksmps = 10	; sr/kr
nchnls = 2	; # of channels

		"""
		return orchestraHeader


	def dfltInstrs(self):
		""" The CsInstruments instruments (data flow and signal-
		processing algorithms). Comments are included within the string
		(preceeded by a semicolon).
		return --> a list of strings, each representing an instrument
					definition
		"""
		# Instrument 1: Stereo filtered pink noise with amplitude
		#envelope.
		instr1	= """
instr    1

idur    = p3

iptch1	= p4
iptch2	= p5

ivibr	= p6

iidev = p7
iadev = p8
iodev = p9

ileft	= sqrt(p10)	; between 0-1, 1 is hard left
iright	= sqrt(1 - p10)

; formants frequencies
ifrq1i	= 1270 + iidev
ifrq2i	= 2140 + iidev
ifrq3i	= 3950 + iidev
ifrq1a	= 1800 + iadev
ifrq2a	= 2150 + iadev
ifrq3a	= 3900 + iadev
ifrq1o	= 1450 + iodev
ifrq2o	= 2800 + iodev
ifrq3o	= 3830 + iodev

; formants amplitudes
iamp1i	= ampdbfs(0)
iamp2i	= ampdbfs(-6)
iamp3i	= ampdbfs(-32)
iamp1a	= ampdbfs(0)
iamp2a	= ampdbfs(-12)
iamp3a	= ampdbfs(-26)
iamp1o	= ampdbfs(0)
iamp2o	= ampdbfs(-11)
iamp3o	= ampdbfs(-22)

; formants band-widths
ibw1i	= 60
ibw2i	= 90
ibw3i	= 100
ibw1a	= 80
ibw2a	= 90
ibw3a	= 120
ibw1o	= 70
ibw2o	= 80
ibw3o	= 100

; specific to birth sounds.
if (iodev == 0) then
	; fof1 i-a envelopes
	kfrq1 linseg ifrq1i, idur * .6, ifrq1a, .01, ifrq1a
	kamp1 linseg iamp1i, idur * .6, iamp1a, .01, iamp1a
	kbw1 linseg ibw1i, idur * .6, ibw1a, .01, ibw1a

	; fof2 i-a envelopes
	kfrq2 linseg ifrq2i, idur * .6, ifrq2a, .01, ifrq2a
	kamp2 linseg iamp2i, idur * .6, iamp2a, .01, iamp2a
	kbw2 linseg ibw2i, idur * .6, ibw2a, .01, ibw2a

	; fof3 i-a envelopes
	kfrq3 linseg ifrq3i, idur * .6, ifrq3a, .01, ifrq3a
	kamp3 linseg iamp3i, idur * .6, iamp3a, .01, iamp3a
	kbw3 linseg ibw3i, idur * .6, ibw3a, .01, ibw3a

	; Pitch envelope
	kptch	linseg iptch1, idur * .3, iptch1, idur * .1, iptch2, idur * .4, iptch2, idur * .2, iptch1

	; vibrato
	klfo lfo 50, ivibr

	; Overall level envelope
	klvlenv linseg  0, .01, 1, idur - .02, 1, .01, 0

	; signal generators
	a1 fof  kamp1, kptch + klfo, kfrq1, 0, kbw1, .003, .02, .007, 1000, 1, 2, idur, rnd(1), 1
	a2 fof  kamp2, kptch + klfo, kfrq2, 0, kbw2, .003, .02, .007, 1000, 1, 2, idur, rnd(1), 1
	a3 fof  kamp3, kptch + klfo, kfrq3, 0, kbw3, .003, .02, .007, 1000, 1, 2, idur, rnd(1), 1
	avoice = (a1 + a2 + a3) * klvlenv * .1

; specific to eating sounds.
else

	; fof1 o envelopes
	kfrq1 = ifrq1o
	kamp1 = iamp1o
	kbw1 = ibw1o

	; fof2 o envelopes
	kfrq2 = ifrq2o
	kamp2 = iamp2o
	kbw2 = ibw2o

	; fof3 o envelopes
	kfrq3 = ifrq3o
	kamp3 = iamp3o
	kbw3 = ibw3o

	; octavation factor
	koct linseg 0, idur, 2

	; Overall level envelope
	klvlenv linseg  0, .01, 1, idur - .02, 1, .01, 0

	; noise envelope
	ilen = idur * 0.5
	knoise linseg 10, .05, 10, idur - .02, 0

	; signal generators
	anoise	rand knoise
	afilt	butterbp anoise, iptch2, 10
	a1 fof  kamp1, iptch1, kfrq1, koct, kbw1, .003, .02, .007, 1000, 1, 2, idur, rnd(1), 1
	a2 fof  kamp2, iptch1, kfrq2, koct, kbw2, .003, .02, .007, 1000, 1, 2, idur, rnd(1), 1
	a3 fof  kamp3, iptch1, kfrq3, koct, kbw3, .003, .02, .007, 1000, 1, 2, idur, rnd(1), 1
	avoice = (a1 + a2 + a3) * klvlenv * 0.9 * afilt

endif

    outs avoice * ileft, avoice * iright
 
 endin
		"""
		# Instrument 2: Stereo sinusoidal oscilator with amplitude
		#envelope, and glissando pitch.
		instr2	= """
    instr 2
kchan	chnget "chan1"			;initialize a real-time control channel

idur			= abs(p3)					; in seconds
iamp			= p4						; 0-32767
iamp1			= iamp * 0.5
ifreq1			= p5						; in hz
ifreq2			= p6
idurtoenvmax		= p8 - .02
idurback		= idur - idurtoenvmax - .02
ileft			= sqrt(p7)					; between 0-1, 1 is hard left
iright			= sqrt(1-p7)

; prtamento for the channel input

if (kchan == 1) then
kgate	port kchan, .01
kbandwidth	port kchan, 10
else
kgate	port kchan, 1
kbandwidth	port kchan, 10
endif

; test if the note is tied
ir		tival
i1	= -1

; if the note is tied, skip the rand initialization and define an amp. envlp.
	tigoto tied
i1	= 0

; amplitude envelope
kampenv		linseg 0, .02, iamp1, idurtoenvmax, iamp;, idurback, iamp1, .5, 0

tied:
; skip this section if the note is tied.
if ir == 0 kgoto signlgen

; amplitude envelope for tied notes.
;kampenvtied		linseg 0, .5, iamp1, idurtoenvmax, iamp, idurback, iamp1, .5, 0
kampenv = k(iamp) + kampenv

signlgen:
; frequency glissando.
kfreqgliss	expseg ifreq1, idur, ifreq2; * .1, ifreq1, idur * .8, ifreq2, idur *.1, ifreq2

; filtered noise
anoise	rand 15000, i1
afilt	butterbp anoise, kfreqgliss, kbandwidth, i1
;abalance balance afilt, anoise
;; oscilator with amplitude and frequency envelopes
;asig		oscili kampenv, kfreqgliss, 1, i1
; stereo output
	afilt = afilt * kgate
    outs afilt * ileft, afilt * iright
    endin
		"""

		instrs = [instr1, instr2]
		return instrs


	def dfltSco(self):
		""" Ths CsScore section. It contains the function definitions,
		and an note statement that does 10 hours of silence, to keep
		the	Csound Api running.
		return --> the score string
		"""
		score	= """
</CsInstruments>
<CsScore>
; a sine wave
f1 0 4096 10 1
f2 0 1024 19 .5 .5 270 .5 ; Rising sigmoid
f3 36000 129 -7 0 128 1

e ; end of the score
</CsScore>
</CsoundSynthesizer>"""
		return score


class CsdGenerator(object):
	"""
	"""
	def __init__(self, instr2clones, specificity):
		"""
		"""
		# Inputed and externally generated attributes.
		self.CsdStrings		= CsdStrings(specificity)
		self.opts			= self.CsdStrings.opts
		self.orchHead		= self.CsdStrings.orchHead
		self.instrs			= self.CsdStrings.instrs
		self.instr1			= self.CsdStrings.instrs[0]
		self.instr2			= self.CsdStrings.instrs[1]
		self.sco			= self.CsdStrings.sco
		self.instr2clones	= instr2clones
		self.strt 			= 1
		# Internally generated attributes
		self.chnnlLst		= self.mkChnnlNmes()
		self.chnnlDeclar	= self.chnnlDeclar()
		self.orc			= self.mkOrc()
		self.csd			= self.makeCSD()


	def mkChnnlNmes(self):
		"""Makes a list of channel-name strings to be used in the
		channel declaration section of the orchestra.
		return	--> a list of channel-name strings
		"""
		dblQuote	= '"'
		prfx		= 'chan'
		nmbr		= self.strt
		chnnlLst	= []

		for x in xrange(self.instr2clones):
			channel = '%s%s%s%s' %(dblQuote, prfx, nmbr, dblQuote)
			chnnlLst.append(channel)
			nmbr += 1
		return chnnlLst


	def chnnlDeclar(self):
		"""Constructs a string with the channel declaration part of the
		orchestra, for input control channels.
		return	--> a string of Csound channel declarations
		"""
		chnnlDeclar	= ''

		for x in self.chnnlLst:
			chnnlDeclar = chnnlDeclar + 'chn_k ' + str(x) + ', 1, 0\n'
		return chnnlDeclar


	def mkInstrClones(self):
		"""Constructs a series of instrument clones based on an
		instrument definition, assigning a different control channel to
		each instrument.
		return	--> a string of cloned instruments
		"""
		instrString		= self.instr2
		instrNo		= 3

		self.chnnlLst.pop(0)
		for x in self.chnnlLst:
			nInstrNo = ''.join(['instr ', str(instrNo)])
			hlfNInstr = self.instr2.replace('instr 2', nInstrNo)
			newInstr = hlfNInstr.replace('"chan1"', str(x))
			instrString = instrString + newInstr
			instrNo += 1
		return instrString


	def mkOrc(self):
		"""Uses the header, channel definition method, and instrument
		instantiation to construct the orchestra.
		return	--> an orchestra string
		"""
		instr2Clones	= self.mkInstrClones()

		orc = '%s%s%s%s' %(self.orchHead, self.chnnlDeclar, self.instr1,
								instr2Clones)
		return orc


	def makeCSD(self):
		"""Constructs a .csd string.
		return	--> a .csd string
		"""
		csd = """%s%s%s""" %(self.opts, self.orc, self.sco)
		return csd
