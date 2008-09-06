## Defines the time it takes for each partial to reach its maximum amplitude (peak).from random import uniform
def ataques(total, espectro_dist, minimo=.001):
    
    ataques		= []
    maximo	    = total.pop(0) * 0.5
    
    for x in espectro_dist:
        un_ataque = uniform(minimo, maximo)
        ataques.append(un_ataque)
    return ataques