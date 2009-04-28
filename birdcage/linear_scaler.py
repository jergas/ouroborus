## Contains linear scaling methods. scascaleValToRng() scales a value,
# scaleToRange() scales a list.


def scaleValToRng(value, oldMin, oldMax, newMin, newMax):	"""Scales a value within a range to it's equivalent in a new range.
	value	---> the value to be scaled.
	oldMin	---> the minimum of the old range
	oldMax	---> the maximum of the old range
	newMin	---> the minimum of the new range
	newMax	---> the maximum of the new range
	return 	--> a scaled value
	"""	oldRange	= (oldMax*1.0) - oldMin	newRange	= newMax - newMin	ratio		= newRange/oldRange	scaledValue	= ((value - oldMin) * ratio + newMin)	return scaledValue


def scaleToRange(values, newMin=0, newMax=1):	"""Scales a list to a new range. With just one argument the new
	range is between 0 and 1. The old range is between the highest and
	lowest values of the original list.
	values	---> a list to be scaled
	newMin	---> the minimum of the new range (optional)
	newMax	---> the maximum of the new range (optional)
	return 	--> a scaled list
	"""			newValues	= []	oldMin		= min(values)	oldMax		= max(values)	oldRange	= (oldMax*1.0) - oldMin	newRange	= newMax - newMin	ratio		= newRange/oldRange		for x in values:		scaling = ((x-oldMin) * ratio + newMin)		newValues.append(scaling)	return newValues
