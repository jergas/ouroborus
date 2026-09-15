"""Observation invariants; execution is delegated to the validation session."""
import json
import random
from types import SimpleNamespace

import pytest

from worldish.bookentry import BookEntry
from worldish.execution import ExecutionOptions, new_metrics
from worldish.forager import SEED_CODE
from worldish.forager_vm import InterpretedProgram
from worldish.observation import Observation, TraceWriter, MAX_EVENT_BYTES
from test_forager import make_body
from test_execution import native_program  # shared native-dispatch fixture


def observer(mode="off", options=None, language="forager-v1"):
    specific = SimpleNamespace(trace_mode=mode, trace_limit=100_000)
    return Observation(specific, language, options or ExecutionOptions(), new_metrics(), {})


def entry_for(observation, name="founder", code=SEED_CODE, prana=24):
    entry = BookEntry(name, "unused")
    entry.agent = make_body(prana)
    if observation.language == "forager-v1":
        entry.execution_options = observation.options
        entry.execution_metrics = observation.metrics
    observation.attach(entry, code)
    return entry


def test_trace_event_and_byte_limits_and_io_failure(tmp_path):
    path = tmp_path / "trace.jsonl"
    trace = TraceWriter("events", 1, path)
    trace.write({"event": "one"})
    trace.write({"event": "two"})
    trace.write({"event": "three"})
    events = [json.loads(line) for line in path.read_text().splitlines()]
    assert [item["event"] for item in events] == ["one", "trace_limit"]
    assert trace.count == 1 and trace.truncated and not trace.active
    trace = TraceWriter("events", 10, path)
    trace.write({"event": "oversized", "raw": "x" * MAX_EVENT_BYTES})
    assert trace.truncated and json.loads(path.read_text())["reason"] == "event_bytes"
    trace = TraceWriter("events", path=tmp_path / "missing" / "trace")
    trace.write({"event": "still_running"})
    assert trace.error and not trace.active
    trace = TraceWriter("events", path=path)
    trace.file.close()  # Simulate a write failure after successful opening.
    trace.write({"event": "still_running"})
    assert trace.error and not trace.active


def run_observed(program, options, mode, instrument=True):
    random.seed(42)
    initial_rng = random.getstate()
    observation = observer(mode, options)
    assert random.getstate() == initial_rng
    entry = entry_for(observation)
    observation.born(entry)
    if not instrument:
        entry.execution_metrics = observation.metrics
    grid = entry.agent.returnTopology()
    for x in range(5):
        for y in range(5):
            grid.set((x, y), 1)
    states = []
    for tick in range(12):
        observation.tick = tick
        before = entry.agent.tellPrana()
        entry.fatum["prayer"] = program.advance(entry.agent, entry.execution_state,
            options, 30, entry.execution_metrics)
        if instrument:
            observation.live_finished(entry, before)
            observation.select(entry.name, {entry.name: entry})
        assert observation.ledger([entry.agent])["balance_error"] == 0
        states.append((entry.agent.tellPrana(), entry.agent.tellAddress(), dict(entry.execution_state),
                       dict(observation.metrics), random.getstate(),
                       [grid.get((x, y)) for x in range(5) for y in range(5)]))
    observation.close()
    return states


@pytest.mark.parametrize("budget", [1, 6])
@pytest.mark.parametrize("policy", ["maintenance", "compute"])
def test_recording_is_passive_and_native_events_match(tmp_path, monkeypatch, native_program, budget, policy):
    monkeypatch.chdir(tmp_path)
    options = ExecutionOptions(instructions_per_tick=budget, energy_policy=policy)
    program = InterpretedProgram(SEED_CODE)
    baseline = run_observed(program, options, "off", instrument=False)
    assert run_observed(program, options, "off") == baseline
    assert not (tmp_path / "events.jsonl").exists()
    assert run_observed(program, options, "instructions") == baseline
    interpreted_events = (tmp_path / "events.jsonl").read_text()
    assert run_observed(native_program, options, "instructions") == baseline
    assert (tmp_path / "events.jsonl").read_text() == interpreted_events


def test_local_counters_and_death_tombstone_do_not_consume_audio_notifications():
    observation = observer()
    first, second = entry_for(observation, "one"), entry_for(observation, "two")
    first.execution_metrics["instructions"] += 3
    second.execution_metrics["instructions"] += 2
    assert observation.metrics["instructions"] == 5
    assert first.local_metrics["instructions"] == 3
    assert second.local_metrics["instructions"] == 2
    class Body:
        def tellPrana(self): return 12
        def tellAddress(self): return (2, 3)
        def hasEaten(self): raise AssertionError("Inspection consumed audio notification")
    first.agent = Body()
    observation.born(first)
    observation.select("one", {"one": first})
    observation.died(first)
    del first.agent
    assert observation.inspection({})["status"] == "dead"
    assert observation.ledger([])["balance_error"] == 0


def test_transfer_is_internal_and_source_delta_is_explicit():
    observation = observer(language="source")
    parent = entry_for(observation, prana=30)
    observation.born(parent)
    parent.agent.losePrana(3)
    observation.live_finished(parent, 30)
    child = entry_for(observation, "child", prana=12)
    child.fatum.update(parent=parent.name, generation=1)
    parent.agent.losePrana(12)
    observation.born(child, transferred=True)
    ledger = observation.ledger([parent.agent, child.agent])
    assert ledger["source_net_change"] == -3
    assert ledger["transferred"] == 12 and ledger["preset_offspring_input"] == 0
    assert ledger["live_prana"] == 27 and ledger["balance_error"] == 0
    observation.died(child)
    assert observation.ledger([parent.agent])["balance_error"] == 0


def test_raw_and_decoded_identities_are_distinct():
    observation = observer()
    one = entry_for(observation, "one", "?? Rt")
    two = entry_for(observation, "two", "!! Rt")
    assert one.genome_info["genome_id"] != two.genome_info["genome_id"]
    assert one.genome_info["program_id"] == two.genome_info["program_id"]


def test_trace_configuration_validation():
    from worldish.config import SimulationConfig
    for values in ({"trace_mode": "unknown"}, {"trace_limit": 0}, {"trace_limit": True},
                   {"trace_limit": 1_000_001}):
        with pytest.raises(ValueError):
            SimulationConfig(**values)
    config = SimulationConfig(trace_mode="instructions", trace_limit=123)
    assert SimulationConfig(**config.to_dict()) == config
