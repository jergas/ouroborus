"""Sequential, declared ecology studies; each simulation owns a fresh process."""
import argparse
import hashlib
import itertools
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time

from .config import SimulationConfig

ROOT = Path(__file__).resolve().parents[1]


def expand_plan(plan):
    allowed = {"seeds", "methods", "allowances", "policies", "prices", "steps",
               "timeout_seconds", "minimum_population", "minimum_generation"}
    if not isinstance(plan, dict) or set(plan) != allowed:
        raise ValueError("Plan must contain exactly: " + ", ".join(sorted(allowed)))
    for key in ("steps", "timeout_seconds", "minimum_population", "minimum_generation"):
        if type(plan[key]) is not int or not 1 <= plan[key] <= 1_000_000:
            raise ValueError(f"{key} must be an integer from 1 to 1,000,000")
    axes = [plan[key] for key in ("seeds", "methods", "allowances", "policies", "prices")]
    count = 1
    for axis in axes:
        if not isinstance(axis, list) or not axis:
            raise ValueError("Study axes must be nonempty lists")
        if any(axis[:index].count(value) for index, value in enumerate(axis)):
            raise ValueError("Duplicate axis values would repeat a condition")
        count *= len(axis)
    if count > 256:
        raise ValueError("At most 256 conditions per study; split larger studies explicitly")
    return [SimulationConfig(preset="forager", steps=plan["steps"], seed=seed,
                             audio="off", execution_method=method,
                             instructions_per_tick=allowance, energy_policy=policy,
                             instructions_per_prana=price, trace_mode="events")
            for seed, method, allowance, policy, price in itertools.product(*axes)]


def source_digest():
    digest = hashlib.sha256()
    for directory in ("worldish", "birdcage"):
        for path in sorted((ROOT / directory).rglob("*")):
            if path.suffix in (".py", ".pyx", ".pxd"):
                digest.update(str(path.relative_to(ROOT)).encode() + b"\0")
                digest.update(path.read_bytes() + b"\0")
    return digest.hexdigest()


def classify(result, config, plan):
    """A finite-horizon screen, never evidence of indefinite viability."""
    for key in ("iterations", "population", "births", "deaths", "max_generation"):
        if type(result[key]) is not int or result[key] < 0:
            raise ValueError(f"Invalid result field: {key}")
    if result["iterations"] != config.steps:
        raise ValueError("Run did not complete the declared horizon")
    if result["births"] - result["deaths"] != result["population"]:
        raise ValueError("Population accounting mismatch")
    if result["observation"]["ledger"]["balance_error"] != 0:
        raise ValueError("Prana accounting mismatch")
    return {"survived": result["population"] > 0,
            "finite_horizon_screen": result["population"] >= plan["minimum_population"]
                                    and result["max_generation"] >= plan["minimum_generation"]}


def command_for(config, output):
    return [sys.executable, "-m", "worldish.start", "--specificity", "forager",
            "--mode", "session", "--display", "debug", "--no-sound", "--fast",
            "--output-dir", str(output), "--seed", str(config.seed), "--steps", str(config.steps),
            "--execution-method", config.execution_method,
            "--instructions-per-tick", str(config.instructions_per_tick),
            "--energy-policy", config.energy_policy,
            "--instructions-per-prana", str(config.instructions_per_prana),
            "--trace-mode", config.trace_mode, "--trace-limit", str(config.trace_limit)]


def run_condition(config, output, plan):
    output.mkdir()
    record = {"config": config.to_dict(), "directory": output.name, "status": "failed"}
    started = time.monotonic()
    process = None
    try:
        with (output / "launcher.log").open("wb") as log:
            process = subprocess.Popen(command_for(config, output), cwd=ROOT,
                                       stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
            record["returncode"] = process.wait(timeout=plan["timeout_seconds"])
        if record["returncode"] != 0:
            record["error"] = "Simulation exited unsuccessfully; see launcher.log"
        else:
            result = json.loads((output / "result.json").read_text())
            record["result"] = result
            record.update(classify(result, config, plan), status="completed")
    except subprocess.TimeoutExpired:
        record.update(status="timeout", error="Wall-clock limit; ecological outcome unknown")
    except (OSError, ValueError, KeyError, TypeError) as error:
        record["error"] = str(error)
    finally:
        if process is not None:
            # Reap owned compiler descendants as well as the worker on timeout/interruption.
            try:
                os.killpg(process.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            process.wait()
        record["elapsed_seconds"] = time.monotonic() - started
    return record


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--plan", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--prepare-only", action="store_true", help="write manifest without running simulations")
    args = parser.parse_args(argv)
    try:
        plan = json.loads(args.plan.read_text())
        configs = expand_plan(plan)
        output = args.output_dir.resolve()
        output.mkdir(parents=True, exist_ok=False)
    except (OSError, ValueError, TypeError) as error:
        parser.error(str(error))
    manifest = {"schema": 1, "plan": plan, "source_sha256": source_digest(),
                "python": sys.version, "executable": sys.executable,
                "conditions": [{"directory": f"run-{index:04d}", "config": config.to_dict()}
                               for index, config in enumerate(configs)],
                "criterion": "completed horizon, zero ledger residual, minimum final population and generation",
                "scope": "finite-horizon screen; failures/timeouts are unknown, not extinctions"}
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    if args.prepare_only:
        print(f"Prepared {len(configs)} conditions in {output}; no simulations launched.")
        return 0
    failures = 0
    with (output / "outcomes.jsonl").open("w", buffering=1) as stream:
        for index, config in enumerate(configs):
            record = run_condition(config, output / f"run-{index:04d}", plan)
            stream.write(json.dumps(record) + "\n")
            failures += record["status"] != "completed"
            print(f"{index + 1}/{len(configs)}: {record['status']}", flush=True)
    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
