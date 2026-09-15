# Session stop thresholds

New implementation checkpoint; validation is pending. These optional controls advance [task B6](evolution-tasklist.md#b-ecology-and-run-controls). They stop an experiment without changing birth eligibility, genome execution or prana funding. All default to zero (unlimited).

| Setting / CLI flag | Count observed |
| --- | --- |
| `max_population` / `--max-population` | Registered living bodies |
| `max_genotypes` / `--max-genotypes` | Distinct raw genomes prepared and retained by observation |
| `max_lifecycle_visits` / `--max-lifecycle-visits` | Completed lifecycle dispatches in the session tick loop |

Each setting accepts an integer from 0 to 1,000,000,000. Nonzero thresholds require CLI `--mode session`; other modes reject them rather than silently ignoring them. The desktop and study runner use session mode. Old settings and plans retain unlimited operation.

A threshold fires when its count is **at least** the configured value. Checks occur after session initialization and after each lifecycle visit. For example, `--max-genotypes 1` stops after preparing the single seed genotype, before the first world tick. Counts already above a threshold at initialization stop immediately after initialization. These are boundary stop thresholds, not reservations or guarantees that preparation never exceeds a memory quota.

Population counts bodies, not pending BookEntries. Genotype count includes raw variants even if they decode identically; it does not count IndividualCompile artifacts or measure native cache bytes. Lifecycle visits include births, live execution, reproduction requests and deaths, but exclude founder preparation performed by initialization. One visit may execute many instructions or no instructions. Empty populations can advance CA ticks without using any visits; the configured iteration horizon and study wall timeout remain independent controls.

A birth transaction commits in full before checking limits: exact parent debit and child credit are preserved. Randomness is not drawn by the monitor. A stop can occur partway through the agents scheduled for a tick; subsequent agents do not execute. Results record `last_tick_complete: false` in that case. The iteration counter already includes the current CA update, so it alone cannot establish completion of an entire world tick.

`result.json` contains a `termination` object with reason (`horizon`, `stopped`, or `resource_limit`), configured limits, all reached thresholds and their observed counts, lifecycle-visit count and tick-completion flag. Enabled traces record a `resource_limit` event unless recording has already reached its independent cap or failed. Result metadata remains available even with tracing off. Desktop completion displays the `limited` state and identifies a configured resource stop.

## Studies

Plans may include a shared optional limits object:

```json
"limits": {
  "max_population": 1000,
  "max_genotypes": 100,
  "max_lifecycle_visits": 100000
}
```

These values apply to every declared condition and are saved in its configuration. They are not swept as axes in this checkpoint. A result stopped at a threshold has study status `limited`, retaining the partial result and termination details. Its ecological outcome is unknown: it is neither extinction nor a finite-horizon success. Even a limit reached at the final declared tick is classified as limited. Study reports count it among unknown outcomes and exclude it from successful method comparisons. The runner/report return nonzero when conditions are limited, as they do for other unknown outcomes.

## Implementation and remaining scope

`RunLimits` validates settings; `RunMonitor` observes the Organizer and its prepared-genome registry. Only the sequential session loop uses the monitor. With all limits disabled, threshold checks return immediately; the loop still counts lifecycle visits for reporting. The existing sound shutdown and result-writing paths handle a resource stop normally.

These limits do not preempt a nonreturning source program, interrupt compilation, cap bytes/RSS, constrain log sizes or evict genotypes. The study's existing wall-clock timeout handles a stalled process and its compiler descendants. Aggregate byte/storage limits and pre-initialization admission policies remain future B6 work. No biological carrying-capacity mechanism is implied by these operational stops.

Validation handoff: [resource-limit checks](../.memory/wiki/notes/run-limits-validation.md). No new tests or studies were executed by the implementation session.
