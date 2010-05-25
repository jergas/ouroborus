"""This module contains the PyGVisual class which is used to produce a pyGame viewer of the circadian cellular automaton.
It requires an enviroment reading interface or a random environment generator (such as getEnvironment from
lib_environment.py). The automaton input must be coded as a list. For this to run you need to have python-pygame(tested under version 1.8.1-release1ubuntu1) and python-imaging (tested under version 1.1.6-3ubuntu) installed.

Coded by Diego Trujillo (aka 5inister) May 2010"""

#Import the needed modules
import pygame
import sys
from pygame.locals import *
import Image
import ImageDraw

class PyGVisual():
     '''This class holds the methods in charge of rendering cellular automata on a pyGame window'''
     def __init__(self, width=800, height=800):
          pygame.init()
          self.screen = pygame.display.set_mode((width,height))
          pygame.display.set_caption("Circadian Viewer")
          self.image = pygame.image.load("buffer.tiff").convert()
          
          
     def generate(self, automaton, environment, side=100, output='buffer.tiff'):
          '''This function generates a buffer image that will be the main visual feature of the viewer
          it requires an automaton coded as a list, an environment value and an image size (default is 100).'''
          self.picture = Image.new("RGB", (side,side))
          self.draw = ImageDraw.Draw(self.picture)
                    
          for i in range(0,side):
               for j in range(0,side):
                    if automaton[(side*i)+j]-5<= environment <= automaton[(side*i)+j]+5:
				     self.draw.point((i,j),(0,255,0))
                    else:
				     self.draw.point((i,j),(0,0,0))
				     
          self.picture = self.picture.resize((8*self.picture.size[0],8*self.picture.size[1]), Image.NEAREST)
          self.picture.save(output)
          

     def update(self,inputImage='buffer.tiff'):
          '''This function is required in order to update the screen'''
          self.image = pygame.image.load(inputImage).convert()
          self.screen.blit(self.image,(0,0))
          pygame.display.flip()
		

     


