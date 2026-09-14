# Evolutionary implementation task list

Status: planned, 2026-09-14. All tasks are pending unless checked. Follow phases 1–4 in order. Optional later branches can proceed independently once their dependencies are met. The [roadmap](evolution-roadmap.md) explains the concepts and open choices; the [current baseline](current-evolution-system.md) documents existing behavior. The compiled forager checkpoint is documented in [forager.md](forager.md); interpretation remains pending.

Checkpoint: phases 1 and the core compiled behavior/transfer in phase 2 are implemented. Session runs pass; full desktop live validation, declared ecological studies and complete trace capture remain unchecked. The initial condition is an evolving XOR CA; static cells are used only in focused tests.

## Phase 1: Create the forager specificity

Purpose: establish the new organism's configuration before writing its behavior. See [roadmap: direction and order](evolution-roadmap.md#direction-and-order).

- [x] 1.1 Choose a specificity name and add its module following existing `specific_*` conventions.
- [x] 1.2 Define topology, neighborhood, controlled food environment, initial population, initial founder prana and run duration. Specify a changing-CA evaluation configuration separately.
- [x] 1.3 Reserve the forager genome entry point; do not expose a placeholder as a working forager.
- [x] 1.4 Add specificity discovery/validation and selection support to CLI, shared settings and desktop. Remove fixed four-choice assumptions where necessary, including world/population summaries.
- [x] 1.5 Use the existing compiled path and compilation strategy; introduce no interpreter dependency yet.
- [ ] 1.6 Validate configuration and no-agent world setup independently of the unfinished genome. Document which behavior becomes available in phase 2.

Completion: the specificity can construct its intended world and its pending organism is clearly identified. Phase 2 supplies the working seed program.

## Phase 2: Design and code the compiled forager

Purpose: obtain a viable organism with correct energy transfer using today's execution method. See [roadmap: one organism, two methods](evolution-roadmap.md#one-organism-two-execution-methods) and [reproduction energy](evolution-roadmap.md#foraging-and-reproduction-energy).

- [x] 2.1 Specify a deterministic sensing/turning/movement/feeding policy, with documented seeded randomness where used.
- [x] 2.2 Define the minimal semantic operations and authoritative program representation so the same organism can later be interpreted. Mark their state changes and possible future charge points; do not implement the interpreter yet.
- [x] 2.3 Choose world-owned reproduction eligibility, transfer amount E, placement and occupancy policy. Identify initial-founder allocation separately from offspring funding.
- [x] 2.4 Choose atomic birth-time transfer or reserved prana for delayed lifecycle requests. Specify failed/cancelled births, parent death and insufficient funds before changing lifecycle code.
- [x] 2.5 Implement the reproduction transfer so the parent's debit is exactly the child's initial prana. Prevent a second allocation from specificity defaults and prevent duplicate processing from duplicating energy.
- [x] 2.6 Implement and annotate the compiled forager using those operations. Route energy transfer through shared world policy; avoid a second private reproduction debit in its genome.
- [x] 2.7 Document the phase-2 maintenance/action-cost policy as a baseline, explicitly subject to compute-cost alignment in phase 4. Keep existing specificities on their supported policies.
- [ ] 2.8 Connect the genome to the new specificity and run a complete birth/live/reproduction/death lifecycle through CLI and desktop session paths.
- [x] 2.9 Test exact prana balances on successful reproduction and all failure paths, including repeated requests and delayed births. Separate transfer from any additional cost in assertions.
- [x] 2.10 Test sensing, movement, consumption and sequential contention with known cell states.
- [ ] 2.11 Select seed set, duration and viability thresholds before evaluation. Demonstrate multiple generations in controlled food conditions and report survival/extinction in changing CA conditions.
- [ ] 2.12 Record baseline genome, configuration, action trace, energy balances and birth/death results for comparison after interpretation is implemented.

Completion: the compiled forager feeds and reproduces with exact offspring funding. No interpreted run is required yet, but the behavior's representation and semantics support the later second execution method.

## Phase 3: Add framework execution-method selection

Purpose: add the architecture before implementing the new interpreter. See [roadmap: execution methods](evolution-roadmap.md#one-organism-two-execution-methods).

- [ ] 3.1 Specify and version `execution_method` with compiled/interpreted values; default missing settings to compiled. Finalize public setting/CLI names before exposing them.
- [ ] 3.2 Keep `compiling` strain-cache/build strategies independent. Define no-agent behavior and reject unsupported method/genome combinations clearly.
- [ ] 3.3 Define a common controller interface for initialization, advance/yield, persistent state, lifecycle requests and cleanup at the `BookEntry` boundary.
- [ ] 3.4 Keep existing compiled module execution as a directly supported option; add new execution implementations alongside it, with explicit defaults.
- [ ] 3.5 Add an interpreter factory/registration point. Until phase 4 supplies a backend, report interpreted execution as unavailable; never silently fall back to compilation.
- [ ] 3.6 Carry execution choice through specificity defaults, CLI overrides, validated desktop settings, worker startup and saved JSON. Define precedence and preserve old settings with no execution field.
- [ ] 3.7 Adjust startup messages and result fields to distinguish building genomes from preparing interpreted programs. Preserve meaning/compatibility of existing compilation metrics.
- [ ] 3.8 Ensure resource/energy policy is selected independently of execution method and shared with reproduction accounting.
- [ ] 3.9 Test default selection, settings round trips, invalid/unavailable methods and compiled baseline behavior. Check that selecting interpretation cannot accidentally start a build.

Completion: compiled runs remain the default and work through the new interface. Interpretation has an explicit configuration/dispatch path but remains unavailable until its implementation passes phase 4.

## Phase 4: Implement the bounded interpreter and align compute accounting

Purpose: run the same forager under both execution methods. See [roadmap: bounded execution and metabolism](evolution-roadmap.md#bounded-execution-and-computation-as-metabolism).

- [ ] 4.1 Finalize instruction semantics: argument types, state changes, branches, loops, missing operands, empty programs, program completion and restart behavior.
- [ ] 4.2 Define which execution state persists across ticks and which state is initialized or inherited at birth.
- [ ] 4.3 Add validated `instructions_per_tick` or equivalent configuration. Choose its default empirically; 64 is not a requirement. Record the value with results.
- [ ] 4.4 Set stack, genome, buffer and numeric limits. Bound or incrementally meter searches/copies and nested operations. Define limit-hit behavior without partial effects.
- [ ] 4.5 Design a prana-per-computation policy as a candidate replacement for the flat per-live-call debit. Define chargeable semantic operations, no-op/branch costs, insufficient-funds handling, zero-prana/death timing and action costs without double charging.
- [ ] 4.6 Choose integer scaling, batch charging or fractional-debt representation if necessary. Preserve exact reproduction transfer and specify rounding/debt inheritance explicitly.
- [ ] 4.7 Define halted/idle-agent policy and population/run limits. Keep a hard scheduling bound independent of energy prices, including zero-price configurations.
- [ ] 4.8 Implement the Python reference interpreter and its per-agent resumable state. Route sensing/actions through the common world interface; do not execute arbitrary generated source as interpretation.
- [ ] 4.9 Adapt the compiled forager's generation/execution path to the same semantic charge points and, where required, resumable scheduling. Native instruction counts and wall-clock time are not equivalent billing units.
- [ ] 4.10 Remove/disable the old routine energy debit for both forager paths when evaluating the replacement policy. Keep a clearly selected historical control policy rather than applying both unintentionally.
- [ ] 4.11 Implement shared metrics for semantic operations, charges, yields, limit hits, food intake and offspring transfers.
- [ ] 4.12 Test infinite loops, stack growth, invalid operations, numeric edges and expensive instructions; confirm bounded work and continued world progress. Report implementation defects separately from defined genome outcomes.
- [ ] 4.13 Compare compiled/interpreted action traces, RNG evolution, prana, lifecycle events and grid states for the same forager across a declared seed set and multiple instruction allowances.
- [ ] 4.14 Repeat the viability study under compute charging. Compare with phase-2 results and resolve food-income/computation-cost balance without silently relaxing reproduction conservation.
- [ ] 4.15 Enable interpreted selection once available; verify desktop pause/step/stop, snapshots and audio integration in both methods. Single-step remains a world tick.
- [ ] 4.16 Document supported genomes, settings and resource policy. Record the selected interpreter/energy decisions and experimental results in memory.

Completion: one authored forager runs both compiled and interpreted with reproducible, equivalent specified semantics. Compilation is still the default. Instruction allowances are configurable; computation charging is evaluated and its selected policy documented.

## Phase 5: Heritable variation

Depends on phase 4. See [roadmap: subsequent directions](evolution-roadmap.md#subsequent-and-optional-directions).

- [ ] 5.1 Specify mutation rates and substitution/insertion/deletion behavior, including length limits and empty genomes.
- [ ] 5.2 Add mutation at reproduction and record instance ID, strain/genome identity, parent ID, generation and mutation events.
- [ ] 5.3 Save initial conditions, RNG/configuration and language versions sufficient to reproduce runs.
- [ ] 5.4 Compare mutation-enabled and no-mutation runs on the same declared seed set. Distinguish executable, surviving and reproducing mutants.
- [ ] 5.5 Track feeding, motion, lifetime, offspring count, genome diversity and extinction. Re-evaluate selected descendants in comparable environments before claiming adaptation.

Completion: heritable differences and their consequences are inspectable and reproducible; adaptive improvement is an experimental finding, not an assumed outcome.

## Optional task groups

These extend the [roadmap's optional directions](evolution-roadmap.md#subsequent-and-optional-directions), not the required sequence above.

### Inspection and replay

Depends on phase 4; ancestry views additionally depend on phase 5.

- [ ] Add stable agent identities and an inspector for program, execution state, prana and ancestry.
- [ ] Extend snapshots selectively without sending every genome each frame.
- [ ] Add complete checkpoints with grid, agents, pending births/transfers, RNG, execution state and configuration versions.
- [ ] Compare resumed runs against uninterrupted execution; distinguish instruction debugging from world-tick transport.

### Ecology and offspring construction

Depends on phase 5 and trustworthy energy/lineage records.

- [ ] Compare food regeneration, local/global placement, scheduling conflicts and alternative energy policies under controls.
- [ ] Explore communication, predation or cooperation with explicit observable mechanisms.
- [ ] Add bounded offspring-code buffers and copy/edit operations if organism-controlled reproduction is pursued.
- [ ] Write a seed replicator, enforce funded finalization, then study mutation of replication machinery separately from world-imposed mutation.

### Alternative machines and scale

Profiling can begin after phase 2; cross-method optimization follows phase 4.

- [ ] Measure CA, execution, rendering, snapshot and audio costs separately.
- [ ] Optimize measured hotspots in Cython and check behavior against reference traces.
- [ ] Explore compact/shared immutable genomes and an alternative register or regulatory backend when useful.
- [ ] Define conflict resolution before parallel execution; define checkpoint/version/migration semantics before distributed populations.

## Completion and validation discipline

Check tasks only when their stated behavior is implemented and validated. For implementation work, run focused semantic tests and the repository Build/Test/Lint commands; inspect audio skips before claiming native-audio coverage. Documentation changes require local-link and whitespace checks. Keep machine-specific troubleshooting in memory unless necessary for public reproducibility.
