# Python 3 port status

Snapshot recorded 2026-09-13 from the completed 2026-09-10 validation and current checkout. Detailed rationale and commands: [port notes](../../docs/python3-port.md), [README](../../README.md), and [AGENTS.md](../../AGENTS.md).

## Completed

- Birdcage and Worldish ported to Python 3/Cython, including all eight extensions and runtime-generated agent modules.
- Root packaging and virtual environment established; Csound native runtime downloaded locally.
- Current examples cover debug, visual, audiovisual, threaded, and experimental execution. Alpha/Beta/Delta contain agents; Epsilon disables them.
- Thread cleanup, error propagation, genome caching, display clipping/rendering, and deferred audio startup were debugged.
- 76 tests passed without skips in 61.97 seconds on 2026-09-10. Coverage includes the original 58 topology tests, all configurations, shared/individual genome builds, birth/death accounting, graphics, experimental scheduling, worker failure propagation, real WAV rendering, and audio startup.
- Manual runs included 200 debug iterations, curses in a pseudo-terminal, Pygame with a dummy driver, and audio-enabled threaded runs. The corrected wrapper completed all ten requested iterations with nonzero audio and no Csound errors/clipping.
- A CPython 3.14 Linux wheel was built; an extracted wheel ran outside the source checkout. It includes eight extensions and six .pxd files. The final wheel was rebuilt after the audio-startup fix.
- Source syntax, Git whitespace checks, and pip dependency consistency passed.

## Limits and future work

On 2026-09-13 the user confirmed they heard Csound during the initial Python 3 terminal test. A visible desktop Pygame window has not been verified. Other Python 3 versions/platforms have not been tested. A complete unmodified Python 2 Worldish run was not established, so exact historical trajectory equivalence is not claimed.

Circadian is retained as a possible future revival, not already ported. The user intends further improvement before publishing on GitHub or a similar host; no exact next feature or hosting destination is selected.

On 2026-09-13, ouroborus-cpp removal was committed, but the port and new documentation still appeared as working-tree changes. This status is a dated observation, not a claim about future Git state.

## Quick start

From the repository root: `./run-worldish --mode visual --steps 100 --seed 42`.
For no display/device: `./run-worldish --mode debug --steps 200 --seed 42`.
For synthesis without speakers: `./run-worldish --mode threaded --display debug --silent-audio --steps 40 --fast`.

The full test suite was not rerun just to populate memory on 2026-09-13; consult the dated validation above.
