# Forager foundations: current status

Status: 2026-09-15. This checkpoint adds a runnable authored Forager and tools for explaining and comparing its behavior. It also includes experimental atomic-codon research. This page supplements the [historical system snapshot](current-evolution-system.md); the [roadmap](evolution-roadmap.md) and [task list](evolution-tasklist.md) retain the remaining work.

## Supported runtime

Agents consume ON cells of the evolving cellular automaton; there is no separate food layer. The Forager specificity uses a toroidal Moore world with an XOR rule. Its six-word program, `Sf Ea Mt Rp Di Rt`, seeks food, eats, pays maintenance, checks reproduction and death, and publishes its lifecycle request. Founders receive 24 prana, the reproduction threshold is 30, and successful offspring transfers debit the parent exactly the child's 12 initial prana. Food consumption supplies five prana. These inputs and expenditures are explicit; conservation of reproduction transfers does not make the whole world energetically closed.

| Choice | Current behavior and default |
| --- | --- |
| Specificity | Select `forager` explicitly; existing specificities remain supported and the CLI still defaults to `alpha`. |
| Genome language | `source` retains source-fragment compilation; Forager selects `forager-v1`. Atomic codons are not a selectable runtime language. |
| Execution | Compilation remains default. Forager also supports interpretation. Both share primitives and scheduling semantics. |
| Instruction allowance | Forager defaults to six instructions per live visit, configurable from 1 to 4096. Source programs do not acquire this bound. |
| Energy policy | Maintenance is default; compute optionally prepays instruction batches with prana. Batch size defaults to six; unused credits persist in the parent and are not inherited. |
| Reproduction | Preset-funded and exact transfer-funded reproduction remain supported. Forager selects transfer. |
| Placement | `policy` is default: local for transfer funding, random for preset funding. Explicit `local` and `random` choices work independently of funding. Overlap is allowed. |
| Observation | Agent inspection and prana accounting are available; optional event/instruction tracing defaults to off. |
| Session limits | Population, prepared raw-genome and lifecycle-visit stop thresholds default to zero, meaning unlimited. |

In `forager-v1`, a live visit executes at most its allowance. An unfinished pass preserves its instruction position and pending request; completion publishes the request and ends the visit. Compute charges include no-ops and return, with explicit zero-prana death boundaries. Empty programs idle without instruction charges. These rules are described in [agent execution](agent-execution.md), with funding in [Forager](forager.md) and placement in [ecology studies](ecology-studies.md).

## Implementation and observation

`worldish.execution` supplies the common scheduler and resource rules. `forager_vm` decodes the bounded six-operation language; compiled genomes dispatch through native modules while interpreted genomes use prepared operation sequences. `GOD` manages lifecycle and funded births, and `placement` resolves offspring coordinates independently of funding. Existing source compilation remains a supported path.

The desktop exposes execution settings, agent selection, raw/decoded genomes, instruction position, pending requests, prana, credits and ancestry. Observation hooks record food, compute, maintenance and transfer activity without consuming audio notifications. Optional JSONL traces are bounded; the prana ledger separates sources, expenditures and internal transfers. See [observation implementation and limits](observability.md).

`study` expands declared plans into isolated session runs; `study_report` preserves failures, missing results and limited outcomes as unknown instead of calling them extinction. Matched final outcomes are not proof of identical full trajectories. `run_limits` checks thresholds after initialization and complete lifecycle dispatches, preserving entire birth transactions. A stop may leave a partial world tick. These controls do not cap memory bytes or preempt a nonreturning source instruction. See [study tooling](ecology-studies.md) and [session limits](run-limits.md).

## Experimental atomic language

The [32-operation proposal](atomic-codon-proposal.md) uses two-character codons over eight provisional bases, with a total redundant 64-codon table. Offline tools measure substitution and recombination geometry and review an [authored 17-codon forager](authored-atomic-forager.md). Measured synonym/family proximity is a property of the table, not a fitness result.

`atomic_state` strictly decodes raw bases under an explicitly pinned candidate hash, preserves synonymous raw identities, and validates independent bounded machine state. It does not execute atomic operations, register a language, or freeze the candidate mapping. Compiled/interpreted atomic execution, runtime synonym equivalence, mutation and sexual reproduction remain future work.

## Evidence and remaining work

The latest implementation checkpoint was validated by the separate validation session: clean build and syntax/whitespace checks, 33 focused tests, and 177 full-suite tests with no failures or skips. That is automated evidence; the expanded live desktop review remains pending. Earlier short Forager runs and execution comparisons do not establish sustained ecological viability. The declared ecology matrices and atomic runtime parity assessment remain uncompleted.

The [closing tasks M1–M3](evolution-tasklist.md#m-minimal-merge-checkpoint) cover this status document, live desktop review and the merge handoff. All later research and implementation tasks remain in place for resumption.
