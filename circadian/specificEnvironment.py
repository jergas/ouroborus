"""These are some specific parameters for running ouroborus.
Alpha is the default specificity."""

############

# The automaton:

size = (70,35)
topology = ("ToroidTopology", 0)
neighborhood = ("MooreNeighborhoodPlus", None ,"lib_environment")
import operator
rule = ("EnvironmentRule", (operator.xor, 0),"lib_environment")
automaton = ("SynchronousAutomaton_2D", )


############

# The starter:

mode = "arduino"
submode = "Normal"


############

# The agents:

# Void - deactivates agents; 
# IndividualCompile - invokes c compiler every time an agent is created
compiling = "Void"

name 	= "heru"
seedCode	= "Yi Yc Ys Cb Cd Cr Ld Lp Le Iy Ir Ip Ix Ik Lr Rd Rl"
prana	= 7
mana		= 1

simWithAgents = False


############

# The iteration:

avatars = 0
doomsday = 1000
seed = ("Random",1)


############

# The display:

# Display type ('curses' or 'pygame')
displayType = 'pygame'

# The criterion function
# (a function which evaluates a cell's state for display,
#  the library where its located must also be specified below)
criterion = 'binarise'

# Curses colours

backgroundColour = "COLOR_BLACK"
manaColour = "COLOR_YELLOW"
agentsColour = "COLOR_GREEN"


############

# The other options:

# Logging
logging = False
logFile = "log.txt"

# Libraries
criterionLocation = "rule"


############

# The sound preferences:

# Partials per background voice (minimum 1 maximum 13)
backgroundPartials = 30

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
