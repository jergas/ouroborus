# Placement and study-report validation handoff

New implementation checkpoint, 2026-09-15. Big Pickle's previous observation/study notes confirm Build/Lint and 124 tests, no skips; one tiny real study completed. A7 manual GUI/audio inspection and the full baseline matrix remain pending. This session read those notes and implemented the next options; no builds, tests, studies or VC mutations were performed.

## Architecture

Placement is independent of energy funding: policy (default) resolves transfer→local and preset→random, preserving old RNG draws and behavior. Explicit local/random work with both funding policies. Random consumes two coordinate draws; no vacancy search, no separate food, no new prana cost. Failed funded preparation keeps any RNG consumption but never debits the parent. Insufficient funding rejects before drawing. Founders unchanged.

Settings propagate through CLI/config/worker/QML and the study runner. Trace run headers and result metadata include requested/effective placement. Study plans accept optional placements axis; omitted means policy. Added a 72-condition local/random plan; it has NOT been run.

worldish.study_report reads manifests/outcomes, validates declared configuration identity, verifies execution/placement metadata against requested settings, recomputes screens and reports unknowns separately from extinction. It groups across seeds and compares paired methods' final ecological results, excluding backend and trace bookkeeping. It does not compare full trajectories. Missing/failed/timed-out/invalid results stay unknown; an interrupted final JSONL fragment is flagged, malformed complete records rejected. Duplicate/undeclared outcomes rejected. No writes or simulation launches in reporter.

## Validation order

Run Build/Lint and focused tests: tests/test_placement.py, tests/test_study.py, tests/test_study_report.py, tests/test_execution.py and tests/test_desktop.py, under AGENTS.md native environment. Then relevant/full regression checks. Report failures without fixing under the user's existing workflow.

Coverage written: unchanged default RNG consumption; local/random exact funding and duplicate/insufficient requests; axis default and 72-condition expansion; reporting equality/difference, failed/missing/invalid outcomes, recomputed criteria, configuration mismatch/duplicates and interrupted tails. Existing real-session native/interpreted full trace comparison now parametrizes default/random placement. Desktop worker test saves/loads random placement and asserts effective result metadata.

Manual check: placement dropdown fits minimum window, old JSON settings load policy, presets retain effective defaults, local/random apply only on restart and affect offspring not founders. A7 GUI/audio review is still pending. Tiny real studies across both placements/methods should have zero ledger residual and matching paired results. Run reporter on completed, prepare-only and intentionally interrupted studies; failures must stay visible. Do not interpret operational timeouts as extinction or final-state equality as trace equality.

Population/cache limits and ecological evaluation are still open (B2–B7). The full matrix can be scheduled separately from regression validation. Public semantics: docs/ecology-studies.md.

## Validation results (Big Pickle, 2026-09-15)

Build: clean (no new Cython sources, `build_ext --inplace` exit 0). Lint: clean.

Focused tests (42 collected): **42/42 passed** in 17.92s. Covers placement RNG preservation, local/random exact transfer and funding, insufficient-funds rejection, placement axis expansion to 72 conditions, old-plan default, study report equality/difference detection, failed/missing/invalid outcomes, recomputed screen, interrupted tail detection, configuration mismatch rejection, execution settings confirmation, native/interpreted trace agreement at both placements, desktop worker save/load with random placement and effective metadata. No skips, no failures.

Full regression suite: **136 passed, 0 failures, 0 skips** in 79.65s. Includes the 13 new placement/report tests plus 123 pre-existing tests covering observation, execution, forager, desktop and session regressions. No fixes needed.
