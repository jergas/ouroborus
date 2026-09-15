# Evolution implementation history

Recorded 2026-09-15. This document collects completed foundations from the original roadmap/task list. The [active roadmap](evolution-roadmap.md) and [active tasks](evolution-tasklist.md) contain future work. Current operational details live in [Forager](forager.md) and [agent execution](agent-execution.md).

## Foundation 1: Forager specificity and compiled organism

The Forager specificity was added to CLI, shared configuration and desktop selection. It uses an evolving XOR cellular automaton whose on cells are food. The authored program senses food, moves, eats, pays maintenance and requests reproduction/death through the existing lifecycle.

A new transfer reproduction policy funds a child with exactly the parent's prana debit, while preset-funded reproduction remains a supported default option for existing specificities. Children receive 12 prana in the initial Forager configuration. Preparation failures do not debit the parent, and transferred births record parent/generation metadata and run-wide transfer totals.

The initial source vocabulary remains available as a supported execution option. This milestone corresponds to original tasks 1.1–1.6 and 2.1–2.10. Broader ecological studies and complete observation were not completed merely by establishing a working seed organism.

Validation recorded in project memory: Build and Lint passed; full suite 94 passed with no skips. An initial 80-tick seed-42 debug run reached generation eight and reported 884 births including three founders, with 10,572 prana transferred to 881 offspring. These are dated checkpoint results, not a general viability claim.

## Foundation 2: Execution methods and bounded forager VM

Added compiled/interpreted method selection with compilation as the default. Both forager-v1 methods use the same six operations, resource scheduler and energy semantics. The compiled path specializes opcode dispatch; the shared primitives and scheduler remain Python. Interpreted strains require no generated native genome modules.

Per-organism state preserves execution position, pending request and prepaid compute credits across budget yields. The allowance is configurable, initially six instructions per live visit. Maintenance remains supported; optional compute charging prepays a configurable instruction batch with one prana. Offspring do not inherit prepaid credit. Settings and worker transport carry the selected options; results report execution settings and metrics.

This milestone covers original phase 3 and the initial six-op portions of phase 4. It does **not** implement general branching, stacks, arithmetic, mutation, sexual reproduction or aggregate population/strain limits. Earlier broadly worded checkboxes about loop/stack safety must not be read as validation of features the initial VM lacks.

Validation recorded on 2026-09-14 by the separate validation session:

- Build and Lint passed; focused execution/forager suite: 20 passed.
- Full suite with local Csound: 108 passed, no skips.
- Exploratory matrix: 36 runs across seeds 7/42/99, allowances 1/2/6, both energy policies and both execution methods, at 80 ticks.
- All runs succeeded, no extinction was observed, and corresponding compiled/interpreted population, birth/death and transfer counters agreed. Interpreted runs emitted no native artifacts.

See [execution validation notes](../.memory/wiki/notes/execution-validation.md) for the recorded handoff and results. Desktop live validation of both methods and declared longer ecological studies remain active work.

## Outstanding work carried forward

Old task IDs are retained here for traceability; new IDs belong to the active task list.

| Previous unfinished work | New location |
| --- | --- |
| 2.11 and 4.14: declared viability studies | [B1–B7](evolution-tasklist.md#b-ecology-and-run-controls) |
| 2.12: full baseline traces and energy records | [A3–A6](evolution-tasklist.md#a-observability) and B5 |
| 4.7: idle policies and aggregate resource limits | [B3 and B6](evolution-tasklist.md#b-ecology-and-run-controls) |
| 4.15: desktop live verification of both methods | [A7](evolution-tasklist.md#a-observability) |
| Phase 5: variation and lineages | [C–E](evolution-tasklist.md#c-atomic-language-and-codon-design), now preceded by explicit codon design |
| Optional inspection/replay | [A](evolution-tasklist.md#a-observability) and [G1](evolution-tasklist.md#g-optional-developments) |
| Optional ecology, construction and scale | [B](evolution-tasklist.md#b-ecology-and-run-controls) and [G](evolution-tasklist.md#g-optional-developments) |

Within-codon sexual reproduction is now explicit future work in [F](evolution-tasklist.md#f-sexual-reproduction); its mapping implications are considered earlier in C.

## Observation and declared-study infrastructure, 2026-09-15

Big Pickle recorded Build/Lint clean and 119 passing tests, no skips, for observation tasks A1–A6. Source/Forager inspection, passive traces, energy accounting and method comparisons are validated at that checkpoint. A7 manual GUI/audio review remains active.

The declared study runner then passed five additional tests (124 total, no skips) and a ten-tick interpreted smoke with population5, generation1 and zero prana residual. The full 36-condition baseline was deferred. This validates infrastructure, not the baseline viability screen or sustained survival. See the [active ecology work](evolution-tasklist.md#b-ecology-and-run-controls) and [study documentation](ecology-studies.md). Later placement/report code is a separate, unvalidated checkpoint.
