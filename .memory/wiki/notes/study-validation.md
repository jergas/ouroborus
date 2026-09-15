# Ecology study runner validation handoff

User reports Big Pickle completed the observation checkpoint and authorizes continuation. Local observation validation notes still lack detailed results; do not invent counts or claim specific manual checks.

Implemented worldish.study, experiments/forager-baseline.json and docs/ecology-studies.md. This is B-phase infrastructure, not ecological findings. No builds, tests, study runs or version-control mutations performed here.

Big Pickle: run tests/test_study.py and relevant regression checks under AGENTS.md environment. Check prepare-only creates a manifest but no workers, existing output refusal, 36-condition expansion, invalid/duplicate axes, extinction versus failed-accounting classification. Add scrutiny to timeout/interruption cleanup: owned simulation/compiler groups must not remain running, and missing outcomes remain unknown. Run a copied tiny plan (one seed, interpreted method, one allowance/policy/price, short horizon) before considering the full 36-run matrix; retain failures. Check trace paths, ledger residual, manifest written before launch and full result retention. Report failures without fixing per user workflow.

The declared baseline is 80 ticks, seeds 7/42/99, both methods/policies, allowances 1/2/6 and price6; minimum final population1/generation2. Passing is a finite-horizon screen only. Wall timeout includes compilation; population/cache/log limits are not implemented. No resumption into old study directories; interrupted manifest entries lacking outcomes are unknown.

## Validation results (Big Pickle, 2026-09-15)

Commit basis: `a885f8c` through the current uncommitted study runner addition. Build: clean. Lint: clean.

Study-focused tests (`tests/test_study.py`): **5/5 passed**. Matrix expansion produces 36 conditions from the baseline plan. Prepare-only writes a manifest with no workers and refuses to overwrite an existing output directory. Duplicate seeds, empty axes, zero-valued steps, and unsupported policy strings are all rejected with `ValueError`. Failed accounting (ledger residual != 0, incomplete iteration horizon) is distinguished from extinction; population=0 at horizon end is correctly classified as survived=False / finite_horizon_screen=False. Timeout and interrupt paths both call `killpg` on the owned process group and then `wait()` without arguments — no lingering simulation or compiler children.

Tiny-study smoke (one condition: seed 7, interpreted, allowance 2, maintenance policy, price 6, 10 steps, 60s timeout): **completed**. Result: population 5, births 5, deaths 0, max generation 1, prana ledger balance error 0. `outcomes.jsonl` records status=completed, survived=True, finite_horizon_screen=True. Manifest was written before launch. Full 36-condition matrix deferred; infrastructure validated on a single real condition.

Full regression suite: **124 passed, 0 failures, 0 skips** (77.43s). Includes the 5 new study tests plus 119 pre-existing tests covering observation, execution, forager, desktop and session regressions. No fixes needed. Report this to the user; failures are none.
