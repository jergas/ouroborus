# Observation checkpoint validation handoff

2026-09-15. Implementation is ready for the separate validation session. **No builds, tests or version-control mutations were performed by the implementation session.** Big Pickle owns those activities; report failures to the user for implementation follow-up, without fixing them unless the user changes that instruction. A1–A5 have code, A6 has written coverage, A7 remains live validation. Checkboxes remain open.

## Changes

- Read-only per-agent inspection in the desktop: compact IDs/centers, overlap cycling, raw and decoded genomes, scheduler state, prana/credits, counters and single-parent lineage. Selected death tombstone retained; stopped runs explicitly show last observation.
- Trace modes off/events/instructions, default off, shared CLI/worker/settings/QML configuration. JSONL streamed to run directory, event count cap plus 64 MiB total and 256 KiB per-event caps. One cap marker is outside event count/byte totals. I/O failures stop recording, not simulation.
- Shared before/after primitive hooks through ObservedMetrics; run-wide and per-agent counters. Lifecycle/transfer records plus effective world settings, seed, initial RNG state and distinct raw/decoded identities.
- Agent-prana ledger: founder/preset inputs, Forager food/cost counters, internal transfers, death removal; source live() signed net change is explicit. Result includes observation ledger and trace summary.

## Suggested validation

1. Run Build and Lint from AGENTS.md. There are no new Cython sources, but native dispatch calls the modified Python scheduler.
2. With the configured native Csound environment, run `.venv/bin/python -m pytest tests/test_observation.py tests/test_execution.py tests/test_forager.py tests/test_desktop.py -q`. Desktop socket/PTY tests may need the previously documented unrestricted environment. Inspect skips and warnings. Then run the full suite if focused checks pass.
3. New observation tests cover caps/write failure, tracing off versus on and unwrapped metrics, RNG preservation, native/interpreted event equality at allowances 1/6 and both energy policies, local/shared counters, selected-death retention without hasEaten(), raw versus decoded identities, and source/transfer ledger arithmetic. The existing real-session comparison now enables full instruction tracing and compares every non-header record, including births/transfers/result ledger, across methods. Header method names and corresponding byte counts intentionally differ.
4. Desktop integration adds trace settings round-trip and real paused inspection: selection must leave tick, cells and ledger unchanged. Grid unit coverage checks centered coordinates and overlapping centers. Existing QML smoke now opens/closes the inspector and still rejects warnings at minimum window size.
5. Manually inspect both Forager execution methods at 800×560 and a larger window: inspector scrolling/readability, white centers and selection outline, overlapping agents, dropdown and typed IDs, raw/decoded text, death retention, save/load (including old JSON files lacking trace fields), pause/step/resume/stop, restart clearing selection and speaker audio. Source Alpha should expose source snippets and net accounting; unavailable instruction fields must be clear. Epsilon should remain agent-free with an empty ledger.
6. Check trace Off creates no events file in a fresh output directory. Use a low cap (e.g. 10) and confirm a limit marker, truncated status in UI/result, and continuing simulation. Inspect an ordinary trace for run/genome/birth/action-or-instruction/live/transfer/result ordering and exact transfer debit=credit. Ensure result ledger residual is zero for both Forager policies and source baseline examples.

## Interpretation and boundaries

- Source net ledger balance does not itemize or prove conservation inside arbitrary source programs. Forager uses current eatMana reward of five prana; update accounting if this primitive changes.
- Instruction events surround primitive/charge execution before scheduler completion/death reset; live records expose final state and published request. Do not compare those two boundaries as if identical.
- Initial RNG state plus metadata is not a resumable checkpoint. Experimental worker ordering remains timing-dependent. Use session mode for deterministic comparisons.
- UI sends at most 1024 center records and one inspection (256 decoded words / 8192 characters per text field). Larger populations remain simulated; ID lookup can address unlisted live agents. World render footprints are deduplicated.
- Trace-off runs still maintain inspection metadata and counters. Processing overhead is expected; no performance claim is made. Population/cache resource policies remain future phase B.
- Check final trace status after stop/normal completion. Abrupt kill can leave an incomplete trace and no result, as with existing run outputs.

Public details: [observability](../../../docs/observability.md). Record findings here, in the log, and update task checkboxes only after relevant validation.

## Validation results (Big Pickle, 2026-09-15)

Commit: `a885f8c` on `forager`. Build: clean (`build_ext --inplace` exit 0, no new Cython sources). Lint: clean (`compileall birdcage worldish tests setup.py .memory/tools` + `git diff --check`). Full suite with local Csound native libraries: **119 passed, 0 failures, 0 skips** (75.5 seconds). Includes real-session compiled/interpreted comparisons, observation trace/Ledger/QML coverage, desktop tests, and existing regressions. A1–A5 implementation and A6 test coverage are validated. A7 (live desktop GUI/audio inspection) remains pending and requires the user's unrestricted environment. Task checkboxes may be updated.

## Ecology study runner validation (Big Pickle, 2026-09-15, same commit basis)

Added worldish.study, experiments/forager-baseline.json and tests/test_study.py after this note was written. Build and lint: clean. Study-focused tests: 5 passed (matrix expansion to 36 conditions, prepare-only manifest without launch, output-dir reuse rejection, duplicate/invalid axis rejection, failed-accounting classification, owned-process cleanup on timeout and interrupt). Tiny-study smoke (one condition: seed 7, interpreted, allowance 2, maintenance, 80 ticks → 10 steps, timeout 60s): completed, population 5, births 5, deaths 0, ledger balance error 0, finite-horizon screen passed. Full 36-condition matrix deferred; the infrastructure is validated. Full regression suite on the same commit: **124 passed** (the 5 new study tests plus 119 pre-existing). No fixes needed. See notes/study-validation.md for the original handoff.

## Closing live review for M2/A7 (2026-09-15)

Pending Big Pickle/user hands-on validation. Earlier automated checks and the earlier audio confirmation do not close this expanded review. Use short Forager runs with both compiled and interpreted methods, at 800×560 and an ordinary larger window. Record revision, method, settings and observed results here.

- Confirm scrolling settings and inspector remain readable and transport remains accessible. Select an agent, inspect raw/decoded state and prana, and check snapshot updates. Paused inspection must not advance the world.
- Save/load execution, energy, placement and resource-limit settings. Exercise pause, single world-tick step, resume, stop and restart; verify draft settings apply to a new run.
- Confirm audible output during running, mute during pause/step, and clean stop. This is an observation of this application, not a general audio diagnosis.
- Exercise both local and random placement choices across the short runs. Set max-genotypes to 1 on a separate short run and confirm a resource-limited result after seed preparation, then restore zero limits for ordinary running. Check the limited state is distinguishable from normal completion.
- Record any visual, settings or transport failures and return them for implementation fixes. If an item cannot be observed, retain it as pending rather than treating automated coverage as a substitute.

Result: pending. On completion update A7/M2 and the [merge handoff](forager-merge-handoff.md).
