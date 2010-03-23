def updateRule(input_list,side,environment):
     '''This module contains the rules for updating the automaton based on each cells
     neighbors and their response value. The neighbor rules are the same as Conways
     game of life but they have been adapted to interact with the response value of
     each cell.
     '''
     espacio2 = {} #A dictionary in which the updated state of each cell is stored
     for i in range(0,side): #Define the state of the cell (+ = alive - = dead)
          for j in range(0,side):
               if abs(abs(input_list[(side*i) + j]) - environment) <= 5:
                    input_list[(side*i) + j] = abs(input_list[(side*i) + j])
               else:
                    input_list[(side*i) + j] = -abs(input_list[(side*i) + j])

     for i in range(0,side): #Check each cell
          for j in range(0,side):
               ONneighbors = 0
               if (side-1)>i>0 and (side-1)>j>0:
                    for (k,l) in [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]:# Define neighbors
                         if input_list[(side*(i+k)) + (j+l)] >= 0:#count living neighbours
                              ONneighbors = ONneighbors + 1
                    
                    if input_list[(side*i) + j] >= 0:#if cell is alive
                         if 2 <= ONneighbors <= 3:
                              espacio2[i,j] = environment
                         elif (input_list[(side*i)+j]-environment) > 0:
                              espacio2[i,j] = environment - 15
                         elif (input_list[(side*i)+j]-environment) < 0:
                              espacio2[i,j] = environment + 15
                         else:
                              if input_list[(side*i)+j]<500:
                                   espacio2[i,j]= environment+15
                              else:
                                   espacio2[i,j]= environment-15

                    else: #if cell is dead
                         if ONneighbors == 3:
                              espacio2[i,j] = environment
                         else:
                              espacio2[i,j]= (abs(input_list[(side*i)+j]))

     for i in range(1,side-1):#Update the automaton
          for j in range(1,side-1):
               input_list[(side*i)+j] = espacio2[i,j]
    
     return input_list 
