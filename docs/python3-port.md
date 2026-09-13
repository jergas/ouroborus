# Python 3 port

## Historical baseline

Source baseline: SVN r395 / Git `c85290d472406d22118b1f87a2ee1a7de718a1b7`.

A separate snapshot was exported to `/tmp/ouroborus-python2-baseline`. CPython 2.7.18 and Pyrex 0.9.9 were built locally. Modern GCC required `-std=gnu17` when building Python 2. Birdcage compiled, and all **58 original topology tests passed**. The Worldish genetics extension also compiled. The unmodified debug launcher could not complete startup: it stopped at the old `Image` import, and its broad ImportError fallback attempted the threaded mode instead. A complete Python 2 simulation was therefore not established; the new runs are not claimed to be bit-for-bit comparisons with a historical simulation.

The Python 2 experiment and its logs live under `/tmp`; the permanent original source/history remains in Git and the separate SVN archive. No system packages or desktop configuration were changed.

## What changed

- A root setuptools/Cython build installs Birdcage and Worldish together. Python 3 package-relative imports replace implicit Python 2 imports, and Cython declarations use qualified Birdcage imports.
- Python 2 print statements, dictionary iteration, old imports, deprecated threading calls, and `string.join` were updated. Integer division for topology centers remains integer division. Exception string methods now return strings.
- Runtime agent builds use the running virtual environment's interpreter in a child process. Compiler arguments and logging no longer overwrite the simulation's process state. Generated modules remain genuine compiled Cython extensions.
- Mass compilation now records compiled genomes and looks up the genome value instead of the literal string `"poeio"`; repeated agents share one module. Individual compilation remains available in configurations.
- The launcher reports invalid selections instead of silently switching modes on import failures, supports bounded/seeded runs, and keeps artifacts in an output directory. Runtime configuration replaces reliance on attributes of `__main__`.
- Older sequences now use current configuration filenames and dictionary-based agent registries. Beta and Delta use the current genome alphabet, preserving their earlier Von Neumann body/Moore sensor configuration in the fixed boilerplate. Epsilon still disables agents.
- Csound's removed `csnd.CppSound` API was replaced with `ctcsound.Csound` and the Csound 6 performance thread API. In-memory CSD compilation no longer names nonexistent orchestra/score files. Audio producers can be stopped and joined before Csound is cleaned up.
- The threaded sequence now hands display work to the main thread and propagates worker errors. It no longer launches an editor, invokes terminal reset commands, or relies on daemon threads to hide incomplete shutdown.
- The experimental sequence retains independently timed automaton and agent workers, with one/custom/per-agent choices. Access to the shared automaton and registry is protected by a lock, displays run on the main thread, and workers are joined at shutdown. This repairs its previously incomplete configuration, synchronization, and error handling; exact old thread timing is not preserved.
- Curses clips agent footprints to the visible area. Pygame is loaded only when selected and renders from an in-memory image; the old repeated resizing of an already enlarged buffer could grow the image on every agent update.

Some Python files mixed tabs and spaces. Indentation was normalized during conversion; whitespace accounts for part of the diff. Historical website and side-project source was not modernized.

## Validation

The final full suite passed on 2026-09-10: **76 tests in 61.97 seconds**, with no skips. This includes both the shared-genome and individual-genome compilation paths, plus a regression test that audio stays paused during genome compilation. The previous 75-test run had also completed successfully before the session interruption.

The test suite includes the original topology tests, real runtime genome compilation, all four configurations, agent lifecycle accounting, the normal display sequences, Pygame rendering with a dummy driver, three experimental scheduling choices, threaded error propagation, a real Csound WAV render, and an audio-enabled threaded simulation.

An installable Linux CPython 3.14 wheel was also built. Its extracted contents ran a five-iteration debug simulation outside the source checkout, compiling a genome and creating three agents. The wheel contains all eight extension modules and six Cython declaration files. Dependency consistency (`pip check`) and whitespace checks (`git diff --check`) passed.

Manual runs completed:

- Alpha debug: 200 iterations, including reproduction and death.
- Alpha curses: 20 iterations in a pseudo-terminal, with terminal restoration.
- Alpha Pygame: 30 iterations using SDL's dummy display.
- Alpha threaded with Csound: 25 iterations with silent output; Csound reported nonzero generated audio, zero clipped samples, and zero performance errors.
- Beta, Delta, Epsilon debug: 35 iterations each.
- The resumed launcher check exposed premature completion with silent audio during slow genome builds. Playback now stays paused until the agents have compiled. After the fix, the wrapper completed all ten requested threaded iterations using the local library/plugin paths, with nonzero audio, zero clipped samples, and zero Csound performance errors. The wheel was rebuilt and checked to contain the corrected startup code.

Validation used CPython 3.14.7, Cython 3.3.0, setuptools 84.0.0, Pillow 12.3.0, Pygame 2.6.1, ctcsound 6.17.1, and Csound 6.18.1. Python dependencies are isolated in `.venv`; the configured distribution mirror's Csound package was extracted into `.deps/native`, which the convenience launcher finds. Older Python 3 versions and other operating systems have not been tested. Physical audio playback and a visible desktop window have not been verified.

## References

- [Cython 3 migration guide](https://docs.cython.org/en/latest/src/userguide/migrating_to_cy30.html): Python 3 semantics and division changes.
- [Csound Python API](https://csound.com/docs/ctcsound/ctcsound-API.html) and [performance thread API](https://csound.com/docs/ctcsound/ctcsound-PT.html): Csound 6 integration.
