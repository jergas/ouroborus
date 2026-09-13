# ADR 0001: Python and Cython stack

Status: Accepted (existing implementation)
Recorded: 2026-09-13
Evidence: root pyproject.toml, setup.py, docs/python3-port.md, and the completed port conversation.

## Decision and rationale

This is a Python project, not a pnpm/Node project. One setuptools distribution, ouroborus, installs the birdcage and worldish packages. Cython compiles seven Birdcage extensions plus worldish.code. Birdcage supplies automata, topologies, neighborhoods, rules, agents, and genomes; Worldish runs agents on those automata.

Python >=3.11 is declared; CPython 3.14.7 on Linux is the tested environment. The port used Cython 3.3.0, setuptools 84.0.0, Pillow 12.3.0, Pygame 2.6.1, ctcsound 6.17.1, and native Csound 6.18.1.

Cython and setuptools are runtime dependencies because Worldish compiles generated agent genomes in child processes using the running interpreter. Both individual and shared-genome compilation are supported. Pillow supplies imaging; Pygame and Csound are optional. Python's curses supports the terminal view.

## Local workflow

Use the repository's .venv, without sudo. Build with `.venv/bin/python setup.py build_ext --inplace`. Test with pytest; AGENTS.md includes the environment variables needed for the downloaded native Csound libraries. No dedicated linter is configured: the documented Lint entry performs Python syntax and Git whitespace checks. Cython syntax is checked by the build.

Native Csound is extracted under .deps/native rather than installed system-wide. The run-worldish wrapper supplies library and plugin paths. Python dependencies are in .venv. Generated environments, binaries, build/dist output, egg-info metadata, and .worldish run artifacts are ignored by Git.

## Consequences

Runtime genome compilation still requires a C compiler and Python headers. A working Birdcage build alone does not prove that generated Worldish agents compile. Audio tests require native libraries in addition to the pip ctcsound package.
