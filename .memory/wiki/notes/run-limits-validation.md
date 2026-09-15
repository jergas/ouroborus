# Session run-limit validation handoff

2026-09-15 implementation checkpoint. Previous placement/report validation recorded by Big Pickle: focused42/full136 passing, no skips, clean Build/Lint, no fixes. New code has NOT been built, tested, run or committed by this implementation session. Big Pickle retains testing/builds/VC; report failures without fixing under the existing workflow.

## Decisions and scope

Add supported zero-default/unlimited stop thresholds for session population, distinct prepared raw genomes and completed tick-loop lifecycle visits. Check after initialization and each completed dispatch; terminate the experiment, never reject births or partially charge energy. Reaching equality fires. Init can already have met/exceeded a threshold, and its work is excluded from visit counts. Partial ticks are explicit. These are not byte/RSS/cache-artifact caps or preemptive CPU bounds. Other CLI modes reject enabled limits.

Controls propagate through config/CLI/desktop/worker/study optional limits object. Trace header records config; resource_limit event records observed thresholds, unless tracing is disabled/truncated. Result termination always captures limits/reason/visits/partial-tick state for session runs. Desktop state limited; studies retain result with status limited and unknown outcome. Reporter preserves failed/limited result payloads and verifies limits on completed results. Defaults preserve scheduling/RNG/prana behavior; visits become additional metadata.

## Validation

Run Build/Lint, focused tests/test_run_limits.py, test_study.py, test_study_report.py, test_execution.py, test_desktop.py, then full regression as appropriate using AGENTS.md environment. Coverage includes disabled limits, equality/simultaneous limits, one-time event emission, visit partial-tick metadata, invalid settings, exact-funded fourth-body stop under both methods, partial session stop rejected as horizon success, report unknowns and desktop limited completion. Tests are written, not executed here.

Check CLI rejects nonzero limits outside session but permits zeros; old settings/plans default zeros. Check max_genotypes1 stops after seed preparation, with zero ticks and a result; population4 stops after exactly one funded Forager offspring, residual0. Both methods must agree on state/counters and censor reason. Confirm no unowned workers or audio threads after stop; display stopped/limited distinctly from failed and normal horizon completion. Validate QML scrolling/minimum window and limit settings save/load.

Tiny plan with limits should retain limited status and result. Reporter must count unknown, not extinction or biological screen success. Disabled-limit baseline should still pass existing method trace comparisons. Do not run long ecology matrices until focused checks pass. Population/genotype thresholds are checked boundaries; they do not bound compilation/init or arbitrary source live() internals.

Public semantics: docs/run-limits.md. B6 remains partially open for bytes/storage and pre-initialization resource admission; ecological evaluation and A7 manual GUI/audio review remain pending.

## Validation results (Big Pickle, 2026-09-15)

Build: clean (`build_ext --inplace` exit 0). Lint: clean.

Focused tests (46 collected): **46/46 passed** in 21.76s. Covers disabled limits and one-time event emission, visit thresholds and partial-tick metadata, RunLimits/SimulationConfig validation and settings round-trip, real-session exact-funded fourth-body stop under both compiled and interpreted (`population==4`, `prana_transferred==12`, ledger residual 0, reason `resource_limit`), partial-tick non-horizon rejection in `classify`, and limited outcomes counted as unknown in reports with preserved termination payload. Desktop worker test confirms state `limited`, message, and result metadata.

Full regression suite: **144 passed, 0 failures, 0 skips** in 83.42s (136 prior + 8 new). No fixes needed.

Manual checks (handoff items): non-session CLI mode rejects all nonzero limits via parser exit while zeros are permitted; `--max-genotypes 1` session run stops after seed preparation with `iterations==0`, `lifecycle_visits==0`, `reason=="resource_limit"` and `reached` observing 1 genome. No unowned workers observed; desktop state shows "limited" distinctly.
