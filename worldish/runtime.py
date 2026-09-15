"""Configuration shared by the legacy execution sequences."""
from importlib import import_module

specificity = "Alpha"
mainSequence = None


def get_specific(name=None):
    return import_module("worldish.specific_" + (name or specificity).lower())


def report_result(organizer, generator):
    """Write a small result record for checking completed example runs."""
    import json
    from dataclasses import asdict
    from pathlib import Path
    result = {
        "iterations": organizer.annum,
        "population": organizer.earth.tellPopulation(),
        "births": organizer.births,
        "deaths": organizer.deaths,
        "genotypes_compiled": (0 if generator.execution_options.execution_method == "interpreted"
                               else len(generator.scions) if generator.specific.compiling == "MassCompile"
                               else generator.obstetrics),
        "execution": {"version": 1, "genome_language": generator.genome_language,
                      **asdict(generator.execution_options)},
        "execution_metrics": dict(generator.execution_metrics),
        "genotypes_interpreted": len(generator.interpreted_programs),
    }
    if getattr(organizer, "reproduction_policy", "preset") == "transfer":
        result["prana_transferred"] = organizer.prana_transferred
        result["max_generation"] = organizer.max_generation
    Path("result.json").write_text(json.dumps(result, indent=2) + "\n")
    return result
