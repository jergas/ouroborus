"""Optional deterministic stop thresholds for the sequential session loop."""
from dataclasses import asdict, dataclass


@dataclass(frozen=True)
class RunLimits:
    max_population: int = 0
    max_genotypes: int = 0
    max_lifecycle_visits: int = 0

    def __post_init__(self):
        for key, value in asdict(self).items():
            if type(value) is not int or not 0 <= value <= 1_000_000_000:
                raise ValueError(f"{key} must be an integer from 0 to 1,000,000,000 (0 is unlimited)")

    @classmethod
    def from_specificity(cls, specific):
        return cls(**{key: getattr(specific, key, 0) for key in cls.__dataclass_fields__})


class RunMonitor:
    def __init__(self, organizer, limits):
        self.organizer, self.limits = organizer, limits
        self.enabled = [(key, value) for key, value in asdict(limits).items() if value]
        self.visits = 0
        self.tick_complete = True
        self.reason = "horizon"
        self.reached = []

    def check(self):
        if self.reached:
            return True
        if not self.enabled:
            return False
        values = {"max_population": self.organizer.earth.tellPopulation(),
                  "max_genotypes": len(self.organizer.generator.observation.genomes),
                  "max_lifecycle_visits": self.visits}
        self.reached = [{"name": key, "limit": limit, "observed": values[key]}
                        for key, limit in self.enabled if values[key] >= limit]
        if self.reached:
            self.reason = "resource_limit"
            self.organizer.generator.observation.emit("resource_limit", **self.summary())
            return True
        return False

    def summary(self):
        return {"reason": self.reason, "limits": asdict(self.limits),
                "reached": self.reached, "lifecycle_visits": self.visits,
                "last_tick_complete": self.tick_complete}
