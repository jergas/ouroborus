tabula = {'Yi':'import topology; import neighborhood; import agent',
          'Yc':'corporality = neighborhood.VonNeumannNeighborhood',
          'Ys':'sensoriality = neighborhood.VonNeumannNeighborhood',
          'Cb':'def birth(earth, code, prana, mana, address):',
          'Cd':'  myself = agent.Agent_2D(code,corporality(earth.returnTopology()),sensoriality(earth.returnTopology()),prana,mana,address)',
          'Cr':'  return myself',
          'Tl':'def live(creature):',
          'Tp':'  prayer = "Live"',
          'Te':'  creature.gainPrana(1)',
          'Tc':'  if creature.tellPrana() > 110:',
          'Tr':'      reproduce(creature)',
          'Tg':'      prayer = "GrantChild"',
          'To':'  return prayer',
          'Rd':'def reproduce(creature):',
          'Rl':'  creature.losePrana(103)',}



  

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

