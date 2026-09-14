"""Forager food semantics and transactional offspring funding."""
from types import SimpleNamespace

import pytest

from birdcage.agent import Agent_2D
from birdcage.neighborhood import MooreNeighborhood
from birdcage.topology import ToroidTopology
from birdcage.genome import Genome
from worldish.forager import SEED_CODE, vocabulary
from worldish.reproduction import transfer_birth


def make_body(prana=30):
    grid = ToroidTopology((5, 5), 0)
    return Agent_2D(SEED_CODE, MooreNeighborhood(grid), MooreNeighborhood(grid), prana, 1, (2, 2))


def test_forager_senses_and_consumes_ca_food():
    program = {}
    exec(Genome(SEED_CODE, vocabulary(), 2).parse(), program)
    body = make_body(10)
    target = body.tellDirections()[1]
    body.returnTopology().set(target, 1)
    assert program['live'](body) == 'Live'
    assert body.tellAddress() == target
    assert body.returnTopology().get(target) == 0
    assert body.tellPrana() == 14  # five from the cell, one maintenance


@pytest.fixture
def family(monkeypatch):
    from worldish import sound_globals
    monkeypatch.setattr(sound_globals, 'simWSound', 0)
    parent = SimpleNamespace(name='parent', agent=make_body(),
                             fatum={'code': SEED_CODE, 'prayer': 'GrantChild'})
    bodies = [parent.agent]
    book = {'parent': parent}
    def generate(code, registry):
        child = SimpleNamespace(agent=None, fatum={}, callModule=lambda: None)
        def instantiate(earth):
            child.agent = make_body(child.fatum['prana'])
        child.instantiateAgent = instantiate
        registry['child'] = child
        return 'child'
    organizer = SimpleNamespace(specific=SimpleNamespace(offspring_prana=12, mana=1),
        generator=SimpleNamespace(generateGenotype=generate), book=book,
        earth=SimpleNamespace(addAgent=bodies.append, removeAgent=lambda a: bodies.remove(a) if a in bodies else None),
        width=5, births=1, prana_transferred=0, max_generation=0)
    return organizer, parent, bodies


def test_exact_transfer_and_duplicate_request(family):
    world, parent, bodies = family
    assert transfer_birth(world, parent) == 'child'
    child = world.book['child']
    assert parent.agent.tellPrana() == 18
    assert child.agent.tellPrana() == 12
    assert sum(body.tellPrana() for body in bodies) == 30
    assert world.births == 2 and world.prana_transferred == 12
    assert child.fatum['generation'] == 1
    assert transfer_birth(world, parent) is None
    assert len(bodies) == 2


def test_insufficient_energy_does_not_create_child(family):
    world, parent, bodies = family
    parent.agent.losePrana(20)
    assert transfer_birth(world, parent) is None
    assert parent.agent.tellPrana() == 10
    assert len(world.book) == len(bodies) == 1


def test_constructor_failure_does_not_debit_parent(family):
    world, parent, bodies = family
    generate = world.generator.generateGenotype
    def failing(code, registry):
        name = generate(code, registry)
        def fail(earth):
            raise RuntimeError('constructor failed')
        registry[name].instantiateAgent = fail
        return name
    world.generator.generateGenotype = failing
    with pytest.raises(RuntimeError, match='constructor failed'):
        transfer_birth(world, parent)
    assert parent.agent.tellPrana() == 30
    assert list(world.book) == ['parent'] and len(bodies) == 1
    assert world.births == 1 and world.prana_transferred == 0


def test_constructor_cannot_mint_energy(family):
    world, parent, bodies = family
    generate = world.generator.generateGenotype
    def dishonest(code, registry):
        name = generate(code, registry)
        def instantiate(earth):
            registry[name].agent = make_body(99)
        registry[name].instantiateAgent = instantiate
        return name
    world.generator.generateGenotype = dishonest
    with pytest.raises(ValueError, match='preserve transferred'):
        transfer_birth(world, parent)
    assert parent.agent.tellPrana() == 30
    assert len(world.book) == len(bodies) == 1


def test_real_compiled_forager(tmp_path):
    from test_worldish import run_example
    result, _ = run_example(tmp_path, '--specificity', 'forager', '--mode', 'debug')
    assert result['iterations'] == 40
    assert result['population'] == result['births'] - result['deaths']
    assert result['max_generation'] >= 2
    assert result['genotypes_compiled'] == 1
    assert result['prana_transferred'] == (result['births'] - 3) * 12
