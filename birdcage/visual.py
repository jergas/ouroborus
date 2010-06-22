import curses
import pygame
from pygame.locals import *
import Image
import ImageDraw
import sys


def setCursesColors(mana, agents, background):
	""" Set the curses colours.
	"""
	curses.init_pair(1, curses.COLOR_RED, curses.COLOR_BLACK)
	curses.init_pair(2, getattr(curses, agents), getattr(curses, background))
	curses.init_pair(3, getattr(curses, mana), getattr(curses, background))
	curses.init_pair(4, curses.COLOR_BLUE, curses.COLOR_BLACK)



def icon(i):
	""" Returns a hash character if the cell is alive
	i      ---> an integer, the cell's state
	return -->> a character: either dot or space.
	"""
	if i==1:
		return ord(",")
	else:
		return ord(" ")


def printIcon(automaton, stdscr, address):
	""" Display a dot on the screen if the cell is alive

	automaton ---> a birdcage automaton instance
	stdscr    ---> a curses stdscr object
	address   ---> a 2-tuple, a cell in the c.a. grid
	"""
	(x,y) = address
	stdscr.addch(y, x, icon(automaton.get(address)), curses.color_pair(3))


def printAgent(stdscr, agent, displaywidth, displayheight):
	""" Display a hash on the screen for every agent

	stdscr    ---> a curses stdscr object
	agent   ---> a birdcage Agent_2D instance
	displaywidth  ---> an integer
	displayheight ---> an integer
	"""
	corporality = agent.tellCorporality()
	for address in corporality:
		(x,y) = address
		if 0 <= x and x <= displaywidth and 0 <= y and y <= displayheight:
			stdscr.addch(y, x, ord("#"), curses.color_pair(2))
	
	
def printTranslucentAgent(stdscr, agent, displaywidth, displayheight, automaton):
	""" Display a hash on the screen for every agent

	stdscr    ---> a curses stdscr object
	agent   ---> a birdcage Agent_2D instance
	displaywidth  ---> an integer
	displayheight ---> an integer
	"""
	corporality = agent.tellCorporality()
	for address in corporality:
		(x,y) = address
		if x < displaywidth and y < displayheight:
			(automaton.get((x,y)) and [stdscr.addch(y, x, ord("@"),
		     curses.color_pair(2))] or [stdscr.addch(y, x, ord("#"),
		     curses.color_pair(2))])[0]


def updateLoop(automaton, stdscr, displaywidth, displayheight):
	"""update the curses display

	automaton     ---> a birdcage automaton instance
	stdscr        ---> a curses stdscr object
	displaywidth  ---> an integer
	displayheight ---> an integer
	"""
	for x in range(displaywidth):
		for y in range(displayheight):
			printIcon(automaton, stdscr, (x,y))

	agents = automaton.tellAgents()

	for agent in agents:
		printAgent(stdscr, agent, displaywidth, displayheight)


def updateBackground(automaton, stdscr, displaywidth, displayheight):
	"""this function is similar to updateLoop(), but only
	updates the background. The method is only
	used in the threaded version of the simulation
	automaton     ---> a birdcage automaton instance
	stdscr        ---> a curses stdscr object
	displaywidth  ---> an integer
	displayheight ---> an integer
	"""
	for x in range(displaywidth):
		for y in range(displayheight):
			printIcon(automaton, stdscr, (x,y))


def updateAgent(agent, stdscr, displaywidth, displayheight):
	"""Update the visualization of a single agent. This method is only
	used in the threaded version of the simulation
	agent			---> a birdcage Agent_2D instance
	stdscr      	---> a curses stdscr object
	displaywidth	---> an integer
	displayheight	---> an integer
	"""

	printAgent(stdscr, agent, displaywidth, displayheight)


def updateLoopTranslucent(automaton, stdscr, displaywidth, displayheight):
	""" Update the curses display

	automaton     ---> a birdcage automaton instance
	stdscr        ---> a curses stdscr object
	displaywidth  ---> an integer
	displayheight ---> an integer
     """

	for x in range(displaywidth):
		for y in range(displayheight):
			printIcon(automaton, stdscr, (x,y))

	agents = automaton.tellAgents()

	for agent in agents:
		printTranslucentAgent(stdscr, agent, displaywidth, displayheight, automaton)

####################################################################

def pygGenerateDisplay(size, caption, zoom=12):
	"""Generates a pyGame windwo to display the automaton, it requires
	the size in pixels as a tuple (width,height) and a caption in string
	format (i.e. "Title") to be displayed
	as the window title.
	"""
	pygame.init()
	screen = pygame.display.set_mode((zoom*size[0],zoom*size[1]))
	global screen
	pygame.display.set_caption(caption)
	fullscreen = False
	
def pygUpdateBackground(automaton, criterion, size,zoom=12,output='buffer.tiff'):
	"""This function generates a buffer image that will be the main
	visual feature of the viewer it requires a birdcage automaton,
	an environment value and an image size-> A tuple in the format
	(width,height).
	"""
	# Maka a new image.
	picture = Image.new("RGB", size)
	draw = ImageDraw.Draw(picture)
	# Go through the automaton, and draw the live cells
	for x in range(0,size[0]):
		for y in range(0,size[1]):
			cellState = automaton.get((x, y))
			if cellState == criterion:
				draw.point((x,y),(0,255,0))
			else:
				draw.point((x,y),(0,0,0))
	
	#Zooms in and saves the image	
	picture = picture.resize((zoom*picture.size[0],
								zoom*picture.size[1]),Image.NEAREST)
	picture.save(output)
	
	#Update the display using the updated 
	ufile = open(output, "rb")
	image = pygame.image.load(ufile).convert()
	screen.blit(image,(0,0))
	pygame.display.flip()
	
	#Force close open files
	ufile.close()
	del ufile      
	image = None
	del image

	
def pygDrawAgent(agent,agentImg='agent.png',output= 'buffer.tiff',zoom =12):
	"""This function places the agents on the buffer image. It requieres the
	corporality (position) of an agent, an agent image file (3x3px) and an
	output image to draw the agent on.
	"""
	picture = Image.open(output)
	agentImg = Image.open(agentImg)
	address = agent.tellAddress()
	picture.paste(agentImg,(address[0]+1,address[1]+1))
	picture.save(output)

	#Zooms in and saves the image	
	picture = picture.resize((zoom*picture.size[0],
								zoom*picture.size[1]),Image.NEAREST)
	picture.save(output)
	
	#Update the display using the updated 
	ufile = open(output, "rb")
	image = pygame.image.load(ufile).convert()
	screen.blit(image,(0,0))
	pygame.display.flip()
	
	#Force close open files
	ufile.close()
	del ufile      
	image = None
	del image


def pygViewClose(self):
	'''Closes the pygame window when the close button is pressed. It also enables and disables fullscreen when F-key is pressed'''
	#Check if close button is pressed and close the program
	for event in pygame.event.get():
		if event.type == pygame.QUIT: sys.exit()
