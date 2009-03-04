# This baby is the start button for the whole ouroborus microworld
#
# Coded by Sat Tara Singh Khalsa and Jergas Apwith 
#
# In its present form --- 19th February 2009 --- it carries the following features
#
# 	* take various command-line options to define execution mode
#	* invoke the corresponding function from the main_sequence module
#	* you may of course hack your own tailor-made execution mode
#
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
#


import main_sequence
import sys

def main(tag = "Audiovisual"):
	"""Main executable program. Sort between various variants of the script.

	return -->> 1

	If you want to write your own execution mode go to the main_sequence module
	and write a startFoo function orchestrating execution as you like it, then
	invoke it from the command line by casting >>python start.py Foo  """

	def chooseExecutionMode():
		module = sys.modules["main_sequence"]
		function = getattr(module, "startExecution"+tag, module.startExecutionAudiovisual)
		return function

	chooseExecutionMode()()
	return 1


if __name__ == "__main__":
	if len(sys.argv) > 1: 
		tag = sys.argv.pop()
	else:
		tag = "Audiovisual"
	
	main(tag)




