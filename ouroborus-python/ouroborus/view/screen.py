# This module contains the class Screen, a Pygame window
# which graphically displays a mundito grid.

# At present, it is limited to 2-state, 2-dimensional birdcage
# cellular automata.

# The Surfarray module included in Pygame and used by this class
# is dependent on the deprecated library Numeric

# It was written in Python 2.3.4 using the modules Pygame 1.6 and
# Numeric 24.2 by Sat Tara Singh Khalsa on December 18 2006, when
# it was found to run successfully on Windows XP, Deg Teg Fateh!

import pygame as P
import pygame.surfarray as S

class Screen:
    """A Pygame window"""

    def __init__(self,size,buffer,name):
        """Create a pygame screen

        size   ---> an n-tuple
        buffer ---> an ouroborus display buffer
        return -->> None"""

        self.size = size
        self.buffer = buffer
        self.screen = P.display.set_mode(self.size)

        P.init()
        P.display.set_caption(name)

    def update(self):
        """Update the display

        return -->> None"""

        array = S.map_array(self.screen,self.buffer.array)
        S.blit_array(self.screen,array)
        P.display.flip()
