# This file was born from the need to have a configuration file be the first
# thing that gets loaded, so that the compilation and installation of birdcage
# could proceed automagically with the chosen compiler.

# Choose the compiler to be used. Possible options are "Cython" and
# "Pyrex". WARNING!!!: At present the simulation may not run with Cython!
compiler = "Pyrex"

# This is the default configuration file. The actual name of the file is
# specificAlpha.py and it should live in the same directory as the main
# sequence, such as worldish for sequence_threaded or circadian for 
# sequence_arduino
specificity = "Alpha"


