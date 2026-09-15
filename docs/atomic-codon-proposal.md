# Atomic codon machine: first concrete proposal

This is a design candidate for [phase C](evolution-tasklist.md#c-atomic-language-and-codon-design), not an accepted mapping or an implemented execution language. The running source and forager-v1 languages remain unchanged. Ecology studies and resource-policy follow-ups remain open; table analysis can proceed independently, but cannot replace viability experiments.

## Representation and machine

Propose eight ASCII bases A–H and two-base codons: 64 words, all assigned explicitly. The candidate has 32 instructions with two synonyms each. Two codons encode NOP: 3.125% of the code space. The candidate is stored in [family-variant-draft.json](../experiments/codons/family-variant-draft.json), separately from executable language definitions.

The proposed machine has:

- An accumulator `A`, a scratch register `R`, and eight memory slots, all signed 16-bit integers. Arithmetic saturates to −32768…32767; comparisons return 0 or 1.
- A memory pointer `p` in 0…7, a heading `h` in 0…7, instruction position, pending lifecycle request, and prepaid compute credits.
- A complete-codon genome of at most 1,024 words. No operands embedded in subsequent codons, no stack, no allocation, and no evaluation of genome-supplied source.

Newborn state is A=R=0, all slots=0, p=0, h=0, instruction position0, pending request Live, and zero compute credits. Registers, memory, heading and unused credits persist between the parent's visits; none are copied into newborns. Initial offspring prana is the exact amount debited from the parent under transfer funding.

Heading0 is north, followed clockwise by NE/E/SE/S/SW/W/NW. A new-language adapter must map these explicit offsets to the topology and body. It must not assume the existing body's neighborhood indices are clockwise: `tellFacing()` returns a coordinate, and the existing facing index0 means staying still. This proposal's heading has eight movement directions and no implicit stationary direction.

Every instruction reads initialized state, so there are no missing-stack-operand cases. External machine state must be type/range validated rather than silently repairing a malformed checkpoint. The genome loader rejects incomplete codons and bases outside the declared alphabet. Every complete codon over the alphabet decodes; there is no unknown-word fallback to NOP. Formatting whitespace can be accepted by an explicit import formatter, but stored genetic sequences contain the actual bases without formatting. Synonymous choices must remain intact.

## Candidate table and semantics

The first base chooses a row; second-base pairs AB, CD, EF and GH choose its four variants. For example, AA/AB encode NOP, AC/AD encode YIELD, and HA/HB encode EAT.

| First base / family | Second A or B | Second C or D | Second E or F | Second G or H |
| --- | --- | --- | --- | --- |
| A: control | NOP | YIELD | SKIP_ZERO | SKIP_POSITIVE |
| B: constants | ZERO | ONE | BIRTH_COST | REPRO_THRESHOLD |
| C: sensing | FOOD_HERE | FOOD_AHEAD | PRANA | FACING |
| D: motion | TURN_LEFT | TURN_RIGHT | RANDOM_TURN | MOVE |
| E: arithmetic | ADD | SUBTRACT | LESS | EQUAL |
| F: register | STORE_R | LOAD_R | SWAP_R | CLEAR_R |
| G: memory | NEXT_SLOT | PREVIOUS_SLOT | LOAD_SLOT | STORE_SLOT |
| H: life | EAT | MAINTAIN | REQUEST_CHILD | REQUEST_DEATH |

All operations retain state not explicitly changed below.

| Instructions | Proposed effect |
| --- | --- |
| NOP | No machine/world change beyond ordinary execution accounting. |
| YIELD | Complete the current program pass and publish its pending request. |
| SKIP_ZERO / SKIP_POSITIVE | Skip the next codon if A=0 / A>0. Otherwise continue normally. |
| ZERO / ONE | Set A to 0 / 1. |
| BIRTH_COST / REPRO_THRESHOLD | Load the configured offspring-prana cost / authored reproduction threshold into A. The new language requires these configuration values to fit nonnegative signed16-bit values, with birth cost positive. |
| FOOD_HERE / FOOD_AHEAD | Set A to1 if the current cell / adjacent cell in heading h is ON, otherwise0. Inspect one cell; never consume it. |
| PRANA / FACING | Load actual prana, saturated to the register range / heading h into A. |
| TURN_LEFT / TURN_RIGHT | Set h=(h−1) mod8 / (h+1) mod8. Do not move. |
| RANDOM_TURN | Choose h uniformly from0…7 using one RNG choice. Do not move. |
| MOVE | Move one cell in heading h, using topology normalization. Do not sense or eat. |
| ADD / SUBTRACT | Set A to saturated A+R / A−R. |
| LESS / EQUAL | Set A to1 if A<R / A=R, otherwise0. |
| STORE_R / LOAD_R | Copy A to R / R to A. |
| SWAP_R / CLEAR_R | Exchange A and R / set R to0. |
| NEXT_SLOT / PREVIOUS_SLOT | Set p=(p+1) mod8 / (p−1) mod8. |
| LOAD_SLOT / STORE_SLOT | Copy memory[p] to A / A to memory[p]. |
| EAT | Attempt the existing cell-consumption operation once; set A to success0/1. A successful current body operation supplies five prana and consumes the ON cell. |
| MAINTAIN | Under maintenance policy, subtract one prana with the existing floor at0. Under compute policy, no extra debit. Retain A. |
| REQUEST_CHILD | Set the pending request to GrantChild unless death is already pending. Do not test the authored threshold, debit energy or create a body. World funding eligibility is checked when the published request is serviced. |
| REQUEST_DEATH | Set the pending request to KillMe, overriding reproduction. Death remains pending until publication. |

Sensing, turning, moving and eating are separate. Reproduction-threshold reasoning also belongs in the genome: the host does not reconstruct an Sf-like foraging strategy. Scratch-register operations and slot operations overlap intentionally, allowing short arithmetic sequences without giving up bounded multi-slot memory; their eventual utility is a tradeoff to review.

## Control flow, work and energy

Each executed codon counts as one instruction, including NOP, YIELD and an untaken conditional skip. Skipped codons are not executed or charged. At the end of the genome (including a skip past the last word), complete the program pass. YIELD also completes it, discarding the remaining suffix for that pass. Completion publishes the pending request, resets instruction position to0 and pending request to Live, and ends the current live visit even if allowance remains. Registers/memory/heading persist. Budget exhaustion preserves position and pending request without publishing it.

This initial model only has forward one-word skips and restart at completion; arbitrary jumps and backward branches are not proposed yet. Conditional blocks can be composed with skips and YIELD. An empty genome idles with no instructions or implicit maintenance, preserving the existing explicit-cost design direction. This permits noncomputing organisms; their ecological treatment must be studied, not silently changed through the decoder.

Use the existing supported energy-policy choices. Compute prepays batches with prana before execution; zero-prana checks before and after an executed instruction force a death request, as in forager-v1. Maintenance only charges MAINTAIN, and explicit genomic death decisions remain possible. Consequently a mutant omitting MAINTAIN may avoid those costs; this is a known property of that policy, not something the codon mapping fixes. MAINTAIN itself still uses one instruction/compute credit under compute pricing, even though it has no additional maintenance debit.

All primitives have fixed bounded work: one arithmetic/register/slot operation, one cell read/move/feed attempt or one request change. Offspring preparation remains a separate world lifecycle transaction; instruction budgets do not bound native compilation or total population. Do not equate equal instruction counts with measured CPU time. Compiled and interpreted methods must share these primitives, scheduling and charge points. Synonymous codons must have identical state, RNG, timing-in-instructions and prana effects; wall-clock equality is not promised.

REQUEST_DEATH may remove a body with positive prana; the ledger accounts for that remaining energy at actual death. Pending births can later fail funding if energy changes before service. Failed preparation must preserve exact funding invariants under all placements.

## What this layout predicts—and does not establish

Under uniform source codons and uniform single-base substitutions, each codon has 14 possible substitutions: seven at each position. In this layout one is silent, six change variants within the same declared family, and seven change family. The predicted totals are 896 directed transitions: 64 silent, 384 same-family and 448 other-family. These are combinatorial expectations for test checking, not measured behavioral robustness.

Thus only 1/14 (about7.14%) of uniformly sampled single-base substitutions are silent. Achieving substantially more redundancy may require fewer instructions, a larger alphabet or a different table. Those changes have expressiveness and mutation-neighborhood consequences; eight bases and 32 instructions remain candidates.

Family equality is a coarse declared heuristic. NOP and a branch share a row without being behaviorally interchangeable; register and memory operations can be related across rows. The table is intentionally arranged to score well under its own family heuristic. Shuffled controls measure that arrangement, not an independently established semantic-distance model or fitness advantage.

Within-codon mating remains the original proposal: XY × ZW yields XW or ZY. This table guarantees synonymous parental codons recombine to synonyms: synonyms differ only within the same second-base pair, preserving row and variant. Arbitrary parental operations need not survive mixing. Uniform ordered-parent enumeration weights unrelated genomes heavily; it is not a prediction of actual mate frequencies.

Fixed and reversed parental roles can have different parental-match frequencies. Randomizing orientation averages the two for one codon. Per-offspring versus per-codon orientation has the same single-codon marginal distribution, but different correlations across a genome. Whole-genome experiments are still required. Equal length does not guarantee corresponding functions at homologous positions. Whole-codon crossover retains parental instructions at each position and is a separate population-level control.

## Analysis tool and next decisions

```sh
.venv/bin/python -m worldish.codon_analysis experiments/codons/family-variant-draft.json \
  --shuffles 20 --seed 42 --include-edges > .worldish/codon-analysis.json
```

Create the output directory first if needed. This offline tool does not import the simulation, compile genomes or enable mutation. It validates total coverage, enumerates all single substitutions and synonymous connected components, and enumerates both orientations for every ordered parental pair. Optional edge/pair records make individual transitions inspectable.

Shuffle controls preserve the exact number of codons per instruction. The report includes the candidate, its content hash, the mapping hash, control mappings and hashes, RNG seed, fractions, control mean/min/max summaries, disconnected synonym counts and recombination summaries. A private RNG makes control generation repeatable without touching the simulation/global RNG. Family labels are fixed across controls. The initial model has no transition/transversion or position-frequency biases; those require explicit additional models before biological analogies are drawn.

The table/prose is a reviewable proposal. Analysis and tests have not been executed in this implementation session. Before freezing a language version: validate the enumerator against hand-worked cases; review measured controls and the family heuristic; assess whether this machine can express the authored forager economically; and decide whether the limited branches, two-synonym allocation and memory/register split are appropriate. Then implement the new language alongside source and forager-v1, retaining compiled default, and compare execution traces before mutation or sexual reproduction is enabled.

Candidate hashes are diagnostic identities, not deployed language versions. A production mapping needs an immutable language/mapping identifier. Never reinterpret a stored raw genome under a changed table silently; mating must require matching versions. Raw offspring bases—not canonical instruction names—must remain the heritable representation.
