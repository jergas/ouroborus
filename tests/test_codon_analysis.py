"""Offline mapping geometry; no VM or evolutionary simulation is exercised."""
import copy
import json
from pathlib import Path
import random

import pytest

from worldish.codon_analysis import analyze_table, compare, validate


def candidate():
    return json.loads((Path(__file__).resolve().parents[1] /
        "experiments/codons/family-variant-draft.json").read_text())


def toy():
    return {"schema": 1, "alphabet": "AB", "word_length": 2,
            "instructions": {"NOP": {"family": "control"}, "EAT": {"family": "life"}},
            "mapping": {"AA": "NOP", "AB": "NOP", "BA": "EAT", "BB": "EAT"}}


def test_hand_worked_two_base_table():
    result = analyze_table(toy(), include_edges=True)
    assert result["substitutions"]["counts"] == {"silent": 4, "same_family": 0, "other_family": 4}
    assert len(result["substitutions"]["edges"]) == 8
    assert result["synonym_components"]["NOP"] == [["AA", "AB"]]
    crosses = result["recombination"]
    assert crosses["ordered_parent_pairs"] == 16
    assert crosses["fixed_orientation"] == {"both": 8, "first_only": 8, "second_only": 0, "neither": 0}
    assert crosses["reverse_orientation"] == {"both": 8, "first_only": 0, "second_only": 8, "neither": 0}
    assert crosses["synonymous_novel_children"] == 0
    assert len(crosses["pairs"]) == 16


def test_candidate_geometry_matches_combinatorial_expectations():
    result = analyze_table(candidate())
    assert len(result["redundancy"]) == 32 and set(result["redundancy"].values()) == {2}
    assert result["substitutions"]["counts"] == {"silent": 64, "same_family": 384, "other_family": 448}
    assert all(len(parts) == 1 and len(parts[0]) == 2 for parts in result["synonym_components"].values())
    crosses = result["recombination"]
    assert crosses["ordered_parent_pairs"] == 4096
    assert crosses["synonymous_parent_pairs"] == 128
    assert crosses["distinct_synonymous_parent_pairs"] == 64
    assert crosses["synonymous_novel_children"] == 0
    assert crosses["fixed_orientation"] == {"both": 128, "first_only": 896, "second_only": 384, "neither": 2688}


def test_controls_preserve_redundancy_and_global_rng():
    table = candidate()
    original = copy.deepcopy(table)
    state = random.getstate()
    report = compare(table, shuffles=2, seed=7)
    assert random.getstate() == state and table == original
    assert compare(table, shuffles=2, seed=7) == report
    from collections import Counter
    for control in report["shuffles"]:
        assert Counter(control["mapping"].values()) == Counter(table["mapping"].values())
    assert "edges" not in report["candidate_analysis"]["substitutions"]


def test_totality_and_symbols_are_validated():
    for change in (lambda c: c["mapping"].pop("AA"),
                   lambda c: c["mapping"].update(ZZ="NOP"),
                   lambda c: c["mapping"].update(AA="undefined"),
                   lambda c: c.update(alphabet="AA"),
                   lambda c: c.update(word_length=3)):
        table = toy()
        change(table)
        with pytest.raises(ValueError):
            validate(table)


def test_disconnected_synonyms_and_disruptive_synonymous_mating():
    table = toy()
    table["mapping"] = {"AA": "NOP", "BB": "NOP", "AB": "EAT", "BA": "EAT"}
    result = analyze_table(table)
    assert result["synonym_components"]["NOP"] == [["AA"], ["BB"]]
    assert result["recombination"]["synonymous_novel_children"] == 8
