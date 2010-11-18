"""These are some specific parameters for running ouroborus.
Delta was meant for debugging"""

from birdcage.specific import *


############

# The automaton:

size = (80,20)
topology = ("ToroidTopology", 0)
neighborhood = ("MooreNeighborhood", None ,"birdcage.neighborhood")
import operator
rule = ("ReductionRule", (operator.xor, 0), "birdcage.rule")
automaton = ("SynchronousAutomaton_2D", )


############

# The agents:

# Void 			- deactivates agents
# 
# IndividualCompile	- invokes c compiler every time an agent is
#					created
# MassCompile		- invokes c compiler only when a genome differs
#					from its predecesors
compiling = "MassCompile"

name = "heru"
seedCode = "Yi Yc Ys Cb Cd Cr Ld Lp Lm Ll Le Iy Ir Ip Ix Ik Lr Md Mf Ma Mr Rd Rl"
prana = 22
mana = 1

simWithAgents	= True


############

# The iteration:

avatars = 3
# Number of agents at start
doomsday = 1000
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
agentThreads	= 'custom'

# Number of agent-managing threads. This option only works if
# agentThreads	= 'custom'
agentThreadsNumber = 4

# This option is the delay time (in seconds)between one annum and the
# next one. The option only works if the attribute threadedAgents is set
# to true (and this is congruent with the chosen sequence).
annumDelay	= .11

# This option is the delay time (in seconds)between one iteration of a
# single agent and the next one. The option only works if the attribute
# threadedAgents is set to true (and this is congruent with the chosen
# sequence).
agentsDelay	= .13


############

# The display

# Display type ('curses' or 'pygame')
displayType = 'curses'

# The criterion function
# (a function which evaluates a cell's state for display,
#  the library where its located must also be specified below)
criterion = 'identity'

# The Curses colours
backgroundColour = "COLOR_BLACK"
manaColour = "COLOR_YELLOW"
agentsColour = "COLOR_GREEN"

# Number of simulation loops per audiovisual loop.
simulationToAudiovisual = 1


############

# The other options:

# Logging
logging = True
logFile = "log.txt"

# Libraries
# (refer to 'The display' section of this file is to understand
#  what the criterion is)
# visual is renamed v in GOD.py
criterionLocation = "v" 


############

# The sound preferences:

# Partials per background voice (minimum 1 maximum 13)
backgroundPartials = 13

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
#csound -odac:alsa_pcm:playback_ -+rtaudio=jack -b1024 -B2048 -d -m0 temp.orc temp.sco
#</CsOptions>"""


############

# The spanish inquisition

# Nobody expects the spanish inquisition!
