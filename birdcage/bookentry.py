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


	def callModule(self):
		self.module = __import__(self.name)


	def instantiateAgent(self, automaton):
		code = self.fatum["code"]
		prana = self.fatum["prana"]
		mana = self.fatum["mana"]		
		address = self.fatum["address"]
		self.agent = self.module.birth(automaton, code, prana, mana, address)


	def agentLive(self):
		"""Call on the agent to perform its live method
		return -->> 1"""

		self.fatum["prayer"] = self.module.live(self.agent) #this is deep magic!
		self.fatum["prana"] = self.agent.tellPrana() # simply update some data now
		self.fatum["address"] = self.agent.tellAddress()
		return 1
