"""Static authored-genome review, not a second implementation of the VM."""
import copy
import json
from pathlib import Path

import pytest

from worldish.codon_program import control_paths, decode_authored, review
from worldish.codon_analysis import fingerprint


ROOT = Path(__file__).resolve().parents[1] / "experiments/codons"


def artifacts():
    return (json.loads((ROOT / "family-variant-draft.json").read_text()),
            json.loads((ROOT / "authored-forager-draft.json").read_text()))


def test_authored_genome_and_conservative_paths():
    candidate, program = artifacts()
    result = review(candidate, program)
    assert result["word_count"] == 17 and len(result["raw_genome"]) == 34
    assert result["path_count"] == 8
    assert (result["minimum_instructions"], result["maximum_instructions"]) == (14, 17)
    for path in result["paths"]:
        assert path["operations"]["MOVE"] == path["operations"]["MAINTAIN"] == 1
        assert path["operations"]["EAT"] == 2
        assert path["completion"] == "yield"
        assert path["compute_prana_zero_credit"] == 3
        assert path["live_visits_from_start"] == 3
    expensive = review(candidate, program, price=1)
    assert all(path["compute_prana_zero_credit"] > path["food_prana_upper_bound"]
               for path in expensive["paths"])


def test_mapping_and_annotation_drift_are_rejected():
    candidate, program = artifacts()
    changed = copy.deepcopy(candidate)
    changed["mapping"]["AA"] = "YIELD"
    with pytest.raises(ValueError, match="Candidate changed"):
        decode_authored(changed, program)
    program["listing"][0]["instruction"] = "NOP"
    with pytest.raises(ValueError, match="Annotation"):
        decode_authored(candidate, program)


def test_synonym_changes_preserve_decoding_but_not_raw_identity():
    candidate, program = artifacts()
    before = review(candidate, program)
    old = program["listing"][0]["codon"]
    replacement = next(word for word, op in candidate["mapping"].items()
                       if op == program["listing"][0]["instruction"] and word != old)
    program["genome"] = replacement + program["genome"][2:]
    program["listing"][0]["codon"] = replacement
    after = review(candidate, program)
    assert before["decoded"] == after["decoded"] and before["paths"] == after["paths"]
    assert before["raw_genome_sha256"] != after["raw_genome_sha256"]


def test_end_skip_empty_program_and_path_cap():
    assert control_paths([]) == [{"positions": [], "branches": [], "completion": "end"}]
    assert len(control_paths(["SKIP_ZERO"])) == 2
    with pytest.raises(ValueError, match="Unsupported"):
        control_paths(["JUMP_BACKWARD"])
    with pytest.raises(ValueError, match="not complete"):
        control_paths(["SKIP_ZERO", "NOP", "YIELD"], max_paths=1)
    candidate, program = artifacts()
    program.update(genome="", listing=[], candidate_sha256=fingerprint(candidate))
    assert review(candidate, program)["paths"][0]["compute_prana_zero_credit"] == 0
