import topology as t
import neighborhood as n
import rule as r
import operator as o
import agent as a
import automaton as u

annuvin = t.ToroidTopology((100,100),0)
caer = n.VonNeumannNeighborhood(annuvin)
sidhe = r.ReductionRule(caer,(o.xor,0))
bran = a.Agent_2D(caer,caer,7,(210,210))
prydain = u.SynchronousAutomaton_2D(sidhe)
prydain.addAgent(bran)
p=prydain.givePopulation()

print p
print bran.tellAddress()
print bran.tellFacing()
bran.changeFacing(4)
print bran.tellFacing()
print bran.advance()
print bran.tellAddress()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.advance()
print bran.tellFacing()
print bran.tellAddress()
bran.changeFacing(2)
print bran.tellFacing()
print bran.move((100,100))
print bran.tellAddress()