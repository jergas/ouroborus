# Environment and Library Gotchas

Recorded 2026-09-13 from the port and its confirmed validation.

## Builds and generated files

- Python 2 distutils/Pyrex build scripts are obsolete. The maintained build is root setuptools/Cython; legacy build entry points delegate to it. The old bilingual READMEs explicitly label their sudo commands historical.
- Worldish compiles genomes at runtime. Cython, setuptools, the C compiler, and Python headers must remain available after the initial installation. The child process uses the same Python interpreter as the simulation.
- .venv, .deps, build, dist, *.egg-info, generated C/extensions, and .worldish outputs are generated/local artifacts. Egg-info is setuptools distribution metadata, not handwritten application source.
- Runs write genomes, build.log, debug_output.txt, and result.json into .worldish or --output-dir. Concurrent runs must use separate output directories.
- .memory/wiki is intended to be tracked; most port changes and the new docs/configuration were still uncommitted/untracked on 2026-09-13. Inspect Git state before staging or committing unrelated work.

## Native audio and graphics

- Installing ctcsound with pip does not install Csound itself. Local native libraries are under .deps/native/usr/lib; plugins are under its csound/plugins64-6.0 subdirectory. run-worldish supplies LD_LIBRARY_PATH and OPCODE6DIR64.
- Without native Csound, audio tests skip; a green suite with skips is not full audio validation. With the local libraries, 76 tests passed without skips on 2026-09-10.
- Csound performance must stay paused until genome compilation finishes. Silent output is unpaced and can exhaust the score during slow compilation, causing early termination despite a zero exit code. Check result.json iterations, not just process success.
- Stop/join audio producer threads before cleaning up the native Csound server.
- Pygame loads only when requested. SDL_VIDEODRIVER=dummy exercises rendering without opening a desktop window. Curses was exercised in a pseudo-terminal. The user later confirmed physical Csound playback in the initial Python 3 terminal test; a visible Pygame window remains unverified.

## Semantics and concurrency

- Preserve integer division in topology centers; Python 3 true division would change coordinates. Exception __str__ methods must return text.
- Snapshot the agent dictionary while iterating when births/deaths can mutate it.
- Keep curses/Pygame updates on the main thread and propagate worker failures. Experimental workers share a locked automaton/registry and must be joined on shutdown.
- --seed is useful for sequential repeatability; independent experimental thread timing is not deterministic.
- /tmp Python 2 experiments and logs are temporary, not durable backups. System installation originally required a sudo password; the migration and port used local tools/environments instead.

## Qt desktop shell

- For sandboxed headless checks set QT_QPA_PLATFORM=offscreen, QT_QUICK_BACKEND=software and QT_QPA_PLATFORMTHEME=basic. The inherited desktop theme otherwise loads GTK and attempts to open the display even with the offscreen platform.
- Package the QML resource directory explicitly; setuptools otherwise warns it is an undeclared importable namespace.
- Desktop tests must override (not setdefault) QT_QPA_PLATFORM and QT_QPA_PLATFORMTHEME: this shell inherits wayland;xcb and gtk3. Leaving these values in place caused a Qt platform-integration SIGABRT during QGuiApplication construction; coredump confirmed the startup stack. Explicit offscreen/basic resolved it.
- The sandbox permits creating a socketpair but rejects the child's socket wrapper around the inherited descriptor (PermissionError). Real desktop worker integration tests need execution outside that sandbox; this is not a remote network connection.
- Master audio control uses a `worldish_attenuation` channel (0 means full gain) so standalone CSD rendering without a Python SoundServer keeps its previous default output. Both stereo channels apply a smoothed gain; desktop pause mutes output but deliberately leaves the musical clock running.
- Keep desktop transport controls outside the scrolling settings region; screenshot inspection caught them disappearing below the initial 740-pixel window once real settings were added. A QML check now verifies visibility at the 800×560 minimum size.

- Resolved 2026-09-14: the user reports that rebooting fixed the machine-wide audio outage and that the new windowed application runs correctly with sound. The outage was external to the project; desktop audio is user-confirmed working. The earlier restriction on live-device probes pending resolution is no longer applicable. Historical diagnostic details remain in log.md.

## Browser automation harvest tooling

- To attach via CDP (Chromium) or WebDriver BiDi (Firefox) the browser must be STARTED with `--remote-debugging-port`. You cannot attach to an already-running instance that lacks the flag; rerun the `launch` subcommand.
- Firefox BiDi has no WebDriver HTTP `/session` endpoint. Connect the websocket directly to `ws://localhost:PORT/session` and send `session.new` (with `capabilities.alwaysMatch.browserName`) as the first command.
- Firefox `script.evaluate` requires an explicit `awaitPromise` boolean and only accepts `resultOwnership` of `none` or `root` — `byValue` is rejected with an "invalid argument" error. Firefox `browsingContext.getTree` omits the context `type` field; match tabs by URL.
- Chromium tabs list is served at `http://localhost:PORT/json/list`; the instance launched without `--remote-allow-origins` still answers websockets only when the client sends `suppress_origin=True`. New `launch` invocations include `--remote-allow-origins=*` for robustness.
- Chromium's Gemini "View sources" dialog renders citation chips as empty Angular placeholders; extraction returns nothing no matter the input method. Firefox's source lists are plain DOM text and harvest cleanly via the `.deep-research-source-lists` class selector.
- Browsers reject sharing a profile directory between two running instances; each debug instance needs its own `--user-data-dir` (Chromium) / `-profile` (Firefox) and its own port.
- The earlier Chromium profile in `/tmp/opencode/gemini-profile` is volatile across reboots; choose a persistent `--profile-dir` outside `/tmp` for reusable agent sessions.

## Public documentation audience

- User preference, 2026-09-14: write public documentation for a general audience and avoid details specific to the user's hardware or local incidents unless necessary. Such context can remain in project memory. Relevant platform requirements and reproducibility details are still appropriate when needed.

## Framework extension policy

- User decision, 2026-09-14: favor adding new supported options and choosing preferred defaults. Existing behavior remains a valid first-class option rather than being demoted to legacy behavior requiring compatibility layers.
- CA on bits ARE food. Forager specificity uses an evolving XOR rule; static cell setups are focused tests only. No separate food layer was introduced.

## Implementation and validation workflow

- User direction, 2026-09-14: Big Pickle in a separate session owns version control and test execution; it should report failures rather than fix them. This agent implements and supplies validation handoffs. User reports the previous forager checkpoint committed on branch forager with tests reporting no errors. Do not infer validation of later edits from that report.
