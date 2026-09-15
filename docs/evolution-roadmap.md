# Evolutionary language roadmap

Agreed direction, 2026-09-15. This document describes the concepts and choices; the [active task list](evolution-tasklist.md) gives ordered implementation work. Completed foundations and dated validation are in [implementation history](evolution-implementation-history.md). Current behavior is described in [Forager](forager.md) and [agent execution](agent-execution.md).

The [observation checkpoint](observability.md) now implements agent inspection, bounded traces and a prana ledger; automated validation is recorded for A1–A6, with manual desktop review still pending.

## Supported foundations

The forager already runs compiled and interpreted, with configurable instruction allowances, maintenance or compute charging, and exact parent-to-offspring prana transfer. Compilation remains the default. CA on cells are the food source; the initial XOR environment evolves. The current six-operation language bundles food sensing, direction choice and movement into `Sf`, so it establishes a working organism but leaves much of its behavior fixed by the host.

Add supported options and select preferred defaults rather than replacing existing behavior with a compatibility path. Source-fragment compilation, forager-v1, preset-funded reproduction and transfer reproduction remain valid choices as new languages and reproductive mechanisms are added.

## Direction and order

1. **Observe execution and energy flows.** Inspect agents and record optional traces that explain feeding, computation, lifecycle requests and offspring transfers. [Tasks A](evolution-tasklist.md#a-observability).
2. **Characterize the ecology.** Study instruction allowance, compute pricing and offspring placement before confusing their effects with genetic variation. Complete remaining desktop and aggregate-resource work. [Tasks B](evolution-tasklist.md#b-ecology-and-run-controls).
3. **Design atomic instructions and codons together.** Replace bundled behavior in a new language with composable sensing, comparisons, turning, movement, feeding, control flow and bounded memory; design its redundant codon mapping at the same time. Existing languages remain supported. [Tasks C](evolution-tasklist.md#c-atomic-language-and-codon-design).
4. **Rewrite the authored forager.** Express the strategy in the new language, with identical specified semantics under compiled and interpreted execution, before mutation is enabled. [Tasks D](evolution-tasklist.md#d-authored-codon-forager).
5. **Introduce base-level mutation.** Begin with substitutions, preserve synonymous genomes and measure their consequences. Add length-changing operators in stages. [Tasks E](evolution-tasklist.md#e-mutation-and-lineages).
6. **Explore sexual reproduction.** Combine one base from each parent's corresponding codon, initially using equal-length genomes, and compare it with inheriting whole codons. Design the encoding with this mechanism in mind from stage C, even though population-level mating comes later. [Tasks F](evolution-tasklist.md#f-sexual-reproduction).

Observability can grow throughout these stages; complete checkpoints are an optional extension rather than a prerequisite for the first mutation experiment.

## Bases, codons and instructions

The first [atomic-machine/table proposal](atomic-codon-proposal.md) and offline analyzer are available for review. Its 32 instructions and two synonyms per operation remain provisional; measurements and ecological results must inform the decision.

Keep three explicit layers: the raw sequence of bases, a versioned codon-to-instruction mapping, and the instructions' execution semantics. Both execution methods consume the same decoded program and apply the same resource and energy rules.

**Two-character codons are retained.** Their original purpose included sexual recombination within a codon, not merely compact notation. The starting design candidate is eight bases, provisionally `A`–`H`, giving 64 possible codons. The exact symbols, instruction set and mapping remain to be designed and evaluated; eight bases is a candidate, not a published language contract.

Every possible codon over the chosen alphabet must map to a defined atomic instruction, with redundancy. Unknown external characters or incomplete input are representation errors to handle explicitly; they are not additional codons. An instruction is atomic at the VM level and must have bounded work and defined behavior for every permitted machine state. It must not secretly implement an entire foraging strategy.

Several codons should encode each operation where the table permits. Place synonymous codons in connected single-base-mutation neighborhoods and favor related operations at other nearby codons. Examples of related functionality include sensing different directions or different turning actions. An operation-family role for the first base and a variant role for the second is a hypothesis to evaluate, not a constraint that overrides measured robustness.

Alphabetical adjacency is not mutational adjacency. Define which base substitutions are possible and their probabilities, then enumerate the resulting codon neighbors. Under uniform substitution, each two-base codon in an eight-base alphabet has 14 distinct single-substitution neighbors. Measure silent, related-operation and other-operation transitions, including directionality and position-specific effects if mutations are biased. Compare structured tables against shuffled tables with the same instruction multiplicities.

Semantic proximity is a design bias, not a guarantee of small behavioral consequences. A nearby turning operation can be fatal in a particular world state. Evaluate instruction-level similarity and observed organism behavior separately.

## No-ops and silent variation

Include a modest allocation of explicit no-op codons as an initial design choice. A no-op can disable an operation without deleting its position or shifting later code; later mutations can reactivate that position. It is not required to make a mapping complete, and its allocation should be assessed rather than used to absorb most codons.

A no-op consumes instruction allowance and may cost prana, so insertion or substitution involving one is not necessarily neutral. Synonymous substitutions are a cleaner source of silent variation: equal decoded instructions must have identical control, timing, RNG and charging semantics under the same initial state.

Preserve raw genomes through birth, storage and observation. Do not canonicalize synonymous codons when reproducing. Distinct raw genomes can share decoded instructions and potentially compiled artifacts, while retaining separate genetic identities. If future organisms can inspect their raw code or construct offspring, synonymous encodings may acquire effects through those additional mechanisms; neutrality is scoped to the selected language and reproduction model.

## Mutations and reading frames

Start with per-base substitutions within the chosen alphabet. A total codon mapping guarantees valid decoding of complete words, not survival or reproduction. Bounded control flow and memory semantics remain necessary after decoding.

Whole-codon insertion/deletion follows as a separately configurable operator. Single-base insertion/deletion is a later frameshift experiment: it changes downstream pairing and can leave an incomplete final word. Specify reading origin, framing, incomplete-tail behavior and length limits before enabling it. Do not quietly repair genomes in ways that introduce an undocumented evolutionary bias.

Record exact genetic changes, ancestry and outcomes. Compare with no-mutation controls and re-evaluate descendants in comparable conditions. Genome diversity, successful execution and adaptive improvement are distinct measurements.

## Recombination within codons

The original proposed mating operation pairs corresponding codons of two equal-length genomes and takes one character from each parent:

```text
Parent 1:  AB  EF  GH
Parent 2:  CD  GH  AB
Offspring: AD  EH  GB
```

A complete codon table makes every resulting word decodable. It can create instructions present in neither parent; this is a feature to investigate rather than a guarantee of useful offspring. Evaluate recombination outcomes while designing the table, including crosses between synonymous parental codons that produce a different instruction.

Support and compare explicit parental-orientation policies: fixed parent roles, a random orientation for the entire offspring, or independently chosen orientation at each codon. Whole-codon crossover provides a useful control that inherits intact instructions. Equal lengths make positional pairing simple but do not establish functional correspondence; unequal-length alignment and inherited insertions/deletions require a later explicit policy.

Mating also requires world rules for proximity, partner selection, eligibility, scheduling and failure. For transfer-funded sexual reproduction, parent contributions must sum exactly to the child's initial prana:

```text
parent_1_debit + parent_2_debit = child_initial_prana
```

Specify how contributions are split; do not assume they must be equal. Computation and any reproductive overhead remain separate expenditures. Failed or duplicate mating transactions must not mint prana, charge only one parent, or allocate offspring twice. Initial founders and CA-driven food changes remain explicit energy sources; reproduction conservation alone does not imply a closed energetic universe.

## Later branches

Full checkpoints and replay, organism-controlled offspring construction, richer resources/communication, alternative machines, and performance work remain optional developments in the [task list](evolution-tasklist.md#g-optional-developments). Organism-controlled construction is distinct from world-managed sexual recombination and need not precede it. Parallel/distributed populations require explicit conflict resolution, versioning and migration semantics.

The [ingested Gemini answer](../.memory/wiki/notes/dna-codon-mutation-robustness.md) inspired the codon discussion. Its quoted text is preserved; project qualifications are recorded separately in that note. The architecture uses redundancy and semantic proximity as testable engineering choices, not as a claim that a biological analogy guarantees evolutionary success.
