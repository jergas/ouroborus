# This module contains the rules for updating the automaton based on each cell's
# neighbors and their response value. The neighbor rules are the same as Conways
# game of life but they have been adapted to interact with the response value of
# each cell.

import serial
import random
import exceptions_birdcage as E
import rule as R


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
     
#################################################################################
cdef class EnvironmentRule(Rule_2D):
     """Rule set for an environmentally responsive automaton. This rules are based on Conway's game of life.
     If the sum of a dead cell's neighbors is 3, the cell becomes alive.  If the sum of a live cell's neighbors
     is 2 or 3, the cell remains alive.  Otherwise, it dies."""

     def  __init__(self, N.Neighborhood_2D neighborhood, param=None):
          """Override Rule_2D.__init__
        
          neighborhood ---> a birdcage Neighborhood_2d object complete
                            with a two-dimensional topology
          param        ---> None or nothing useful"""

          R.Rule_2D.__init__(self, neighborhood, param)
          self.name = "Environment Rule"

     def apply(self, address):
     
          state = 0
          sumstates = self.neighborhood.countAlive(address)
          cell = neighborhood.topology.get(address)
     
          if binarise(cell) == 1:  # If cell is alive
               if 2 <= sumstates <= 3:
                    state = environment
               elif (cell - environment) > 0:
                    state = environment - 15
               elif (cell - environment) < 0:
                    state = environment + 15
               elif cell < 500:
                    state = environment+15
               else:
                    state = environment-15
     
          elif binarise(cell) == 0:     # If cell is dead
               if sumstates == 3:
                    state = environment
               else:
                    state = cell
     
          self.neighborhood.topology.set(address, state)
     
     def applyToTarget(self, object address, T.GridTopology target):
     
          if not (len(address) == 2):
               raise E.InvalidAddressError(address, self.neighborhood.topology.name)
               
          state = 0
          sumstates = self.neighborhood.countAlive(address)
          cell = neighborhood.topology.get(address)
     
          if binarise(cell) == 1:  # If cell is alive

               if 2 <= sumstates <= 3:
                    state = environment
               elif (cell - environment) > 0:
                    state = environment - 15
               elif (cell - environment) < 0:
                    state = environment + 15
               else:
                    if cell < 500:
                         state = environment+15
                    else:
                         state = environment-15
     
          elif binarise(cell) == 0:     # If cell is dead
               if sumstates == 3:
                    state = environment
               else:
                    state = cell
          
          target.set(address, state)


cdef class MooreNeighborhoodPlus(MooreNeighborhood):
     """The MooreNeighborhood class from neighborhood.pyx with one extra method for 
     counting living neighbors based on reduceStates"""
          
     def countAlive(self, object address):
          """Counts all positive neighbors as living"""
     
          return self.reduceStates(address, addBinarised, 0)


def binarise(int integer):
     """Take an integer input and return 1 if it is positive and 0 if it is negative"""
     
     return ((integer / abs(integer)) + 1)/2
     

def addBinarised(int a, int b):
     """Takes too integer inputs and adds them after binarising them."""
     
     return binarise(a) + binarise(b)

def getEnvironment(port='/dev/ttyUSB0'):
     ''' Gets a reading from the environment sensor. In case there is no such
     device, prints a notification of such a lack and generates a random environmental value.
     '''
     ## The try except clause is used in order to be able to run the code
     # without an arduino interface.
     try:
          sensor =  serial.Serial(str(port), 9600)
          environment = []
          # loop until a reading is received.
          while len(environment) < 1:
               environment = sensor.readline()
               environment = environment.split()
          sensor.close()
          # The try exept clause makes sure that only the integer part of the reading (i.e. not the '\n')
          #is asigned to environment
          try:
               environment = int(environment[0])
          except TypeError:
               getEnvironment(port)
               environment = int(environment[0])
     except serial.serialutil.SerialException:
          print 'No serial reading!!! using random environment.'
          environment=random.randint(400,600)
     return environment
	
