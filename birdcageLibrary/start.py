#!/usr/bin/python
#
# This baby is the start button for the whole ouroborus microworld
#
# Coded by Sat Tara Singh Khalsa and Jergas Apwith 
#
# In its present form --- 9th March 2009 --- it carries the following features
#
# 	* take various command-line options to define execution mode
#	* invoke the corresponding function from the corresponding module
#	* you may of course hack your own tailor-made execution mode
#
# Read some history at EOF

import sys
import os

def main(mode = "Audiovisual", submode = "Normal"):
	"""Main executable program. Sort between the variants of the execution sequence.

	return -->> 1

	If you want to write your own execution mode go to the Foo module and write 
	a startExecutionBar function orchestrating execution as you like it, then
	invoke it from the command line by casting >>python start.py Foo Bar """

	def chooseExecutionMode():
		try:
			module = __import__("sequence_"+mode.lower())
		except ImportError:
			module = __import__("sequence_arduino")
		function = getattr(module, "startExecution"+submode.capitalize(), module.startExecutionNormal)
		return function

	chooseExecutionMode()()
	return 1


if __name__ == "__main__":
	(mode, submode) = ("Audiovisual", "Normal")
	if len(sys.argv) == 3:
		submode = sys.argv.pop()
		mode = sys.argv.pop()
	elif len(sys.argv) == 2:
		mode = sys.argv.pop()
	while len(sys.argv) > 1:
		del sys.argv[-1]
	main(mode, submode)
	os.system("rm khonsu*")


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

