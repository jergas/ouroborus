# ADR 0005: Passive observation and agent-prana ledger

Accepted implementation direction, 2026-09-15, under the user's authorization to progress the agreed roadmap. Current checkpoint is implemented but unvalidated.

Add observation before ecology/mutation. Retain compiled default, maintenance default, and source programs as supported choices. Trace defaults off; optional events/instructions modes stream JSONL with event, total-byte and per-event limits. I/O failures disable tracing, not execution. Event/byte counters exclude a final cap marker.

Keep organism IDs (run-local), full raw representation hashes, and decoded program hashes distinct. Do not canonicalize raw genomes or change compiled cache behavior. Capture initial RNG state and effective settings without consuming randomness. No observer may call hasEaten, which consumes the audio notification. Shared scheduler hooks keep native and interpreted primitive trace boundaries identical.

Account for founder and preset-child inputs, five-prana Forager feeding, maintenance/compute spending and energy removed at actual death. Transfer is internal, not input or spending. Source live() exposes a signed net delta; never present it as itemized source costs. CA generation is outside the agent-prana ledger. A zero source residual is not proof of internal energy conservation.

Snapshots include at most 1024 live IDs/centers and one bounded genome inspection. Selection can address any live ID. Retain only the selected organism's death record, not an unbounded dead-agent history. Record genome metadata once per distinct raw representation. These observational bounds do not solve population/cache resource policy (phase B).

See [implementation and limits](../../../docs/observability.md), [task list](../../../docs/evolution-tasklist.md) and [validation handoff](../notes/observability-validation.md). Big Pickle retains builds, test execution and version control. No tests/builds or VC mutations were performed in the implementation session.
