"""Validated, serializable launch settings shared by desktop and worker."""
from dataclasses import asdict, dataclass
import math


@dataclass(frozen=True)
class SimulationConfig:
    preset: str = "alpha"
    steps: int = 4000
    seed: int = 42
    interval: float = 0.1
    audio: str = "speakers"
    volume: float = 0.5

    def __post_init__(self):
        if self.preset not in ("alpha", "beta", "delta", "epsilon"):
            raise ValueError("Unknown simulation preset")
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

    def to_dict(self):
        return asdict(self)
