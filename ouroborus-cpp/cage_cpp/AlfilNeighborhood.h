#ifndef AlfilNeighborhood_H
#define AlfilNeighborhood_H

//read first Neighborhood.h class definition!!!! 
#include "Neighborhood.h"

class AlfilNeighborhood : public Neighborhood{
    
	/**This vector will be used for create a neighbor position
    and push in to the container (neighborsPositions). */
    std::vector<int> neighborCoordinates2;
	
	int sizeCopy;

	void calculateRecursiveTree(int  index){
            //si todo esta listo ponlos en la bolsa
            if(index == neighborCoordinates.size()-1){
			
		neighborCoordinates[index] += sizeCopy;
		neighborsPositions.push_back(neighborCoordinates);
		neighborCoordinates[index] -= sizeCopy+sizeCopy;
		neighborsPositions.push_back(neighborCoordinates);

            }//if
            // si no modifica recursivamente hasta que todo este listo
            else{
			// yama a  la rema del arbol con este valor mas uno
			neighborCoordinates[index] += sizeCopy;
			calculateRecursiveTree(index + 1);
			//resetea los valores para otra rama del arbol
			for(size_t i = index; i < neighborCoordinates.size();++i){
				neighborCoordinates[i] = neighborCoordinates2[i];
			}
			neighborCoordinates[index] -=sizeCopy;
			calculateRecursiveTree(index + 1);
		}//else
		
}
    
    public:
    
    ///The constructor
    AlfilNeighborhood(int numDim, int s = 1):Neighborhood(numDim, s){  
        //this->dimension = numDim;
        //this->size = s;
    }
		
    /*************************************************************
    * This is the main method in the class.
	* In this method, the container of neighbor positions, 
	* is fill with the vector positions of the neighbors, 
	* the positions of the vertex with an edge to the vertex 
	* represented by the input vector  (the vertex position).   
	**************************************************************/
    void calculateNeighborhood(const std::vector<int> position){
    
		//first empty the position vector and the neighborsPositions vector
		neighborCoordinates.clear();
		neighborsPositions.clear();
		neighborCoordinates2.clear();
		
		sizeCopy = 0;

		neighborCoordinates2 = position;
		
		for(int i = 0; i < size; ++i){
			//To make the calculations easy start with a copy of 
			//the input Coordinates vector, this copy is gone to be modify
			//and push_back in the neighborsPositions vector, without 
			//modify the given input need for calculate the other
			//positions 
			neighborCoordinates = position;
    
			sizeCopy = i+1;
			calculateRecursiveTree(0);
	
		}// end i for ----   

	}//----calculateNeighborhood(const vector<int> &position)----
     
};
#endif //AlfilNeighborhood_H
