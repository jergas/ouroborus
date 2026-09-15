"""Report declared study outcomes without running or modifying simulations."""
import argparse
from collections import Counter
from dataclasses import asdict
import copy
import json
from pathlib import Path

from .config import SimulationConfig
from .study import classify, expand_plan
from .placement import resolve_placement
from .run_limits import RunLimits


def comparable_result(result):
    """Compare final ecological state/counters, not backend bookkeeping or timing."""
    result = copy.deepcopy(result)
    for field in ("execution", "genotypes_compiled", "genotypes_interpreted"):
        result.pop(field, None)
    result.get("observation", {}).pop("trace", None)
    return result


def build_report(manifest, outcomes):
    if manifest.get("schema") != 1:
        raise ValueError("Unsupported study manifest schema")
    declared = manifest["conditions"]
    configs = expand_plan(manifest["plan"])
    if len(declared) != len(configs):
        raise ValueError("Manifest conditions do not match its plan")
    expected = {}
    for condition, config in zip(declared, configs):
        directory = condition["directory"]
        if not isinstance(directory, str) or directory in expected:
            raise ValueError("Duplicate or invalid condition directory")
        if SimulationConfig(**condition["config"]) != config:
            raise ValueError("Manifest configuration does not match its plan")
        expected[directory] = config
    records = {}
    for outcome in outcomes:
        directory = outcome["directory"]
        if directory not in expected or directory in records:
            raise ValueError("Unknown or duplicate outcome directory")
        if SimulationConfig(**outcome["config"]) != expected[directory]:
            raise ValueError("Outcome configuration differs from the declared condition")
        if outcome["status"] not in ("completed", "failed", "timeout", "limited"):
            raise ValueError("Unknown outcome status")
        records[directory] = outcome

    rows, groups, pairs = [], {}, {}
    for directory, config in expected.items():
        outcome = records.get(directory)
        row = {"directory": directory, "config": config.to_dict(),
               "status": outcome["status"] if outcome else "missing"}
        if outcome:
            row["error"] = outcome.get("error")
            if "result" in outcome:
                row["result"] = outcome["result"]
        if row["status"] == "completed":
            try:
                result = outcome["result"]
                execution = result["execution"]
                if any(execution.get(key) != value for key, value in asdict(config.execution_options()).items()):
                    raise ValueError("Result execution settings differ from the declared condition")
                if execution.get("genome_language") != "forager-v1":
                    raise ValueError("Result language differs from the declared Forager study")
                placement = result.get("offspring_placement")
                expected_placement = {"requested": config.offspring_placement,
                                      "effective": resolve_placement(config.offspring_placement, "transfer")}
                if placement != expected_placement and (placement is not None or config.offspring_placement != "policy"):
                    raise ValueError("Result placement differs from the declared condition")
                limits = {key: getattr(config, key) for key in RunLimits.__dataclass_fields__}
                recorded_limits = result.get("termination", {}).get("limits")
                if recorded_limits != limits and (recorded_limits is not None or any(limits.values())):
                    raise ValueError("Result stop thresholds differ from the declared condition")
                screen = classify(result, config, manifest["plan"])
                # Recompute classifications, never trust previously cached booleans.
                row.update(screen, result=result)
            except (ValueError, TypeError, KeyError, AttributeError) as error:
                row.update(status="invalid", error=str(error))
        rows.append(row)
        group_config = config.to_dict()
        group_config.pop("seed")
        key = json.dumps(group_config, sort_keys=True)
        group = groups.setdefault(key, {"config": group_config, "declared": 0,
                                       "completed": 0, "unknown": 0, "survived": 0,
                                       "extinct": 0, "screen_passed": 0})
        group["declared"] += 1
        if row["status"] == "completed":
            group["completed"] += 1
            group["survived"] += row["survived"]
            group["extinct"] += not row["survived"]
            group["screen_passed"] += row["finite_horizon_screen"]
        else:
            group["unknown"] += 1
        pair_config = config.to_dict()
        pair_config.pop("execution_method")
        key = json.dumps(pair_config, sort_keys=True)
        pair = pairs.setdefault(key, {"config": pair_config, "methods": {}})
        pair["methods"][config.execution_method] = row

    comparisons = []
    for pair in pairs.values():
        methods = pair["methods"]
        comparison = {"config": pair["config"],
                      "directories": {method: row["directory"] for method, row in methods.items()}}
        if set(methods) != {"compiled", "interpreted"}:
            comparison["status"] = "not_paired_in_plan"
        elif any(row["status"] != "completed" for row in methods.values()):
            comparison["status"] = "unknown"
        else:
            left = comparable_result(methods["compiled"]["result"])
            right = comparable_result(methods["interpreted"]["result"])
            comparison["status"] = "equal" if left == right else "different"
            comparison["differing_fields"] = sorted(key for key in left.keys() | right.keys()
                                                     if left.get(key) != right.get(key))
        comparisons.append(comparison)
    counts = Counter(row["status"] for row in rows)
    return {"schema": 1, "source_sha256": manifest.get("source_sha256"),
            "plan": manifest["plan"], "declared": len(rows), "statuses": dict(counts),
            "unknown": sum(row["status"] != "completed" for row in rows),
            "groups": list(groups.values()), "method_comparisons": comparisons,
            "conditions": rows,
            "scope": "final outcomes/counters only; equality does not establish trajectory or trace equality"}


def read_report(directory):
    manifest = json.loads((directory / "manifest.json").read_text())
    path = directory / "outcomes.jsonl"
    lines = path.read_text().splitlines(keepends=True) if path.exists() else []
    outcomes = []
    partial = False
    for index, line in enumerate(lines):
        try:
            outcomes.append(json.loads(line))
        except json.JSONDecodeError:
            if index == len(lines) - 1 and not line.endswith("\n"):
                partial = True  # A killed writer may leave its last outcome incomplete.
            else:
                raise ValueError(f"Malformed outcome at line {index + 1}")
    report = build_report(manifest, outcomes)
    report["incomplete_last_record"] = partial
    return report


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("study", type=Path)
    args = parser.parse_args(argv)
    try:
        report = read_report(args.study)
    except (OSError, ValueError, KeyError, TypeError, AttributeError) as error:
        parser.error(str(error))
    print(json.dumps(report, indent=2))
    return int(report["unknown"] > 0 or any(pair["status"] == "different"
                                           for pair in report["method_comparisons"]))


if __name__ == "__main__":
    raise SystemExit(main())
