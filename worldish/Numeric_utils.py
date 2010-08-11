## Contains classes that collect numeric utilities.

from math import sqrt

class Series(object):
	""" Contains methods to generate the following numeric series: even,
	odd, fibo (fibonacci), and prime.
	"""
	def __init__(self, harmonic):
		""" The initialization parameter should be 0 or 1. When zero is
		chosen, the methods construct series with as many elements as
		desired. If the value is one, the series are limited to a number
		of elements, depending on the series. The criterium fot the
		limit is: 20 (minimum audible frequency) elevated to the last
		value of the series has to be less than 20,000 (maximum audible
		frequency).
		harmonic	---> 0 for any series, 1 for spectral-purpose series
		"""
		if not harmonic or harmonic ==1:
			self.harmonic = harmonic
		else:
			print 'Initialization parameter must be 0 or 1'


	def naturals(self, noOfElmnts):
		""" Constructs a natural number series of noOfElements.
		noOfElements	---> the desired elements in the series
		"""
		naturalLst    = []
		natural       = 1
		# If series is intended for a harmonic series, limit the series
		# so that its last harmonic is below 1/2 of the sample rate
		# (assuming a fundamental of 20hz and a distortion facotr of 1).
		if self.harmonic == 1 and noOfElmnts > 500:
			noOfElmnts = 500

		for x in xrange(noOfElmnts):
			naturalLst.append(natural)
			natural += 1
		return naturalLst


	def even(self, noOfElmnts):
		""" Constructs an even-number series of noOfElements.
		noOfElements	---> the desired elements in the series
		"""
		evenLst    = []
		even        = 2
		# If series is intended for a harmonic series, limit the series
		# so that its last harmonic is below 1/2 of the sample rate
		# (assuming a fundamental of 20hz and a distortion facotr of 1).
		if self.harmonic == 1 and noOfElmnts > 250:
			noOfElmnts = 250

		for x in xrange(noOfElmnts):
			evenLst.append(even)
			even = even + 2
		return evenLst


	def odd(self, noOfElmnts):
		""" Constructs an odd-number series of noOfElements.
		noOfElements	---> the desired elements in the series
		"""
		oddLst    = []
		odd         = 1
		counter     = 0
		# If series is intended for a harmonic series, limit the series
		# so that its last harmonic is below 1/2 of the sample rate
		# (assuming a fundamental of 20hz and a distortion facotr of 1).
		if self.harmonic == 1 and noOfElmnts > 250:
			noOfElmnts = 250
		
		for x in xrange(noOfElmnts):
			oddLst.append(odd)
			odd = odd+2
		return oddLst

	def fibo(self, noOfElmnts):
		""" Constructs a fibonacci-number series of noOfElements.
		noOfElements	---> the desired elements in the series
		"""
		fiboLst    = []
		a           = 0
		b           = 1
		# If series is intended for a harmonic series, limit the series
		# so that its last harmonic is below 1/2 of the sample rate
		# (assuming a fundamental of 20hz and a distortion facotr of 1).
		if self.harmonic == 1 and noOfElmnts > 12:
			noOfElmnts = 12
		if self.harmonic == 1:
			a = 1
		
		for x in xrange(noOfElmnts):
			fiboLst.append(b)
			a, b = b, a+b
		return fiboLst


	def prime(self, noOfElmnts):
		""" Constructs a prime-number series of noOfElements.
		noOfElements	---> the desired elements in the series
		"""
		primeLst    = []
		candidate   = 2
		counter     = 0
		# If series is intended for a harmonic series, limit the series
		# so that its last harmonic is below 1/2 of the sample rate
		# (assuming a fundamental of 20hz and a distortion facotr of 1).
		if self.harmonic == 1 and noOfElmnts > 95:
			noOfElmnts = 95

		while counter < noOfElmnts:
			maxTest = int(sqrt(candidate)) + 1
			for x in range(2, maxTest):
				if candidate % x == 0:
					candidate += 1
					break
			else:
				primeLst.append(candidate)
				candidate += 1
				counter += 1
		return primeLst


class Scaling(object):
	""" Contains methods for scaling values or lists.
	"""
	def lstToTotl(self, aList, newTotl):
		"""Scales the values in aList so they add up to a new total.
		aList	---> the list to scale
		newTotl	---> the sum of all elements of the scaled list
		return	--> a scaled list
		"""
		oldTotl	= 0.0
		newLst		= []
		
		for x in aList:
			oldTotl = oldTotl + x
		scaleFactor = newTotl / oldTotl
		for x in aList:
			newVal = x * scaleFactor
			newLst.append(newVal)
		return newLst


	def valToRng(self, val, oldMin, oldMax, newMin, newMax):
		"""Scales a value within a range to it's equivalent in a new range.
		val		---> the value to be scaled.
		oldMin	---> the minimum of the old range
		oldMax	---> the maximum of the old range
		newMin	---> the minimum of the new range
		newMax	---> the maximum of the new range
		return 	--> a scaled value
		"""
		oldRng = (oldMax*1.0) - oldMin
		newRng = newMax - newMin
		ratio = newRng/oldRng
		scaledVal	= ((val - oldMin) * ratio + newMin)
		return scaledVal
