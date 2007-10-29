// 
// File:   ArrangedNeighborhood.h
// Author: Administrador
//
// Created on 30 de agosto de 2007, 11:05 PM
//

#ifndef ArrangedNeighborhood_H
#define	ArrangedNeighborhood_H

#include "Neighborhood.h"


///This Neighborhoods child class extends his parent, by keeping the normal spatial coordinates of every neighbor.
/**
* This class has other container as well as the neighborsPositions container, 
* defined in the Neighborhood class, the neighborsNormalCoordinates vector 
* type container, this container keep the vectors normal coordinates of the 
* entire neighborhood.
* The coordinates are the same if you calculate the neighborhoods coordinates 
* for the 0,0,0 …….0 n-dimensional position vector.   
*/
class ArrangedNeighborhood : public Neighborhood{
public:
    ///The container of vectors normal coordinates of the entire neighborhood.
    std::vector< std::vector<int> > neighborsNormalCoordinates;     
    /* TODO: Como que se deve de calcular todos los vecindarios normales y luego cuando se calcule alguno otro
     *se podria crear el puntero a este vector, o se podria crear cada elemento cuando se crean las direcciones a algun
     *vecino, asi el indice sirve igual para vecinos que para elementos en el vector de normales 
     */ 
    claculateNormalNeighborhood();

};


#endif	/* ArrangedNeighborhood_H */

