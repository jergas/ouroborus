#!/usr/bin/python

"""This baby is the start button for the whole ouroborus microworld

Coded by Sat Tara Singh Khalsa and Jergas Apwith 

In its present form --- 9th March 2009 --- it carries the following features

 	* take various command-line options to define execution mode
	* invoke the corresponding function from the corresponding module
	* you may of course hack your own tailor-made execution mode

Read some history at EOF"""

import sys
import os
from getopt import *

# The following two constants define the options and longoptions available.
# They must be hardcoded somewhere, as the config scripts will be loaded
# according to the options used. However, the options must be processed
# after the config is loaded, so that its values may be modified accordingly.

options		= ""
longOptions	= ["specificity="]

# Now the options are parsed:

optionList, arguments = gnu_getopt(sys.argv[1:], options, longOptions)
sys.argv = [sys.argv[0]] + arguments

# Now the optionList will be parsed. 
# For now we are only looking for the specificity so a placeholder for the variable must exist.

specificity = "Alpha"

for option in optionList:
	if option[0] == "--specificity": specificity = option[1].capitalize()
	else: specificity = "Alpha"

# NOTE that all other options are being ignored.

try:
	specific = __import__("specific" + specificity)
except (ImportError, NameError, TypeError):
	specific = __import__("specificAlpha")

# Now the specificity has been loaded.


def main(mode = "Audiovisual", submode = "Normal"):
	"""Main executable program. Sort between the variants of the execution sequence.

	return -->> 1

	If you want to write your own execution mode go to the Foo module and write 
	a startExecutionBar function orchestrating execution as you like it, then
	invoke it from the command line by casting >>python start.py Foo Bar """

	def chooseExecutionMode():
		global module
		try:
			module = __import__("sequence_"+mode.lower())
		except ImportError:
			notify()
			module = __import__("sequence_debug")
			notify()
		function = getattr(module, "startExecution"+submode.capitalize(), module.startExecutionNormal)
		return function
		
		def notify():
			print "ImportError:"

	chooseExecutionMode()()
	return 1

def setMode():
	global specific
	submode = "Normal"
	mode = "Audiovisual"
	if len(sys.argv) == 3:
		submode = sys.argv.pop()
		mode = sys.argv.pop()
	elif len(sys.argv) == 2:
		mode = sys.argv.pop()
	elif len(sys.argv) == 1:
		try:
			submode = specific.submode
			mode = specific.mode
		except AttributeError:
			submode = "Normal"
			mode = "Audiovisual"
	while len(sys.argv) > 1:
		del sys.argv[-1]
	return (mode, submode)

if __name__ == "__main__":
	(mode, submode) = setMode()
	main(mode, submode)
	os.system("rm " + module.specific.name + "*")


# History
#	
# This little "ignition" module was added by Sat Tara Singh while working late one
# night in the quiet city of Bikaner in Rajasthan, world capital of camels. Should
# you ever wander into this quiet place make sure to try the excellent cuisine at
# the Kishan Palace hotel, owned by the grandson of a Rajput lieutenant colonel of
# the former princely state. Allow ample time for the preparation of your meal.
# The whole  main_sequence thing was getting rather too bulky and debugging had
# become downright nightmarish. While in Amsterdam, Jergas did make a half-hearted 
# suggestion that I use a debugger. Very smart, surely, but as I did then, let me 
# ask again: who debugs the debugger? 
#
# A few days later we ran into a mess when we realised Ernesto and I were working
# simultaneously on main_sequence. To solve this, I split the execution sequences
# into separate modules. I did this while sitting backwards on a train from the
# best and most decadent city in the world, which is Calcutta, towards Shantiniketan
# where Rabindranath Tagore put his ideal university.
