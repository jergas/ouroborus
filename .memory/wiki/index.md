# Project Memory Index

Durable project knowledge consolidated on 2026-09-13 from the migration/port conversation, current source, and the user's latest scope decision. Historical validation is dated; it is not evidence that tests ran in a later session.

## Architecture and scope

- [Stack and build](adrs/0001-initial-stack.md)
- [Repository boundaries and historical components](adrs/0002-repository-boundaries.md)
- [Accepted desktop architecture](adrs/0003-desktop-app-proposal.md)

- [Current system and evolutionary-language baseline](../../docs/current-evolution-system.md) (source snapshot, 2026-09-14; proposed language directions remain undecided)

- [Evolutionary language roadmap](../../docs/evolution-roadmap.md) (compiled forager first, execution-method selection, then bounded interpretation)
- [Ordered evolutionary task list](../../docs/evolution-tasklist.md) (cross-referenced implementation phases and validation)

- [Compiled forager and transfer policy](../../docs/forager.md) (checkpoints verified; execution and forager VM validated)

- [Executor and energy settings and semantics](../../docs/agent-execution.md)
- [Execution validation notes](notes/execution-validation.md) (validated by Big Pickle; no fixes needed)

## Execution knowledge

- [Environment and library gotchas](gotchas.md)
- [Failed approaches and their resolutions](failed_approaches.md)
- [SVN migration and preservation](migration.md)
- [Python 3 port status and validation](port-status.md)
- [Significant changes](log.md)

## Research and surveys

- [Languages for in silico code evolution](notes/digital-life-languages-survey.md) (Gemini report + source lists, 2026-09-14)

## Source-of-truth links

- [Repository instructions](../../AGENTS.md)
- [Setup and example commands](../../README.md)
- [Detailed port notes](../../docs/python3-port.md)
- [Packaging configuration](../../pyproject.toml)

The source files in this directory are the repository-local memory required by AGENTS.md. These curated pages are also written to the connected Mnemosyne/ai-memory project wiki for retrieval. Future edits should keep the two copies consistent; this does not assert automatic synchronization. Memory records facts and prior decisions; current user instructions and actual repository state take precedence.
