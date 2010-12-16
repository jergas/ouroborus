# This file contains the dictionary that defines the genetic system.
# The system is a dictionary, where every genetic word corresponds to a line of
# code. This dictionary must always implement the 'boilerplate' key. This
# special word is fixed, always included first by default, and cannot mutate.
# It would make no sense for the initial imports and setup to mutate.

tabula = {'boilerplate':'import birdcage.topology as topology; import birdcage.neighborhood as neighborhood; import birdcage.agent as agent; corporality = neighborhood.MooreNeighborhood; sensoriality = neighborhood.MooreNeighborhood',
          'Cb':'def birth(earth, code, prana, mana, address):',
          'Cd':'  myself = agent.Agent_2D(code,corporality(earth.returnTopology()),sensoriality(earth.returnTopology()),prana,mana,address)',
          'Cr':'  return myself',
          'Ld':'def live(creature):',
          'Lp':'  prayer = "Live"',
          'Lm':'  move(creature)',
          'Ll':'  creature.losePrana(1)',
          'Le':'  creature.eatMana()',
          'Iy':'  if creature.tellPrana() > 27:',
          'Ir':'      prayer = "GrantChild"',
          'Ip':'      reproduce(creature)',
          'Ix':'  elif creature.tellPrana() <= 0:',
          'Ik':'      prayer = "KillMe"',
          'Lr':'  return prayer',
          'Md':'def move(creature):',
          'Mf':'  creature.randomFacing()',
          'Ma':'  creature.advance()',
          'Mr':'  return',
          'Rd':'def reproduce(creature):',
          'Rl':'  creature.losePrana(14)',
          'Rp':'  prayer = "Live"',
          'Rr':'  return prayer'}
  

tabula_antica = {'Yi':'import topology; import neighborhood; import agent',
          'Yc':'corporality = neighborhood.VonNeumannNeighborhood',
          'Ys':'sensoriality = neighborhood.VonNeumannNeighborhood',
          'Cb':'def birth(earth, code, prana, mana, address):',
          'Cd':'  myself = agent.Agent_2D(code,corporality(earth.returnTopology()),sensoriality(earth.returnTopology()),prana,mana,address)',
          'Cr':'  return myself',
          'Tl':'def live(creature, numen, index):',
          'Te':'  pass # creature.eatMana()',
          'Tr':'  if creature.tellPrana() > 11: reproduce(creature, numen, index)',
          'Tp':'  pass',
          'Rd':'def reproduce(creature, numen, index):',
          'Rp':'  numen[index-1][4]["prayer"]="GRANT_CHILD"',
          'Rc':'  numen[index-1][4]["code"]=creature.tellCode()',
          'Rl':'  creature.losePrana(10)'}

