## Constructs the parameters for an additive-synthesis note. Each evaluation of
#the method "nota" yields a single additive-synthesis note, composed of several
#csound notes. Note that each string in the returned list is a csound score line
#for.from random import random, choice, randint, uniformfrom SeriesArmonicas4 import *from EspectroDistorsionado5 import espectro_distorsionadofrom Comienzos2 import comienzos
from Duraciones2 import duracionesfrom Amplitudes2 import amplitudesfrom PaneosEspectrales1 import paneos_espectralesfrom Ataques2 import ataquesfrom Decadencias2 import decadencias## All the parameters needed for a single note from the Distorted Harmonic
#Spectrum Model.def nota(fundamental, numeroDeArmonicos, spectrum_type, distorsion,
		panoramica_gral, duracionTotal):
## Which kind of partials will be present in a note.
	species						= [parciales_pares, parciales_nones,
								parciales_fibonacci, parciales_primos]
	spectrum_choice				= species.pop(spectrum_type)
	parciales					= spectrum_choice(numeroDeArmonicos)	espectro_dist				= espectro_distorsionado(fundamental,
								parciales, distorsion)## Csound instrument no. (for now, constant)	instrumento_csd				= 1## Defines the start times of the partials. In seconds	comienzos_csd				= comienzos(espectro_dist)## Defines the durations of the partials. In seconds	duraciones_csd				= duraciones(comienzos_csd, duracionTotal)## Defines the amplitudes of the partials. Between (0-32767)	amplitudes_csd				= amplitudes(espectro_dist)##Gives a little "space" to the note. Just like when humans speak: low tones
#resonate towards the chest and high ones towrds the forehead.	panoramica_espectral_csd	= paneos_espectrales(panoramica_gral,
								espectro_dist)## Attack time of the partials. In seconds.	ataques_csd					= ataques(duraciones_csd[:1], espectro_dist)	## Decay time  of the partials. In seconds.	decadencias_csd				= decadencias(duraciones_csd[:1], espectro_dist)## Contains the csound notes that integrate an additive synthesis note.	parciales_csnd				= []								## Constructs the csound score lines (each string is a line) for an additive
#synthesis note.	while len(espectro_dist) > 0:		nota_csnd = ("i%s %s %s %s %s %s %s %s" %(instrumento_csd,
				comienzos_csd.pop(0), duraciones_csd.pop(0),
				amplitudes_csd.pop(0), espectro_dist.pop(0),				panoramica_espectral_csd.pop(0), ataques_csd.pop(0),
				decadencias_csd.pop(0)))		parciales_csnd.append(nota_csnd)	return parciales_csnd
