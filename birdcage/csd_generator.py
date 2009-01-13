
## Defines an orchestra with instances of the same instrument with different internal channel control numbers
# so that they can be controled independently.

## Imports the csd parts (options, header, instruments and score).
import csd_parts

def namesChannels(numberOfChannels, start = 1):
	"""Makes a list of channel-name strings to be used in the channel declaration section of the 		orchestra."""
	doubleQuote	= '"'
	prefix		= 'chan'
	number		= start
	counter		= numberOfChannels
	channelList	= []

	while counter > 0:
		channel = '%s%s%s%s' %(doubleQuote, prefix, number, doubleQuote)
		channelList.append(channel)
		number = number + 1
		counter = counter - 1
	return channelList

def declarationChannels(number):
	"""Constructs a string with the channel declaration part of the orchestra, for input control
	channels that use a linear scale."""
	channelList = namesChannels(number)
	channelsDeclaration = ''

	for x in channelList:
		channelsDeclaration = channelsDeclaration + 'chn_k ' + x + ', 1, 1, 1, 0, 1\n'
	return channelsDeclaration

def recursiveInstrumentDefinition(noOfCopies):
	"""Constructs a series of instrument based on an instrument definition, assigning a different control
	channel to each instrument"""
	channelList		= namesChannels(noOfCopies)
	originalInstrument2	= csd_parts.instrument2
	instrumentList		= originalInstrument2
	instrumentNo		= 3

	channelList.pop(0)
	for x in channelList:
		newInstrumentNo = 'instr ' + str(instrumentNo)
		halfNewInstrument = originalInstrument2.replace('instr 2', newInstrumentNo)
		newInstrument = halfNewInstrument.replace('"chan1"', str(x))
		instrumentList = instrumentList + newInstrument
		instrumentNo = instrumentNo + 1
	return instrumentList

def makeOrchestra(noInstrInstances):
	"""Uses the header, channel definition method, and instrument instantiation 
	to construct the orchestra"""
	channelDeclaration	= declarationChannels(noInstrInstances)
	instrument2Instances	= recursiveInstrumentDefinition(noInstrInstances)
	
	orchestra = """%s
%s%s%s""" %(csd_parts.orchestraHeader, channelDeclaration, csd_parts.instrument1, instrument2Instances)
	return orchestra

def makeCSD(noInstrInstances):
	"""Uses the above methods, and the variables from csd_parts.py to construct a (csound) csd string."""
	orchestra	= makeOrchestra(noInstrInstances)

	csd = """%s
%s
%s""" %(csd_parts.csOptions, orchestra, csd_parts.csScore)
	return csd
