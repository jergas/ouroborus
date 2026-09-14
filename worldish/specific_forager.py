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
