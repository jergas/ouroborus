"""Study reporting retains missing/failed conditions and compares matched methods."""
from dataclasses import asdict
import copy
import json

import pytest

from test_study import plan
from worldish.config import SimulationConfig
from worldish.study import expand_plan
from worldish.study_report import build_report, read_report


def fixture_data():
    specification = plan()
    specification.update(seeds=[7], allowances=[2], policies=["maintenance"])
    configs = expand_plan(specification)
    conditions = [{"directory": f"run-{index}", "config": config.to_dict()}
                  for index, config in enumerate(configs)]
    manifest = {"schema": 1, "plan": specification, "conditions": conditions}
    outcomes = []
    for condition in conditions:
        outcomes.append({**copy.deepcopy(condition), "status": "completed", "result": {
            "iterations": 80, "population": 5, "births": 8, "deaths": 3,
            "max_generation": 2, "execution": {"genome_language": "forager-v1",
                **asdict(SimulationConfig(**condition["config"]).execution_options())},
            "genotypes_compiled": 1 if condition["config"]["execution_method"] == "compiled" else 0,
            "observation": {"ledger": {"balance_error": 0}, "trace": {"bytes_written": len(outcomes)}}}})
    return manifest, outcomes


def test_equal_methods_ignore_only_backend_bookkeeping():
    manifest, outcomes = fixture_data()
    report = build_report(manifest, outcomes)
    assert report["unknown"] == 0
    assert report["method_comparisons"][0]["status"] == "equal"
    outcomes[1]["result"]["max_generation"] = 3
    pair = build_report(manifest, outcomes)["method_comparisons"][0]
    assert pair["status"] == "different" and pair["differing_fields"] == ["max_generation"]


def test_failures_and_missing_are_unknown_not_extinctions():
    manifest, outcomes = fixture_data()
    outcomes[0]["status"] = "timeout"
    report = build_report(manifest, outcomes[:1])
    assert report["unknown"] == 2
    assert report["statuses"] == {"timeout": 1, "missing": 1}
    assert all(group["extinct"] == 0 for group in report["groups"])
    assert report["method_comparisons"][0]["status"] == "unknown"


def test_recompute_screen_and_reject_wrong_or_duplicate_conditions():
    manifest, outcomes = fixture_data()
    outcomes[0]["finite_horizon_screen"] = False
    assert build_report(manifest, outcomes)["conditions"][0]["finite_horizon_screen"]
    with pytest.raises(ValueError, match="duplicate"):
        build_report(manifest, outcomes + outcomes[:1])
    outcomes[0]["config"]["seed"] = 99
    with pytest.raises(ValueError, match="differs"):
        build_report(manifest, outcomes)


def test_invalid_accounting_is_not_a_completed_result():
    manifest, outcomes = fixture_data()
    outcomes[0]["result"]["observation"]["ledger"]["balance_error"] = 1
    report = build_report(manifest, outcomes)
    assert report["conditions"][0]["status"] == "invalid"
    assert report["unknown"] == 1


def test_partial_tail_and_prepared_only_study(tmp_path):
    manifest, outcomes = fixture_data()
    (tmp_path / "manifest.json").write_text(json.dumps(manifest))
    assert read_report(tmp_path)["unknown"] == 2
    path = tmp_path / "outcomes.jsonl"
    path.write_text(json.dumps(outcomes[0]) + '\n{"directory":')
    report = read_report(tmp_path)
    assert report["incomplete_last_record"] and report["unknown"] == 1
    path.write_text('{broken}\n')
    with pytest.raises(ValueError, match="Malformed"):
        read_report(tmp_path)


def test_placement_axis_and_old_plan_default():
    specification = plan()
    assert {c.offspring_placement for c in expand_plan(specification)} == {"policy"}
    specification["placements"] = ["local", "random"]
    configs = expand_plan(specification)
    assert len(configs) == 72
    assert {c.offspring_placement for c in configs} == {"local", "random"}
    specification["placements"] = ["nearby"]
    with pytest.raises(ValueError):
        expand_plan(specification)


def test_result_must_confirm_requested_execution_settings():
    manifest, outcomes = fixture_data()
    outcomes[0]["result"]["execution"]["energy_policy"] = "compute"
    assert build_report(manifest, outcomes)["conditions"][0]["status"] == "invalid"
