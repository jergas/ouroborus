# Atomic codon proposal and analysis validation handoff

2026-09-15. User reports Big Pickle validated the resource-stop checkpoint: Build/Lint clean, focused46 and full144 tests passed without skips/failures; manual non-session rejection and max-genotypes1 zero-tick resource stop confirmed. New work begins phase C design/analysis while ecological matrices and byte/storage/admission policies remain pending.

## New artifacts and provisional decisions

- docs/atomic-codon-proposal.md defines a PROPOSED accumulator/scratch-register/eight-slot machine with saturating signed16-bit arithmetic, explicit eight-way heading, bounded forward skips/YIELD, 32 operations and supported maintenance/compute charging. No running language was changed, no mutation/reproduction operator enabled, and no mapping frozen.
- experiments/codons/family-variant-draft.json assigns all64 A–H two-character codons to32 instructions, two synonyms each. First character selects one of eight declared families, second character one of four variants in paired synonyms. NOP gets2/64 codons. Raw synonyms remain heritable in the planned language.
- worldish.codon_analysis validates candidate totality, enumerates all directed single substitutions and synonym components, enumerates both orientations of all ordered codon-parent pairs, and produces redundancy-preserving shuffled controls using an isolated Random instance. Records candidate/control tables and hashes, model assumptions, fractions and control summaries; optional edges/pairs expose transitions. This is OFFLINE table geometry, not VM execution or simulation validation.

The family metric is explicitly heuristic and partly circular: the candidate is arranged by those same labels. It misses cross-family similarities and does not imply conserved behavior/fitness. Uniform parent-pair sampling differs from actual mating distributions. Per-offspring and per-codon orientation have equal single-site marginals but different genome correlations; whole-genome mating is later work.

## Validation requested of Big Pickle

No tests, analysis command, build or simulation was executed in this implementation session. No version-control mutations. Please run tests/test_codon_analysis.py, applicable lint/build checks and regressions under the existing workflow. Report failures without fixing.

Tests include a hand-worked two-base/four-codon table, candidate combinatorial counts, private RNG/no input mutation, shuffle redundancy, totality/symbol checks, and a disconnected synonym layout where crossing synonymous parents creates different instructions.

Then run `.venv/bin/python -m worldish.codon_analysis experiments/codons/family-variant-draft.json --shuffles 20 --seed 42 --include-edges`, writing JSON to a fresh artifact path. Expected candidate counts derived analytically: 896 directed substitutions, 64 silent/384 same-family/448 other-family; 32 connected two-codon synonym components; 4096 ordered parental pairs; 128 synonymous pairs including64 with distinct raw codons; no novel synonymous-child instructions. Fixed-orientation matches: both128, first-only896, second-only384, neither2688. Check empirical output against these expectations and record control results without claiming a fitness benefit.

Keep the JSON report and summarize its fractions/control mean/min/max and recombination implications in this note. The candidate is NOT accepted solely because tests match these formulas. Alphabet size, two-synonym redundancy, 32-op expressiveness, branch limitations, memory/register overlap and energy-policy incentives still need review before implementation/freezing. Newborn machine state, charging, malformed external input and native/interpreted equality are only specified, not tested by this offline tool.

Public plan: docs/atomic-codon-proposal.md. Check C tasks only after the corresponding design/measurement/implementation requirement is fulfilled; no C completion is inferred from a draft table alone.

## Validation results (Big Pickle, 2026-09-15)

Build: clean (`build_ext --inplace` exit 0). Lint: clean.

Focused tests (5 collected): **5/5 passed**. Hand-worked two-base/four-codon table with substitution/synonym/recombination edges; combinatorial expectations for the candidate (896 directed substitutions: 64 silent / 384 same-family / 448 other-family; 32 single-codon synonym components; 4096 ordered pairs; 128 synonymous pairs with 64 distinct; 0 novel synonymous children; fixed-orientation both128/first896/second384/neither2688); shuffle controls preserve redundancy and never touch global RNG (both determinism and input immutability checked); totality/symbol/word-length/alphabet validation; disconnected-synonym layout producing novel synonymous children.

Full regression suite: **149 passed, 0 failures, 0 skips** in 83.18s (144 prior + 5 new). No fixes needed.

Measurement run (`--shuffles 20 --seed 42 --include-edges`, rc 0): the report at experiments/codons/family-variant-analysis-report.json reproduces every analytical expectation above (including edge/pair counts 896/4096 and 20 control tables with per-codon redundancy 2). Candidate substitution fractions: silent 0.0714, same-family 0.4286, other-family 0.5000. Shuffled control means: silent 0.0174 (min 0.0045, max 0.0268), same-family 0.0962 (min 0.0781, max 0.1183), other-family 0.8864 (min 0.8616, max 0.9085). Random-orientation recombination fractions: both 0.0312, first-only 0.1562, second-only 0.1562, neither 0.6562. The candidate carries roughly 4.1× the control silent rate and 4.5× the same-family rate for comparable other-family suppression; these reflect the deliberately labelled layout and do NOT establish conserved behavior or fitness. Candidate name atomic-family-variant-draft-1, mapping sha256 cb8ea5062ec1f90d, candidate sha256 1c975a9849aeb90c.

Recombination implication: with 64 distinct synonymous parent pairs, four-fifths of random-orientation crosses inherit no parent instruction (neither 0.6562), about a third inherit at least one parent instruction, and crossing synonymous parents yields no novel instruction in this exact-table layout (but non-synonymous crosses commonly split parent instructions across children). Alphabet size, redundancy level, 32-op expressiveness, branch limits, register/memory overlap and energy-policy incentives remain open as the handoff stated. The candidate is not accepted on these numbers alone; newborn machine state, charging, malformed external input and native/interpreted equality remain untested (offline tool).

Master copy: /tmp/opencode/codon-report.json (1,598,690 bytes) matches the committed report file.
