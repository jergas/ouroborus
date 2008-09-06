import GOD
print "imported GOD!"

mary = GOD.Generator("kristos")
print "instantiated Generator"


# the following lines contain all the data to build a complete automaton
size = (90,40)
topologyData = ("GridTopology", 0)
neighborData = ("VonNeumannNeighborhood", )
import operator
ruleData = ("ReductionRule", (operator.xor, 0))
automatonData = ("SynchronousAutomaton_2D", )

# invoke God.Generator's automaton creation method with the data given above
terra = mary.generateAutomaton(size, topologyData, neighborData, ruleData, automatonData)
print "an earth has been created as", terra

biblos = []
print "the book of life is", biblos

magdalen = GOD.Organizer(terra, biblos)
print "instantiated Organizer"

avatars = 3

for i in range(avatars):
	mary.generateGenotype(["a","i"], biblos)

print avatars, "files have been written"

print "magdalen's book of life is", magdalen.book


