# Agent execution methods

Status: implemented and validated 2026-09-14 (Build, Lint, full suite 108 passed, compiled/interpreted trace and session agreement, 36-run exploratory matrix). See the [roadmap](evolution-roadmap.md) and [task list](evolution-tasklist.md) for broader experiments that remain pending.

## Supported choices

Compilation remains the default. Execution method, genome language, compilation strategy and energy policy have separate responsibilities:

| Setting | Choices and purpose |
| --- | --- |
| `execution_method` | `compiled` (default), `interpreted` |
| `genome_language` | `source` (default for existing specificities), `forager-v1` (Forager) |
| `compiling` | Existing `MassCompile`, `IndividualCompile`, `Void` strategies; `Void` creates no agents under either method |
| `energy_policy` | `maintenance` (default) or `compute` for `forager-v1` |
| `instructions_per_tick` | Forager instruction allowance, 1–4096, default 6 |
| `instructions_per_prana` | Instructions prepaid by one prana under compute policy, 1–4096, default 6 |

`source` remains the supported source-fragment compiler with its existing whole-`live()` behavior and genome-defined costs. It cannot be interpreted by the forager VM, and nondefault resource settings are rejected rather than silently ignored. Its default numeric fields do not imply a six-instruction limit on generated Python/Cython code.

`forager-v1` supports both methods. The forager's original source vocabulary is still available through `genome_table`; setting its specificity's `genome_language = "source"` selects that directly supported execution option. The desktop uses the shipped specificity's language; it exposes interpretation and resource settings for Forager only.

Under `compiled`, each unique forager genome is emitted as native opcode dispatch through the existing Cython build path. The first implementation compiles dispatch, while primitives and the resource scheduler remain shared Python code. Under `interpreted`, a cached immutable operation sequence is prepared without generating or importing a native genome module. Both invoke the same primitives. No performance superiority is claimed for either method before measurement.

## Launching and settings

```sh
.venv/bin/python -m worldish.start --specificity forager --mode session \
  --display debug --no-sound --steps 80 --seed 42 --fast \
  --execution-method interpreted --instructions-per-tick 6 \
  --energy-policy compute --instructions-per-prana 6
```

Replace `interpreted` with `compiled` to use the other method. CLI values override specificity values; absent fields use `ExecutionOptions` defaults. Desktop launch settings store all four execution/resource fields and explicitly pass them to the worker. Settings files missing those fields receive defaults. Execution and energy changes apply on the next run, not to an active organism.

The existing version-1 settings envelope remains supported with additive fields. Result execution metadata carries version 1 and the selected language/options. `genotypes_compiled` is zero for interpreted runs; `genotypes_interpreted` counts prepared interpreted strains. Shared `execution_metrics` count instructions, computation and maintenance prana, food consumption, budget yields and program completions, including work by organisms that subsequently die.

## Forager v1 semantics

The genome is a sequence of two-character words, allowing ordinary spaces between words. At most 1024 words and 4096 raw characters are accepted. Odd-length input, non-string genomes and oversized input are rejected during preparation. Unknown complete words execute as no-ops and still consume instruction allowance and, under compute policy, prepaid credit.

| Word | Operation |
| --- | --- |
| `Sf` | Sense current cell and Moore neighbors; stay on food or move toward the first food cell; choose a random direction when none is visible |
| `Ea` | Consume the on cell under the body, clear it and gain five prana |
| `Mt` | Deduct one prana under maintenance policy; no energy effect under compute policy |
| `Rp` | Record `GrantChild` when prana meets the specificity's reproduction threshold |
| `Di` | Record `KillMe` at zero prana |
| `Rt` | Finish this program invocation and publish its recorded lifecycle request |

Reaching the genome's end also completes an invocation. Completion resets the instruction position and pending request for the next live visit; it does not start another invocation in the same tick even if allowance remains. An empty genome idles without executing instructions or paying maintenance. Arbitrary conditionals, jumps, stacks, code editing and arithmetic are not yet provided. This is a bounded forager instruction machine, not a full Push implementation.

Budget exhaustion preserves instruction position and pending request and returns `Live` to the world. A pending reproduction request is only published when the invocation completes, so a partial invocation cannot repeatedly request births. If its pending request is eventually rejected for insufficient offspring funding, the existing transfer policy leaves the parent undebited.

Each live visit executes at most the allowance; lifecycle-only visits execute no instructions. The session normally has one lifecycle visit per organism per world tick. The experimental independently clocked scheduling mode remains distinct: there the allowance is per live visit rather than a global-world-tick quota.

Bodies use Moore neighborhoods, bounding `Sf` to nine sensed positions. There are no growing stacks or unbounded search operands. The program length and per-visit allowance bound work; these are not wall-clock deadlines or aggregate population limits. Population/strain counts and overall run resources are not bounded by this VM, and broader resource controls remain future work.

## Prana charging and offspring

Maintenance keeps the existing authored `Mt` debit. Compute charging replaces that debit with prepaid batches: before the first instruction of a batch, the organism pays one prana and receives `instructions_per_prana` credits. Each instruction, including `Mt`, `Rt` and no-ops, consumes one credit. Unused credit persists between invocations and budget yields. Offspring begin with zero credits; copying a genome does not copy the parent's prepaid computation.

Under compute policy, zero prana before an instruction requests death without executing it. After charging and executing an instruction, zero prana also requests death, overriding a pending reproduction request. Thus `Ea` can recover energy if it is the instruction that spends the last prana; a preceding `Sf` cannot defer its resulting zero-energy check until a later `Ea`. These explicit boundaries differ from maintenance's authored `Di` check and must be included in ecological comparisons.

An empty program pays nothing because it does no work; idle persistence is currently allowed. Charged prana is an explicit energy expenditure, not a transfer to food or another organism. The hard instruction allowance still applies regardless of prepaid credits.

Reproduction continues to debit exactly the prana assigned to the child. Computation costs and offspring transfers are separate ledger quantities. On CA cells remain the food source and the XOR environment still evolves. Longer viability studies under different compute prices and allowances are pending; numerical defaults are initial experimental settings.
