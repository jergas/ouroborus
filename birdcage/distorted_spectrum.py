## Generates a distorted harmonic spectrum based on iterating the function
#"s = f*p to the d". The partials present in the spectrum come from one of the
#series constructed by numeric_series.py.from numeric_series import *def distortedSpectrum(fundamental, partials, distortion):		spectrum = []		while len(partials) > 0:		onePartial = partials.pop(0)		distortedPartial = pow(onePartial, distortion)		onePartialFrequency = fundamental * distortedPartial		if  onePartialFrequency < 20000 :
			onePartialFrequency = round(onePartialFrequency, 3)
			spectrum.append(onePartialFrequency)		else:			break	return spectrum
