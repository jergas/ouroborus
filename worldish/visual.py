import curses
from PIL import Image, ImageDraw
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

        if i:
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
                if 0 <= x and x < displaywidth and 0 <= y and y < displayheight:
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

        updateBackground(automaton, stdscr, displaywidth, displayheight)
        agents = automaton.tellAgents()

        for agent in agents:
                printAgent(stdscr, agent, displaywidth, displayheight)


def updateLoopTranslucent(automaton, stdscr, displaywidth, displayheight):
        """ Update the curses display

        automaton     ---> a birdcage automaton instance
        stdscr        ---> a curses stdscr object
        displaywidth  ---> an integer
        displayheight ---> an integer
     """

        updateBackground(automaton, stdscr, displaywidth, displayheight)
        agents = automaton.tellAgents()

        for agent in agents:
                printTranslucentAgent(stdscr, agent, displaywidth, displayheight, automaton)


def debugUpdateDisplay(annum, book, debugFile):
        """ Display data relative to one iteration of the simulation's
        automaton and agents.
        annum           ---> the number of iterations that the automaton has
                                                undergone
        book            ---> a book of life dictionary containing birdcage Agent_2D
                                                instances
        debugFile       ---> the output file
        """
        # If there is a debug file, write the output in it. Otherwise,
        # output to screen.
        if debugFile:
                debugFile.write('#' * 14 + 'Automaton and agents will now be refreshed.' + '#' * 14 + '\n' + '#' * 72 + '\n')

                debugUpdateBackground(annum, debugFile)

                debugFile.write("The organizer will now read the book of life...\n")
                debugFile.write("There are " + str(len(list(book.keys()))) + " creatures on this worldish:\n")

                # Display the BookEntries as they currently stand.
                for key in list(book.keys()):
                        debugFile.write('\n' + str(book[key]) + '\n')

                debugFile.write("The book has been read.")
                debugFile.write("\n")
                debugFile.write('#' * 72 + '\n' + '#' * 72 + '\n')
        else:
                debugUpdateBackground(annum, debugFile)

                print("The organizer will now read the book of life...")
                print("There are "+str(len(list(book.keys())))+" creatures on this worldish:")

                # Display the BookEntries as they currently stand.
                for key in list(book.keys()):
                        print(book[key])

                print("The book has been read.")
                print("\n")


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


def debugUpdateBackground(annum, debugFile):
        """ Display data relative to one iteration of the simulation's
        automaton.
        annum   ---> the number of iterations that the automaton has
                                        undergone
        debugFile       ---> the output file
        """
        if debugFile:
                debugFile.write("\nThe time now is \t" + str(annum) + '\n')
        else:
                print("\n")
                print("The time now is \t", annum)


def updateAgent(agent, stdscr, displaywidth, displayheight):
        """Update the visualization of a single agent. This method is only
        used in the threaded version of the simulation
        agent                   ---> a birdcage Agent_2D instance
        stdscr          ---> a curses stdscr object
        displaywidth    ---> an integer
        displayheight   ---> an integer
        """

        printAgent(stdscr, agent, displaywidth, displayheight)

'A single agent will be updated.'
def debugUpdateAgent(entry, debugFile):
        """Display data relative to the actualization of a single birdcage
        agent. This method is only used in the threaded version of the
        simulation.
        entry                   ---> the agent's bookentry
        debugFile       ---> the output file
        """
        if debugFile:
                debugFile.write('-' * 20 + 'A single agent will be updated.' + '-' * 20 + '\n')
                debugFile.write("\nThe following agent is being updated:")
                debugFile.write('\n' + str(entry) + '\n')
                debugFile.write("\n")
                debugFile.write('-' * 72 + '\n')
        else:
                print("The following agent is being updated:")
                print(entry)
                print("\n")

####################################################################

def identity(state):
        """This is the identity function, the most trivial criterion for cell
        state display. It most only be used if cells only take alive (anything)
        or dead (0) values.
        """

        return state

####################################################################

def pygGenerateDisplay(size, caption, zoom=12):
        """Generates a pyGame windwow to display the automaton, it requires
        the size in pixels as a tuple (width,height) and a caption in string
        format (i.e. "Title") to be displayed
        as the window title.
        """

        global pygame, screen
        import pygame
        pygame.display.init()
        screen = pygame.display.set_mode((zoom * size[0], zoom * size[1]))
        pygame.display.set_caption(caption)
        return screen


def pygUpdateBackground(automaton, criterion, size, zoom=12, output='buffer.tiff'):
        """Render at grid resolution and scale once for display."""
        picture = Image.new("RGB", size)
        draw = ImageDraw.Draw(picture)
        for x in range(size[0]):
                for y in range(size[1]):
                        if criterion(automaton.get((x, y))):
                                draw.point((x, y), (0, 255, 0))
        image = pygame.image.frombytes(picture.tobytes(), size, "RGB")
        screen.blit(pygame.transform.scale(image, screen.get_size()), (0, 0))
        for agent in automaton.tellAgents():
                pygDrawAgent(agent, zoom=zoom)
        pygame.display.flip()
        pygViewClose()


def pygDrawAgent(agent, agentImg='agent.png', output='buffer.tiff', zoom=12):
        """Draw the agent's footprint in grid coordinates without repeatedly scaling a file."""
        for x, y in agent.tellCorporality():
                pygame.draw.rect(screen, (255, 255, 0), (x * zoom, y * zoom, zoom, zoom))
        pygame.display.flip()


def pygViewClose(self=None):
        """Allow the window close button to stop the simulation cleanly."""
        for event in pygame.event.get():
                if event.type == pygame.QUIT:
                        raise KeyboardInterrupt
