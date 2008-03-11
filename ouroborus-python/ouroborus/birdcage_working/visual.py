import curses as c
import time as t


def icon(i):
    """Returns a hash character if the cell is alive
    i      ---> an integer, the cell's state
    return -->> a character: either dot or space"""

    if i==1: return ord(".")
    else: return ord(" ")


def printIcon(automaton, stdscr, address):
    """Display a dot on the screen if the cell is alive

    automaton ---> a birdcage automaton instance
    stdscr    ---> a curses stdscr object
    address   ---> a 2-tuple, a cell in the c.a. grid"""

    (x,y) = address
    stdscr.addch(y, x, icon(automaton.get(address)))


def printAgent(stdscr, agent):
    """Display a hash on the screen for every agent

    stdscr    ---> a curses stdscr object
    address   ---> a birdcage Agent_2D instance"""
    
    corporality = agent.tellCorporality()
    for address in corporality:
        (x,y) = address
        stdscr.addch(y, x, ord("#"))


def updateLoop(automaton, stdscr, size):
    """update the curses display

    automaton ---> a birdcage automaton instance
    stdscr    ---> a curses stdscr object"""

    (width, height) = size
    for x in range(width):
        for y in range(height):
            printIcon(automaton, stdscr, (x,y))

    agents = automaton.tellAgents()

    for agent in agents:
        printAgent(stdscr, agent)


