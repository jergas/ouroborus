#!/usr/bin/python

"""This baby is the start button for the whole ouroborus microworld!

Coded by Jergas Apwith, Ernesto Illescas and Sat Tara Singh Khalsa. 

It arrived at its present form on 24th August 2011.

Some words are in order: 

1) start.py should be called directly from the command line, with 
root privileges to ensure file-writing and compilation operations
throughout the program will be completed successfully.

2) What this code does is read command line options and store them in
variables at the local namspace, which would normally be __main__. If
this is imported as a module and called from someplace else, then it
will be necessary to adjust this, both here and elsewhere throughout
the program.

3) The first option, stored as specificity, is a config file module
with various information needed for the runtime implementation of the
microworld, ranging from the name of a debug log file to the genetics
of the original creatures. The names of these config modules begin 
with 'specificity_', typically followed by a Greek letter name. You may of course modify the existing ones or create your own.

4) The option for mode also directs importation of a module. This module contains the code that actually orchestrates the microworld, using the objects defined in the various components of ouroborus. For
this reason these modules are generically termed mainSequence, and 
their names begin with 'sequence_'. You're welcome to try out 
your own.

5) The submode refers to the function within the mainSequence module
which actually starts execution. Of course it is possible to have 
variants within the same module, which is the reason why this option
exists. The name of the function begins with 'startExecution'.

Read some history at EOF"""

# First the usual imports - basic system stuff really.

import sys
from getopt import gnu_getopt

# Now parse config file options from the command line. Available 
# options are presented in the 3 lines immediately below, along 
# with their default values. The program then reads command line
# input from sys.argv[1:] and checks for various alternate format
# styles. Once the input is read, relevant information is stored
# in the form of global variables, and a corresponding config file
# is imported. Appropriate defaults are provided in case things 
# don't run smoothly.
#
# These 3 lines need to be modified if new options are introduced.
# All parsing up to global variable definitions will then follow 
# by magic.

options	= "s:m:n:"
longOptions	= ["specificity=", "mode=", "submode="]
defaults = ["Alpha", "Threaded", "Normal"]

# The magic begins here

optionList, arguments = gnu_getopt(sys.argv[1:], options, longOptions)
sys.argv = [sys.argv[0]] + arguments

def removeTrailingEqual(string):
	"""Remove a trailing equal sign from a string, if present.
	string ---> a longOption name from the command line
	return -->> the name without any trailing "="
	"""
	if string[-1] == "=":
		string = string[0:-1]
	return string

def processOption(string):
	"""Accept variations of command line options.
	string ---> the different alternatives for an option
	return -->> a standard format for the same
	"""
	if string[0] == "=":
		string = string[1:len(string)]
	string = string.capitalize()
	return string

strippedOptions = "".join(options.split(":"))
strippedLongOptions = [removeTrailingEqual(option) for option in longOptions]
assert len(strippedOptions) == len(strippedLongOptions)

# Assign global variables with correct format.

for i in range(len(strippedOptions)):
	shortName = strippedOptions[i]
	longName = strippedLongOptions[i]
	for optionPair in optionList:
		(name, value) = optionPair
		value = processOption(value)
		if name in ("-" + shortName, "--" + longName):
			setattr(sys.modules["__main__"], longName, value)
			break

# If variables are not set, assign default values.

for i in range(len(strippedLongOptions)):
	if strippedLongOptions[i] not in dir(sys.modules["__main__"]):
		setattr(sys.modules["__main__"], strippedLongOptions[i], defaults[i])


# Now that the global variables have been set, dynamic importation of
# modules and similar specific operations are carried out for each
# one.
#
# This needs to be looked at if new options are introduced.

try:
	specific = __import__("specific_"+specificity.lower())
except ImportError:
	specificity = defaults[0]
	specific = __import__("specific_"+specificity.lower())

try:
	mainSequence = __import__("sequence_"+mode.lower())
except ImportError:
	mode = defaults[1]
	mainSequence = __import__("sequence_"+mode.lower())

try:
	executionFunction = getattr(mainSequence, "startExecution"+submode)
except AttributeError:
	submode = defaults[2]
	executionFunction = getattr(mainSequence, "startExecution"+submode)

# This is some text output, useful for debugging. Note that when the
# mainSequence module is imported stdout is redirected to a log file
# named in the config module. This output text will be found there
# rather than in the terminal.

print "Starting sequence has run successfully."
print "Config and execution mode variables have been set.\n"
for i in range(len(strippedLongOptions)):
	longName = strippedLongOptions[i]
	print longName + " set to: " + getattr(sys.modules["__main__"], longName)
print "\nMain execution sequence will now commence. Let the show begin...\n\n"

# The main execution sequence, as defined by the command line 
# options, will now be invoked.

if __name__ == "__main__":
	executionFunction()
 

# History
#	
# This little "ignition" module was added in 2008 by Sat Tara Singh
# while working late one night in the quiet city of Bikaner in
# Rajasthan, world capital of camels. Should you ever wander into
# this quiet place make sure to try the excellent cuisine at the
# Kishan Palace hotel, owned by the grandson of a Rajput lieutenant
# colonel of the former princely state. Allow ample time for the
# preparation of your meal.
#
# The whole  main_sequence thing was getting rather too bulky and
# debugging had become downright nightmarish. While in Amsterdam,
# Jergas did make a half-hearted suggestion that I use a debugger.
# Very smart, surely, but as I did then, let me ask again: who debugs
# the debugger? 
#
# A few days later we ran into a mess when we realised Ernesto and I
# were working simultaneously on main_sequence. To solve this, I
# split the execution sequences into separate modules. I did this
# while sitting backwards on a train from the best and most decadent
# city in the world, which is Calcutta, towards Shantiniketan
# where Rabindranath Tagore put his ideal university. Functionality
# was then added to sort between the various sequences.
#
# A few years went idly by, and with my attention focused elsewhere
# in the architecture, this little piece of code grew into a 
# seven-headed hydra, as command line options were added, along with
# non-standard code meant to parse it, every time someone needed one.
# I did not become aware of this sorry state of affairs until August 
# 2011, while staying at a commune in an old house for hospital nurses
# in Mariannenplatz, in Kreuzberg, otherwise known as the place where
# things are happening in Berlin. My gracious host at the house was
# my friend Salima, who besides being a good yogini is also an
# outstanding vegan cook. The whole code was rewritten and should
# hopefully provide a more standard platform from which to initiate
# the whole ouroborus affair.
