# If simWSound is 1, then GOD and bookentry carry out sound-related
# activities.
simWSound		= 0

# 1, while the simulation is running.
mainIterCycle	= 1

# A dictionary used to control the background sound. It contains channel
# numbers as keys and a 3-tuple consisting of a cell address, a cell
# state, and a counter as values.
cellControlDict	= []

# A list with the data needed to update the background sound.
backgroundUpdateList = []
