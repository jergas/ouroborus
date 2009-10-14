### These are some specific parameters for running ouroborus"""

############

# The automaton:

size = (80,20)
topology = ("ToroidTopology", 0)
neighborhood = ("VonNeumannNeighborhood", )
import operator
rule = ("ReductionRule", (operator.xor, 0))
automaton = ("SynchronousAutomaton_2D", )

############

# The agents:

seedCode = "Yi Yc Ys Cb Cd Cr Ld Lp Le Iy Ir Ip Ix Ik Lr Rd Rl"
prana = 7
mana = 1

############

# The iteration:

avatars = 5
doomsday = 100
