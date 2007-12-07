#ifndef QueenNeighborhood_H

#define QueenNeighborhood_H


#include "TowerNeighborhood.h"

#include "AlfilNeighborhood.h"


//read first Neighborhood.h class definition!!!! 

#include "Neighborhood.h"


/**




	The QueenNeighborhod is the mixture between the TowerNieghborhood and 

	the AlfilNeighborhood

*/

class QueenNeighborhood : public Neighborhood{

    

	/**This is used to calculate the alfil neighborhood part*/

	AlfilNeighborhood *alfilNeighborhood;

	/**This is used to calculate the tower neighborhood part*/

	TowerNeighborhood *towerNeighborhood;


	

    public:

     ///The constructor

    QueenNeighborhood(int numDim, int s = 1){ 

        this->dimension = numDim;

        this->size = s;

        alfilNeighborhood = new AlfilNeighborhood(size);

        towerNeighborhood = new TowerNeighborhood(size);

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

		

		alfilNeighborhood->calculateNeighborhood(position);

		for(size_t i = 0; i < alfilNeighborhood->neighborsPositions.size(); ++i)
			neighborsPositions.push_back(alfilNeighborhood->neighborsPositions[i]);

		

		towerNeighborhood->calculateNeighborhood(position);

		for(size_t i = 0; i < towerNeighborhood->neighborsPositions.size(); ++i)
			neighborsPositions.push_back(towerNeighborhood->neighborsPositions[i]);

		

		

		

	}//----calculateNeighborhood(const vector<int> &position)----

     

};

#endif //QueenNeighborhood_H
