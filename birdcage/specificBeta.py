"""These are some specific parameters for running ouroborus.
Specificity Beta is meant to provide appropriate defaults for Diego's Demo."""

############

# The automaton:

size = (80,20)
topology = ("ToroidTopology", 0)
neighborhood = ("MooreNeighborhood", )
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

avatars = 2
doomsday = 100
seed = ("Random",1)

############

# Sound preferences:

# One of the csOptions should be commented. If you don't know
# what you are doing, use the first version (uses the ALSA
# sound module). The second version uses JACK.
csOptions	= """
<CsoundSynthesizer>
<CsOptions>
csound -odac -+rtaudio=alsa -b1024 -B2048 -d -m0 temp.orc temp.sco
</CsOptions>"""

#csOptions	= """
#<CsoundSynthesizer
#<CsOptions>
#csound -odac:alsa_pcm:playback_ -+rtaudio=jack -b1024 -B2048 -d -m0 temp.orc #temp.sco
#</CsOptions>"""
