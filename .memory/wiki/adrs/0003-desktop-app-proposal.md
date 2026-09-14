# Desktop application architecture

Status: accepted by the user on 2026-09-13; initial working implementation completed after the user restored the session budget and confirmed the shell runs.

The desktop uses optional PySide6/Qt Quick and pyte dependencies. A managed Linux worker owns Worldish, generated-genome compiler children and Csound. Real curses output travels over a PTY; a separate bounded, versioned JSON socket-pair protocol carries commands, states and snapshots. Qt remains in the GUI process. Stop/close escalates against only the owned process group when cooperative shutdown cannot complete.

The purple/green shell has a scrollable left settings area with fixed transport controls. It supports preset, iteration limit, seed, pacing, audio output, volume/mute, JSON save/load, start/stop, pause/resume and single tick. Terminal and Living grid views observe the same world and can switch live. Grid snapshots are coalesced for GUI display; lifecycle/control messages remain ordered. Each run has its own .worldish/desktop/<run-id>/ directory and logs.

The new `worldish --mode session` CLI mode reuses ThreadedSequence initialization and lifecycle helpers, but advances ticks and curses on the worker process main thread. Old CLI modes remain supported; Birdcage is Qt-free. Curses initialization historically plants one seed cell, so it happens once, never on view switches. Pause freezes simulation ticks and fades master audio gain to zero while the Csound/background musical clock continues; sample-exact audio pause/resume is not promised. Audio performance still waits for genome compilation.

An audio-open phase is capped at 20 seconds before terminating the worker with an actionable error. Desktop output selects PulseAudio if its runtime socket exists, otherwise PortAudio, with WORLDISH_AUDIO_BACKEND override (pulse/pa/alsa/jack). No desktop or audio-service configuration is changed.

Remaining extensions: configurable world dimensions/rules/genomes and initial population, audio-device enumeration, grid zoom/panning, and further extraction from legacy global configuration. Existing preset sizes/rules remain authoritative. Launch `.venv/bin/python -m worldish.desktop.app`; installed entry point `worldish-desktop`. See [full architecture and implementation status](../../../docs/desktop-architecture.md).

The user confirmed audible Csound during the initial Python 3 port terminal test. During desktop implementation they reported every app has lacked audible output since the previous day despite volume meters moving, and intend to try rebooting. Current device-opening stalls therefore do not establish a desktop regression. Silent synthesis, generated WAVs and headless GUI tests are the usable validation paths until the machine-wide audio issue is resolved. The agent did not reboot or restart audio services.
