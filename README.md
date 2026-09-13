# Ouroborus

An artificial life project: agents live, feed, reproduce, and die on a cellular automaton. Worldish exposes the simulation through a terminal view, a Pygame view, and Csound voices.

- **birdcage/** — compiled cellular automata, neighborhoods, rules, agents, and genomes.
- **worldish/** — the agent framework, configurations, execution sequences, and audiovisual views.
- **website/** — the historical website.
- **circadian/** — retained for possible revival; not included in this Python 3 port.

The historical **ouroborus-cpp/** component was removed from the working tree; its contents remain in Git history and a separate backup tarball.

The original SVN history is retained in Git. See [the port notes](docs/python3-port.md) for the baseline, changes, and validation.

## Run on this machine

Dependencies are already installed in `.venv/`, with Csound 6 extracted into `.deps/native/`. The wrapper supplies the local Csound library/plugin paths.

```sh
# Terminal view, without sound
./run-worldish --mode visual --steps 100 --seed 42

# Full threaded audiovisual example (uses your audio device)
./run-worldish --mode threaded --steps 100

# Debug run without a display or audio device
./run-worldish --mode debug --steps 200 --seed 42

# Exercise audio synthesis without playing it through a device
./run-worldish --mode threaded --display debug --silent-audio --steps 40 --fast
```

Each run writes `debug_output.txt`, `build.log`, generated genomes, and `result.json` into `.worldish/`. Use `--output-dir PATH` for separate runs. Do not run two simulations against the same output directory simultaneously. `--seed` makes random choices repeatable in the sequential modes; independently scheduled experimental workers are timing-dependent.

Other options:

- `--specificity alpha|beta|delta|epsilon`: configuration; Epsilon runs without agents.
- `--mode debug|visual|audiovisual|threaded|experimental`: execution sequence.
- `--display curses|pygame|debug`: view, except debug mode always uses its textual view.
- `--no-sound`: disable audio; visual and debug modes already do this.
- `--fast`: omit configured delays (experimental workers retain a 1 ms scheduling yield).
- `--agent-threads one|custom|onePerAgent`, `--agent-workers N`: experimental scheduling.

## Install elsewhere

Use Python 3.11 or newer, a C compiler, and Python development headers. The tested interpreter is CPython 3.14.7 on Linux. Curses is supplied by Python on supported Unix platforms. Audio additionally requires **Csound 6** and its shared libraries; pip installs the Python binding, not the native engine.

```sh
python3 -m venv .venv
.venv/bin/python -m pip install -e '.[graphics,audio,test]'
.venv/bin/worldish --mode visual --steps 100
```

For debug/curses-only use, install `-e '.[test]'`. Pygame and Csound are optional. Cython and setuptools remain runtime dependencies because Worldish translates genomes into extension modules while running. Runtime builds take place inside the chosen output directory and require no root privileges.

The root build compiles all seven Birdcage modules and `worldish.code`. The old build-script entry points delegate to this build. Keep generated C, binaries, environments, and simulation logs out of Git.

## Test

```sh
# With system-installed Csound
.venv/bin/python -m pytest -q

# With the local Csound downloaded on this machine
LD_LIBRARY_PATH="$PWD/.deps/native/usr/lib" .venv/bin/python -m pytest -q
```

Audio tests explicitly skip if native Csound libraries are unavailable. Pygame tests use SDL's dummy display driver. These do not verify physical speakers or a desktop window.
