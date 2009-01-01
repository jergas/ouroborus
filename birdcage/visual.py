import curses as c
import time as t


def icon(i):
    """Returns a hash character if the cell is alive
    i      ---> an integer, the cell's state
    return -->> a character: either dot or space"""

    if i==1: return ord(",")
    else: return ord(" ")


def printIcon(automaton, stdscr, address):
    """Display a dot on the screen if the cell is alive

    automaton ---> a birdcage automaton instance
    stdscr    ---> a curses stdscr object
    address   ---> a 2-tuple, a cell in the c.a. grid"""

    (x,y) = address
    stdscr.addch(y, x, icon(automaton.get(address)), c.color_pair(3))


def printAgent(stdscr, agent, displaywidth, displayheight):
    """Display a hash on the screen for every agent

    stdscr    ---> a curses stdscr object
    address   ---> a birdcage Agent_2D instance
    displaywidth  ---> an integer
    displayheight ---> an integer"""

    corporality = agent.tellCorporality()
    for address in corporality:
        (x,y) = address
        if x < displaywidth and y < displayheight:
	    stdscr.addch(y, x, ord("#"), c.color_pair(2))
	
	
def printTranslucentAgent(stdscr, agent, displaywidth, displayheight, automaton):
    """Display a hash on the screen for every agent

    stdscr    ---> a curses stdscr object
    address   ---> a birdcage Agent_2D instance
    displaywidth  ---> an integer
    displayheight ---> an integer"""

    corporality = agent.tellCorporality()
    for address in corporality:
        (x,y) = address
        if x < displaywidth and y < displayheight:
	    (automaton.get((x,y)) and [stdscr.addch(y, x, ord("@"), c.color_pair(2))] or [stdscr.addch(y, x, ord("#"), c.color_pair(2))])[0]


def updateLoop(automaton, stdscr, displaywidth, displayheight):
    """update the curses display

    automaton     ---> a birdcage automaton instance
    stdscr        ---> a curses stdscr object
    displaywidth  ---> an integer
    displayheight ---> an integer"""

    for x in range(displaywidth):
        for y in range(displayheight):
            printIcon(automaton, stdscr, (x,y))

    agents = automaton.tellAgents()

    for agent in agents:
        printAgent(stdscr, agent, displaywidth, displayheight)


def updateLoopTranslucent(automaton, stdscr, displaywidth, displayheight):
    """update the curses display

    automaton     ---> a birdcage automaton instance
    stdscr        ---> a curses stdscr object
    displaywidth  ---> an integer
    displayheight ---> an integer"""

    for x in range(displaywidth):
        for y in range(displayheight):
            printIcon(automaton, stdscr, (x,y))

    agents = automaton.tellAgents()

    for agent in agents:
        printTranslucentAgent(stdscr, agent, displaywidth, displayheight, automaton)
