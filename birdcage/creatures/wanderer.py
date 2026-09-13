from birdcage import topology, neighborhood, rule, automaton, agent, genome
import operator
import random
topos = topology.ToroidTopology((90,40),0)
ball = neighborhood.VonNeumannNeighborhood(topos)
change = rule.ReductionRule(ball,(operator.xor,0))
robot = automaton.SynchronousAutomaton_2D(change)
myself = agent.Agent_2D(genome.Genome([],{},2),ball,ball,7,1,(30,8))
def wander():
  direction = random.randint(0,4)
  myself.changeFacing(direction)
  myself.advance()
def __print__():
  print(myself.tellAddress())
