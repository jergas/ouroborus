# Evolutionary language roadmap

Status: planned direction, 2026-09-14. This roadmap describes the conceptual architecture and choices. The [implementation task list](evolution-tasklist.md) gives the ordered, fine-grained work and completion criteria. The [current system baseline](current-evolution-system.md) describes what exists today. The compiled forager and transfer reproduction option are implemented as an initial checkpoint; interpretation remains pending. See [current forager](forager.md) for behavior and validation.

## Extension policy

Favor adding supported options and selecting preferred defaults over replacing behavior and adding compatibility layers. Existing source-genome compilation and preset-funded reproduction remain first-class choices; the forager selects the new transfer option.

## Direction and order

The first organism will be a hand-authored viable forager that can eventually run both compiled and interpreted. Establish it in the existing compiled framework before adding interpretation. Preserve compilation as the default execution method.

The work proceeds in this order:

1. **Create a forager specificity** defining its environment and initial population. See [task list, phase 1](evolution-tasklist.md#phase-1-create-the-forager-specificity).
2. **Design and implement the compiled forager**, including exact parent-to-offspring prana transfer. See [phase 2](evolution-tasklist.md#phase-2-design-and-code-the-compiled-forager).
3. **Add execution-method selection to the framework**, retaining compilation and introducing an interpretation option. See [phase 3](evolution-tasklist.md#phase-3-add-framework-execution-method-selection).
4. **Implement the bounded interpreter** and run the same forager under both methods, with configurable computation limits and a considered prana cost model. See [phase 4](evolution-tasklist.md#phase-4-implement-the-bounded-interpreter-and-align-compute-accounting).

Mutation and more ambitious evolutionary experiments follow this foundation. The implementation order does not require settling every future opcode or ecological feature before establishing the compiled forager.

## One organism, two execution methods

A specificity defines a world and its initial organisms. Execution method determines how an organism's program runs. These should be independent: switching execution method should not implicitly select a different world, genome or energy policy.

Proposed configuration names are `execution_method = "compiled" | "interpreted"`, with `compiled` as the default when absent. These names are a design proposal, not an existing API. The current `compiling` setting selects `IndividualCompile`, `MassCompile` or `Void`; it is not the new execution-method selector. Keep strain reuse/build strategy separate from execution method, and preserve no-agent configurations explicitly.

The framework should dispatch through a common agent-controller interface. Compiled controllers use the existing build/import path; interpreted controllers use a shared runtime and per-agent execution state. The body, world, lifecycle and energy accounting remain common. The existing generated `birth()`/`live()` execution remains a directly supported option. New execution mechanisms are added alongside it; arbitrary Python/Cython source is not assumed to be interpretable by the new genome interpreter.

For the forager, prefer one authoritative program representation with compiled and interpreted realizations. Establish a small, explicit set of operations while writing the compiled version; the interpreter can later implement their semantics. This need not mean building a general compiler before the forager works. Avoid two independently maintained behavioral implementations that merely happen to produce similar results.

An execution method and an energy policy must not be conflated. Existing compiled agents retain their supported policy while the forager's two execution methods share the new policy. If computational charging or resumable budgets change the compiled implementation, adapt it rather than allowing method choice to change the experimental rules.

## Foraging and reproduction energy

The agent's energy is **prana**. The stored **mana** value is food-related configuration; currently `eatMana()` checks cell state 1 and adds five prana. The current Alpha genome deducts 14 on reproduction while its offspring receives preset prana of 22. The historical reason for that difference has not been established.

For the new forager, successful reproduction transfers exactly an amount E:

```text
parent_after = parent_before - E
child_initial = E
parent_after + child_initial = parent_before
```

No second default-energy allocation may be applied to that child. Initial founders are a separate, explicit initialization input. Any reproduction-computation cost is an additional, separately recorded expenditure, not part of E or an unexplained mismatch in the transfer.

The transfer must remain correct across delayed births, failure, cancellation and parent death. Choose an atomic transfer at successful birth or an explicit reservation held until completion. Define the handling of rejected births and insufficient prana. World-owned accounting prevents an organism from requesting offspring without funding them.

This guarantees conservation at reproduction. Full-world conservation would additionally require accounting for food creation, consumption, computation, dissipation and death. The cellular automaton currently creates/removes edible states; a closed energetic universe is a separate ecological choice. Record sources and sinks rather than claiming global conservation from the reproduction invariant alone.

## Bounded execution and computation as metabolism

A bounded interpreter reads genome instructions as data and returns control after a configurable amount of work. An organism can retain its instruction pointer and stacks between world ticks. Budget exhaustion yields to the scheduler; it is distinct from program completion and prana exhaustion.

The instruction allowance should be a validated variable, provisionally named `instructions_per_tick`, recorded in experiment configuration. There is no selected value of 64. Choose defaults from forager viability and measured runtime. Population-wide work still scales with the number of agents and their allowances; individual limits do not guarantee real-time performance.

Bounds must also cover stacks, genome/offspring buffers, numeric sizes, and work performed inside an instruction. A search or copy cannot evade the allowance by doing unbounded work inside one opcode. Empty stacks, invalid branches and arithmetic edge cases need defined outcomes. Interpreter defects should surface as errors rather than being silently treated as ordinary mutant behavior.

Explore charging **prana for computation instead of routinely subtracting a fixed amount every live call**. Count shared semantic operations, not Python bytecodes, native machine instructions or wall-clock duration: those differ with execution method and hardware. If this policy is adopted, the compiled forager must execute the same charge points and suspension rules as the interpreted one, including branches, no-ops and repeated actions.

The hard scheduling allowance and prana price solve different problems. Retain a hard bound even if computation costs prana; otherwise zero-cost settings, cheap loops or energy gained during execution could let an organism monopolize the world. Define whether an unaffordable instruction is suspended or results in death, and whether feeding may rescue an agent at zero energy. Avoid accidentally retaining the old flat debit in addition to the new computation charge.

Prana is currently an integer. Small computation costs may require rescaling energy units, charging batches, or tracking fractional debt. Choose a representation that preserves exact offspring transfer and consistent charging. Also decide what halted organisms pay: removing routine maintenance allows inactive organisms to persist unless another world rule removes them. Such persistence is an ecological consequence to evaluate, not automatically an error.

## Evidence of success

The compiled forager should first demonstrate sensing, feeding and funded reproduction in a controlled food environment. Then run it under changing CA conditions. Define seed sets, duration and viability criteria before evaluation, and retain extinction results.

After interpretation exists, compare both methods with identical program, specificity, RNG state and resource policy. Compare action traces, prana balances, births/deaths and world state at equivalent scheduling boundaries. Equal aggregate population counts alone are not evidence of semantic equivalence. Observe responsiveness and resource bounds under looping and malformed genomes as well as under the viable seed organism.

## Subsequent and optional directions

The [later-work tasks](evolution-tasklist.md#phase-5-heritable-variation) turn these directions into concrete experiments.

- **Heritable variation:** introduce substitution, insertion and deletion after both forager execution methods are validated. Track ancestry, mutant viability and behavioral outcomes against no-mutation controls.
- **Inspection and replay:** inspect instructions, energy and lineage; checkpoint complete world, lifecycle, RNG and execution state. Settings files alone are not checkpoints.
- **Ecology:** compare local/global reproduction, food regeneration, action costs and computation prices. Investigate communication or cooperation when their mechanisms can be observed.
- **Offspring construction:** later let organisms copy and edit offspring code themselves; world validation still enforces energy/resource rules.
- **Alternative machines:** compare stack, register or regulatory execution behind the same world interface where useful. Equal instruction counts across different languages need not imply equal work.
- **Performance and scale:** profile before optimizing; compare Cython paths against reference semantics. Parallel and distributed populations depend on explicit conflict, checkpoint and migration semantics.

Public documentation is intended for a general audience. Keep individual hardware and local troubleshooting history in memory unless needed for requirements or reproducibility.
