"""Validated, serializable launch settings shared by desktop and worker."""
from dataclasses import asdict, dataclass
import math
from .execution import ExecutionOptions


@dataclass(frozen=True)
class SimulationConfig:
    preset: str = "alpha"
    steps: int = 4000
    seed: int = 42
    interval: float = 0.1
    audio: str = "speakers"
    volume: float = 0.5
    execution_method: str = "compiled"
    instructions_per_tick: int = 6
    energy_policy: str = "maintenance"
    instructions_per_prana: int = 6

    trace_mode: str = "off"
    trace_limit: int = 100_000
    offspring_placement: str = "policy"

    def __post_init__(self):
        from .placement import resolve_placement
        resolve_placement(self.offspring_placement, "transfer" if self.preset == "forager" else "preset")
        from .observation import validate_trace
        validate_trace(self.trace_mode, self.trace_limit)
        if self.preset not in ("alpha", "beta", "delta", "epsilon", "forager"):
            raise ValueError("Unknown simulation specificity")
        self.execution_options().validate_language(
            "forager-v1" if self.preset == "forager" else "source", self.preset == "epsilon")
        if type(self.steps) is not int or not 1 <= self.steps <= 1000000:
            raise ValueError("Iterations must be between 1 and 1,000,000")
        if type(self.seed) is not int or not 0 <= self.seed <= 2147483647:
            raise ValueError("Seed must be between 0 and 2,147,483,647")
        if not isinstance(self.interval, (int, float)) or not math.isfinite(self.interval) or not 0.01 <= self.interval <= 5:
            raise ValueError("Tick interval must be between 0.01 and 5 seconds")
        if self.audio not in ("off", "speakers", "silent"):
            raise ValueError("Unknown audio output")
        if not isinstance(self.volume, (int, float)) or not math.isfinite(self.volume) or not 0 <= self.volume <= 1:
            raise ValueError("Volume must be between 0 and 1")

    def execution_options(self):
        return ExecutionOptions(self.execution_method, self.instructions_per_tick,
                                self.energy_policy, self.instructions_per_prana)

    def to_dict(self):
        return asdict(self)
