# Memory Update Log

## [2026-09-14] DOCUMENT | Current system baseline before evolutionary-language work

Added docs/current-evolution-system.md with high-level architecture, source map, genome translation/build/cache mechanics, BookEntry lifecycle and tick timing, agent primitives, Alpha behavior, reproduction/energy semantics, desktop process boundaries and observability. Confirmed that normal births copy genomes unchanged, place children globally, and allocate preset energy; costs/death requests live in generated behavior. Recorded these facts in the document and this durable memory log. Linked the document from the memory index. Language alternatives and interpreter integration are explicitly proposals, not accepted decisions or implemented features. Validation: source cross-checks, relative document-link checks and git diff --check; no runtime behavior changed.

## [2026-09-14] DOCUMENT | Ingested Gemini survey on in silico evolution languages

Extracted a Gemini report ("Architectures of Digital Life: A Comprehensive Survey of Languages for In Silico Code Evolution") from a share link via a logged-in Chromium/CDP dump. Reconstructed tables and headings into Markdown at notes/digital-life-languages-survey.md, added it to the index under Research and surveys, and mirrored it (pinned) in the ai-memory wiki. The report surveys Redcode/Coreworld, Tierra, Avida, Push/Plush, CGP, Fraglets/String, COSMOS/REPLiCa, Aevol, and compares them for the unfinished Ouroborus agent language. Later the same day, recovered the two source-lists ("Sources used in the report", 53 entries; "Sources read but not used in the report", 92 entries) from the live Gemini conversation (the share link omits them) via CDP DOM extraction of the source chips, and appended them with their original hrefs to both the repo-local and ai-memory copies.

## [2026-09-13] PROPOSE | Desktop shell with curses, audio and future graphical views

Documented a proposed Qt Quick desktop shell, managed simulation/audio worker, PTY-hosted curses view and staged extraction of a session/snapshot API. Recorded the user's left-toolbar and bright purple/green design requirements. See adrs/0003-desktop-app-proposal.md and docs/desktop-architecture.md. This is a proposal, not an accepted architecture or implemented feature.

## [2026-09-13] INIT | Created project memory vault

## [2026-09-13] DOCUMENT | Recorded SVN migration completed in the earlier session

Preserved 395 revision histories and seven author usernames in Git, plus an SVN dump/archive for metadata Git cannot express. Added migration.md with archive location, verification, and preservation limits.

## [2026-09-13] DOCUMENT | Recorded Python 3 port and 2026-09-10 validation

Added port-status.md, gotchas.md, and failed_approaches.md covering builds, runtime genomes, views/audio, thread cleanup, and the deferred-playback fix. Historical full-suite result: 76 passing tests, no skips.

## [2026-09-13] DECISION | Retain the active components together and keep Circadian for possible revival

Recorded the user's accepted single-repository approach. Confirmed ouroborus-cpp removal commit a5ad657 and the existing backups/ouroborus-cpp-20260913.tar.gz. Removal is completed, not a pending task.

## [2026-09-13] CONFIG | Replace pnpm placeholders with Python project commands

Updated AGENTS.md Build/Test/Lint entries for the existing Cython build, pytest with local Csound paths, and syntax/whitespace checks. No dedicated linter or application feature was added. Populated repository memory and published the curated pages into the connected Mnemosyne project wiki.

## [2026-09-13] PUBLISH | Commit the port and Mnemosyne for public GitHub publication

The user explicitly selected public visibility for https://github.com/jergas/ouroborus. The repository was created and configured as origin. The Python 3 port is committed separately as 3c9b297, followed by the Mnemosyne integration (AGENTS.md, repository wiki, handoff guidance, and memory ignore entries). Existing SVN-derived history is retained on main. The README now reflects the C++ removal and Circadian's possible revival.

## [2026-09-13] IMPLEMENT | Accepted desktop architecture and completed shell checkpoint

The user accepted the proposal and requested small initial steps due to remaining usage allowance. Added an optional PySide6 desktop package, QML sidebar/canvas with purple/green styling, honest inactive simulation controls, a module launcher and worldish-desktop entry point. Installed PySide6 6.11.2. Updated README with launch and headless smoke commands. Fixed explicit QML packaging and documented the headless platform-theme quirk.

Validation: Cython build, Python/QML packaging build, headless window load/exit, syntax and whitespace checks passed. Full regression suite: 76 passed, no skips, in 151.28 seconds. Visible desktop behavior has not been inspected. No simulation worker, curses embedding or desktop audio integration yet. Next bounded checkpoint: PTY terminal compatibility spike. Changes remain uncommitted.

## [2026-09-13] IMPLEMENT | Working desktop simulation, terminal/grid views and transport

Connected the Qt shell to a managed Linux PTY worker with a separate versioned local control socket. Added the shared CLI session mode, real curses rendering, snapshot Living grid view, validated preset/seed/iteration settings, JSON save/load, live pacing/volume/mute, pause/resume/single-step, isolated run logs and bounded stop/close cleanup. Preset-derived world dimensions/rules remain fixed. Fixed transport placement after screenshot inspection and QML shutdown ordering after observing teardown warnings.

Validation: 88 tests passed without skips in 93.29 seconds. Coverage includes original regression tests, real desktop-worker genomes, pause/step, terminal resizing/Unicode/colors, stop during compilation, worker crash/restart, settings/QML layout, silent Csound and stereo WAV gain/mute. Headless window smoke, Python syntax/whitespace and build/package checks passed. The new session CLI completed three requested ticks. Inspected terminal and grid screenshots under .worldish/. Changes remain uncommitted.

## [2026-09-13] CONTEXT | User confirms prior audible Csound and current machine-wide audio outage

The user heard Csound during the initial Python 3 terminal test. Since the previous day all apps have lacked audible sound despite system meters showing activity; the user intends to try rebooting. Standalone and desktop Csound device-open probes stalled, while the PulseAudio-on-PipeWire service answered a read-only info request. Added a 20-second device-open timeout with an actionable desktop error, and stopped live-device testing. No audio service, desktop configuration or reboot was performed. Audible playback should be rechecked after the system audio issue is resolved; this is not evidence of a desktop regression.
