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
	def __init__(self):
		""" Runs the methods in the class in order to set the classe's
		attributes. For information on the attributes, read its method
		doc-string.
		"""
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
		csOptions	= """
<CsoundSynthesizer>
<CsOptions>
csound -odac -+rtaudio=alsa -b8192 -B8192 -d -m0 temp.orc temp.sco
</CsOptions>"""
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
	instr 1
idur		= p3			; in seconds
iamp		= p4			; 0-32767
icntrfreq	= p5			; in hz
ileft		= sqrt(p6)		; between 0-1, 1 is hard left
iright		= sqrt(1-p6)
iattkt		= p7			; in seconds
idcyt		= p8
imaxampdur	= idur - (iattkt + idcyt)
; amplitude envelope
kampenv	envlpx iamp, .0001, idur, 1, 2, 0.1, .001
; enveloped pink noise
apink	pinkish kampenv, 0
; resonating filter
ares	reson apink, icntrfreq, 20		
; stereo output
	outs ares * ileft, ares * iright
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
kgate			= kchan
; test if the note is tied
ir		tival
i1	= -1
; if the note is tied, skip the oscili initialization and define an amp. envlp.
	tigoto tied
i1		= 0
; amplitude envelope
kampenv		expseg 0.001, 1, iamp1, idurtoenvmax, iamp, idurback, iamp1, .5, 0.001
tied:
; skip this section if the note is tied.
if ir == 0 kgoto oscilator
; amplitude envelope for tied notes.
kampenvtied		expseg 0.001, .5, iamp1, idurtoenvmax, iamp, idurback, iamp1, .5, 0.001
kampenv = kampenv + kampenvtied
oscilator:
; frequency glissando.
kfreqgliss	expseg ifreq1, idur * .1, ifreq1, idur * .8, ifreq2, idur *.1, ifreq2
; oscilator with amplitude and frequency envelopes
asig		oscili kampenv * kgate, kfreqgliss, 1, i1
; stereo output
    outs asig * ileft, asig * iright
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
f2 0 129 -7 0 128 1

; ten hours of silence:
i1	0	36000	0	3000	0	0	0
e ; end of the score
</CsScore>
</CsoundSynthesizer>"""
		return score


class CsdGenerator(object):
	"""
	"""
	def __init__(self, instr2clones):
		"""
		"""
		# Inputed and externally generated attributes.
		self.CsdStrings		= CsdStrings()
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
