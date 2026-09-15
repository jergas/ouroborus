# Authored atomic forager and static review handoff

2026-09-15. Prior codon analysis validation: Build/Lint clean; focused5/full149 tests passed without skips/failures. Measurement report exists at experiments/codons/family-variant-analysis-report.json and matches the combinatorial expectations. Candidate silent7.1% versus shuffled mean1.7%, same-family42.9% versus9.6% describes deliberate layout geometry, not fitness. The table remains provisional.

New checkpoint: authored-forager-draft.json contains a17-codon/34-base genome using13 instructions from the existing draft mapping. No new opcode or table change. It attempts eating locally, senses ahead, conditionally random-turns, moves/eats, maintains, makes an explicit death decision, compares fresh prana against saved threshold and requests birth before YIELD. An unnecessary FOOD_HERE/conditional-EAT probe was removed because EAT alone is cheaper at equal instruction prices. Two EAT and two PRANA codons preserve distinct synonymous spellings.

Added worldish.codon_program: hash-pinned annotation/decoding validation and bounded static path/cost review. It is NOT a VM and does not evaluate registers, CA, RNG, food success, mortality or transfers. Skip conditions are independent, so path counts overapproximate feasible dynamics. Unsupported instruction semantics and path-limit overflow reject analysis. Runtime source/forager-v1 and specificities are unchanged; no mutation enabled or mapping frozen.

## Validation for Big Pickle

No tests, review command, build, simulation or VC mutation was performed in the implementation session. Run tests/test_codon_program.py and relevant regression/lint/build checks. Then run the review CLI on the authored artifact at allowance6/price6 and price1, retaining reports under fresh artifact names. Expected:17 words,34 bases,8 conservative paths,14–17 executed instructions; every complete path has one MOVE/MAINTAIN and two EAT attempts, ends at YIELD, takes three live visits at allowance6, and charges three prana from zero credit at price6. At price1 each complete path costs more than maximum food input10.

Tests cover those bounds, candidate-hash and annotation drift rejection, exact raw synonym preservation with equal decoded paths, empty/end-skip semantics and path-cap rejection. Check unknown opcodes reject rather than being treated as linear instructions. Reports are static expectations, not evidence of dynamic viability or correct future VM execution. Report failures without fixing under the user's workflow.

The design uses the original threshold30/endowment12; actual funding remains world-owned and rechecked later. Death requests override reproduction; compute zero-energy guards may terminate before a full path. Reading ahead can become stale across CA ticks. Memory slots and many candidate instructions are unused, so this does not validate their value or justify freezing the32-op design.

Public rationale/annotated listing: docs/authored-atomic-forager.md. Next runtime work should add the agreed language and exact authored bases, with shared primitive/charging semantics and compiled/interpreted trace equality, before mutation. Ecology evaluation remains open.

## Validation results (Big Pickle, 2026-09-15)

Build: clean (`build_ext --inplace` exit 0). Lint: clean.

Focused tests (9 collected across test_codon_program.py + test_codon_analysis.py): **9/9 passed**. Authored genome and conservative paths (17 words / 34 bases, 8 paths, 14–17 instructions, MOVE/MAINTAIN×1 and EAT×2 per path, all yield, 3 live visits, zero-credit prana 3 at price6, price1 cost above food bound); mapping and annotation drift rejection; synonym changes preserve decoding and paths but change raw identity; end-skip, empty program, path-cap and unsupported-instruction rejection.

Full regression suite: **153 passed, 0 failures, 0 skips** in 82.94s (149 prior + 4 new). No fixes needed.

Review CLI runs (rc 0, reports retained):
- allowance6/price6 (experiments/codons/authored-forager-review-price6.json): word_count 17, path_count 8, instructions 14–17, all paths end at YIELD with one MOVE, one MAINTAIN and two EAT attempts; every path takes 3 live visits and charges 3 prana from zero credit; food-prana upper bound 10. Raw genome sha256 a105d9b8c418e308.
- allowance6/price1 (experiments/codons/authored-forager-review-price1.json): identical structure, but zero-credit compute prana 14–17 across paths, strictly above the food-prana upper bound 10 on every path as expected; a price-1 environment therefore cannot sustain these completed paths from food income alone.

Unknown opcodes are rejected (Unsupported draft instruction semantics) rather than treated as linear instructions, verified in tests. These remain static control-flow and completed-pass cost bounds only; registers, CA, RNG, food success, mortality, transfers, and zero-energy early termination are not evaluated here. No mutation enabled, mapping not frozen.

Master copies: /tmp/opencode/authored-review-price6.json and /tmp/opencode/authored-review-price1.json match the committed report files.
