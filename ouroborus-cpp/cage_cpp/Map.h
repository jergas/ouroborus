#ifndef Map_H
#define Map_H

#include <vector>

#include "Topology.h"
#include "Neighborhood.h"
#include "TowerNeighborhood.h"
/// this class “maps” the topology of the net and the neighborhood in each cell for the cellular automata to determine the actual form in the graph.  
/** 
* The topology establish a possible form of a network, and the neighborhood establish a 
* desired form in the relation of a center cell and the neighborhood cells, or a node with 
* the edges formed to other nodes. The map class correlates this, to forms the 
* concrete form of the graph or cellular automata.
*/
class Map {
	
    
    ///The Map has a pointer to a Topology object who determines the possible form of the graph.
    Topology *topology;
    
    ///The Map has a pointer to a Neighborhood element to define the desired form of the relation center cell with neighborhood cells.
    Neighborhood *neighborhood;
    
    /**
    * The edges from a Node (center cell) to other Nodes (neighbors in the cellular automata) 
    * are pointers, this pointers when created are keep in a container, the container is
    * a vector, a vector of vectors, a container whit the coordinates of the element who 
    * related to.
    */
    std::vector< std::vector<int> > edge; 
    
    /**
    * need a copy vector to calculations in setEdge method and don't 
    * want to create a new one every time the method is called
    */
    std::vector< std::vector<int> > copyEdge;
    
    public:
        
    ///constructor
    Map(Topology *top, Neighborhood *hood):topology(top), neighborhood(hood){}
    /// The copy-constructor:
    Map(const Map &m):  topology(m.topology), neighborhood(m.neighborhood){}   
    
    ///Overwrite the = operator to avoid problems when you forget initialize whit the constructor
    Map& operator=(const Map& m) {
        topology = m.topology;
        neighborhood = m.neighborhood;
        return *this;
    }   

    //-------get set methods------------------------------
    ///Change the used topology.
    inline void setTopology(Topology *top){topology = top;} 
    ///Change the used Neighborhood.
    inline void setNeighborhood(Neighborhood *hood){neighborhood = hood;}
    ///Used to change the normalization in a specific dimension, the dimension characterized by the input number.
    inline void setNormalizedDimencion(int dim){topology->setDimensionNormalized(dim);}
    ///Used to change dimension size, the dimension characterized by the input number. 
    inline void setDimencionSize(int dim, int dimSize){topology->setDimensionSize(dim, dimSize);}
    /// Used to change the Neighborhood "radius".
    inline void setNeighborhoodSize(int size){neighborhood->setSize(size);}
    ///Once the calculations in setEdge() has been done use this method to get the container of vector positions of the each of the neighbors.
    inline std::vector < std::vector<int> > getEdge(){return edge;}       
        
    /**
    * This is the main method of the class, in this method
    * the Topology and Neighborhood objects are mixed
    * to calculate the real coordinates of the vertex with an edge 
    * in common with (neighbors of)the element represented by the input 
    * vector(center cell).
    */        
    void setEdge(const std::vector<int> position)
    {
        //first clean the last calculated coordinates, and then calculates the new ones
	edge.clear();
	neighborhood->calculateNeighborhood(position);
	copyEdge = neighborhood->getNeighborhood();
	//for all neighbors positions, check if they exist in the actual topology
	//and if they do, push it back in the container. 
	for(unsigned int i = 0; i < copyEdge.size(); ++i)
            if( !(topology->isOutOfBounds(copyEdge[i])) )
		edge.push_back( topology->getPos(copyEdge[i]) );    
				  
    }//-------------setEdge(const vector<int> position)----

    //-------end get set methods--------------------------
        
};
#endif //Map_H
