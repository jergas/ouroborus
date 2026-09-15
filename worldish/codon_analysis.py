"""Offline codon-table analysis; this module is not a simulation decoder."""
import argparse
from collections import Counter
import hashlib
import itertools
import json
from pathlib import Path
import random


def fingerprint(value):
    data = json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=True)
    return hashlib.sha256(data.encode()).hexdigest()


def validate(candidate):
    if not isinstance(candidate, dict) or candidate.get("schema") != 1:
        raise ValueError("Expected codon-candidate schema 1")
    alphabet = candidate["alphabet"]
    if (not isinstance(alphabet, str) or not 2 <= len(alphabet) <= 8
            or len(set(alphabet)) != len(alphabet)
            or any(not char.isascii() or not char.isprintable() or char.isspace() for char in alphabet)):
        raise ValueError("Alphabet requires 2–8 distinct printable, non-space ASCII bases")
    if candidate.get("word_length") != 2:
        raise ValueError("This analyzer requires two-character codons")
    codons = ["".join(pair) for pair in itertools.product(alphabet, repeat=2)]
    table, instructions = candidate["mapping"], candidate["instructions"]
    if not isinstance(table, dict) or set(table) != set(codons):
        raise ValueError("Mapping must cover every codon exactly, with no extra words")
    if not isinstance(instructions, dict) or not instructions:
        raise ValueError("Instruction definitions are required")
    for name, instruction in instructions.items():
        if not isinstance(name, str) or not isinstance(instruction, dict):
            raise ValueError("Invalid instruction definition")
        if not isinstance(instruction.get("family"), str) or not instruction["family"]:
            raise ValueError("Each instruction needs an explicit semantic-family label")
    if any(not isinstance(value, str) or value not in instructions for value in table.values()):
        raise ValueError("Every codon must name a declared instruction")
    if set(table.values()) != set(instructions):
        raise ValueError("Every declared instruction must have at least one codon")
    return codons


def neighbors(codon, alphabet):
    for position in range(2):
        for base in alphabet:
            if base != codon[position]:
                yield position, codon[:position] + base + codon[position + 1:]


def relation(left, right, instructions):
    if left == right:
        return "silent"
    if instructions[left]["family"] == instructions[right]["family"]:
        return "same_family"
    return "other_family"


def proportions(counts):
    total = sum(counts.values())
    return {key: value / total if total else 0 for key, value in counts.items()}


def substitution_analysis(codons, alphabet, table, instructions, include_edges):
    counts = Counter(silent=0, same_family=0, other_family=0)
    by_position = [counts.copy(), counts.copy()]
    edges = []
    for codon in codons:
        for position, mutant in neighbors(codon, alphabet):
            kind = relation(table[codon], table[mutant], instructions)
            counts[kind] += 1
            by_position[position][kind] += 1
            if include_edges:
                edges.append({"parent": codon, "mutant": mutant, "position": position,
                              "before": table[codon], "after": table[mutant], "relation": kind})
    result = {"directed_transitions": sum(counts.values()), "counts": dict(counts),
              "fractions": proportions(counts),
              "by_position": [{"counts": dict(count), "fractions": proportions(count)}
                              for count in by_position]}
    if include_edges:
        result["edges"] = edges
    return result


def synonym_components(codons, alphabet, table):
    result = {}
    for instruction in sorted(set(table.values())):
        unseen = {codon for codon in codons if table[codon] == instruction}
        components = []
        while unseen:
            start = min(unseen)
            unseen.remove(start)
            pending, connected = [start], []
            while pending:
                codon = pending.pop()
                connected.append(codon)
                for _, neighbor in neighbors(codon, alphabet):
                    if neighbor in unseen:
                        unseen.remove(neighbor)
                        pending.append(neighbor)
            components.append(sorted(connected))
        result[instruction] = components
    return result


def recombination_analysis(codons, table, include_edges):
    # Enumerate ordered parental pairs, including identical genomes. Orientation
    # randomness is integrated exactly, without drawing RNG values.
    counts = [Counter(both=0, first_only=0, second_only=0, neither=0) for _ in range(2)]
    synonymous_pairs = distinct_synonymous_pairs = synonymous_novel = different = 0
    edges = []
    for first, second in itertools.product(codons, repeat=2):
        parent_ops = (table[first], table[second])
        children = (first[0] + second[1], second[0] + first[1])
        child_ops = tuple(table[child] for child in children)
        synonymous_pairs += parent_ops[0] == parent_ops[1]
        distinct_synonymous_pairs += parent_ops[0] == parent_ops[1] and first != second
        different += child_ops[0] != child_ops[1]
        for index, child_op in enumerate(child_ops):
            left, right = child_op == parent_ops[0], child_op == parent_ops[1]
            category = "both" if left and right else "first_only" if left else "second_only" if right else "neither"
            counts[index][category] += 1
            synonymous_novel += parent_ops[0] == parent_ops[1] and not left
        if include_edges:
            edges.append({"first": first, "second": second, "children": list(children),
                          "parent_instructions": list(parent_ops), "child_instructions": list(child_ops)})
    total = len(codons) ** 2
    result = {"ordered_parent_pairs": total, "fixed_orientation": dict(counts[0]),
              "reverse_orientation": dict(counts[1]),
              "random_orientation_fractions": {key: (counts[0][key] + counts[1][key]) / (2 * total)
                                                for key in counts[0]},
              "orientation_changes_instruction_pairs": different,
              "synonymous_parent_pairs": synonymous_pairs,
              "distinct_synonymous_parent_pairs": distinct_synonymous_pairs,
              "synonymous_novel_children": synonymous_novel,
              "synonymous_child_trials": synonymous_pairs * 2}
    if include_edges:
        result["pairs"] = edges
    return result


def analyze_table(candidate, table=None, include_edges=False):
    codons = validate(candidate)
    table = candidate["mapping"] if table is None else table
    # Alternate tables are only used internally for redundancy-preserving shuffles.
    return {"redundancy": dict(sorted(Counter(table.values()).items())),
            "substitutions": substitution_analysis(codons, candidate["alphabet"], table,
                                                    candidate["instructions"], include_edges),
            "synonym_components": synonym_components(codons, candidate["alphabet"], table),
            "recombination": recombination_analysis(codons, table, include_edges)}


def compare(candidate, shuffles=20, seed=42, include_edges=False):
    codons = validate(candidate)
    if type(shuffles) is not int or not 0 <= shuffles <= 1000:
        raise ValueError("Shuffle count must be an integer from 0 to 1000")
    if type(seed) is not int:
        raise ValueError("Shuffle seed must be an integer")
    rng = random.Random(seed)  # Never touch the simulation/global RNG.
    controls = []
    assignments = [candidate["mapping"][codon] for codon in codons]
    for index in range(shuffles):
        shuffled = assignments.copy()
        rng.shuffle(shuffled)
        table = dict(zip(codons, shuffled))
        analysis = analyze_table(candidate, table)
        controls.append({"index": index, "mapping_sha256": fingerprint(table), "mapping": table,
                         "substitution_fractions": analysis["substitutions"]["fractions"],
                         "disconnected_instructions": sum(len(parts) > 1 for parts in analysis["synonym_components"].values()),
                         "recombination": analysis["recombination"]})
    control_summary = {}
    for kind in ("silent", "same_family", "other_family"):
        values = [control["substitution_fractions"][kind] for control in controls]
        control_summary[kind] = ({"mean": sum(values) / len(values), "min": min(values), "max": max(values)}
                                 if values else None)
    return {"schema": 1, "candidate_name": candidate.get("name"),
            "candidate_sha256": fingerprint(candidate), "candidate": candidate,
            "analysis_model": "uniform source codons; uniform position and alternative-base substitution; uniform ordered parental pairs",
            "semantic_distance": "instruction identity, then declared family equality; no behavioral or fitness distance inferred",
            "mapping_sha256": fingerprint(candidate["mapping"]),
            "candidate_analysis": analyze_table(candidate, include_edges=include_edges),
            "shuffle_seed": seed, "control_substitution_summary": control_summary, "shuffles": controls,
            "scope": "table geometry only, not execution safety, neutrality, viability or population-level mating"}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("--shuffles", type=int, default=20)
    parser.add_argument("--seed", type=int, default=42)
    parser.add_argument("--include-edges", action="store_true")
    args = parser.parse_args(argv)
    try:
        if args.candidate.stat().st_size > 1_000_000:
            raise ValueError("Candidate file exceeds 1 MB")
        candidate = json.loads(args.candidate.read_text())
        report = compare(candidate, args.shuffles, args.seed, args.include_edges)
    except (OSError, ValueError, TypeError, KeyError) as error:
        parser.error(str(error))
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
