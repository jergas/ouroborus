






tabula = {'Yi':'import topology; import neighborhood; import agent',
          'Yc':'corporality = neighborhood.VonNeumannNeighborhood',
          'Ys':'sensoriality = neighborhood.VonNeumannNeighborhood',
          'Cb':'def birth(earth, code, prana, mana, address):',
          'Cd':'  myself = agent.Agent_2D(code,corporality(earth.returnTopology()),sensoriality(earth.returnTopology()),prana,mana,address)',
          'Cr':'  return myself',
          'Ld':'def live(creature):',
          'Lp':'  prayer = "Live"',
          'Ll':'  creature.losePrana(1)',
          'Le':'  creature.eatMana()',
          'Iy':'  if creature.tellPrana() > 13:',
          'Ir':'      prayer = "GrantChild"',
          'Ip':'      reproduce(creature)',
          'Ix':'  elif creature.tellPrana() <= 0:',
          'Ik':'      prayer = "KillMe"',
          'Lr':'  return prayer',
          'Rd':'def reproduce(creature):',
          'Rl':'  creature.losePrana(14)',
          'Rp':'  prayer = "Live"',
          'Rr':'  return prayer',}
  

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

