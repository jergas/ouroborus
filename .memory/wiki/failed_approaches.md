# Failed Implementation Paths

Recorded 2026-09-13. These are historical failures and resolutions, not pending instructions.

## Treating an SVN checkout as the complete migration

A checkout is only a working copy, and Git cannot natively retain every SVN property, empty directory, or exact subsecond timestamp. Resolution: archive the complete remotely exposed SVN dump and verbose XML log, restore SVN locally, then import history into Git and verify all revisions. See migration.md.

## Running the historical source unchanged

Python 3.14 rejected Python 2 print syntax and lacked distutils. A temporary Python 2.7/Pyrex environment compiled Birdcage and passed its 58 tests, but unmodified Worldish stopped at the old Image import; a broad ImportError handler misleadingly fell back to threaded mode. Resolution: modernize packaging/imports and report selection/import errors directly. No complete historical simulation was established for bit-for-bit comparison.

## Reusing the old runtime compiler and genome cache

In-process distutils setup changed argv/stdout. The shared-genome cache looked up the literal "poeio" rather than the genome value and failed to record compiled strains. Resolution: isolated child-process builds and a populated cache keyed by actual genome values; both compilation paths are covered by tests.

## Reusing legacy example data structures and configuration names

Some sequences imported pre-rename configuration modules or used list-style agent registries after the framework changed to dictionaries. Beta/Delta still referenced old import genes. Resolution: current module names, dictionary registries, and the current genome alphabet with explicit historical body/sensor boilerplate.

## Keeping the removed Csound API

csnd.CppSound and command strings naming nonexistent temp.orc/temp.sco files are obsolete. Resolution: ctcsound.Csound, in-memory CSD compilation, and Csound 6 performance-thread methods.

## Starting silent playback before genome compilation

The score could finish while Cython/GCC built the first agents; a launcher requesting ten iterations completed only one yet exited successfully. Resolution: prepare a paused performance and start playback only after simulation initialization. A regression test checks no score-time progression during the build phase.

## Retaining old display and thread behavior

Repeatedly enlarging the Pygame buffer could grow the image on each agent update. Old thread handling could swallow errors or wait indefinitely and leave cleanup to daemon exit. Resolution: in-memory rendering at grid resolution, explicit main-thread display dispatch, error propagation, locked experimental state, interruptible audio producers, and joined workers.
