"""Source vocabulary for the authored forager; operations remain explicit.

The ordered words are the authoritative program. A future interpreter can
implement this same vocabulary without maintaining a second foraging policy.
"""
SEED_CODE = "Sf Ea Mt Rp Di Rt"


def vocabulary(reproduction_threshold=30):
    return {
        "boilerplate": '''from birdcage.agent import Agent_2D
from birdcage.neighborhood import MooreNeighborhood

def birth(earth, code, prana, mana, address):
    grid = earth.returnTopology()
    return Agent_2D(code, MooreNeighborhood(grid), MooreNeighborhood(grid), prana, mana, address)

def live(creature):
    prayer = "Live"
''',
        # Stay on food; otherwise take the first food-bearing neighbor.
        # Explore randomly only when the complete sensory neighborhood is empty.
        "Sf": '''    grid = creature.returnTopology()
    for facing, address in enumerate(creature.tellDirections()):
        if grid.get(address) == 1:
            creature.changeFacing(facing)
            break
    else:
        creature.randomFacing()
    creature.advance()''',
        "Ea": "    creature.eatMana()",
        # Explicit supported maintenance policy, pending compute-cost experiments.
        "Mt": "    creature.losePrana(1)",
        "Rp": f'''    if creature.tellPrana() >= {reproduction_threshold}:
        prayer = "GrantChild"''',
        "Di": '''    if creature.tellPrana() <= 0:
        prayer = "KillMe"''',
        "Rt": "    return prayer",
    }
