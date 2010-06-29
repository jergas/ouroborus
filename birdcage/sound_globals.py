# If simWSound is 1, then GOD and bookentry carry out sound-related
# activities.
simWSound		= 0

# 1, while the simulation is running.
mainIterCycle	= 1

# A dictionary used to control the background sound. It contains channel
# numbers as keys and a 2-tuple consisting of a cell address and a cell
# state.
cellControlDict	= []

# A list with the data needed to update the background sound.
backgroundUpdateList = []

# The normalized population of the automaton as a one-element list.
populNorm	= [.001875]
populMin	= [.001875] 
populMax	= [.0025] 
