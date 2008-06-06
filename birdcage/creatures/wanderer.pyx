import topology; import neighborhood; import rule; import operator; import automaton; import agent; import genome; import random
def beBorn(topos):
  ball = neighborhood.VonNeumannNeighborhood(topos)
  myself = agent.Agent_2D(genome.Genome([],{},2),ball,ball,50,1,(30,8))
  return myself
def wander(agent):
  direction = random.randint(0,4)
  agent.changeFacing(direction)
  agent.advance()
  agent.eatMana()
