"""Forager v1 primitives, interpreted dispatch and compiled dispatch emission.

Genomes are data. No genome-supplied text is evaluated as Python. Both dispatch
methods invoke the same finite-cost primitives, with Moore bodies (nine sensed
positions), no stacks, no arithmetic operands and at most 1024 genetic words.
"""
from .execution import advance

MAX_WORDS = 1024


def parse(code):
    if not isinstance(code, str) or len(code) > MAX_WORDS * 4:
        raise ValueError("Forager genomes must be strings of at most 4096 characters")
    compact = code.replace(" ", "")
    if len(compact) % 2 or len(compact) > MAX_WORDS * 2:
        raise ValueError("Forager genomes require at most 1024 two-character words")
    return tuple(compact[i:i + 2] for i in range(0, len(compact), 2))


def birth(earth, code, prana, mana, address):
    from birdcage.agent import Agent_2D
    from birdcage.neighborhood import MooreNeighborhood
    grid = earth.returnTopology()
    return Agent_2D(code, MooreNeighborhood(grid), MooreNeighborhood(grid), prana, mana, address)


def seek(creature, state, options, threshold, metrics):
    grid = creature.returnTopology()
    for facing, address in enumerate(creature.tellDirections()):
        if grid.get(address) == 1:
            creature.changeFacing(facing)
            break
    else:
        creature.randomFacing()
    creature.advance()


def eat(creature, state, options, threshold, metrics):
    if creature.eatMana():
        metrics["food_eaten"] += 1


def maintain(creature, state, options, threshold, metrics):
    if options.energy_policy == "maintenance":
        before = creature.tellPrana()
        creature.losePrana(1)
        metrics["maintenance_prana"] += before - creature.tellPrana()


def reproduce(creature, state, options, threshold, metrics):
    if creature.tellPrana() >= threshold:
        state["prayer"] = "GrantChild"


def die(creature, state, options, threshold, metrics):
    if creature.tellPrana() <= 0:
        state["prayer"] = "KillMe"


def finish(creature, state, options, threshold, metrics):
    return True


def noop(creature, state, options, threshold, metrics):
    pass


OPERATIONS = {"Sf": seek, "Ea": eat, "Mt": maintain,
              "Rp": reproduce, "Di": die, "Rt": finish}


class InterpretedProgram:
    birth = staticmethod(birth)

    def __init__(self, code):
        self.words = parse(code)
        self.operations = tuple(OPERATIONS.get(word, noop) for word in self.words)

    def step(self, creature, state, options, threshold, metrics):
        return self.operations[state["ip"]](creature, state, options, threshold, metrics)

    def advance(self, creature, state, options, threshold, metrics):
        return advance(self.step, len(self.words), creature, state, options, threshold, metrics)


def compiled_source(code):
    """Specialize opcode dispatch into a native module; primitives stay shared.

    Only trusted function names and bounded integer indices enter the emitted
    code, never arbitrary genome text. This first compiler specializes dispatch,
    not the shared scheduler or primitive implementations.
    """
    words = parse(code)
    lines = ["from worldish import forager_vm as vm",
             "from worldish.execution import advance as run_slice",
             "birth = vm.birth", "",
             "def step(creature, state, options, threshold, metrics):"]
    for index, word in enumerate(words):
        function = OPERATIONS.get(word, noop).__name__
        lines += [f"    if state['ip'] == {index}:",
                  f"        return vm.{function}(creature, state, options, threshold, metrics)"]
    lines += ["    return True", "",
              "def advance(creature, state, options, threshold, metrics):",
              f"    return run_slice(step, {len(words)}, creature, state, options, threshold, metrics)"]
    return "\n".join(lines) + "\n"
