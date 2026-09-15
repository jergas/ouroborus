"""Stop thresholds preserve committed lifecycle operations and censored outcomes."""
from types import SimpleNamespace

import pytest

from worldish.run_limits import RunLimits, RunMonitor
from worldish.config import SimulationConfig


def monitor(limits):
    events = []
    observation = SimpleNamespace(genomes={"seed": {}}, emit=lambda *args, **kwargs: events.append((args, kwargs)))
    organizer = SimpleNamespace(earth=SimpleNamespace(tellPopulation=lambda: 3),
                                generator=SimpleNamespace(observation=observation))
    return RunMonitor(organizer, limits), events


def test_disabled_and_reached_thresholds_record_once():
    current, events = monitor(RunLimits())
    assert not current.check() and events == []
    current, events = monitor(RunLimits(max_population=3, max_genotypes=1))
    assert current.check() and current.check()
    assert len(events) == 1
    assert len(current.summary()["reached"]) == 2
    assert current.summary()["reason"] == "resource_limit"


def test_visit_threshold_and_partial_tick():
    current, events = monitor(RunLimits(max_lifecycle_visits=2))
    current.visits = 1
    assert not current.check()
    current.visits = 2
    current.tick_complete = False
    assert current.check()
    assert not events[0][1]["last_tick_complete"]


def test_limit_validation_and_settings_roundtrip():
    for value in (-1, True, 1.5, 1_000_000_001):
        with pytest.raises(ValueError):
            SimulationConfig(max_population=value)
    config = SimulationConfig(max_population=10, max_genotypes=4, max_lifecycle_visits=100)
    assert SimulationConfig(**config.to_dict()) == config


@pytest.mark.parametrize("method", ["compiled", "interpreted"])
def test_real_session_stops_after_committed_birth(tmp_path, method):
    from test_worldish import run_example
    result, _ = run_example(tmp_path, "--specificity", "forager", "--mode", "session",
                            "--display", "debug", "--no-sound", "--execution-method", method,
                            "--max-population", "4")
    assert result["population"] == 4
    assert result["prana_transferred"] == 12
    assert result["observation"]["ledger"]["balance_error"] == 0
    assert result["termination"]["reason"] == "resource_limit"
    assert result["termination"]["reached"][0]["observed"] == 4


def test_partial_tick_is_not_horizon_success(tmp_path):
    from test_worldish import run_example
    from worldish.study import classify
    result, _ = run_example(tmp_path, "--specificity", "forager", "--mode", "session",
                            "--display", "debug", "--no-sound", "--execution-method", "interpreted",
                            "--max-lifecycle-visits", "1")
    assert result["termination"]["lifecycle_visits"] == 1
    assert not result["termination"]["last_tick_complete"]
    assert result["observation"]["ledger"]["balance_error"] == 0
    with pytest.raises(ValueError):
        classify(result, SimulationConfig(preset="forager", steps=result["iterations"]),
                 {"minimum_population": 1, "minimum_generation": 1})


def test_limited_outcomes_remain_unknown_in_reports():
    from test_study_report import fixture_data
    from worldish.study_report import build_report
    from worldish.study import expand_plan
    manifest, outcomes = fixture_data()
    manifest["plan"]["limits"] = {"max_population": 4}
    configs = expand_plan(manifest["plan"])
    for condition, outcome, config in zip(manifest["conditions"], outcomes, configs):
        condition["config"] = outcome["config"] = config.to_dict()
        outcome["status"] = "limited"
        outcome["result"]["termination"] = {"reason": "resource_limit"}
    report = build_report(manifest, outcomes)
    assert report["unknown"] == 2
    assert report["statuses"] == {"limited": 2}
    assert report["conditions"][0]["result"]["termination"]["reason"] == "resource_limit"
    assert report["method_comparisons"][0]["status"] == "unknown"
