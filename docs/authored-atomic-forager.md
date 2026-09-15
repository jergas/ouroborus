# Authored atomic forager: expressiveness review

This design checkpoint expresses a forager in the [proposed atomic machine](atomic-codon-proposal.md) before freezing its mapping or implementing it in the simulation. The authored artifact is [authored-forager-draft.json](../experiments/codons/authored-forager-draft.json). The existing Forager specificity and both execution methods are unchanged.

## Genome and strategy

The genome has 17 codons / 34 bases:

```text
HA CD AG DF DG HB HC CF AG HH BG FB CE EF AG HF AC
```

The JSON stores contiguous bases, exact synonymous choices, decoded annotations and a hash of the full candidate table. The spaced line here is for reading. HA/HB both encode EAT and CF/CE both encode PRANA; these distinct synonymous choices are deliberately preserved.

| Position | Codon | Instruction | Purpose |
| --- | --- | --- | --- |
| 0 | HA | EAT | Attempt to consume the current ON cell before leaving. |
| 1 | CD | FOOD_AHEAD | Inspect the adjacent cell in the current heading. |
| 2 | AG | SKIP_POSITIVE | If food was sensed ahead, skip the random turn. |
| 3 | DF | RANDOM_TURN | Otherwise choose a heading; do not scan all neighbors. |
| 4 | DG | MOVE | Move once in the chosen heading. |
| 5 | HB | EAT | Attempt to consume the destination cell. |
| 6 | HC | MAINTAIN | Pay the explicit maintenance-policy debit. |
| 7 | CF | PRANA | Read energy after feeding and maintenance. |
| 8 | AG | SKIP_POSITIVE | If energy is positive, skip REQUEST_DEATH. |
| 9 | HH | REQUEST_DEATH | Mark death pending; it cannot be overwritten by a child request. |
| 10 | BG | REPRO_THRESHOLD | Load the configured authored threshold, initially30. |
| 11 | FB | STORE_R | Save that threshold in R. |
| 12 | CE | PRANA | Read current energy for the reproduction decision. |
| 13 | EF | LESS | Set A to1 when energy is below R, otherwise0. |
| 14 | AG | SKIP_POSITIVE | If below threshold, skip REQUEST_CHILD. |
| 15 | HF | REQUEST_CHILD | Request a world-managed birth. No energy changes here. |
| 16 | AC | YIELD | Publish the pending request; restart at position0 next pass. |

No new operation is required for this strategy. Its 13 distinct instructions separate sensing, orientation, movement, feeding, arithmetic and lifecycle requests. Scratch R is rewritten before use, heading persists between passes, and no memory slot is required by this seed. That demonstrates a small forager, not the utility of all32 proposed instructions or the optimality of an eight-slot memory.

EAT already performs a bounded consumption attempt and reports success. Under equal per-instruction charges, probing FOOD_HERE before EAT adds work without reducing the cost of a failed attempt. The initial local eating attempt therefore has no preceding sensor. FOOD_AHEAD is useful because its result changes the movement decision. This distinction should be reconsidered if operation-specific charges are later introduced.

Unlike forager-v1's Sf operation, this genome only inspects one direction and sometimes makes a blind random move. It neither searches all neighboring cells nor guarantees a food-bearing destination. A sensor result may also become stale if an instruction budget splits sensing and action across evolving CA ticks. These are ecological differences to measure, not compiler discrepancies.

## Control flow and funding

Each SKIP_POSITIVE controls exactly the following codon. The reproduction branch is intentionally based on LESS: below-threshold energy produces1 and skips birth; threshold-or-greater produces0 and requests it. REQUEST_DEATH is sticky until publication, so even an abstract path visiting both request instructions cannot replace death with reproduction.

The genome assumes the initial configured values of threshold30 and offspring endowment12. The world rechecks funding at the later birth transaction. Sensing sufficient energy is not a reservation; compute charging between the read and actual transaction may reduce it. Both supported placement choices must retain the same exact parent-debit/offspring-credit invariant. The BIRTH_COST opcode is available but unused by this seed; different threshold/endowment choices may produce rejected requests and require ecological assessment.

The proposed compute-policy zero-prana guard may terminate a visit before this genomic death logic executes. The maintenance policy relies on the explicit MAINTAIN and death branch. The static reviewer does not execute either mortality mechanism; it describes control paths of complete passes assuming execution reaches their end.

## Work and energy bounds

There are three conditional skips, giving eight conservative branch combinations. Every full control path reaches YIELD, executes one MOVE, one MAINTAIN and two EAT attempts. It executes 14–17 instructions. Branches are treated independently: some combinations, such as sensing zero energy and later sufficient birth energy without an intervening gain, may be infeasible. The bound remains conservative.

At an allowance of six, these completed paths require three live visits from position0. Birth servicing, initial preparation and death dispatches are separate lifecycle visits and are not included. A pass can span several world ticks, and YIELD ends its visit even when instruction allowance remains.

With six instructions per prana and zero starting credit, a complete pass prepays three prana. With maximum carried credit of five instructions, it prepays two. Maintenance adds no debit under compute policy. Under maintenance policy, the one MAINTAIN costs at most one prana because the body floors energy at zero.

Two successful EAT attempts can supply at most ten prana with the current five-prana food reward. Thus one instruction per prana necessarily costs more than maximum intake on every completed pass: at least14 spent versus at most10 gained, before any parental transfer. Absent external inputs, that setting cannot sustain repeated full passes indefinitely. The six-instructions-per-prana setting permits positive energy balance when feeding succeeds, but does not guarantee that food is available, that a pass completes before starvation, or that descendants survive.

Reproduction transfers are not consumption of total agent energy: they move12 prana from parent to child when committed. A parent's energy history includes that debit; whole-population accounting keeps it internal. The bounds above describe metabolic work and food intake before such transfers.

## Review tool and validation

```sh
.venv/bin/python -m worldish.codon_program \
  experiments/codons/family-variant-draft.json \
  experiments/codons/authored-forager-draft.json \
  --allowance 6 --price 6
```

The tool validates the exact candidate hash, raw bases and codon annotations. It enumerates acyclic skip/YIELD paths, reports executed positions and decisions, and derives completed-pass work, visit and charge bounds. It preserves raw-genome identity separately from decoding. Unknown instruction semantics and excessive path enumeration are rejected; it never presents a truncated path set as complete.

This is a static reviewer, not an alternative VM. It does not simulate A/R values, heading, RNG, CA updates, failed food attempts, actual prana balances or births. Its per-pass estimates exclude early death and other operational termination. The small fixed opcode vocabulary prevents silently treating a future jump as ordinary fall-through.

The new tests and review command have not run in the implementation session; they are handed to Big Pickle. Earlier mapping measurements passed and remain in [the analysis report](../experiments/codons/family-variant-analysis-report.json). Those measurements validate table geometry, not this genome's execution.

## Decision exposed by this exercise

The proposed forward skips and YIELD can express this starter strategy without extending the opcode set. This removes an immediate expressiveness blocker. It leaves open whether32 instructions, paired synonyms and eight memory slots are the right long-term balance; only13 operations are used here. The next runtime checkpoint should implement the agreed machine as an additional language, use this exact raw genome, and compare both methods' state/energy traces. Viability must then be assessed under declared CA, allowance, price and placement conditions before adding mutation.
