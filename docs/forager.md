# Authored forager

The `forager` specificity runs a hand-authored organism, with compilation as the default execution method, on an evolving XOR cellular automaton. The CA's on cells are the food: consuming one changes it to the background state and grants five prana. The initial specificity uses Alpha's 80 × 20 toroidal Moore world with 100 random cell placements, three founders with 24 prana each, and a shared compiled strain.

Select **Forager** in the desktop Specificity selector, or run:

```sh
.venv/bin/python -m worldish.start --specificity forager --mode session --display debug --no-sound --steps 80 --seed 42 --fast
```

The vocabulary in [forager.py](../worldish/forager.py) encodes the ordered program `Sf Ea Mt Rp Di Rt`: seek nearby food (stay if already on food), eat, pay one prana maintenance, request reproduction at 30 prana, request death at zero, return the lifecycle request. When no nearby food is visible, the organism chooses a random direction. This program now also has compiled and interpreted forager-v1 dispatch; see [agent execution](agent-execution.md) for limits, energy options and the supported source-table path.

## Supported reproduction options

The framework now recognizes `reproduction_policy = "preset"` (the default) and `"transfer"`. Existing specificities keep preset-funded reproduction as a supported option. The forager selects transfer and `offspring_prana = 12`.

Transfer prepares the child, verifies its constructor preserved the specified prana, and registers it before debiting the parent exactly 12. Preparation failure removes the prospective child and does not debit the parent. Insufficient funds reject the request. The world executes this operation within its serialized lifecycle update. By default the child appears at the parent's location; explicit local or random placement can be selected independently of funding. Overlapping occupancy remains allowed. See [placement choices](ecology-studies.md#offspring-placement-comparison).

A transfer-funded child is already instantiated and counted when the transfer completes. Its next `BeBirthed` visit activates it without constructing or charging again; this preserves the presentation's birth notification. It begins normal behavior on a following visit. The parent returns to `Live`, so processing it again does not repeat the same birth request. No energy is left reserved across ticks. Initial founders remain an explicit energy input.

`result.json` includes `prana_transferred` and `max_generation` for transfer-policy runs. Child bookkeeping stores parent name and generation. This is minimal ancestry metadata, not a durable genealogy database. Food-driven energy inputs and maintenance expenditures remain separate from conserved reproduction transfer.

## Initial validation and next work

An initial 80-tick debug run with seed 42 reached eight descendant generations, with 884 total births (three founders), 632 deaths and 252 survivors. Transfers totalled 10,572 prana, exactly 881 × 12. This is an initial smoke result, not a general ecological viability study. The XOR rule is a simple initial environment, not a final ecological choice.

Focused checks cover sensing/consumption, exact transfer, insufficient funds, duplicate requests, constructor failure, and a constructor attempting to allocate extra prana. A real compiled run checks descendants and total transfers. Longer evaluation across declared seeds, richer energy ledgers and desktop live inspection remain work in the [task list](evolution-tasklist.md).

Execution-method selection and the bounded forager interpreter are implemented and validated. The default allowance is six instructions per live visit; computation charging is optional and maintenance remains supported. Focused trace/session tests plus a 36-run compiled/interpreted matrix confirm matching behavior and energy accounting. See [agent execution](agent-execution.md) and the [roadmap](evolution-roadmap.md).
