# Memory Update Log

## [2026-09-15] VALIDATE | Authored atomic forager and static review validated

Build clean, lint clean, 153 passed in 82.94s (0 skips, 0 failures) on the authored-codon commit basis. Focused tests 9/9 (codon_program 4 + analysis 5): 17 words/34 bases, 8 paths, 14–17 instructions, MOVE/MAINTAIN×1 and EAT×2 per path all ending YIELD, 3 live visits and zero-credit prana 3 at price6, price1 above food bound, candidate/annotation drift rejection, synonym-preserved decoding, end-skip/empty/path-cap/unsupported rejection. Review CLI at allowance6: price6 report and price1 report saved under experiments/codons/authored-forager-review-{price6,price1}.json; all expectations matched (genome sha a105d9b8c418e308, price1 zero-credit prana 14–17 > food 10). Static bounds only; no VM evaluation. Updated notes/authored-codon-validation.md. Committed pending.

## [2026-09-15] IMPLEMENT | Authored atomic forager and bounded static path review

Acknowledged Big Pickle codon measurements and focused5/full149 passing tests. Authored17 codons using13 proposed instructions without changing the candidate table, preserving exact raw synonyms and pinning candidate hash. Added static decode/annotation/path/cost review and tests; no shadow VM or simulation changes. Conservative full-pass bounds14–17 instructions expose compute price1 as net-negative even at two successful feeds, while price6 permits but does not establish positive energy balance. Removed redundant local food probing because direct EAT is cheaper under equal opcode pricing. Wrote docs/authored-atomic-forager.md and notes/authored-codon-validation.md. No tests/builds/reviewer runs/simulations or VC mutations; new validation, runtime language and ecology assessment remain pending.

## [2026-09-15] VALIDATE | Atomic codon proposal and table-geometry analysis validated

Build clean, lint clean, 149 passed in 83.18s (0 skips, 0 failures) on the codon analysis commit basis. Focused tests 5/5: hand-worked two-base table, candidate combinatorial counts (896 directed: 64 silent/384 same-family/448 other; 32 components; 4096 pairs; 128 synonymous/64 distinct/0 novel; both128/first896/second384/neither2688), isolated RNG and determinism, totality/symbol validation, disconnected-synonym novel children. Measurement run (20 shuffles, seed 42, include-edges) reproduced every expectation; report at experiments/codons/family-variant-analysis-report.json. Candidate/control fractions: candidate silent 0.0714/same 0.4286/other 0.5 vs control means 0.0174/0.0962/0.8864 — geometry bonus only, no fitness claim; recombination neither 0.6562. Offline table analysis only; no VM/codon() implementation or ecological inference. Updated notes/codon-design-validation.md. Committed pending.

## [2026-09-15] IMPLEMENT | Offline codon analysis and concrete atomic-machine proposal

Acknowledged resource-stop validation: focused46/full144 passing, clean Build/Lint, CLI boundary checks confirmed by Big Pickle/user. Added a provisional32-op register/memory machine specification, total A–H/64-codon family/variant table with two synonyms per instruction, and an offline analyzer for directed substitutions, synonym connectivity, both mating orientations and redundancy-preserving shuffled controls. Explicitly distinguish family labels from measured semantics/fitness, singleton-site orientation marginals from genome correlations, and candidate hashes from deployed language versions. Wrote hand-worked/candidate/counterexample tests and notes/codon-design-validation.md. No analysis/tests/builds/simulations or VC mutations in this session; runtime unchanged. Table remains a proposal pending measurements/review, and ecology matrices remain open.

## [2026-09-15] VALIDATE | Session run-limit thresholds validated

Build clean, lint clean, 144 passed in 83.42s (0 skips, 0 failures) on the run-limits commit basis. Focused tests 46/46: disabled limits, equality/simultaneous firing, one-time resource_limit event, visit partial-tick metadata, invalid settings round-trip, exact-funded fourth-body stop under both methods (pop4, transfer12, residual0), partial-tick non-horizon rejection, limited outcomes stay unknown with preserved result payloads, desktop limited-completion message/state. Manual checks: non-session modes reject nonzero limits; max-genotypes1 stops after seed preparation with zero iterations/visits and reason resource_limit. Updated notes/run-limits-validation.md. Committed pending.

## [2026-09-15] IMPLEMENT | Optional session resource stops and limited study outcomes

Read Big Pickle placement/report validation: focused42/full136 passed without skips, Build/Lint clean. Added zero-default population, prepared raw-genome and lifecycle-visit stop thresholds for session mode, checked after initialization/complete dispatches. Births remain atomic, no changed biological eligibility; partial ticks and reached counts reported explicitly in termination metadata and trace events. Wired CLI/config/QML/worker/study/report, including limited desktop state and unknown study outcomes with retained partial results. Wrote tests and notes/run-limits-validation.md; no execution/builds/tests/VC mutations in this implementation session. B6 byte/storage/admission controls and ecological evaluation remain pending.

## [2026-09-15] VALIDATE | Placement choices and study-report validated

Build clean, lint clean, 136 passed in 79.65s (0 skips, 0 failures) on the placement/report commit basis. Focused tests 42/42: placement RNG preservation, local/random exact transfer funding, insufficient-funds rejection, 72-condition placement axis, study-report equality/difference, failed/missing/invalid outcomes stay unknown, recomputed screen, interrupted tail detection, config mismatch rejection, native/interpreted agreement at both placements, desktop random-placement save/load. Full regression includes all prior suites. Updated notes/placement-report-validation.md. Committed pending.

## [2026-09-15] IMPLEMENT | Offspring placement options and paired study reports

Read Big Pickle validation records: 124 tests passed without skips, clean Build/Lint, tiny study completed; full baseline and A7 manual review remain pending. Marked A1–A6 and declared-plan B1 complete on that evidence, preserving pending ecology conclusions. Added independent policy/local/random offspring placement across both funding paths, CLI/settings/desktop/worker, trace/result metadata and optional study axis; default behavior/RNG unchanged. Added read-only study reporter with declared-condition validation, retained unknowns, grouping across seeds and paired final-outcome comparisons. Added 72-condition placement plan, regression coverage and notes/placement-report-validation.md. New checkpoint not executed or tested; no VC mutations. Resource policies, long-horizon ecology and codon implementation remain subsequent work.

## [2026-09-15] VALIDATE | Observation checkpoint and ecology-study runner validated

Build clean, lint clean, 124 tests passed in 77.43s (0 skips, 0 failures) on the uncommitted study-runner commit basis. Observation checkpoint (a885f8c) validation confirmed: 119 of those 124 are the pre-existing observation/execution/forager/desktop suite. Ecology-study runner validated: tests/test_study.py 5/5 passed, prepare-only manifest, output-dir reuse rejection, duplicate/invalid axis rejection, failed-accounting vs extinction classification, owned-process cleanup on timeout and interrupt; tiny-study smoke (seed 7, interpreted, allowance 2, maintenance, 10 steps) completed with population 5, zero ledger residual, screen pass. Full 36-condition matrix deferred. Updated notes/observability-validation.md with a885f8c results (missed during the earlier commit) and notes/study-validation.md with the runner results. Commit pending.

## [2026-09-15] IMPLEMENT | Browser-tab harvest tool with CDP and Firefox BiDi backends

Added `.memory/tools/harvest.py` plus README: a reusable CLI that attaches to a live browser tab and dumps innerText, source chips (`.deep-research-source-lists`) and an HTML snapshot. Chromium/Cdp backend generalized from the Gemini extraction scripts and verified against the live session on port 9222; Firefox backend implemented from scratch as a pure-Python WebDriver BiDi client and verified end-to-end against Firefox 155.0.1 on a detached instance loading a test page. `launch` subcommand prints browser commands (Chromium flags include `--remote-allow-origins=*`; Firefox uses `--remote-debugging-port` + `-profile`). Profile-model and persistence guidance in the README; both browsers can run side-by-side with distinct ports and profile directories. Protocol discoveries recorded in gotchas.md: BiDi has no HTTP `/session` endpoint (websocket + `session.new`), Firefox rejects `resultOwnership: byValue` and requires `awaitPromise`, and `getTree` omits context `type`. Chromium "View sources" remains unfixable; Firefox source lists extract cleanly. Committed 950eb3b and 8a572f1 on forager.

## [2026-09-15] IMPLEMENT | Declared ecology studies and retained outcomes

User reports Big Pickle completed observation validation/version control; committed checkpoint is a885f8c. Detailed validation counts/manual results are not recorded locally. Added a sequential study runner with pre-run manifest, source digest, explicit finite-horizon criteria, isolated subprocess/output directories, streamed full outcomes, and owned-process cleanup on timeout/interruption. Failures/timeouts are unknown outcomes, not extinctions. Added the 36-condition baseline plan, unit coverage, public semantics and notes/study-validation.md handoff. No tests/builds/studies or VC mutations performed in this session. B-phase evaluation and aggregate resource policy remain pending.

## [2026-09-15] IMPLEMENT | Agent inspection, bounded traces and prana ledger; validation pending

Implemented roadmap A1–A5 with regression coverage for A6. Added per-run observation metadata, shared scheduler trace hooks, per-agent metrics, full raw/decoded genome hashes, optional bounded JSONL recording, lifecycle/transfer events and an agent-prana ledger. Desktop snapshots carry compact IDs/centers plus one selected inspection; QML inspector supports paused lookup, overlapping-center cycling and selected-death retention. Trace settings propagate across CLI/config/worker/desktop and default off. Source programs expose signed net live() energy changes without pretending to expose instruction costs. Preserved compilation/maintenance defaults and existing reproduction semantics.

Read-only source/diff review only: no builds, tests or VC mutations, per the user's Big Pickle workflow. Wrote tests/test_observation.py, extended native/session and desktop tests, and created notes/observability-validation.md. Updated public docs and active roadmap/tasklist; completion checkboxes remain pending independent validation. Architectural choices and bounds are in adrs/0005-observation-and-prana-ledger.md. Ecology, aggregate simulation resource policies, atomic codons and mutation remain subsequent work.

## [2026-09-15] DOCUMENT | Agreed codon language, mutation and sexual-reproduction plan

Reorganized docs/evolution-roadmap.md into the agreed conceptual direction and docs/evolution-tasklist.md into active sequential tasks A–G. Added docs/evolution-implementation-history.md for completed foundations, dated validation and explicit old-to-new mapping of unfinished tasks. Plan: observability/energy traces, ecology, atomic instruction and codon design together, authored codon forager, mutation, then sexual reproduction. Retained two-character codons for the original within-codon mating idea; eight bases/64 codons are the starting candidate, not a frozen table. Recorded synonym preservation, modest charged no-ops, actual mutation-neighborhood and recombination evaluation, staged indels/frameshifts, parental-orientation choices, same-length initial mating, whole-codon crossover controls and exact combined-parent offspring funding. Added ADR 0004 and appended separately labelled project qualifications to the intact Gemini ingestion. Runtime unchanged; version control and runtime testing remain delegated to Big Pickle.

## [2026-09-15] DOCUMENT | Ingested Gemini follow-up on DNA codon mutation robustness

Extracted a new Gemini answer ("DNA Codon Structure and Mutation Robustness") from the live conversation (https://gemini.google.com/app/a35957a414e98087), a follow-up to the Digital Life Languages Survey. The answer explains codon redundancy, silent and conservative point mutations, and maps the lessons to digital evolution: redundant binary-to-opcode mapping, semantic proximity between similar instructions, and neutral networks / junk instructions. Reproduced it faithfully in Markdown at notes/dna-codon-mutation-robustness.md, complete with the prompt it answers, and added it to the index under Research and surveys. The answer's source chips could not be expanded to their source list (empty Angular placeholders; "View sources" does not open on trusted CDP input, matching the user's Chromium experience); the user later pasted the dialogue's chip labels and the deduplicated source appendix was appended to both copies of the note.

## [2026-09-14] VALIDATE | Execution-method and forager VM checkpoint confirmed

Ran the execution validation for the compiled/interpreted forager VM checkpoint on branch forager. Build and Lint passed. Focused suite (test_execution, test_forager): 20 passed. Full suite with local Csound runtime: 108 passed, no skips (94 baseline plus new execution tests), including real-session compiled/interpreted result comparison. Exploratory matrix of 36 runs (seeds 7/42/99, allowances 1/2/6, maintenance/compute, compiled and interpreted at 80 ticks, separate output dirs): all succeeded, compiled and interpreted reported identical population/births/deaths/prana-transferred for every combination; no extinction observed; interpreted runs compiled no genomes and produced no native artifacts. No fixes needed. Committed as part of this checkpoint.

## [2026-09-14] IMPLEMENT | Execution choices and bounded forager VM, validation pending

Added compiled/interpreted execution selection throughout CLI/settings/worker/desktop, with compiled default. Source-table execution remains directly supported; Forager selects forager-v1. Added immutable program dispatch and per-organism resumable state with a shared resource scheduler and primitives; compiled path specializes dispatch through Cython. Default six-instruction allowance matches authored program length and is configurable. Maintenance remains default; optional compute policy prepays one prana per configurable batch, default six, and disables Mt charging. Added run-wide execution metrics and explicit unsupported-language errors. Wrote tests/test_execution.py for native/interpreted trace and session comparisons, configuration and boundaries, but ran no tests/builds per user delegation to Big Pickle. Created notes/execution-validation.md handoff and docs/agent-execution.md; task completion remains pending validation. No version-control mutations. General stack language and aggregate resource caps remain unimplemented.

## [2026-09-14] IMPLEMENT | Compiled forager and exact prana-transfer option

Added Forager specificity to CLI/settings/desktop, specificity-owned genome vocabulary, authored compiled food-seeking program, and optional transfer reproduction alongside supported default preset funding. Transfers create/validate/register offspring before exact parent debit; children activate next lifecycle visit. Added parent/generation metadata and transfer metrics. On CA cells remain the food; initial environment is evolving XOR, not static. Recorded user policy to add supported options rather than compatibility layers. Updated roadmap/tasks and docs/forager.md. Interpreter and execution-method selection remain pending. Focused tests cover food and transfer failure invariants, with real compiled and session runs; Alpha regression, QML/settings, Build and Lint checked. Initial 80-tick seed-42 debug result: 884 births including three founders, generation 8, 10,572 prana transferred. Full suite repeated on the forager branch at commit check: Build and Lint passed; 94 tests passed, no skips (baseline 88 plus food/transfer tests).

## [2026-09-14] IMPLEMENT | Specificity label and revised evolutionary planning

Changed the desktop label and accessible name to Specificity, with a tooltip explaining world rules, population and seed genome; retained serialized preset fields for compatibility and aligned README/desktop documentation. Removed the completed terminology task from planning. Split conceptual docs/evolution-roadmap.md from sequential docs/evolution-tasklist.md, with cross-references. User-directed order: new forager specificity; compiled viable forager with exact parent-to-offspring prana transfer; framework execution-method option retaining compilation as default; bounded interpreter running the same forager. Compilation strategy/caching remains distinct from execution method. Instruction allowance must be configurable (64 was illustrative). Evaluate prana-per-computation instead of flat debits, and adapt compiled execution for equivalent semantics/charges. Interpreter details and compute prices remain open; no forager or backend code implemented in this documentation/label change. Validation: Build and Lint passed; QML settings/layout check and desktop smoke passed; 36 local documentation links including section anchors validated. Full suite: 84 passed and four desktop failures caused by the known sandbox socket restriction; all nine desktop tests then passed outside the sandbox, with no skips.

## [2026-09-14] DOCUMENT | Evolution roadmap and resolved desktop audio validation

User confirms reboot resolved the external audio outage and the windowed application runs correctly with sound. Removed the outage from current-evolution-system.md and corrected stale public desktop-architecture validation notes; retained resolution and the general-audience documentation preference in gotchas.md. Added docs/evolution-roadmap.md with bounded execution semantics, a hand-authored viable forager milestone, mutation/lineage work, decision points, optional development branches and acceptance checks. User likes the forager direction; detailed interpreter/ecology choices remain open. Recommended the desktop label Specificity with explanatory tooltip and saved-settings compatibility; label change remains under consideration and no UI/runtime changes were made. Validation: relative documentation links and whitespace checks.

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
