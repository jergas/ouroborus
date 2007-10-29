#ifndef TowerNeighborhood_H
#define TowerNeighborhood_H


//*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   ACAESTOY:
//*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//read first Neighborhood.h class definition!!!! 
#include "Neighborhood.h"

class TowerNeighborhood : public Neighborhood{
    
    
    public:
    
    ///The constructor
    TowerNeighborhood(int numDim, int s = 1):Neighborhood(numDim, s){ 
        //this->dimension = numDim;
        //this->size = s;
    }     
    /*************************************************************
    * This is the main method in the class.
    * In this method, the container of neighbor coordinates
    * is filled, with vectors, each container representing one coordinate for one neighbor, 
    * or can see as the positions of the vertex with an edge to the vertex 
    * represented by the input vector (the vertex position).   
    **************************************************************/
    void calculateNeighborhood(const std::vector<int> position){
    
		//first empty the coordinates vector and the neighborsPositions vector
		neighborCoordinates.clear();
		neighborsPositions.clear();
    
		//To make the calculations easy start with a copy of 
		//the input Coordinates vector, this copy is gone to be modify
		//and push_back in the neighborsPositions vector, without 
		//modify the gived input need for calculate the other
		//positions 
		neighborCoordinates = position;
    
		//make the calculations for each dimensions. 
		for(unsigned int i = 0; i < neighborCoordinates.size() ; ++i){
        
			//Make a number of neighbors cordinates vector in one direction
			//this number depends on the size variable. 
			for(int j = 0; j < size; ++j ){
				neighborCoordinates[i] = neighborCoordinates[i] + 1;   
				neighborsPositions.push_back(neighborCoordinates);
			}//---end for j----------------   
        
			//Reset the position values.
			neighborCoordinates.clear();
			neighborCoordinates = position;
        
			//Make a number of neighbors positions vector in the other 
			//direction this number depends on the size variable 
			for(int j = 0; j < size; ++j ){
				neighborCoordinates[i] = neighborCoordinates[i] - 1;   
				neighborsPositions.push_back(neighborCoordinates);
			}//---end for j----------------
         
			//Reset the position values.
			neighborCoordinates.clear();
			neighborCoordinates = position;
    
		}// end i for ----   
    
	}//----calculateNeighborhood(const vector<int> &position)----
     
};
#endif //TowerNeighborhood_H
