# Declared ecology studies

The initial runner passed five tests and a tiny real-run smoke in the separate validation session (124 full-suite tests, no skips). The baseline study remains unrun. Placement options and outcome reporting are a new checkpoint awaiting validation. This supplies tooling for [tasks B1–B3 and B5](evolution-tasklist.md#b-ecology-and-run-controls), not completed ecological findings.

Run from the repository root with the usual native Csound environment from AGENTS.md, even when audio output is disabled:

```sh
.venv/bin/python -m worldish.study --plan experiments/forager-baseline.json \
  --output-dir .worldish/study-preview --prepare-only
.venv/bin/python -m worldish.study --plan experiments/forager-baseline.json \
  --output-dir .worldish/study-baseline
```

Use a fresh output directory each time. Prepare-only writes a reviewable manifest and launches nothing; execution requires another fresh directory. The runner never overwrites an earlier study or silently resumes it.

The initial plan declares 36 conditions: seeds 7/42/99, compiled/interpreted methods, instruction allowances 1/2/6, maintenance/compute policies and a compute batch of six. Each runs for 80 world ticks on the evolving Forager XOR environment. On cells remain food; the default placement and reproduction policies are retained. Edit a copy of the plan to compare compute prices or longer horizons. Price has no effect under maintenance, so avoid interpreting repeated maintenance conditions at different prices as independent replicates.

The finite-horizon screen requires completion, consistent population accounting, a zero prana-ledger residual, at least one final living agent and generation two or greater. These thresholds are declared in the plan before any run. They establish neither indefinite survival nor adaptation. Larger studies must explicitly split into batches (maximum 256 conditions per invocation).

`manifest.json` records the exact plan, expanded configs, source-content digest and Python version before launching the first simulation. The digest covers Python/Cython/interface sources in worldish and birdcage; it is not a full dependency lock or native-binary fingerprint. Retain the checkout and environment alongside results for reproduction.

Each run has its own numbered directory, subprocess and event trace. `outcomes.jsonl` streams full result records, configs, status, elapsed time and screen outcome. Results retain population, births/deaths, generation depth, food intake, energy expenditure, transfers and trace truncation/error status. A failed run, invalid result or wall-clock timeout has an unknown ecological outcome and is never classified as extinction. The runner continues after those failures and exits nonzero if any condition failed. Completed runs that fail the biological screen still count as completed experiments.

The wall-clock timeout includes initialization and compilation, so it is an operational limit, not an ecological death rule or a fair speed benchmark. The Linux runner owns a process group per condition and kills/reaps it on timeout or interruption, including compiler descendants. Interruption may leave a manifest condition without an outcome; treat missing outcomes as unknown. Logs/results already written remain available. Event traces retain their existing limits; launcher/debug logs and simulation population/cache sizes are not bounded by this runner. Resource-policy task B6 remains open.

Compare paired seeds across methods and examine failures before aggregating successful runs. The tool preserves raw results rather than automatically asserting equivalence or discarding failed conditions. Keep the initial 80-tick study as a baseline, then declare longer horizons and additional seed sets before assessing sustained viability. No study has been run as part of this implementation checkpoint.

## Offspring placement comparison

`offspring_placement` is independent of funding and supports `policy` (default), `local`, and `random`. Policy resolves to local for transfer funding and random for preset funding, preserving existing behavior and RNG draw counts. Local places a child on the parent's current cell. Random samples each coordinate uniformly across the whole world, using two coordinate draws. Both permit overlaps and food contention; neither searches for vacancies or adds a movement cost. Epsilon has no offspring, so placement has no effect there.

Select **Offspring placement** in the desktop or pass `--offspring-placement local|random|policy` to the CLI. Old settings load as policy. CLI omission permits a specificity-defined choice; explicit policy selects the funding policy's default. Founders retain their existing placement. Result metadata and trace run headers identify requested and effective choices.

Exact parent debit equals child prana for either transfer placement. Insufficient funds are rejected before drawing a position. If preparation later fails, the parent is not charged, but any already-drawn random position has consumed RNG state; rollback does not rewind randomness. Preset funding retains its existing energy rules.

The optional study-plan `placements` axis defaults to `["policy"]`. `experiments/forager-placement.json` declares the 72-condition local/random comparison using the baseline seeds, methods, allowances and energy policies. Do not run it in the baseline output directory. Different placement policies consume different randomness: matching seeds define paired initial conditions, not identical subsequent random trajectories.

## Outcome reports

```sh
.venv/bin/python -m worldish.study_report .worldish/study-baseline > .worldish/study-baseline-report.json
```

This reads existing artifacts without launching simulations or changing them. The JSON report retains every declared condition, aggregates across seeds within otherwise identical configurations, and counts completed, unknown, surviving, extinct and screen-passing cases separately. Screen results are recomputed from the declared thresholds and result accounting. Unknown outcomes are not included in the extinction count or treated as successful trials.

Within each seed/configuration, the report compares compiled and interpreted final result data, excluding execution metadata, compiled/interpreted genotype counters and trace bookkeeping. It retains ecological counters, energy ledger, transfer and placement results. Equality is only final-outcome equality, not full trace or trajectory equivalence. Trace comparisons remain separate validation. An unpaired single-method plan is labelled accordingly; it is not a failed comparison.

Missing outcomes, failed runs, timeouts and invalid completed results remain unknown. Duplicate/undeclared outcomes or configurations inconsistent with the manifest are rejected. An interrupted last JSONL record without a terminating newline is reported as an incomplete tail; malformed earlier records are errors. Prepare-only studies report every condition missing. Exit status is nonzero for unknown outcomes or method differences; a completed biological screen failure alone does not make report generation fail.

The report does not provide statistical significance or claim adaptation. Further work includes declared longer-horizon studies, aggregate simulation resource policies (B6), and validation of the authored forager against those criteria (B7). These tools do not enable mutations or freeze a codon mapping.
