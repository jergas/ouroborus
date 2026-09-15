"""Experimental atomic-machine data boundaries; no execution or language registration.

Candidate hashes pin a reviewed draft, not a deployed language version. State
validation describes suspended live visits, not lifecycle/world checkpoints.
"""
from dataclasses import dataclass
import hashlib

from .codon_analysis import fingerprint, validate


DRAFT_INSTRUCTIONS = frozenset("""NOP YIELD SKIP_ZERO SKIP_POSITIVE ZERO ONE BIRTH_COST
REPRO_THRESHOLD FOOD_HERE FOOD_AHEAD PRANA FACING TURN_LEFT TURN_RIGHT RANDOM_TURN MOVE
ADD SUBTRACT LESS EQUAL STORE_R LOAD_R SWAP_R CLEAR_R NEXT_SLOT PREVIOUS_SLOT LOAD_SLOT
STORE_SLOT EAT MAINTAIN REQUEST_CHILD REQUEST_DEATH""".split())


@dataclass(frozen=True)
class DecodedGenome:
    raw: str
    words: tuple
    operations: tuple
    candidate_sha256: str
    raw_sha256: str
    program_sha256: str


def decode_genome(candidate, raw, *, expected_candidate_sha256):
    """Decode exact bases under an explicitly pinned, total draft mapping."""
    validate(candidate)
    candidate_hash = fingerprint(candidate)
    if expected_candidate_sha256 != candidate_hash:
        raise ValueError("Candidate differs from the explicitly pinned draft")
    if not set(candidate["instructions"]).issubset(DRAFT_INSTRUCTIONS):
        raise ValueError("Unsupported draft instruction semantics")
    if (not isinstance(raw, str) or len(raw) > 2048 or len(raw) % 2
            or any(base not in candidate["alphabet"] for base in raw)):
        raise ValueError("Genome requires at most 1024 complete codons without formatting")
    words = tuple(raw[index:index + 2] for index in range(0, len(raw), 2))
    operations = tuple(candidate["mapping"][word] for word in words)
    return DecodedGenome(
        raw, words, operations, candidate_hash,
        hashlib.sha256(raw.encode("ascii")).hexdigest(),
        fingerprint({"candidate_sha256": candidate_hash, "operations": operations}),
    )


def new_state():
    """Fresh offspring state; no parent registers, slots or credit are inherited."""
    return {"a": 0, "r": 0, "memory": [0] * 8, "p": 0, "h": 0,
            "ip": 0, "prayer": "Live", "credit": 0}


def _integer(value, lower, upper, name):
    if type(value) is not int or not lower <= value <= upper:
        raise ValueError(f"{name} must be an integer from {lower} to {upper}")


def validate_state(state, *, program_length, instructions_per_prana):
    """Return an independent validated copy; reject rather than repair input.

    Completion must normalize ip to zero before suspension. An empty program
    therefore also requires ip zero. Credit bounds use the originating compute
    batch size, including when maintenance policy leaves credit unused.
    """
    _integer(program_length, 0, 1024, "program_length")
    _integer(instructions_per_prana, 1, 4096, "instructions_per_prana")
    if not isinstance(state, dict) or set(state) != set(new_state()):
        raise ValueError("State must contain exactly the atomic-machine fields")
    for name in ("a", "r"):
        _integer(state[name], -32768, 32767, name)
    memory = state["memory"]
    if not isinstance(memory, list) or len(memory) != 8:
        raise ValueError("Memory must be a list of eight signed integers")
    for value in memory:
        _integer(value, -32768, 32767, "memory slot")
    for name in ("p", "h"):
        _integer(state[name], 0, 7, name)
    _integer(state["ip"], 0, max(0, program_length - 1), "ip")
    _integer(state["credit"], 0, instructions_per_prana - 1, "credit")
    if state["prayer"] not in ("Live", "GrantChild", "KillMe"):
        raise ValueError("Unknown pending prayer")
    return {**state, "memory": memory.copy()}
