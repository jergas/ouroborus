# Atomic decoder and state validation handoff

Implementation checkpoint, 2026-09-15. Not executed or validated in this session. Big Pickle retains build, test execution and version-control ownership.

## Scope

Added `worldish/atomic_state.py`: explicit candidate-hash pin, strict raw decoding, immutable decoded data, separate raw and candidate-scoped decoded identities, fresh offspring state, and defensive suspended-state validation. The static reviewer imports its instruction vocabulary from this module. No executor, language registration, mapping freeze, simulation or configuration change. See [public design](../../../docs/atomic-codon-proposal.md).

## Requested validation

Run the repository Build/Lint commands and focused tests:

```sh
.venv/bin/python -m pytest -q tests/test_atomic_state.py tests/test_codon_program.py tests/test_codon_analysis.py
```

Then the standard full regression with the documented native audio environment. Report failures without fixing, per the user's workflow. No ecological runs or additional measurements are needed for this data-only checkpoint.

Coverage includes all 64 codons; raw synonyms with distinct raw hashes/equal decoded hashes; immutable decoding independent of subsequent candidate edits; empty/max-length/malformed inputs; pin mismatch; unsupported table instructions even for empty genomes; fresh and restored slot ownership; signed integer/type, pointer, credit, state-shape and originating-context rejection. Existing reviewer and analysis tests guard the vocabulary move.

## Boundaries and next work

State keys are a/r/memory/p/h/ip/prayer/credit. External states are rejected rather than repaired; completed passes must normalize ip before suspension. Eight slots are copied defensively. Caller supplies originating program length and instructions-per-prana; this is not a complete checkpoint loader. Existing six-op state is unchanged. Draft table validation reuses the offline candidate schema; production versioning and cache integration remain undecided. No semantic/RNG/charging parity or viability claim follows from decoding synonyms identically.

Next: implement atomic operations and lifecycle-aware scheduling, retaining supported execution/energy options; then compiled/interpreted trace parity and authored-forager assessment before mutation.

## Validation results (Big Pickle, 2026-09-15)

Build: clean (`build_ext --inplace` exit 0). Lint: clean (`compileall` + `git diff --check`).

Focused tests (33 collected across test_atomic_state.py + test_codon_program.py + test_codon_analysis.py): **33/33 passed**. Coverage confirmed: all 64 codons decode totalling 64 words; raw synonyms keep distinct raw hashes but equal decoded hashes; immutable decoding survives later candidate edits; empty/max-length/malformed/pin-mismatch rejection; unsupported table instructions rejected even for empty genomes; fresh and restored slot ownership with defensive copy; signed/type/pointer/credit/state-shape/originating-context rejection.

Full regression suite: **177 passed, 0 failures, 0 skips** in 81.98s (153 prior + 24 new across the three touched files). No fixes needed.

No executor, language registration, mapping freeze, simulation or configuration change was introduced; the checkpoint is data boundaries only, as declared. `worldish.codon_program.DRAFT_INSTRUCTIONS` now imports the shared vocabulary from `worldish.atomic_state`.
