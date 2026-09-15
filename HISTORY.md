# History

This document preserves the text of work that was removed or restructured from the active evolutionary task list during branch development. It supplements [evolution implementation history](docs/evolution-implementation-history.md) (which captures the validated substance of completed work) and the [active task list](docs/evolution-tasklist.md) (which retains all future work). No history predating this branch is included.

## [Unreleased] - 2026-09-15

### Removed — Phase-based task list restructured to lettered format

Commit `89661f3` replaced the original Phase 1–5 + optional-groups structure in `docs/evolution-tasklist.md` with the current A–G structure. The checked (completed) items were removed entirely from the task list and summarized as foundations in [evolution implementation history](docs/evolution-implementation-history.md). Pending items with clear successors were remapped to the new IDs (see table below). The old text is preserved here verbatim for traceability.

#### Completed tasks (no new ID)

**Phase 1: Create the forager specificity**

- [x] 1.1 Choose a specificity name and add its module following existing `specific_*` conventions.
- [x] 1.2 Define topology, neighborhood, controlled food environment, initial population, initial founder prana and run duration. Specify a changing-CA evaluation configuration separately.
- [x] 1.3 Reserve the forager genome entry point; do not expose a placeholder as a working forager.
- [x] 1.4 Add specificity discovery/validation and selection support to CLI, shared settings and desktop. Remove fixed four-choice assumptions where necessary, including world/population summaries.
- [x] 1.5 Use the existing compiled path and compilation strategy; introduce no interpreter dependency yet.
- [x] 1.6 Validate configuration and no-agent world setup independently of the unfinished genome. Document which behavior becomes available in phase 2.

**Phase 2: Design and code the compiled forager**

- [x] 2.1 Specify a deterministic sensing/turning/movement/feeding policy, with documented seeded randomness where used.
- [x] 2.2 Define the minimal semantic operations and authoritative program representation so the same organism can later be interpreted. Mark their state changes and possible future charge points; do not implement the interpreter yet.
- [x] 2.3 Choose world-owned reproduction eligibility, transfer amount E, placement and occupancy policy. Identify initial-founder allocation separately from offspring funding.
- [x] 2.4 Choose atomic birth-time transfer or reserved prana for delayed lifecycle requests. Specify failed/cancelled births, parent death and insufficient funds before changing lifecycle code.
- [x] 2.5 Implement the reproduction transfer so the parent's debit is exactly the child's initial prana. Prevent a second allocation from specificity defaults and prevent duplicate processing from duplicating energy.
- [x] 2.6 Implement and annotate the compiled forager using those operations. Route energy transfer through shared world policy; avoid a second private reproduction debit in its genome.
- [x] 2.7 Document the phase-2 maintenance/action-cost policy as a baseline, explicitly subject to compute-cost alignment in phase 4. Keep existing specificities on their supported policies.
- [x] 2.8 Connect the genome to the new specificity and run a complete birth/live/reproduction/death lifecycle through CLI and desktop session paths.
- [x] 2.9 Test exact prana balances on successful reproduction and all failure paths, including repeated requests and delayed births. Separate transfer from any additional cost in assertions.
- [x] 2.10 Test sensing, movement, consumption and sequential contention with known cell states.

**Phase 3: Add framework execution-method selection**

- [x] 3.1 Specify and version `execution_method` with compiled/interpreted values; default missing settings to compiled. Finalize public setting/CLI names before exposing them.
- [x] 3.2 Keep `compiling` strain-cache/build strategies independent. Define no-agent behavior and reject unsupported method/genome combinations clearly.
- [x] 3.3 Define a common controller interface for initialization, advance/yield, persistent state, lifecycle requests and cleanup at the `BookEntry` boundary.
- [x] 3.4 Keep existing compiled module execution as a directly supported option; add new execution implementations alongside it, with explicit defaults.
- [x] 3.5 Add an interpreter factory/registration point. Until phase 4 supplies a backend, report interpreted execution as unavailable; never silently fall back to compilation.
- [x] 3.6 Carry execution choice through specificity defaults, CLI overrides, validated desktop settings, worker startup and saved JSON. Define precedence and preserve old settings with no execution field.
- [x] 3.7 Adjust startup messages and result fields to distinguish building genomes from preparing interpreted programs. Preserve meaning/compatibility of existing compilation metrics.
- [x] 3.8 Ensure resource/energy policy is selected independently of execution method and shared with reproduction accounting.
- [x] 3.9 Test default selection, settings round trips, invalid/unavailable methods and compiled baseline behavior. Check that selecting interpretation cannot accidentally start a build.

**Phase 4: Implement the bounded interpreter and align compute accounting**

- [x] 4.1 Finalize instruction semantics: argument types, state changes, branches, loops, missing operands, empty programs, program completion and restart behavior.
- [x] 4.2 Define which execution state persists across ticks and which state is initialized or inherited at birth.
- [x] 4.3 Add validated `instructions_per_tick` or equivalent configuration. Choose its default empirically; 64 is not a requirement. Record the value with results.
- [x] 4.4 Set stack, genome, buffer and numeric limits. Bound or incrementally meter searches/copies and nested operations. Define limit-hit behavior without partial effects.
- [x] 4.5 Design a prana-per-computation policy as a candidate replacement for the flat per-live-call debit. Define chargeable semantic operations, no-op/branch costs, insufficient-funds handling, zero-prana/death timing and action costs without double charging.
- [x] 4.6 Choose integer scaling, batch charging or fractional-debt representation if necessary. Preserve exact reproduction transfer and specify rounding/debt inheritance explicitly.
- [x] 4.8 Implement the Python reference interpreter and its per-agent resumable state. Route sensing/actions through the common world interface; do not execute arbitrary generated source as interpretation.
- [x] 4.9 Adapt the compiled forager's generation/execution path to the same semantic charge points and, where required, resumable scheduling. Native instruction counts and wall-clock time are not equivalent billing units.
- [x] 4.10 Remove/disable the old routine energy debit for both forager paths when evaluating the replacement policy. Keep a clearly selected historical control policy rather than applying both unintentionally.
- [x] 4.11 Implement shared metrics for semantic operations, charges, yields, limit hits, food intake and offspring transfers.
- [x] 4.12 Test infinite loops, stack growth, invalid operations, numeric edges and expensive instructions; confirm bounded work and continued world progress. Report implementation defects separately from defined genome outcomes.
- [x] 4.13 Compare compiled/interpreted action traces, RNG evolution, prana, lifecycle events and grid states for the same forager across a declared seed set and multiple instruction allowances.
- [x] 4.16 Document supported genomes, settings and resource policy. Record the selected interpreter/energy decisions and experimental results in memory.

#### Optional tasks (removed, remapped to A–G)

**Inspection and replay**

- [ ] Add stable agent identities and an inspector for program, execution state, prana and ancestry.
- [ ] Extend snapshots selectively without sending every genome each frame.
- [ ] Add complete checkpoints with grid, agents, pending births/transfers, RNG, execution state and configuration versions.
- [ ] Compare resumed runs against uninterrupted execution; distinguish instruction debugging from world-tick transport.

**Ecology and offspring construction**

- [ ] Compare food regeneration, local/global placement, scheduling conflicts and alternative energy policies under controls.
- [ ] Explore communication, predation or cooperation with explicit observable mechanisms.
- [ ] Add bounded offspring-code buffers and copy/edit operations if organism-controlled reproduction is pursued.
- [ ] Write a seed replicator, enforce funded finalization, then study mutation of replication machinery separately from world-imposed mutation.

**Alternative machines and scale**

- [ ] Measure CA, execution, rendering, snapshot and audio costs separately.
- [ ] Optimize measured hotspots in Cython and check behavior against reference traces.
- [ ] Explore compact/shared immutable genomes and an alternative register or regulatory backend when useful.
- [ ] Define conflict resolution before parallel execution; define checkpoint/version/migration semantics before distributed populations.

#### Pending tasks with new IDs

| Old ID | Task | New ID(s) |
| --- | --- | --- |
| 2.11 | Select seed set, duration and viability thresholds before evaluation | B1 |
| 2.12 | Record baseline genome, configuration, action trace, energy balances and birth/death results | A3–A6, B5 |
| 4.7 | Define halted/idle-agent policy and population/run limits | B3, B6 |
| 4.14 | Repeat viability study under compute charging | B1–B7 |
| 4.15 | Enable interpreted selection once available; verify desktop pause/step/stop, snapshots and audio | A7 |
| 5.1 | Specify mutation rates and substitution/insertion/deletion behavior | E1, E6, E7 |
| 5.2 | Add mutation at reproduction and record instance ID, strain/genome identity, parent ID, generation | E1, E2 |
| 5.3 | Save initial conditions, RNG/configuration and language versions sufficient to reproduce runs | A4, G1 |
| 5.4 | Compare mutation-enabled and no-mutation runs on the same declared seed set | E3, E4 |
| 5.5 | Track feeding, motion, lifetime, offspring count, genome diversity and extinction; re-evaluate descendants | B5, E5 |

### Deprecated — Historical versioning scheme

The project historically used informal tarball version numbers (`0.0.1`, `0.0.2`, `0.1.0`, `0.2`) and a declared `1.0.0` stable release for Birdcage, embedded in `pyproject.toml`. No CHANGELOG, release notes or git tags have ever been maintained. The SVN-era revision numbers (r0–r395) served as a de facto history via `git-svn-id` trailers but had no semantic meaning. The `Version Numbering` section of the old `guidelines.html` was a placeholder left blank. This is preserved for context; the branch follows no formal release or versioning discipline yet.

## Versioning notes

### Historical scheme

Ouroborus and its Birdcage predecessor did not maintain a formal versioning scheme. The observable history:

- **SVN revisions (r0–r395):** Commit-level numbering, retained in `git-svn-id` trailers after migration. No semantic versioning; no trunk/branches/tags convention.
- **Tarball filenames:** `ouroborus_0.0.1.zip`, `ouroborus_0.0.2.zip`, `ouroborus_0.1.0.zip`, `ouroborus0.2.tgz` — published to the project website without corresponding git tags or release discipline.
- **Birdcage 0.5.5 → 1.0.0:** A declared stable release (`9e51dc0`), updated in `pyproject.toml` as `version = "1.0.0"`. This was the only version bump that touched a machine-readable field.
- **No changelog file** exists in the entire git history. The `website/downloads.html` page served as a minimal download index, not a release log.
- **No git tags** have ever been created.
- **`worldish/protocol.py` VERSION = 1:** An internal wire-format marker, unrelated to release versioning.

### Observations

The versioning was ad-hoc and file-name-based, with no separation between "what changed in this release" and "where can I download it." The Birdcage 1.0.0 declaration was aspirational — the project continued active development without subsequent releases. The ouroborus pyproject kept `1.0.0` without any release mechanism, making it a static label rather than a versioning system.

### Future directions

The branch has now accumulated enough discrete, validated checkpoints (compiled forager, execution methods, observation, study runner, placement reports, session limits, codon design, authored forager, atomic decoder) to justify a lightweight versioning and release discipline. A natural approach:

- Adopt [Semantic Versioning](https://semver.org/) with `pyproject.toml` as the single source of truth, or consider CalVer given the project's research pace.
- Create lightweight git tags for validated checkpoints — the commit hash is already the effective version, tags would just make them discoverable.
- Maintain `HISTORY.md` (this file) in [Keep a Changelog](https://keepachangelog.com/) format, with a `[Unreleased]` section for in-progress work and dated sections for tagged checkpoints.
- Resist premature release automation; the value is in recording what changed and when, not in distribution packaging.
