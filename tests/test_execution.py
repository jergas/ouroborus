"""Validation for the shared forager semantics and real native dispatch.

Written for the separate validation session; do not infer execution from the
presence of this file. The native fixture builds once for all comparison cases.
"""
import importlib.util
import random
import subprocess
import sys
from pathlib import Path

import pytest

from worldish.config import SimulationConfig
from worldish.execution import ExecutionOptions, new_state, new_metrics
from worldish.forager import SEED_CODE
from worldish.forager_vm import InterpretedProgram, compiled_source
from test_forager import make_body


@pytest.fixture(scope="module")
def native_program(tmp_path_factory):
    root = Path(__file__).resolve().parents[1]
    output = tmp_path_factory.mktemp("native-forager-vm")
    source = output / "forager_vm_test.pyx"
    source.write_text(compiled_source(SEED_CODE))
    build = subprocess.run([sys.executable, str(root / "worldish/_compile.py"),
                            "forager_vm_test", str(source)], cwd=output,
                           capture_output=True, text=True, timeout=90)
    assert build.returncode == 0, build.stdout + build.stderr
    module_path = next(output.glob("forager_vm_test*.so"))
    spec = importlib.util.spec_from_file_location("forager_vm_test", module_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def trace(program, options):
    random.seed(42)
    creature = make_body(24)
    grid = creature.returnTopology()
    for x in range(5):
        for y in range(5):
            grid.set((x, y), 1)
    state, metrics, records = new_state(), new_metrics(), []
    for _ in range(30):
        prayer = program.advance(creature, state, options, 30, metrics)
        records.append((prayer, creature.tellAddress(), creature.tellPrana(),
                        dict(state), dict(metrics), random.getstate(),
                        [grid.get((x, y)) for x in range(5) for y in range(5)]))
    return records


@pytest.mark.parametrize("budget", [1, 2, 6, 12])
@pytest.mark.parametrize("policy", ["maintenance", "compute"])
def test_native_and_interpreted_traces_agree(native_program, budget, policy):
    options = ExecutionOptions(instructions_per_tick=budget, energy_policy=policy)
    assert trace(native_program, options) == trace(InterpretedProgram(SEED_CODE), options)


def test_budget_yield_preserves_pending_request():
    program = InterpretedProgram("Rp Rt")
    body, state, metrics = make_body(30), new_state(), new_metrics()
    options = ExecutionOptions(instructions_per_tick=1)
    assert program.advance(body, state, options, 30, metrics) == "Live"
    assert state["ip"] == 1 and state["prayer"] == "GrantChild"
    assert program.advance(body, state, options, 30, metrics) == "GrantChild"
    assert state["ip"] == 0 and state["prayer"] == "Live"


def test_unknown_words_are_bounded_and_charged():
    program = InterpretedProgram("??" * 100)
    body, state, metrics = make_body(30), new_state(), new_metrics()
    options = ExecutionOptions(instructions_per_tick=7, energy_policy="compute")
    assert program.advance(body, state, options, 30, metrics) == "Live"
    assert metrics["instructions"] == state["ip"] == 7
    assert metrics["compute_prana"] == 2
    assert body.tellPrana() == 28


def test_compute_replaces_maintenance_and_credit_is_not_inherited():
    program = InterpretedProgram("Mt Rt")
    body, state, metrics = make_body(30), new_state(), new_metrics()
    options = ExecutionOptions(energy_policy="compute")
    program.advance(body, state, options, 30, metrics)
    assert body.tellPrana() == 29
    assert metrics["maintenance_prana"] == 0
    assert state["credit"] == 4 and new_state()["credit"] == 0


def test_empty_and_oversized_programs():
    body, state, metrics = make_body(), new_state(), new_metrics()
    assert InterpretedProgram("").advance(body, state, ExecutionOptions(), 30, metrics) == "Live"
    assert metrics["instructions"] == 0
    for code in (None, "x", "Rt" * 1025):
        with pytest.raises(ValueError):
            InterpretedProgram(code)


def test_settings_defaults_and_invalid_combinations():
    assert SimulationConfig().execution_method == "compiled"
    assert SimulationConfig(preset="forager", execution_method="interpreted").to_dict()["instructions_per_tick"] == 6
    with pytest.raises(ValueError, match="compiled execution only"):
        SimulationConfig(preset="alpha", execution_method="interpreted")
    for value in (0, 4097, True):
        with pytest.raises(ValueError):
            ExecutionOptions(instructions_per_tick=value)


def test_real_session_methods_agree(tmp_path):
    from test_worldish import run_example
    results, events = [], []
    for method in ("compiled", "interpreted"):
        result, output = run_example(tmp_path / method, '--specificity', 'forager',
                                     '--mode', 'session', '--display', 'debug', '--no-sound',
                                     '--execution-method', method, '--instructions-per-tick', '2',
                                     '--energy-policy', 'compute', '--trace-mode', 'instructions')
        if method == 'interpreted':
            assert result['genotypes_compiled'] == 0
            assert result['genotypes_interpreted'] == 1
            assert not list(output.glob('*.so'))
            assert not list((output / 'creatures').glob('*.pyx'))
        import json
        events.append([record for line in (output / 'events.jsonl').read_text().splitlines()
                       if (record := json.loads(line))['event'] != 'run'])
        assert result['observation']['ledger']['balance_error'] == 0
        assert not result['observation']['trace']['truncated']
        result['observation'].pop('trace')  # Header method names change byte counts.
        for field in ('genotypes_compiled', 'genotypes_interpreted', 'execution'):
            result.pop(field)
        results.append(result)
    assert results[0] == results[1]
    assert events[0] == events[1]
