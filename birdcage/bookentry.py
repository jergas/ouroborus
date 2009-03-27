import string

class BookEntry:
	"""An entry into the book of life, comprising of:

	name  ---> a string,
	module ---> a module object with the compiled genome,
	agent  ---> a birdcage agent object, and
	fatum  ---> a dictionary with data written by the agent"""

	def __init__(self, name):
		self.name = name
		self.module = None
		self.agent = None
		self.fatum = {"prayer":"BeBirthed"}

	def __str__(self):
		display = ["Name of entry in BOL: "+self.name, "Entry's fatum:"]
		display.extend(["\t"+str(key)+":\t"+str(value) for key,value in self.fatum.items()])
		return string.join(display, "\n")

		
