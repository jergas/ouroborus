import topology as t
import neighborhood as n
import rule as r
import operator as o
import agent as a
import automaton as u

annuvin = t.ToroidTopology((100,100),0)
caer = n.VonNeumannNeighborhood(annuvin)
sidhe = r.ReductionRule(caer,(o.xor,0))
bran = a.Agent_2D(caer,caer,7,1,(210,210))
prydain = u.SynchronousAutomaton_2D(sidhe)
prydain.addAgent(bran)

prydain.set((11,11),1)
print bran.tellPrana()
bran.changeFacing(3)
bran.advance()
print bran.eatMana()
bran.changeFacing(2)
bran.advance()
print bran.eatMana()
print bran.tellPrana()
print prydain.get((11,11))