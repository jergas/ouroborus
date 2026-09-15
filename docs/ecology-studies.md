# Declared ecology studies

Implementation checkpoint; tests and execution of the study are pending. This supplies tooling for [tasks B1–B3 and B5](evolution-tasklist.md#b-ecology-and-run-controls), not completed ecological findings.

Run from the repository root with the usual native Csound environment from AGENTS.md, even when audio output is disabled:

```sh
.venv/bin/python -m worldish.study --plan experiments/forager-baseline.json \
  --output-dir .worldish/study-preview --prepare-only
.venv/bin/python -m worldish.study --plan experiments/forager-baseline.json \
  --output-dir .worldish/study-baseline
```

Use a fresh output directory each time. Prepare-only writes a reviewable manifest and launches nothing; execution requires another fresh directory. The runner never overwrites an earlier study or silently resumes it.

The initial plan declares 36 conditions: seeds 7/42/99, compiled/interpreted methods, instruction allowances 1/2/6, maintenance/compute policies and a compute batch of six. Each runs for 80 world ticks on the evolving Forager XOR environment. On cells remain food; placement and reproduction policies are unchanged. Edit a copy of the plan to compare compute prices or longer horizons. Price has no effect under maintenance, so avoid interpreting repeated maintenance conditions at different prices as independent replicates.

The finite-horizon screen requires completion, consistent population accounting, a zero prana-ledger residual, at least one final living agent and generation two or greater. These thresholds are declared in the plan before any run. They establish neither indefinite survival nor adaptation. Larger studies must explicitly split into batches (maximum 256 conditions per invocation).

`manifest.json` records the exact plan, expanded configs, source-content digest and Python version before launching the first simulation. The digest covers Python/Cython/interface sources in worldish and birdcage; it is not a full dependency lock or native-binary fingerprint. Retain the checkout and environment alongside results for reproduction.

Each run has its own numbered directory, subprocess and event trace. `outcomes.jsonl` streams full result records, configs, status, elapsed time and screen outcome. Results retain population, births/deaths, generation depth, food intake, energy expenditure, transfers and trace truncation/error status. A failed run, invalid result or wall-clock timeout has an unknown ecological outcome and is never classified as extinction. The runner continues after those failures and exits nonzero if any condition failed. Completed runs that fail the biological screen still count as completed experiments.

The wall-clock timeout includes initialization and compilation, so it is an operational limit, not an ecological death rule or a fair speed benchmark. The Linux runner owns a process group per condition and kills/reaps it on timeout or interruption, including compiler descendants. Interruption may leave a manifest condition without an outcome; treat missing outcomes as unknown. Logs/results already written remain available. Event traces retain their existing limits; launcher/debug logs and simulation population/cache sizes are not bounded by this runner. Resource-policy task B6 remains open.

Compare paired seeds across methods and examine failures before aggregating successful runs. The tool preserves raw results rather than automatically asserting equivalence or discarding failed conditions. Keep the initial 80-tick study as a baseline, then declare longer horizons and additional seed sets before assessing sustained viability. No study has been run as part of this implementation checkpoint.
