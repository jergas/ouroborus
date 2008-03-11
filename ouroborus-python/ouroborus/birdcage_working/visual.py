import curses as c
import time as t

def fireUpCurses():
    """Initialise a curses window for visual display"""

    global stdscr
    stdscr = c.initscr()
    c.noecho()
    c.cbreak()
    stdscr.keypad(1)


def makePad(size):
    """Define a curses pad corresponding to the c.a. grid

    size   ---> a 2-tuple
    return -->> a 3-tuple, the pad, along with its visible size"""
    
    #create the curses pad, this may be larger than the window
    (width, height) = size
    pad = c.newpad(height, width)

    #the limits for the visible portion of the pad
    (pad_width, pad_height) = (78,23)

    #reset the visible portion of the pad if the grid is small
    if width < pad_width: pad_width = width
    if height < pad_height: pad_height = height

    #return the dimensions of the visible portion of the pad
    return (pad, pad_width, pad_height)


def icon(i):
    """Returns a hash character if the cell is alive
    i      ---> an integer, the cell's state
    return -->> a character: either dot or space"""

    if i==1: return "."
    else: return " "


def printIcon(automaton, pad, address):
    """Display a dot on the screen if the cell is alive

    automaton ---> a birdcage automaton instance
    pad       ---> a curses pad for display
    address   ---> a 2-tuple, a cell in the c.a. grid"""

    (x,y) = address
    pad.addch(y, x, icon(automaton.get(address)))


#def printAgent(pad, address):
#    """Display a hash on the screen for every agent

#    pad       ---> a curses pad for display
#    address   ---> a 2-tuple, a cell in the c.a. grid"""
    
#    (x,y) = address
#    pad.addch(y, x, "#")


def printAgent2(pad, agent):
    """Display a hash on the screen for every agent

    pad       ---> a curses pad for display
    address   ---> a birdcage Agent_2D instance"""
    
    corporality = agent.tellCorporality()
    for address in corporality:
        (x,y) = address
        pad.addch(y, x, "#")

#def updateLoop(automaton, pad, size):
#    """update the curses display

#    automaton ---> a birdcage automaton instance
#    pad       ---> a curses pad for display"""

#    (width, height) = size
#    for x in range(width):
#        for y in range(height):
#            printIcon(automaton, pad, (x,y))

#    agentAddresses = automaton.tellAgentAddresses()

#    for i in range(len(agentAddresses)):
#        printAgent(pad, agentAddresses[i])


def updateLoop2(automaton, pad, size):
    """update the curses display

    automaton ---> a birdcage automaton instance
    pad       ---> a curses pad for display"""

    (width, height) = size
    for x in range(width):
        for y in range(height):
            printIcon(automaton, pad, (x,y))

    agents = automaton.tellAgents()

    for agent in agents:
        printAgent2(pad, agent)


def refreshDisplay(padinfo):
    """Refresh the curses pad

    padinfo ---> a 3-tuple comprising of a curses pad and its visible size"""

    (pad, pad_width, pad_height) = padinfo
    pad.refresh(0, 0, 1, 1, pad_height, pad_width)


def shutDownCurses():
    """Finalise the curses display"""

    stdscr.keypad(0)
    curses.nocbreak()
    curses.echo()
    curses.endwin()
    del stdscr

