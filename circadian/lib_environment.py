# This module contains the rules for updating the automaton based on each cell's
# neighbors and their response value. The neighbor rules are the same as Conways
# game of life but they have been adapted to interact with the response value of
# each cell.

import serial
import random


def updateRule(input_list,side,environment):
     
     espacio2 = {}  #A dictionary in which the updated state of each cell is stored
     for i in range(0,side): 
          for j in range(0,side):
               #Define the state of the cell (+ = alive - = dead)
               if abs(abs(input_list[(side*i) + j]) - environment) <= 5:
                    input_list[(side*i) + j] = abs(input_list[(side*i) + j])
               else:
                    input_list[(side*i) + j] = -abs(input_list[(side*i) + j])

     for i in range(0,side):                                          #Check each cell
          for j in range(0,side):
               ##! This block needs to be replaced by the MooreNeighborhood class from neighborhood.pyx
               ONneighbors = 0
               if (side-1)>i>0 and (side-1)>j>0:
                    for (k,l) in [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]: # Define neighbors
                         if input_list[(side*(i+k)) + (j+l)] >= 0:    #count living neighbours
                              ONneighbors = ONneighbors + 1
                    
                    if input_list[(side*i) + j] >= 0:                 #if cell is alive
                         if 2<= ONneighbors<= 3:
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
     
#################################################################################

def binarise(integer):
     """Take an integer input and return 1 if it is positive and 0 if it is negative"""
     
     return ((integer / abs(integer)) + 1)/2
     

def addBinarised(a, b):
     """Takes too integer inputs and adds them after binarising them."""
     
     return binarise(a) + binarise(b)
     
def readArduino(port='/dev/ttyUSB0'):
     sensor = serial.Serial(str(port), 9600)
     reading = sensor.readline()
     sensor.close()
     return reading

def getEnvironment():
     ''' Gets a reading from the environment sensor. In case there is no such
     device, prints a notification of such a lack and generates a random environmental value.
     '''
     ## The try except clause is used in order to be able to run the code
     # without an arduino interface.
     try:
          environment = []
          # loop until a reading is received.
          while len(environment) < 1:
               environment = readArduino()
               environment = environment.split()

          # The while loop makes sure that only the integer part of the reading (i.e. not the '\n')
          #is asigned to environment
          while type(environment) != int:
               environment = readArduino()
               environment = environment.split()
               environment = int(environment[0])
               
     except serial.serialutil.SerialException:
          print 'No serial reading!!! using simulated environment.'
          environment = random.randint(100,100)
               
     return environment
	
