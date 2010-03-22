def updateRule(input_list,side,environment):
     espacio2 ={}
     print environment
     for cell in input_list:
          print cell
          if abs(abs(cell) - environment) <= 5:
               cell = abs(cell)
          else:
    	          cell = -abs(cell)
    	
     for i in range(0,side):
          for j in range(0,side):
               ONneighbors = 0
               if (side-1)>i>0 and (side-1)>j>0:
                    for (k,l) in [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]:
                         if input_list[(side*(i+k)) + (j+l)] >= 0:
                              ONneighbors = ONneighbors + 1
                    #print ONneighbors
                    if input_list[(side*i) + j] >= 0:
                         if 2 <= ONneighbors <= 3:
                              espacio2[i,j] = environment
                         elif (input_list[(side*i)+j]-environment) > 0:
                              espacio2[i,j] = environment - 15
                         elif (input_list[(side*i)+j]-environment) < 0:
                              espacio2[i,j] = environment + 15
                         else:
                              if input_list[(side*i)+j]<500:
                                   espacio2[i,j]= environment+15
                              if input_list[(side*i)+j]>500:
                                   espacio2[i,j]= environment-15
                    	
               else:
                    if ONneighbors == 3:
                         espacio2[i,j] = environment
                    else:
                        espacio2[i,j]= (abs(input_list[(side*i)+j]))

     for i in range(1,side-1):
          for j in range(1,side-1):
               input_list[(side*i)+j] = espacio2[i,j]
    
     return input_list 