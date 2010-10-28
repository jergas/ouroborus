"""These are some specific parameters for running ouroborus.
Delta was meant for debugging"""

from birdcage.specific import *


############

# The automaton:

size = (80,40)
topology = ("ToroidTopology", 0)
neighborhood = ("VonNeumannNeighborhood", None ,"birdcage.neighborhood")
import operator
rule = ("ReductionRule", (operator.xor, 0), "birdcage.rule")
automaton = ("SynchronousAutomaton_2D", )


############

# The agents:

# These are the options:
# 	Void - deactivates agents; 
# 	IndividualCompile	- invokes c compiler every time an agent is
#						created
#	MassCompile			- invokes c compiler only when a genome differs
#						from its predecesors
compiling = "MassCompile"

name = "heru"
seedCode = "Yi Yc Ys Cb Cd Cr Ld Lp La Lm Ll Le Iy Ir Ip Ix Ik Lr Rd Rl Md Mp"
prana = 22
mana = 1


############

# The iteration:

avatars = 3
# Number of agents at start
doomsday = 4000
# Number of iterations to run through
seed = ("Random",1)


############

# The delays

# Set this option to true if you are running a simulation with one
# thread per agent.
# 'one'			- All the agents run in a single thread
# 'custom'		- Specify a fixed number of threads to manage the
			# agents
# 'onePerAgent'	- Each agent runs in a single thread
agentThreads	= 'one'

# Number of agent-managing threads. This option only works if
# agentThreads	= 'custom'
agentThreadsNumber = 5

# This option is the delay time (in seconds)between one annum and the
# next one. The option only works if the attribute threadeAgents is set
# to true (and this is congruent with the chosen sequence).
annumDelay	= .1

# This option is the delay time (in seconds)between one iteration of a
# single agent and the next one. The option only works if the attribute
# threadeAgents is set to true (and this is congruent with the chosen
# sequence).
agentsDelay	= .5


############

# Display type ('curses' or 'pygame')

displayType = 'curses'

# The criterion function
# (a function which evaluates a cell's state for display,
#  the library where its located must also be specified below)
criterion = 'identity'

# The Curses colours

backgroundColour = "COLOR_BLACK"
manaColour = "COLOR_GREEN"
agentsColour = "COLOR_RED"

simWithAgents = True


# Number of simulation loops per audiovisual loop.
simulationToAudiovisual = 1


############

# The other options:

# Logging
logging = False
logFile = "log.txt"

# Libraries
criterionLocation = "v" # visual is renamed v in GOD.py


############

# Sound preferences:

# Partials per background voice (minimum 1 maximum 13)
backgroundPartials = 7

# One of the csOptions should be commented. If you don't know
# what you are doing, use the first version (uses the ALSA
# sound module). The second version uses JACK.
csOptions	= """
<CsoundSynthesizer>
<CsOptions>
csound -odac -+rtaudio=alsa -b1024 -B2048 -d -m0 temp.orc temp.sco
</CsOptions>"""

#csOptions	= """
#<CsoundSynthesizer>
#<CsOptions>
#csound -odac:alsa_pcm:playback_ -+rtaudio=jack -b1024 -B2048 -d -m0 temp.orc #temp.sco
#</CsOptions>"""
