"""Execution choices and a shared resource scheduler for the forager VM."""
from dataclasses import dataclass


@dataclass(frozen=True)
class ExecutionOptions:
    execution_method: str = "compiled"
    instructions_per_tick: int = 6
    energy_policy: str = "maintenance"
    instructions_per_prana: int = 6

    def __post_init__(self):
        if self.execution_method not in ("compiled", "interpreted"):
            raise ValueError("Unknown execution method")
        if self.energy_policy not in ("maintenance", "compute"):
            raise ValueError("Unknown energy policy")
        for field in ("instructions_per_tick", "instructions_per_prana"):
            value = getattr(self, field)
            if type(value) is not int or not 1 <= value <= 4096:
                raise ValueError(f"{field} must be an integer from 1 to 4096")

    @classmethod
    def from_specificity(cls, specific):
        return cls(**{key: getattr(specific, key, field.default)
                      for key, field in cls.__dataclass_fields__.items()})

    def validate_language(self, language, no_agents=False):
        if language not in ("source", "forager-v1"):
            raise ValueError("Unknown genome language")
        if no_agents:
            return
        if language == "source":
            if self.execution_method != "compiled":
                raise ValueError("The source genome language supports compiled execution only")
            if (self.energy_policy != "maintenance" or self.instructions_per_tick != 6
                    or self.instructions_per_prana != 6):
                raise ValueError("Instruction budgets and compute charging require forager-v1")


def new_state():
    return {"ip": 0, "prayer": "Live", "credit": 0}


def new_metrics():
    return {"instructions": 0, "compute_prana": 0, "maintenance_prana": 0,
            "food_eaten": 0, "budget_yields": 0, "program_completions": 0}


def advance(step, length, creature, state, options, threshold, metrics):
    """Run a bounded slice; compiled/interpreted dispatch share this contract.

    Each opcode, including no-ops and return, counts once. Completion restarts
    next live visit. Budget exhaustion preserves state; lifecycle requests are
    published only on completion. Compute batches are prepaid, never inherited.
    """
    if not length:
        metrics["program_completions"] += 1
        return "Live"  # Empty programs idle; no implicit maintenance is imposed.
    for _ in range(options.instructions_per_tick):
        if options.energy_policy == "compute":
            if creature.tellPrana() <= 0:
                state.update(ip=0, prayer="Live")
                return "KillMe"
            if not state["credit"]:
                creature.losePrana(1)
                metrics["compute_prana"] += 1
                state["credit"] = options.instructions_per_prana
            state["credit"] -= 1
        complete = step(creature, state, options, threshold, metrics)
        metrics["instructions"] += 1
        state["ip"] += 1
        if options.energy_policy == "compute" and creature.tellPrana() <= 0:
            state.update(ip=0, prayer="Live")
            return "KillMe"
        if complete or state["ip"] >= length:
            prayer = state["prayer"]
            state.update(ip=0, prayer="Live")
            metrics["program_completions"] += 1
            return prayer
    metrics["budget_yields"] += 1
    return "Live"
