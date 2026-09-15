# Agent observation and prana accounting

Observation checkpoint validated on 2026-09-15 by Big Pickle: Build/Lint clean, 119 tests passed without skips. Manual desktop/audio review remains pending; later placement changes require new validation. This implements the first part of [task-list phase A](evolution-tasklist.md#a-observability), supporting the [evolution roadmap](evolution-roadmap.md). It adds observation to the existing execution methods and energy policies; compilation and maintenance remain the defaults.

## Using the inspector

In the desktop, open **Inspect** and choose an agent, or click a white organism center in **Living grid**. Purple cells still show the body's footprint. Repeated clicks at an overlapping center cycle the listed agents. An outlined cell marks the selected living agent.

The inspector shows the selected organism's raw genome, decoded program, next instruction position (zero-based), lifecycle and pending VM requests, prana, prepaid compute credits, parent, generation, and instruction/energy counters. Source-fragment programs expose their raw code and translated fragments, but their internal instruction position and per-operation counters are unavailable.

Inspection works while paused and does not advance time. **Step** still advances a complete world tick. The selected organism's last state is retained when it dies; after a run ends, all displayed information is explicitly last-observed data. Other dead organisms are not retained for browsing. Trace files provide the recorded history when enabled.

Snapshots carry at most 1,024 agent IDs and center positions, with a visible truncation notice. An ID outside that list can be entered directly while the worker is running. Only the selected organism's genome and state travel with each snapshot. Genome displays stop at 256 decoded words and 8,192 characters per text field, explicitly marking truncation; the hashes always identify the full representation. IDs are unique within a run; qualify them with the run ID/output directory across experiments.

## Optional traces

Choose **Event trace: Off / Events / Instructions** before starting a desktop run. Settings files include the mode and event limit; older settings load with tracing off. The CLI equivalents are:

```sh
.venv/bin/python -m worldish.start --specificity forager \
  --mode session --display debug --no-sound --steps 80 --seed 42 \
  --execution-method interpreted --trace-mode instructions --trace-limit 100000 \
  --output-dir .worldish/observed-forager
```

`events.jsonl` is streamed into the run directory. Off is the default and creates no trace file. Events mode records lifecycle activity, rejected/failed offspring preparation, completed transfers, and Forager actions that change position, food, energy or pending requests. Instructions mode additionally records every executed opcode, including no-ops. Both record completed `live` visits, including budget yields and their retained execution state. An empty program produces no instruction events.

The first record identifies trace schema 1, specificity, execution settings, language, effective world parameters, launcher arguments (including seed and mode), and Python RNG state before world construction. Genome records associate exact raw representations and decoded instructions with separate SHA-256 identities. `forager-v1` identifies the current language semantics; source program identity includes its decoded fragments and boilerplate. The decoded identity excludes execution method, allowing method comparisons. These are diagnostic identities, not compiled-cache keys or portable executable hashes: compare the same implementation revision and dependency versions when interpreting results.

Each record has a tick and sequence number. An instruction record surrounds charging and the primitive operation, before completion/death resets the instruction pointer. The following `live` record shows the published lifecycle request and final scheduler state. Birth records describe actual body registration, not just requested reproduction. A transfer birth is counted once, even though the child's next lifecycle visit activates it.

The configurable cap is 1–1,000,000 events (default 100,000). There are also fixed limits of 64 MiB of event data and 256 KiB per event. Reaching any cap writes one small `trace_limit` marker and stops recording; its reason distinguishes the caps. Event counts/bytes exclude that marker. Write errors disable recording and are reported in snapshots and `result.json`; simulation continues. Existing files are replaced when explicitly reusing the same output directory with tracing enabled. Desktop runs have separate directories.

Traces are diagnostic histories, not resumable checkpoints. Truncated or failed recordings are incomplete. A recorded initial RNG state does not establish deterministic ordering for the experimental threaded scheduler; use the sequential session loop for method comparisons. Source programs expose net `live()` changes rather than invented instruction-level explanations. Trace limits do not cap simulation population or genotype caches; those policies remain in phase B.

## Prana ledger

Snapshots and `result.json` include a ledger of **agent prana**:

```
accounted live prana = founder input + preset offspring input + food input
                     - compute spent - maintenance spent - prana removed on death
                     + source live() net change
balance error = actual live prana - accounted live prana
```

Transfers are reported separately: the parent's debit and child's credit are equal and leave total agent prana unchanged. Supported preset-funded offspring are external input to this ledger. Death removes whatever prana remains when the body is removed, which need not be zero for a source program.

Forager food input is five prana per successful `eatMana()`, matching the current body implementation. Compute and maintenance are measured by the existing scheduler/primitive counters. Source programs contribute their signed net change across each `live()` call; this may combine food, costs and other source-defined actions. A zero residual for source programs confirms net accounting, not a verified decomposition of those actions.

CA on cells remain food. CA evolution generates and removes potential food outside this ledger: the accounting boundary covers agent prana, not a conservation law for the entire CA universe.

## Implementation

`worldish/observation.py` owns identity metadata, selected-agent descriptions, scalar ledger totals and the bounded trace writer. `Generator.makeEntry()` attaches shared genome metadata and, for Forager, an `ObservedMetrics` mapping. That mapping forwards writes to the existing run-wide counters while accumulating deltas on the current `BookEntry`.

The shared scheduler calls optional before/after observation hooks around each primitive. Ordinary metrics dictionaries remain supported. Both native and interpreted dispatch use the same hook boundaries; neither dispatch implements its own trace semantics. No observer draws random numbers, consumes the body's `hasEaten()` notification, modifies CA cells or changes requests/credits. Observation adds processing and I/O time; performance neutrality is not claimed.

`Organizer` reports completed births, live visits and deaths. `transfer_birth()` reports rejection, preparation failure and the committed transfer after funding. The existing transaction semantics and activation timing remain intact. The generator retains metadata per distinct raw genome; only one selected tombstone is retained, and events are never accumulated in an in-memory history.

`SessionControl` adds compact organism records, selected inspection, ledger and trace status to snapshots. Its `inspect` command runs between world ticks, including while paused. Render footprints are deduplicated without changing their visible coverage. The desktop controller handles selection by run ID, and `AgentInspector.qml` presents the details. The launcher closes recording on exit; result reporting flushes/closes it before publishing final trace status.

Validation coverage is written in `tests/test_observation.py`, `tests/test_execution.py` and `tests/test_desktop.py`. Build and tests passed for the original observation checkpoint; manual GUI/audio review remains with the separate validation session. Those results do not validate later changes.
