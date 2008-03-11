import topology as t
import neighborhood as n
import rule as r
import operator as o
import agent as a
import automaton as u
import genome as g
import visual as v
import random

size = (80,27)
iterate = 30000

tabula = {'aa':'self.changeFacing(3)', 'ab':'self.advance()', 'ap':'print self.tellAddress()'}
poeio = ['a','a','a','b']
samskara = g.Genome(poeio, tabula, 2)

annuvin = t.ToroidTopology(size,0)
caer = n.VonNeumannNeighborhood(annuvin)
sidhe = r.ReductionRule(caer,(o.xor,0))
prydain = u.SynchronousAutomaton_2D(sidhe)
bran = a.Agent_2D(samskara,caer,caer,7,1,(40,15))
gwydion = a.Agent_2D(samskara,caer,caer,7,1,(45,5))
amatheon = a.Agent_2D(samskara,caer,caer,7,1,(30,8))
gwion = a.Agent_2D(samskara,caer,caer,7,1,(10,12))

prydain.addAgent(bran)
prydain.addAgent(gwydion)
prydain.addAgent(amatheon)
prydain.addAgent(gwion)
prydain.set((11,10),1)
prydain.set((9,10),1)
prydain.set((10,11),1)
prydain.set((10,9),1)
bran.changeFacing(1)
gwydion.changeFacing(2)
amatheon.changeFacing(3)
gwion.changeFacing(4)

v.fireUpCurses()
pad = v.makePad(size)

v.updateLoop2(prydain, pad[0], size)
v.refreshDisplay(pad)

t = 0
print "t = %i\r" % (t)
    
for i in range(iterate):
    prydain.update()
    t = t+1
    v.updateLoop2(prydain, pad[0], size)
    a = random.randint(0,4)
    amatheon.changeFacing(a)
    amatheon.advance()
    a = random.randint(0,4)
    bran.changeFacing(a)
    bran.advance()
    a = random.randint(0,4)
    gwydion.changeFacing(a)
    gwydion.advance()
    a = random.randint(0,4)
    gwion.changeFacing(a)
    gwion.advance()
    v.refreshDisplay(pad)
    print "t = %i" % (t)



raw_input("Done")

 
