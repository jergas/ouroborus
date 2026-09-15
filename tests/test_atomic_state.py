"""Data-boundary tests; these do not claim atomic execution parity."""
from dataclasses import FrozenInstanceError
import json
from pathlib import Path

import pytest

from worldish.atomic_state import decode_genome, new_state, validate_state
from worldish.codon_analysis import fingerprint


@pytest.fixture
def candidate():
    path = Path(__file__).resolve().parents[1] / "experiments/codons/family-variant-draft.json"
    return json.loads(path.read_text())


def decode(candidate, raw):
    return decode_genome(candidate, raw, expected_candidate_sha256=fingerprint(candidate))


def test_total_decoding_and_synonymous_identity(candidate):
    words = sorted(candidate["mapping"])
    program = decode(candidate, "".join(words))
    assert len(program.words) == 64
    assert program.operations == tuple(candidate["mapping"][word] for word in words)
    left, right = decode(candidate, "AA"), decode(candidate, "AB")
    assert left.operations == right.operations == ("NOP",)
    assert left.raw_sha256 != right.raw_sha256
    assert left.program_sha256 == right.program_sha256
    assert right.raw == "AB" and right.words == ("AB",)
    with pytest.raises(FrozenInstanceError):
        right.raw = "AA"
    candidate["mapping"]["AB"] = "YIELD"
    assert right.operations == ("NOP",)


@pytest.mark.parametrize("raw", ["A", "AA AB", "aa", "AZ", "AA\n", "AA" * 1025, None])
def test_reject_malformed_genomes(candidate, raw):
    with pytest.raises(ValueError):
        decode(candidate, raw)


def test_empty_limit_and_candidate_pin(candidate):
    assert decode(candidate, "").operations == ()
    assert len(decode(candidate, "AA" * 1024).operations) == 1024
    with pytest.raises(ValueError, match="pinned"):
        decode_genome(candidate, "AA", expected_candidate_sha256="wrong")
    candidate["instructions"]["UNKNOWN"] = candidate["instructions"].pop("NOP")
    for word in ("AA", "AB"):
        candidate["mapping"][word] = "UNKNOWN"
    with pytest.raises(ValueError, match="Unsupported"):
        decode(candidate, "")  # Even unused unsupported operations invalidate the table.


def test_fresh_and_resumed_state_ownership():
    parent, child = new_state(), new_state()
    parent.update(a=-32768, r=32767, p=7, h=7, ip=16, credit=5, prayer="GrantChild")
    parent["memory"][7] = 32767
    restored = validate_state(parent, program_length=17, instructions_per_prana=6)
    assert restored == parent
    restored["memory"][7] = -1
    assert parent["memory"][7] == 32767
    assert child == new_state()
    assert validate_state(child, program_length=0, instructions_per_prana=1) == child


@pytest.mark.parametrize("field,value", [
    ("a", True), ("a", -32769), ("r", 32768), ("r", 1.0),
    ("p", -1), ("h", 8), ("ip", 17), ("credit", 6), ("credit", -1),
    ("memory", [0] * 7), ("memory", [0] * 7 + [False]),
    ("memory", [0] * 7 + [32768]), ("prayer", "CreateMe"),
])
def test_reject_invalid_state_fields(field, value):
    state = new_state()
    state[field] = value
    with pytest.raises(ValueError):
        validate_state(state, program_length=17, instructions_per_prana=6)


def test_reject_state_shape_and_context():
    for state in ({}, {**new_state(), "extra": 1}, None):
        with pytest.raises(ValueError):
            validate_state(state, program_length=17, instructions_per_prana=6)
    for length, price in ((True, 6), (1025, 6), (1, 0), (1, True), (1, 4097)):
        with pytest.raises(ValueError):
            validate_state(new_state(), program_length=length, instructions_per_prana=price)
    with pytest.raises(ValueError):
        validate_state({**new_state(), "ip": 1}, program_length=0, instructions_per_prana=6)
