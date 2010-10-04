"""These are some specific parameters for running ouroborus.
Delta was meant for debugging"""

############

# The automaton:

size = (40,20)
topology = ("ToroidTopology", 0)
neighborhood = ("VonNeumannNeighborhood", None ,"neighborhood")
import operator
rule = ("ReductionRule", (operator.xor, 0), "rule")
automaton = ("SynchronousAutomaton_2D", )


############

# The agents:

compiling = "Void"
# These are the options:
# 	Void - deactivates agents;
# IndividualCompile		- invokes c compiler every time an agent is
#						created
#	MassCompile			- invokes c compiler only when a genome differs
#						from its predecesors

simWithAgents = False

name = "heru"
seedCode = None
prana = 7
mana = 1


############

# The iteration:

avatars = 3
# Number of agents at start
doomsday = 300
# Number of iterations to run through
seed = ("Random",2)


############

# The delays

# Set this option to true if you are running a simulation with one
# thread per agent.
threadedAgents	= True

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
