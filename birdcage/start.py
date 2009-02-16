import main_sequence
import sys

def main(tag = "VisualSound"):
	"""Main executable program. Sort between various variants of the script.

	return -->> 1"""

	def chooseExecutionMode():
		module = sys.modules["main_sequence"]
		function = getattr(module, "startExecution"+tag, module.startExecutionVisualSound)
		return function

	chooseExecutionMode()()

if len(sys.argv) > 1: 
	tag = sys.argv.pop()
else:
	tag = "VisualSound"
	
main(tag)




