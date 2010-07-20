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
# 	IndividualCompile - invokes c compiler every time an agent is created

simWithAgents = False

name = "heru"
seedCode = None
prana = 7
mana = 1


############

# The iteration:

avatars = 3
# Number of agents at start
doomsday = 39
# Number of iterations to run through
seed = ("Random",2)


############

# Display type ('curses' or 'pygame')

displayType = 'curses'

# The Curses colours

backgroundColour = "COLOR_BLACK"
manaColour = "COLOR_GREEN"
agentsColour = "COLOR_RED"


############

# Keeping a log:

logging = False
logFile = "log.txt"


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
