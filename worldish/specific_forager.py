"""Authored forager on an evolving XOR CA; on cells are its food."""
from .specific_alpha import *
from .forager import SEED_CODE, vocabulary

name = "forager"
seedCode = SEED_CODE
prana = 24
avatars = 3
seed = ("Random", 100)
doomsday = 200
compiling = "MassCompile"
reproduction_policy = "transfer"
offspring_prana = 12
reproduction_threshold = 30
genome_table = vocabulary(reproduction_threshold)

# Both execution methods support this finite opcode language. The source-table
# option above remains usable by selecting genome_language = "source".
genome_language = "forager-v1"
execution_method = "compiled"
instructions_per_tick = 6
energy_policy = "maintenance"
instructions_per_prana = 6
