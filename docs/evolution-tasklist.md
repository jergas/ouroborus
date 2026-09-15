# Active evolutionary task list

Agreed plan, 2026-09-15. All unchecked tasks are pending. Follow A–E as the core route; consider recombination during C and implement mating in F after the codon forager and lineage machinery exist. The [roadmap](evolution-roadmap.md) explains the concepts. Completed foundations are in [implementation history](evolution-implementation-history.md); this document retains their unfinished follow-ups.

## A. Observability

See [roadmap: direction and order](evolution-roadmap.md#direction-and-order).

2026-09-15 validation: Big Pickle recorded a clean build/lint and 119 passing tests without skips for A1–A6. A7 live GUI/audio review remains pending. Later placement/report changes require their own validation. See [observation implementation and limits](observability.md) and the [validation handoff](../.memory/wiki/notes/observability-validation.md).

- [x] A1 Add stable agent IDs to snapshots and selection without transmitting every genome every frame.
- [x] A2 Add an inspector showing raw genome, decoded words/instructions, execution position, pending request, prana, compute credits, parent and generation. Later extend it to two parents and bounded VM memory.
- [x] A3 Add optional bounded or streamed event traces for food consumption, motion, executed instructions, energy charges, lifecycle requests, rejected births and completed offspring transfers.
- [x] A4 Record configuration, RNG seed/state as appropriate, genome, language/mapping version and scheduling policy with traces. Keep instance, raw-genome and decoded-program identity distinct.
- [x] A5 Add energy accounting that explains founder input, food intake, maintenance/compute expenditure, reproduction transfer and energy removed on death. Do not label reproduction transfers as creation or consumption of total agent energy.
- [x] A6 Verify observation does not alter simulation/RNG behavior and compare compiled/interpreted traces at equivalent execution boundaries.
- [ ] A7 Complete live desktop validation of both methods: minimum-window layout, save/load, pause/step/stop, snapshots and audio. Keep world-tick stepping distinct from future instruction debugging.

Completion: the execution and prana history of selected organisms can be explained and compared across methods. Full resumable checkpoints are not required here.

## B. Ecology and run controls

New checkpoint: [declared study runner](ecology-studies.md) supplies manifests, isolated runs and failure-preserving outcomes for B1–B3/B5. The initial runner passed its five tests and a tiny real-run smoke; the 36-condition study remains pending. New placement options and paired outcome reports are implemented but await validation. No viability conclusion is implied.

See [roadmap: supported foundations](evolution-roadmap.md#supported-foundations). The evolving CA's on cells remain food; static arrangements are focused test fixtures only.

- [x] B1 Declare seed sets, run duration, viability criteria and comparisons before evaluating outcomes. Use the recorded 36-run matrix as prior exploratory evidence, not a substitute for the new study.
- [ ] B2 Evaluate instruction allowances, especially cases where sensing and eating fall on different CA ticks.
- [ ] B3 Compare maintenance and compute pricing, zero-prana boundaries, prepaid credits and idle organisms. Keep these as supported policy choices with explicit defaults.
- [ ] B4 Compare parent-local offspring placement with a separately selected alternative, documenting overlap and food contention.
- [ ] B5 Record survival/extinction, generation depth, intake, expenditure and reproductive success; retain failed runs and baseline traces.
- [ ] B6 Specify and implement population, strain-cache and total-run resource policies. Distinguish stopping an experiment at a limit from changing birth eligibility; report all limit events. [Session stop thresholds](run-limits.md) passed the separate validation checkpoint (144 full-suite tests, no skips); byte/storage and pre-initialization controls remain open.
- [ ] B7 Complete or revise the forager viability assessment using the declared criteria, preserving exact offspring funding throughout.

Completion: environmental and scheduling effects are observable enough to interpret later genetic experiments. More appropriate CA rules can be introduced as additional specificities or options.

## C. Atomic language and codon design

A [concrete 32-instruction proposal](atomic-codon-proposal.md), total 64-codon candidate table and offline substitution/recombination analyzer now support this phase. They are not a frozen language or a runtime implementation. Analysis execution, validation and design review remain pending; ecological evaluation continues separately.

See [roadmap: bases and instructions](evolution-roadmap.md#bases-codons-and-instructions), [no-ops](evolution-roadmap.md#no-ops-and-silent-variation) and [recombination](evolution-roadmap.md#recombination-within-codons).

- [ ] C1 Draft a small atomic instruction set: separate sensing, comparison, turning, movement, feeding, reproduction request, bounded memory and control flow. Avoid hiding a foraging strategy in one operation.
- [ ] C2 Specify stack/register types, capacity, arithmetic bounds, missing operands/targets, branching, completion, resume behavior and initial offspring state. Choose a concrete machine model rather than implementing several at once.
- [ ] C3 Specify finite work and prana charge points for every operation in both execution methods, including no-ops and control flow.
- [ ] C4 Retain two-character codons. Evaluate eight bases, provisionally A–H, as the starting alphabet giving 64 words; finalize symbols and instruction count before freezing a mapping.
- [ ] C5 Construct a total redundant table assigning every possible codon to one instruction. Allocate a modest, explicit no-op group; evaluate its size rather than using no-op as an unspecified fallback.
- [ ] C6 Define the single-base substitution model, including probabilities and any position/base biases. Enumerate all transitions and verify synonym connectivity and related-operation neighborhoods.
- [ ] C7 Measure silent/related/other transition proportions and compare with shuffled mappings preserving redundancy. Document the semantic-distance heuristic and its limits.
- [ ] C8 Enumerate within-codon recombinations for parental codon pairs, including synonymous pairs. Compare fixed parental roles and randomized orientation. Assess an operation-family/variant decomposition without assuming it is optimal.
- [ ] C9 Check that synonymous codons have identical instruction, RNG, timing and charging behavior in the initial execution model. Distinguish this property from neutrality under future raw-code introspection.
- [ ] C10 Specify raw-genome storage and hashing separately from decoded-program identity and code caching. Preserve original bases through copying and serialization.
- [ ] C11 Define mapping/language version identifiers and same-version mating requirements. Do not reinterpret stored genomes under a changed table without an explicit experiment or conversion.
- [ ] C12 Publish the proposed table, instruction specification, mutation/recombination analysis and remaining tradeoffs before enabling evolutionary variation.

Completion: every codon has defined bounded execution semantics, the mapping's local properties are measured, and its mating implications are explicit. Alphabet symbols and the full table remain open until this work is done.

## D. Authored codon forager

See [roadmap: direction and order](evolution-roadmap.md#direction-and-order).

- [ ] D1 Add the codon language as a supported option alongside source and forager-v1; keep compilation as the default method.
- [ ] D2 Implement the common decoder and atomic operations with compiled and interpreted execution paths.
- [ ] D3 Write and annotate the forager's base sequence using the new atomic instructions. Keep its actual synonymous choices, not only a canonical instruction listing.
- [ ] D4 Extend inspection to raw codons, decoded instructions and bounded memory. Ensure debug instruction names are not accidentally used as the genetic representation.
- [ ] D5 Validate every codon's decoding, empty programs, unexpected machine states, loops, resource limits and malformed external input. Future stack/jump tests are new coverage, not inherited from the six-op VM checkpoint.
- [ ] D6 Compare full traces and energy accounting between methods across declared seeds and allowances; verify synonymous substitutions preserve those traces in the initial model.
- [ ] D7 Demonstrate feeding and exact funded reproduction before enabling mutation. Re-evaluate viability using phase B's methodology; finer instructions may change computation cost and timing.

Completion: the same hand-authored base genome runs under both execution methods and expresses its strategy without the bundled Sf behavior.

## E. Mutation and lineages

See [roadmap: mutation and framing](evolution-roadmap.md#mutations-and-reading-frames).

- [ ] E1 Add world-managed per-base substitutions at reproduction, with configurable rates and the declared base-transition model. Preserve no-mutation copying as a supported option.
- [ ] E2 Preserve raw parental and offspring sequences, record mutation positions/old/new bases, mapping version, parent IDs, generation and decoded changes.
- [ ] E3 Compare no-mutation controls, structured tables and redundancy-matched shuffled tables under the same declared environmental conditions.
- [ ] E4 Distinguish silent substitutions, instruction changes, executable mutants, survivors and reproducing descendants. Measure behavior and energy costs, not only genome diversity.
- [ ] E5 Re-evaluate selected descendants under comparable conditions before attributing improvement to adaptation.
- [ ] E6 Add whole-codon insertion/deletion as separately configurable operators with explicit length limits, framing and empty-genome semantics.
- [ ] E7 Only then design an optional single-base insertion/deletion experiment: specify reading origin, downstream frameshifts, incomplete tails and interactions with mating eligibility. Do not silently repair malformed offspring.

Completion: variation and its inheritance are reproducible and distinguishable from environmental luck. Beneficial adaptation is a finding to test, not assumed from mutation or diversity.

## F. Sexual reproduction

See [roadmap: within-codon recombination](evolution-roadmap.md#recombination-within-codons). Mapping analysis starts in C; this phase adds population-level mating.

- [ ] F1 Define partner proximity/selection, eligibility, encounter timing, duplicate-request handling and reproductive mode selection. Retain asexual copying as a supported option.
- [ ] F2 Restrict the initial scheme to equal-length, complete-codon genomes using the same alphabet/mapping version. Specify rejection behavior for ineligible pairs; equal length does not guarantee functional correspondence.
- [ ] F3 Implement positional mating: one base from each parent's corresponding codon, preserving the selected orientation. Example: AB × CD produces AD or CB.
- [ ] F4 Add explicit fixed-parent, per-offspring-random and per-codon-random orientation policies as comparison options. Record the chosen policy and random decisions needed for reproducibility.
- [ ] F5 Specify both parents' prana contributions, which need not be equal. Implement atomic or explicitly reserved funding so their combined debit equals the child's initial prana. Keep compute/overhead charges separate.
- [ ] F6 Test insufficient funds, parent death, cancellation, constructor failure and duplicate requests; prevent partial charging and double births.
- [ ] F7 Record two-parent ancestry and define generation numbering; specify whether mutation happens before or after recombination.
- [ ] F8 Compare within-codon mating, whole-codon crossover and asexual copying under controls, including crosses between synonymous genomes. Measure novel instructions, offspring viability and disruption of useful instruction combinations.
- [ ] F9 Treat unequal-length alignment as later work. Define correspondence, unpaired material and structural variation explicitly before lifting the equal-length restriction.

Completion: mating produces reproducible raw genomes and exactly funded offspring, with evidence about its effects rather than an assumption that decodable offspring are viable.

## G. Optional developments

See [roadmap: later branches](evolution-roadmap.md#later-branches).

- [ ] G1 Add full checkpoints: grid, agents, raw genomes, mapping versions, execution state, pending lifecycle transactions, RNG and policies. Compare resumed and uninterrupted runs.
- [ ] G2 Explore richer CA ecology, communication, predation or cooperation with explicit mechanisms and controls.
- [ ] G3 Add bounded offspring-code buffers and copy/edit operations if organism-controlled reproduction is pursued. This is separate from world-managed mating; write a seed replicator before varying its construction machinery.
- [ ] G4 Profile CA, execution, snapshots, rendering and audio separately; optimize measured hotspots against reference traces.
- [ ] G5 Explore alternative machines behind the supported execution interfaces without assuming equal opcode counts imply equal work.
- [ ] G6 Define conflict resolution before parallel execution and checkpoint/version/migration semantics before distributed populations.

## Validation and workflow

Check tasks only after implementation and relevant validation. The separate validation session owns builds, test execution and version control and reports failures for implementation follow-up. Keep a concrete validation handoff with each code checkpoint. Historical green results do not validate later changes. Public documentation should serve a general audience; keep individual hardware/troubleshooting history in memory unless necessary for reproducibility.
