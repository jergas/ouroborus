# This module contains all exceptions raised by the birdcage package

# It was written in Pyrex 0.9.6 on November 8th 2007
# by Sat Tara Singh Khalsa. Deg Teg Fateh!

# This Pyrex code was compiled on a Windows XP machine  
# using MinGW's gcc compiler, and run from Python 2.5.
# It has also been seen to compile successfully on
# Ubuntu's GNU gcc

# Note that for exceptions to work properly when compiling Pyrex
# from Python 2.5 it is necessary to add a patch softening Python's
# rigorous treatment of Exception classes as new-style objects.
# More info on this can be found at <www.spacemonkey.info> or
# <ouroborus.sf.net>


class BirdcageError(Exception):  
      """Base class for all exceptions in this package"""

      pass


class SizeError(BirdcageError):
      """Raise when a grid is bigger than allowed"""

      def __init__(self, value, limit):
          self.value = value
          self.limit = limit

      def __str__(self):
          print "\n%i is greater than limiting value of %i" % (self.value,self.limit)


class DimensionError(BirdcageError):
      """Raise when a grid's dimension does not correspond to its requirement"""

      def __init__(self, name, target, actual):
          self.name = name
          self.target = target
          self.actual = actual

      def __str__(self):
          print "\n%s must be dimension %i instead of %i" % (self.name, self.target, self.actual)


class InvalidAddressError(BirdcageError):
      """Raise when an invalid address is entered for normalisation"""

      def __init__(self, address, name):
          self.address = address
          self.name = name

      def __str__(self):
          print "\naddress %s is not valid in a %s" % (self.address, self.name)


class ConflictingTopologyError(BirdcageError):
      """Raise when an object's underlying topology is not the required one"""

      def __init__(self, name1, name2):
          self.name1 = name1
          self.name2 = name2

      def __str__(self):
          print "\n%s does not match %s" % (self.name1, self.name2)


class NotInNeighborhoodError(BirdcageError):
      """Raise when an unacceptable value is passed to the neighborhood"""

      def __init__(self, value, name):
          self.value = value
          self.name = name

      def __str__(self):
          print "\nvalue %s is not valid in a %s" % (self.value, self.name)
