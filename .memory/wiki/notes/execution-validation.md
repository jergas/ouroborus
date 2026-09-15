# Execution-method checkpoint: validation handoff

2026-09-14. The user assigns version control and test execution to Big Pickle in a separate session, with no fixes: failures should be reported to the user for implementation follow-up. Current branch is forager. This implementation session made no commits and ran no tests or builds for these changes.

## Validation outcome (Big Pickle, committed 2026-09-14)

Build and Lint passed. Focused suite `tests/test_execution.py tests/test_forager.py`: 20 passed. Full suite with local Csound runtime: 108 passed, no failures or skips (94 baseline plus new tests), including real-session compiled/interpreted comparisons. Exploratory matrix, 36 runs (compiled+interpreted × seeds 7/42/99 × allowances 1/2/6 × maintenance/compute, 80 ticks, separate output dirs): all succeeded; compiled and interpreted produced identical population/births/deaths/prana-transferred for every combination. No extinction in the matrix; allowance 1 yields tiny static populations (0 deaths), allowance 6 reproduces and dies as in the compiled checkpoint. Interpreted runs reported `genotypes_compiled == 0`, `genotypes_interpreted == 1`, and generated no native artifacts. No fixes were required.

## What changed

- New worldish/execution.py options and shared bounded scheduler; worldish/forager_vm.py interpreted dispatch plus compiled dispatch emission.
- Source-fragment execution remains directly supported. Forager now selects forager-v1, with compiled as default and interpreted as a selectable method.
- Per-organism instruction position, pending prayer and compute credit; run-wide counters. Shared primitives keep method semantics aligned.
- Config/CLI/desktop/worker execution and energy settings; startup messages and result metrics distinguish preparation from native compilation.
- Optional compute charging prepays one prana for six instructions by default and disables the Mt debit. Exact offspring transfer remains unchanged.

## Suggested validation order

1. Run repository Build and Lint commands first. Cython source for per-genome compiled dispatch is additionally exercised by the new native fixture in tests/test_execution.py.
2. Run `.venv/bin/python -m pytest tests/test_execution.py tests/test_forager.py -q`. Native dispatch fixture builds once. Trace tests compare action, energy, RNG, state and cell sequences across allowances 1/2/6/12 and both policies. The real session test compares compiled/interpreted result counters at allowance 2 with compute charging and asserts no generated native artifacts on interpreted runs.
3. Run the existing suite with local Csound runtime as instructed in AGENTS.md. Desktop worker tests require execution outside the socket-restricted sandbox. Inspect skips rather than interpreting a skipped audio test as validation.
4. Inspect Forager desktop settings at minimum window size, both execution methods, save/load, pause/step/stop and audio. Check old settings without new fields still load with defaults. Alpha/Beta/Delta remain compiled and Epsilon remains agent-free.
5. Compare compiled/interpreted runs with seeds 7, 42 and 99 at 80 ticks and allowances 1, 2 and 6, for each energy policy. Record extinction as a result. This is a declared exploratory matrix, not a guarantee of viability at all rates. Use separate output directories.

## Review points / limitations

- Compilation currently specializes opcode dispatch; primitives and scheduler remain Python. Do not claim a speedup.
- No general stack/jump language yet. Unknown complete words no-op; malformed representation is rejected. Empty programs idle.
- Limits apply per live visit; experimental threaded clocks are not deterministic world ticks. No population/strain cap yet.
- Prepaid compute credits persist in parents but are not inherited. Zero-prana checks occur before/after every compute-policy instruction; maintenance retains Di semantics.
- Pending lifecycle requests must survive budget yields but publish once at completion. Credits and pending state must not leak between organisms sharing one program.
- Report any build failure, trace mismatch, UI load warning, conservation violation, hidden compilation in interpreted mode, or behavior regression. Do not repair it in the validation session without the user's changed instruction.

Public semantics are documented in docs/agent-execution.md. Checkbox tasks remain pending until independently validated; implementation status is recorded separately.
