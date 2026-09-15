"""Review an authored genome against a pinned draft mapping, without executing it."""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path

from .codon_analysis import fingerprint, validate
from .atomic_state import DRAFT_INSTRUCTIONS


def decode_authored(candidate, program):
    validate(candidate)
    if not isinstance(program, dict) or program.get("schema") != 1:
        raise ValueError("Expected authored-program schema 1")
    if program.get("candidate_sha256") != fingerprint(candidate):
        raise ValueError("Candidate changed; review and explicitly re-author the program")
    genome = program["genome"]
    if (not isinstance(genome, str) or len(genome) % 2 or len(genome) > 2048
            or any(base not in candidate["alphabet"] for base in genome)):
        raise ValueError("Genome requires at most 1024 complete codons with no formatting spaces")
    words = [genome[index:index + 2] for index in range(0, len(genome), 2)]
    listing = program["listing"]
    if not isinstance(listing, list) or len(listing) != len(words):
        raise ValueError("Annotation count differs from raw genome length")
    decoded = []
    for word, annotation in zip(words, listing):
        instruction = candidate["mapping"][word]
        if annotation.get("codon") != word or annotation.get("instruction") != instruction:
            raise ValueError("Annotation does not match the actual raw codon")
        decoded.append(instruction)
    return words, decoded


def control_paths(instructions, max_paths=4096):
    """Conservative acyclic paths: each skip condition is independently unknown.

    This does not evaluate registers, energy, food or the CA. Correlated branch
    conditions may make some enumerated paths infeasible at runtime.
    """
    if any(instruction not in DRAFT_INSTRUCTIONS for instruction in instructions):
        raise ValueError("Unsupported draft instruction semantics")
    if len(instructions) > 1024:
        raise ValueError("Program exceeds 1024 instructions")
    if type(max_paths) is not int or not 1 <= max_paths <= 4096:
        raise ValueError("Path limit must be from 1 to 4096")
    pending = [(0, [], [])]
    completed = []
    while pending:
        position, visited, decisions = pending.pop()
        if position >= len(instructions):
            completed.append({"positions": visited, "branches": decisions, "completion": "end"})
        else:
            instruction = instructions[position]
            visited = visited + [position]
            if instruction == "YIELD":
                completed.append({"positions": visited, "branches": decisions, "completion": "yield"})
            elif instruction in ("SKIP_ZERO", "SKIP_POSITIVE"):
                for skip in (True, False):
                    pending.append((position + (2 if skip else 1), visited,
                                    decisions + [{"position": position, "skip": skip}]))
            else:
                pending.append((position + 1, visited, decisions))
        if len(completed) >= max_paths and pending:
            raise ValueError("Control-path limit exceeded; analysis is not complete")
    return completed


def review(candidate, program, allowance=6, price=6, max_paths=4096):
    for value in (allowance, price):
        if type(value) is not int or not 1 <= value <= 4096:
            raise ValueError("Instruction allowance and compute batch must be from 1 to 4096")
    words, instructions = decode_authored(candidate, program)
    paths = control_paths(instructions, max_paths)
    for path in paths:
        counts = Counter(instructions[position] for position in path["positions"])
        count = len(path["positions"])
        path["instructions"] = count
        path["operations"] = dict(counts)
        # Completion is a live-visit boundary; this excludes CreateMe, birth,
        # reproduction and death dispatches, and early termination on zero prana.
        path["live_visits_from_start"] = max(1, (count + allowance - 1) // allowance)
        path["compute_prana_zero_credit"] = (count + price - 1) // price
        path["compute_prana_max_credit"] = (max(0, count - (price - 1)) + price - 1) // price
        path["maintenance_debit_upper_bound"] = counts["MAINTAIN"]
        path["food_prana_upper_bound"] = counts["EAT"] * 5
    return {"schema": 1, "name": program.get("name"), "candidate_sha256": fingerprint(candidate),
            "raw_genome": program["genome"], "raw_genome_sha256": hashlib.sha256(program["genome"].encode("ascii")).hexdigest(),
            "word_count": len(words), "decoded": instructions,
            "instructions_per_live_visit": allowance, "instructions_per_prana": price,
            "food_prana_per_success": 5,
            "path_count": len(paths), "minimum_instructions": min(p["instructions"] for p in paths),
            "maximum_instructions": max(p["instructions"] for p in paths), "paths": paths,
            "scope": "conservative static control flow and completed-pass cost bounds; no execution or viability claim"}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("program", type=Path)
    parser.add_argument("--allowance", type=int, default=6)
    parser.add_argument("--price", type=int, default=6)
    parser.add_argument("--max-paths", type=int, default=4096)
    args = parser.parse_args(argv)
    try:
        for path in (args.candidate, args.program):
            if path.stat().st_size > 1_000_000:
                raise ValueError("Input exceeds 1 MB")
        result = review(json.loads(args.candidate.read_text()), json.loads(args.program.read_text()),
                        args.allowance, args.price, args.max_paths)
    except (OSError, ValueError, TypeError, KeyError, AttributeError) as error:
        parser.error(str(error))
    print(json.dumps(result, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
