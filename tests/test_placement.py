"""Placement choices preserve funding and default random consumption."""
import random
from types import SimpleNamespace

import pytest

from worldish.config import SimulationConfig
from worldish.placement import offspring_address, resolve_placement
from worldish.reproduction import transfer_birth
from test_forager import family


def test_policy_defaults_preserve_rng_sequence():
    world = SimpleNamespace(specific=SimpleNamespace(), width=80, height=20)
    parent = SimpleNamespace(agent=SimpleNamespace(tellAddress=lambda: (4, 5)))
    random.seed(42)
    before = random.getstate()
    assert offspring_address(world, parent, "transfer") == (4, 5)
    assert random.getstate() == before
    expected = (random.randint(0, 79), random.randint(0, 19))
    after = random.getstate()
    random.setstate(before)
    assert offspring_address(world, parent, "preset") == expected
    assert random.getstate() == after
    with pytest.raises(ValueError):
        resolve_placement("nearest", "transfer")
    with pytest.raises(ValueError):
        SimulationConfig(offspring_placement="nearest")


@pytest.mark.parametrize("placement", ["local", "random"])
def test_placement_does_not_change_exact_transfer(family, monkeypatch, placement):
    world, parent, bodies = family
    world.height = 5
    world.specific.offspring_placement = placement
    draws = []
    def draw(low, high):
        draws.append((low, high))
        return 4
    monkeypatch.setattr(random, "randint", draw)
    child_name = transfer_birth(world, parent)
    expected = (2, 2) if placement == "local" else (4, 4)
    assert world.book[child_name].fatum["address"] == expected
    assert len(draws) == (0 if placement == "local" else 2)
    assert parent.agent.tellPrana() == 18
    assert world.book[child_name].agent.tellPrana() == 12
    assert sum(body.tellPrana() for body in bodies) == 30
    # Duplicate requests never draw a second position or charge twice.
    assert transfer_birth(world, parent) is None
    assert len(draws) == (0 if placement == "local" else 2)


def test_insufficient_funds_do_not_draw_a_position(family, monkeypatch):
    world, parent, _ = family
    world.specific.offspring_placement = "random"
    parent.agent.losePrana(25)
    def fail(*args):
        raise AssertionError("Rejected birth drew randomness")
    monkeypatch.setattr(random, "randint", fail)
    assert transfer_birth(world, parent) is None
