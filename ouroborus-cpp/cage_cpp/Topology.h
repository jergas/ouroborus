#ifndef Topology_H
#define Topology_H

#include <vector>

#include "Dimension.h"
///This class represents in a very general form the possible structure of the graph. 
/**
* This class determines who can form an edge with whom, so determines the allowed 
* form in the net, the dimension of the grid (remember the dimensions are finite and 
* discrete), and the normalization of the dimensions, for example if you normalize 
* a one dimension topology you end with a ring.
*/ 
class Topology{

    ///represents the number of dimension's of the cellular automata, and the created dimension's objects
    int dimension;
    /**represents the number of dimension's objects with no bound's (dimensions normalized), 
	can't be (dimension < dimNormalized)*/
    int dimNormalized;
    
    ///the dimension object container
	std::vector<Dimension> dimensions; 
    
    public:
        
    ///constructor (dimension, Num# dimensions normalized)
    Topology(int dim, int norm=0):dimension(dim),dimNormalized(norm){
		
		//because we know the number of dimension's object's that
		//we are gone to use, reserve the specific space of memory
		dimensions.reserve(dimension);   
		//create and add the dimensions (default size of 100, can be modified later) 
		for(int i=0; i< dimension; ++i){
			if(norm != 0){//if you want to normalize some dim's
                dimensions.push_back(Dimension(100, true));
                //quits from the count the normalized dimension
                norm -= 1;            
			}
			else //if you want's dimension whit bounds
                dimensions.push_back(Dimension(100, false));           
		}		
	}//-------------Topology constructor--------------
    
    /// The copy-constructor:
    Topology(const Topology& t): dimension(t.dimension), dimNormalized(t.dimNormalized){}    
    
	///Overwrite the = operator to avoid problems when you forget initialize whit the constructor
	Topology& operator=(const Topology& t) {
        dimension = t.dimension;
        dimNormalized = t.dimNormalized;
        return *this;
    }
	 ///the destructor 
	~Topology(){dimensions.clear();}
    
    //---------------get methods---------------------------------  
    
	///return the dimension of the topology
    inline size_t getDimensionality(){return dimensions.size();}
    
    ///return the number of "dimensions" with no bounds
    inline int getDimNormalized(){return dimNormalized;}
    
    ///return the specific size of a dimension
    inline int getDimensionSize(int dim){
        return dimensions[dim].getSize();}
    
    ///change the dimension size
    inline void setDimensionSize(int dim, int dsize){
        dimensions[dim].setSize(dsize);}  
                 
    ///return if a specific dimension has no bounds
    inline  bool getDimensionNormalized(int dim){
        return dimensions[dim].getNormalized();}
    
    ///change the dimension normalization
    inline void setDimensionNormalized(int dim){
        dimensions[dim].setNormalized(true);
		dimNormalized += 1;
	}
    
    ///return if a coordinate is out of bounds
	inline bool isOutOfBounds(std::vector<int> vect){
    
		//check all the coordinates in the vector  
		for(int i=0; i< int(dimensions.size()); ++i){
			//if some coordinate is out of bounds
			if( dimensions[i].isOutOfBounds(vect[i]) ){
				return  true;
			}                
		}	
		return false;//if nothing happens is in bounds
	}//------isOutOfBounds(vector<int> vect)-----------


    
    /**
    * transform all the coordinates in the new ones
    * in base of the topology characteristics
    * is a must!!! to check if they are out of bounds first!
    * with the isOutOfBound method
    */
    std::vector<int> getPos(std::vector<int> vect){
		//check all the coordinates in the vector  
		for(int i=0; i < int(vect.size()); ++i){
			/*for al entries of the position vector, 
			* ask the corresponding object dimension,
			* for the concrete coordinates in that 
			* dimension in base of the topology form*/
			vect[i] = dimensions[i].getPos(vect[i]);                
		}
		//And last return the vector with the new actualized position entries
		return vect;
	}//-----getPos(vector<int> vect)--------------

    
    //get methods --------------------------------
};
#endif //Topology_H
