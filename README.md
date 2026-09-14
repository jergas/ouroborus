# Ouroborus

An artificial life project: agents live, feed, reproduce, and die on a cellular automaton. Worldish exposes the simulation through a terminal view, a Pygame view, and Csound voices.

The windowed **worldish-desktop** app is the main interface: it hosts the real curses terminal view and a graphical **Living grid** view, with start, pause, single-step and stop transport alongside specificity, seed, iteration limit, tick pacing, audio and JSON save/load settings. The same simulation also runs entirely from the command line, in Pygame, or with Csound voices.

- **birdcage/** — compiled cellular automata, neighborhoods, rules, agents, and genomes.
- **worldish/** — the agent framework, configurations, execution sequences, and audiovisual views.
- **website/** — the historical website.
- **circadian/** — retained for possible revival; not included in this Python 3 port.

The historical **ouroborus-cpp/** component was removed from the working tree; its contents remain in Git history and a separate backup tarball.

The original SVN history is retained in Git. See [the port notes](docs/python3-port.md) for the baseline, changes, and validation.

## Requirements

Use Python 3.11 or newer, a C compiler, and the Python development headers. The tested interpreter is CPython 3.14.7 on Linux; older Python 3 versions and other operating systems have not been tested. Curses is supplied by Python on supported Unix platforms.

The C compiler and headers are needed both to build the Cython extension modules at install time and because Worldish keeps translating genomes into extension modules while it runs.

Install them for your platform:

- Debian/Ubuntu: `sudo apt install build-essential python3-dev`
- Fedora/RHEL: `sudo dnf install gcc gcc-c++ python3-devel`
- Arch: `sudo pacman -S base-devel`
- macOS: `xcode-select --install` (Xcode Command Line Tools)

## Install

Clone the repository and install the package in a virtual environment:

```sh
git clone https://github.com/jergas/ouroborus.git
cd ouroborus
python3 -m venv .venv
.venv/bin/python -m pip install -e '.[desktop,audio,graphics,test]'
```

The extras are optional feature groups:

- `desktop` — the Qt windowed interface (`worldish-desktop`).
- `audio` — Csound voices (ctcsound, numpy).
- `graphics` — the Pygame view.
- `test` — the pytest test suite.

For a minimal debug/curses-only environment, install just `'.[test]'`; Pygame, the desktop, and Csound are optional. Cython and setuptools remain runtime dependencies because Worldish compiles genomes while running. Runtime builds take place inside the chosen output directory and require no root privileges.

The root build compiles all seven Birdcage modules and `worldish.code`. The old build-script entry points delegate to this build. Keep generated C, binaries, environments, and simulation logs out of Git.

## Optional: Csound 6 for audio

Sound is optional: every mode runs with audio **Off** when Csound is not installed. If you want the voices, install the native **Csound 6** engine — `pip install` only brings the `ctcsound` Python binding, not the engine itself.

```sh
# Debian/Ubuntu
sudo apt install csound
# Fedora/RHEL
sudo dnf install csound
# Arch
sudo pacman -S csound
# macOS (Homebrew)
brew install csound
```

On Windows, use the 64-bit installer from https://csound.com/download.

## Desktop application (Linux)

Start the windowed interface:

```sh
.venv/bin/worldish-desktop
```

or, equivalently:

```sh
.venv/bin/python -m worldish.desktop.app
```

The Qt desktop hosts the real curses view and a graphical **Living grid** view. Switching views preserves the running world. The sidebar provides the four existing specificities, iteration limit, random seed, tick pacing, audio output, volume/mute, and JSON save/load settings. Start, pause, single-step and stop controls remain visible while the settings scroll.

Native Csound 6 is required for audio; the launcher automatically uses the repository's `.deps/native` libraries when present. The desktop prefers PulseAudio when its runtime socket exists and otherwise uses PortAudio; `WORLDISH_AUDIO_BACKEND` can select `pulse`, `pa`, `alsa`, or `jack`. A device-open stall is stopped after 20 seconds and reported in the window. Select **Off** to run without Csound, or **Silent test** to exercise Csound without opening an audio device.

Specificity, seed, iteration limit and output changes apply on the next run. Pace, volume and mute apply live. Pause stops simulation ticks and fades audio to silence; Csound's musical clock continues, so resume does not rewind or preserve sample-exact audio timing. Single-step advances one automaton tick and its agent updates while keeping audio muted. Stop followed by Start applies draft settings to a new world. World sizes/rules and initial agent counts currently come from the selected legacy specificity.

Each run has a separate `.worldish/desktop/<run-id>/` directory containing its configuration, genomes, logs and result. **Run logs** opens that folder. Startup can take time while genomes compile. Stop and window close request cleanup and terminate the owned worker/compiler process group if necessary. Runtime failures appear in the window; diagnostic details remain in the run logs.

The terminal pane clips worlds larger than its available character grid; reduce **Text size**, enlarge the window, or choose **Living grid** to see the whole world. The terminal supports the curses output used here; it is not intended as a general-purpose terminal application.

For a headless window-load check:

```sh
QT_QPA_PLATFORM=offscreen QT_QUICK_BACKEND=software QT_QPA_PLATFORMTHEME=basic .venv/bin/python -m worldish.desktop.app --smoke-test
```

Desktop tests require permission to create a PTY and use the worker's inherited local socket. Existing CLI execution modes remain supported. See the [accepted desktop architecture](docs/desktop-architecture.md) for implementation boundaries and further work.

## Command-line usage

After installing the package, the `worldish` command is available in the virtual environment:

```sh
# Terminal view, without sound
.venv/bin/worldish --mode visual --steps 100 --seed 42

# Full threaded audiovisual example (uses your audio device)
.venv/bin/worldish --mode threaded --steps 100

# Debug run without a display or audio device
.venv/bin/worldish --mode debug --steps 200 --seed 42

# Exercise audio synthesis without playing it through a device
.venv/bin/worldish --mode threaded --display debug --silent-audio --steps 40 --fast
```

Within a source checkout, the convenience launcher `./run-worldish` is equivalent to `.venv/bin/python -m worldish.start` and additionally supplies the repository-local Csound library/plugin paths under `.deps/native/` when present.

Each run writes `debug_output.txt`, `build.log`, generated genomes, and `result.json` into `.worldish/`. Use `--output-dir PATH` for separate runs. Do not run two simulations against the same output directory simultaneously. `--seed` makes random choices repeatable in the sequential modes; independently scheduled experimental workers are timing-dependent.

Other options:

- `--specificity alpha|beta|delta|epsilon`: configuration; Epsilon runs without agents.
- `--mode debug|visual|audiovisual|threaded|experimental`: execution sequence.
- `--display curses|pygame|debug`: view, except debug mode always uses its textual view.
- `--no-sound`: disable audio; visual and debug modes already do this.
- `--fast`: omit configured delays (experimental workers retain a 1 ms scheduling yield).
- `--agent-threads one|custom|onePerAgent`, `--agent-workers N`: experimental scheduling.

The controllable execution loop is also available without Qt:

```sh
.venv/bin/worldish --mode session --display curses --steps 200 --seed 42
```

## Test

```sh
# With system-installed Csound
.venv/bin/python -m pytest -q

# With a local Csound extraction under .deps/native
LD_LIBRARY_PATH="$PWD/.deps/native/usr/lib" .venv/bin/python -m pytest -q
```

Audio tests explicitly skip if native Csound libraries are unavailable. Pygame tests use SDL's dummy display driver. These do not verify physical speakers or a desktop window.