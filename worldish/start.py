#!/usr/bin/env python3
"""Launch Worldish. Original launcher by Jergas Apwith, Ernesto Illescas,
and Sat Tara Singh Khalsa; see the history below.
"""
import argparse
import importlib
import os
from pathlib import Path
import random
import sys

if not __package__:
    sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from worldish import runtime


def positive(value):
    value = int(value)
    if value <= 0:
        raise argparse.ArgumentTypeError("must be greater than zero")
    return value


def main(argv=None):
    parser = argparse.ArgumentParser(description="Run agents on a Birdcage cellular automaton.")
    parser.add_argument("-s", "--specificity", "--spec", default="alpha", type=str.lower,
                        choices=["alpha", "beta", "delta", "epsilon", "forager"])
    parser.add_argument("-m", "--mode", default="threaded", type=str.lower,
                        choices=["debug", "visual", "audiovisual", "threaded", "experimental", "session"])
    parser.add_argument("-n", "--submode", default="normal", type=str.capitalize)
    parser.add_argument("--execution-method", choices=["compiled", "interpreted"],
                        help="agent execution method (specificity default, otherwise compiled)")
    parser.add_argument("--instructions-per-tick", type=positive,
                        help="forager-v1 instruction allowance per live visit (1–4096)")
    parser.add_argument("--energy-policy", choices=["maintenance", "compute"])
    parser.add_argument("--instructions-per-prana", type=positive,
                        help="instructions prepaid by one prana under compute charging (1–4096)")
    parser.add_argument("--steps", type=positive, help="override the number of automaton iterations")
    parser.add_argument("--seed", type=int, help="seed Python's random generator for repeatable runs")
    parser.add_argument("--display", choices=["curses", "pygame", "debug"])
    parser.add_argument("--no-sound", action="store_true")
    parser.add_argument("--silent-audio", action="store_true", help="run Csound without an audio device")
    parser.add_argument("--fast", action="store_true", help="omit configured simulation delays")
    parser.add_argument("--agent-threads", choices=["one", "custom", "onePerAgent"],
                        help="agent scheduling for experimental mode")
    parser.add_argument("--agent-workers", type=positive, help="worker count for custom experimental scheduling")
    parser.add_argument("--output-dir", type=Path, default=Path(".worldish"),
                        help="directory for generated genomes and logs (default: .worldish)")
    parser.add_argument("--trace-mode", choices=["off", "events", "instructions"], default="off")
    parser.add_argument("--trace-limit", type=positive, default=100_000,
                        help="maximum recorded events (1–1,000,000); tracing defaults to off")
    parser.add_argument("--offspring-placement", choices=["policy", "local", "random"],
                        help="offspring position; policy retains the funding policy default")
    from .run_limits import RunLimits
    for field in RunLimits.__dataclass_fields__:
        parser.add_argument("--" + field.replace("_", "-"), type=int,
                            help="session stop threshold; 0 disables the limit")
    args = parser.parse_args(argv)
    from .observation import validate_trace
    try:
        validate_trace(args.trace_mode, args.trace_limit)
    except ValueError as error:
        parser.error(str(error))
    runtime.observation = None
    # Preserve the old debug/Beta shorthand while configuring every module consistently.
    if args.mode == "debug" and args.submode == "Beta":
        args.specificity, args.submode = "beta", "Normal"
    runtime.launch_metadata = {key: value for key, value in vars(args).items()
                               if key != "output_dir"}
    output = args.output_dir.resolve()
    output.mkdir(parents=True, exist_ok=True)
    (output / "creatures").mkdir(exist_ok=True)
    previous_dir = Path.cwd()
    previous_stdout, previous_stderr = sys.stdout, sys.stderr
    os.chdir(output)
    sys.path.insert(0, str(output))
    log = None
    try:
        runtime.specificity = args.specificity.capitalize()
        specific = runtime.get_specific()
        specific.trace_mode, specific.trace_limit = args.trace_mode, args.trace_limit
        if args.offspring_placement is not None:
            specific.offspring_placement = args.offspring_placement
        for field in RunLimits.__dataclass_fields__:
            if getattr(args, field) is not None:
                setattr(specific, field, getattr(args, field))
        try:
            limits = RunLimits.from_specificity(specific)
            if args.mode != "session" and any(vars(limits).values()):
                raise ValueError("Run stop thresholds require --mode session")
        except ValueError as error:
            parser.error(str(error))
        from .execution import ExecutionOptions
        for field in ExecutionOptions.__dataclass_fields__:
            value = getattr(args, field)
            if value is not None:
                setattr(specific, field, value)
        try:
            ExecutionOptions.from_specificity(specific).validate_language(
                getattr(specific, "genome_language", "source"), specific.compiling == "Void")
        except ValueError as error:
            parser.error(str(error))
        if args.agent_threads:
            specific.agentThreads = args.agent_threads
        if args.agent_workers is not None:
            specific.agentThreadsNumber = args.agent_workers
        if args.steps is not None:
            specific.doomsday = args.steps
        if args.seed is not None:
            random.seed(args.seed)
        if args.fast:
            specific.annumDelay = specific.agentsDelay = 0
        if args.display:
            specific.displayType = args.display
        if args.mode == "debug":
            specific.displayType = "debug"
        if args.silent_audio:
            specific.csOptions = "<CsoundSynthesizer>\n<CsOptions>\n-n -d -m0\n</CsOptions>"
        if args.no_sound or args.mode in ("debug", "visual"):
            specific.soundOn = False
        log = (output / specific.debugFileName).open("w", buffering=1)
        specific.debugFile = log
        # Keep stdout diagnostics away from the terminal display.
        specific.debugOutputToFile = specific.sysOutToFile = True
        runtime.mainSequence = importlib.import_module("worldish.sequence_" + args.mode)
        function = getattr(runtime.mainSequence, "startExecution" + args.submode, None)
        if function is None:
            parser.error(f"mode {args.mode} has no submode {args.submode}")
        print(f"Worldish: {args.specificity}, {args.mode}, {specific.doomsday} iterations")
        function()
    finally:
        if runtime.observation is not None:
            runtime.observation.close()
        sys.stdout, sys.stderr = previous_stdout, previous_stderr
        visual = sys.modules.get("worldish.visual")
        if visual is not None and hasattr(visual, "pygame"):
            visual.pygame.quit()
        if log:
            log.close()
        sys.path.remove(str(output))
        os.chdir(previous_dir)
    print(f"Worldish finished. Logs and generated genomes: {output}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

# History
#
# This little "ignition" module was added in 2008 by Sat Tara Singh
# while working late one night in the quiet city of Bikaner in
# Rajasthan, world capital of camels. Should you ever wander into
# this quiet place make sure to try the excellent cuisine at the
# Kishan Palace hotel, owned by the grandson of a Rajput lieutenant
# colonel of the former princely state. Allow ample time for the
# preparation of your meal.
#
# The whole  main_sequence thing was getting rather too bulky and
# debugging had become downright nightmarish. While in Amsterdam,
# Jergas did make a half-hearted suggestion that I use a debugger.
# Very smart, surely, but as I did then, let me ask again: who debugs
# the debugger?
#
# A few days later we ran into a mess when we realised Ernesto and I
# were working simultaneously on main_sequence. To solve this, I
# split the execution sequences into separate modules. I did this
# while sitting backwards on a train from the best and most decadent
# city in the world, which is Calcutta, towards Shantiniketan
# where Rabindranath Tagore put his ideal university. Functionality
# was then added to sort between the various sequences.
#
# A few years went idly by, and with my attention focused elsewhere
# in the architecture, this little piece of code grew into a
# seven-headed hydra, as command line options were added, along with
# non-standard code meant to parse it, every time someone needed one.
# I did not become aware of this sorry state of affairs until August
# 2011, while staying at a commune in an old house for hospital nurses
# in Mariannenplatz, in Kreuzberg, otherwise known as the place where
# things are happening in Berlin. My gracious host at the house was
# my friend Salima, who besides being a good yogini is also an
# outstanding vegan cook. The whole code was rewritten and should
# hopefully provide a more standard platform from which to initiate
# the whole ouroborus affair.
