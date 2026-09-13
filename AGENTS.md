# Repository Instructions & Memory Protocol

## Context & Build Commands

Run from the repository root, using the project virtual environment. This is a Python/Cython project; no pnpm scripts are configured.

* Build: `.venv/bin/python setup.py build_ext --inplace`
* Test: `LD_LIBRARY_PATH="$PWD/.deps/native/usr/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}" OPCODE6DIR64="${OPCODE6DIR64:-$PWD/.deps/native/usr/lib/csound/plugins64-6.0}" .venv/bin/python -m pytest -q`
* Lint: `.venv/bin/python -m compileall -q birdcage worldish tests setup.py && git diff --check` (syntax and whitespace checks; no dedicated linter is configured).

The Test command includes the downloaded local Csound runtime. With system-installed Csound, `.venv/bin/python -m pytest -q` is sufficient. Audio tests skip if native libraries are unavailable; check skips before claiming full audio validation. Cython syntax is validated by Build. Circadian is retained for possible revival but is not part of the current port or checks.

For initial setup, use `python3 -m venv .venv` and `.venv/bin/python -m pip install -e '.[graphics,audio,test]'`. Native Csound 6 is a separate dependency; pip installs its Python binding only. Runtime genome compilation also needs Cython, setuptools, a C compiler, and Python headers. See `README.md` for examples and `docs/python3-port.md` for validation history.

## Memory Management Protocol

1. BEFORE REFACTORING OR WRITING CODE:
   * Read `.memory/wiki/index.md` and check `.memory/wiki/gotchas.md`.
   * Search for prior failures in `.memory/wiki/failed_approaches.md` before re-attempting complex fixes.
2. DURING AND AFTER WORK:
   * If you encounter a library bug, environment quirk, or make an architectural decision, immediately record it under `.memory/wiki/`.
   * Log significant changes in `.memory/wiki/log.md` using the format: `## [YYYY-MM-DD] ACTION | Summary`.
   * Never store architectural decisions or quirks solely in session-private memory.
