"""Configuration shared by the legacy execution sequences."""
from importlib import import_module

specificity = "Alpha"
mainSequence = None


def get_specific(name=None):
    return import_module("worldish.specific_" + (name or specificity).lower())


def report_result(organizer, generator):
    """Write a small result record for checking completed example runs."""
    import json
    from pathlib import Path
    result = {
        "iterations": organizer.annum,
        "population": organizer.earth.tellPopulation(),
        "births": organizer.births,
        "deaths": organizer.deaths,
        "genotypes_compiled": len(generator.scions) if generator.specific.compiling == "MassCompile" else generator.obstetrics,
    }
    Path("result.json").write_text(json.dumps(result, indent=2) + "\n")
    return result
