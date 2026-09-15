"""Supported offspring-placement choices, independent of energy funding."""
import random

PLACEMENTS = ("policy", "local", "random")


def resolve_placement(choice, reproduction_policy):
    if choice not in PLACEMENTS:
        raise ValueError("Unknown offspring placement")
    if reproduction_policy not in ("preset", "transfer"):
        raise ValueError("Unknown reproduction policy")
    if choice == "policy":
        return "local" if reproduction_policy == "transfer" else "random"
    return choice


def placement_settings(specific):
    requested = getattr(specific, "offspring_placement", "policy")
    funding = getattr(specific, "reproduction_policy", "preset")
    return {"requested": requested, "effective": resolve_placement(requested, funding)}


def offspring_address(organizer, parent, funding):
    placement = resolve_placement(getattr(organizer.specific, "offspring_placement", "policy"), funding)
    if placement == "local":
        return parent.agent.tellAddress()
    # Preserve the preset policy's historical two coordinate draws. No occupancy
    # filtering: both choices permit overlapping organisms and food contention.
    return (random.randint(0, organizer.width - 1), random.randint(0, organizer.height - 1))
