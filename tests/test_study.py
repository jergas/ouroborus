"""Study validation for the separate test session; no ecological matrix here."""
import json
from pathlib import Path

import pytest

from worldish.study import expand_plan, classify, main


def plan():
    return json.loads((Path(__file__).resolve().parents[1] /
                       "experiments/forager-baseline.json").read_text())


def test_matrix_and_prepare_only(tmp_path):
    specification = plan()
    assert len(expand_plan(specification)) == 36
    source = tmp_path / "plan.json"
    source.write_text(json.dumps(specification))
    output = tmp_path / "study"
    assert main(["--plan", str(source), "--output-dir", str(output), "--prepare-only"]) == 0
    assert len(json.loads((output / "manifest.json").read_text())["conditions"]) == 36
    assert not (output / "outcomes.jsonl").exists()
    with pytest.raises(SystemExit):
        main(["--plan", str(source), "--output-dir", str(output), "--prepare-only"])


def test_reject_duplicate_or_invalid_axes():
    for key, value in (("seeds", [7, 7]), ("methods", []), ("prices", [0]),
                       ("allowances", [True]), ("steps", 0), ("policies", ["unknown"])):
        specification = plan()
        specification[key] = value
        with pytest.raises(ValueError):
            expand_plan(specification)


def test_failed_accounting_is_not_extinction():
    specification = plan()
    config = expand_plan(specification)[0]
    result = dict(iterations=80, population=0, births=3, deaths=3, max_generation=0,
                  observation={"ledger": {"balance_error": 0}})
    assert classify(result, config, specification) == {"survived": False, "finite_horizon_screen": False}
    result["iterations"] = 79
    with pytest.raises(ValueError):
        classify(result, config, specification)
    result.update(iterations=80, population=2, births=5, max_generation=2)
    assert classify(result, config, specification)["finite_horizon_screen"]
    result["observation"]["ledger"]["balance_error"] = 1
    with pytest.raises(ValueError):
        classify(result, config, specification)


@pytest.mark.parametrize("interrupted", [False, True])
def test_owned_process_cleanup_on_timeout_or_interrupt(tmp_path, monkeypatch, interrupted):
    import subprocess
    from worldish import study
    calls = []
    class Process:
        pid = 12345
        def wait(self, timeout=None):
            calls.append(("wait", timeout))
            if timeout is not None:
                if interrupted:
                    raise KeyboardInterrupt()
                raise subprocess.TimeoutExpired("simulation", timeout)
            return -9
    monkeypatch.setattr(study.subprocess, "Popen", lambda *args, **kwargs: Process())
    monkeypatch.setattr(study.os, "killpg", lambda pid, sig: calls.append(("kill", pid)))
    specification = plan()
    config = expand_plan(specification)[0]
    if interrupted:
        with pytest.raises(KeyboardInterrupt):
            study.run_condition(config, tmp_path / "run", specification)
    else:
        result = study.run_condition(config, tmp_path / "run", specification)
        assert result["status"] == "timeout" and "survived" not in result
    assert ("kill", 12345) in calls
    assert calls[-1] == ("wait", None)
