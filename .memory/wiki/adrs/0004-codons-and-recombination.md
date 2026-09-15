# ADR 0004: Codon language and recombination direction

Status: accepted direction, 2026-09-15. Exact alphabet symbols, instruction table and reproductive policy parameters remain open. No new language or mutation implementation is implied by this decision.

## Decisions

Preserve two-character codons. The user's original motivation included sexual reproduction by taking one character from each parent's corresponding codon. Start table design with eight bases, provisionally A–H, yielding 64 codons, and evaluate the alphabet/table alongside a small atomic instruction set.

Every codon over the chosen alphabet must map to a defined operation, redundantly. Favor connected synonym neighborhoods and nearby related functionality under the specified base-mutation model. Evaluate within-codon recombination as well as substitutions before freezing the mapping. A family/variant interpretation of the two positions is a candidate to test, not an accepted fixed layout.

Use a modest explicit no-op allocation. No-op execution still costs allowance and may cost prana; distinguish this from synonymous substitutions that preserve decoded behavior and charging. Preserve raw genomes and identities separately from decoded programs and compiled caches.

Sequence: observation and energy traces; ecological characterization; atomic instructions and codons together; authored codon forager in both methods; base substitutions and lineages; staged indels and sexual-reproduction experiments. Keep existing languages, energy and reproduction behaviors as supported options; compilation remains default.

Initial mating pairs equal-length, complete-codon, same-version genomes. Compare fixed parental roles, per-offspring randomized orientation and per-codon randomized orientation; whole-codon crossover and asexual copying are controls. Unequal-length alignment is later work. Combined parent contributions exactly fund child prana; failed/duplicate transactions must not partially charge or mint energy.

## Documentation and workflow

Keep the roadmap conceptual and task list sequential. Completed foundations move to docs/evolution-implementation-history.md; unfinished tasks stay active with a mapping from old IDs. Preserve Gemini's ingested text and append project qualifications separately. The separate Big Pickle session retains version control and test execution responsibilities.

See [roadmap](../../../docs/evolution-roadmap.md), [task list](../../../docs/evolution-tasklist.md), and [Gemini follow-up with project qualifications](../notes/dna-codon-mutation-robustness.md).
