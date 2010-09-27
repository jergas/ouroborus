"""These are some specific parameters for running ouroborus.
Alpha is the default specificity."""

############

# The automaton:

size = (80,20)
topology = ("ToroidTopology", 0)
neighborhood = ("MooreNeighborhood", None ,"neighborhood")
import operator
rule = ("ReductionRule", (operator.xor, 0), "rule")
automaton = ("SynchronousAutomaton_2D", )

# This option is the delay time (in seconds)between one annum and the
# next one. The option only works in simulations where the automaton
#runs in a thread that is autonomus from the agents.
annumDuration	= .1


############

# The agents:

# Void - deactivates agents; 
# IndividualCompile		- invokes c compiler every time an agent is
#						created
#	MassCompile			- invokes c compiler only when a genome differs
#						from its predecesors
compiling = "IndividualCompile"

name 		= "heru"
seedCode	= "Yi Yc Ys Cb Cd Cr Ld Lp Le Iy Ir Ip Ix Ik Lr Rd Rl"
prana		= 7
mana		= 1

simWithAgents = True


############

# The iteration:

avatars = 3
doomsday = 70
seed = ("Random",2)


############

# The Display

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
logging = False
logFile = "log.txt"

# Libraries
criterionLocation = "v" # visual is renamed v in GOD.py


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
#csound -odac:alsa_pcm:playback_ -+rtaudio=jack -b1024 -B2048 -d -m0 temp.orc #temp.sco
#</CsOptions>"""
