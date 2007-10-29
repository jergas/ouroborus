#ifndef Neighborhood_h
#define Neighborhood_h

#include <vector>

///This class represents the form of the neighborhood, the “form” of the set of edges to every node.
/**
* This class represents the desired "form" of the neighborhood 
* for some center cell, the specific edges of a vertex, is the desired 
* form because the topology of the net, can allow or not the existence 
* of some edge between two nodes, aloud that some cell be or not 
* part of the neighborhood for some other (center cell).
* This mix and the derived correlation's are performed in the map class. 
*/
class Neighborhood{
	public:
    
    /**In this vector container are keep all neighbor's coordinates vectors,
    the edges positions set for some center cell, some node in the graph.*/
    std::vector< std::vector<int> > neighborsPositions; 
    
     ///The container of vectors of normal coordinates of the entire neighborhood.
    std::vector< std::vector<int> > neighborsNormalCoordinates;     
    
    /**This vector will be used for create a neighbor coordinates 
    and push in to the container (neighborsPositions). */
    std::vector<int> neighborCoordinates; 
    ///The number of dimensions in the Automaton.
    int dimension;
    /**
    * The size variable represents how far we are gonna take 
    * neighbors. For example if we take size = 1, in the tower 
    * neighborhood (1 dimension) you have:                     
    * 0X0 and if we have size = 2 we have: 00X00
    * The x is the center cell, and the 0's are the neighbors 
	*/
    int size;
     
    ///The constructor
    Neighborhood(int Numdim, int size = 1): dimension(Numdim), size(size){} 

    /// The copy-constructor:
    Neighborhood(const Neighborhood& n): dimension(n.dimension), size(n.size){}
	
    ///Overwrite the = operator to avoid problems when you forget initialize whit the constructor
    Neighborhood& operator=(const Neighborhood& n) {
        dimension = n.dimension;
        size = n.size;
        return *this;
    }   
    
    ///the destructor 
    ~Neighborhood(){
	neighborsPositions.clear(); 
	neighborCoordinates.clear(); 
    }
    
    //------get set methods-----------------------------
    
    /// Return the container of coordinates for neighbors (neighborsPositions). 
    inline std::vector< std::vector<int> > getNeighborhood(){return neighborsPositions;}
    ///Return the size variable (the “diameter” of the Neighborhood). 
    inline int getSize(){return size;}    
    ///Change the size of the diameter for the Neighborhood
    inline void setSize(int s){size = s;}
        
    //------end get set  methods-------------------------         
    
    /**
    * This is the main method in the class.
    * In this method, the container of neighbor coordinates, 
    * is fill with the vector positions of the neighbors, 
    * the positions of the vertex’s with an edge to the vertex 
    * represented by the input vector, the coordinates for 
    * a cell in the cellular automata.   
    */
    virtual void calculateNeighborhood(const std::vector<int> position) {};          
    /**
     * This method is for create an arranged neighborhood, 
     * this method only call calculateNeighborhood method, 
     * with the cero vector as input, and copy the neighborhood 
     * output to the neighborsNormalCoordinates vector.
     * In this vector the normal coordinates of the neighborhood 
     * are keeping, so every time the calculateNeighborhood 
     * method is called, every neighborhood created can have a pointer 
     * to the normal position used to calculate is actual position, 
     * translated for the center cell coordinates.
     * With this relation you can know the real position 
     * of the neighbor and the normal position (remember 
     * the coordinates are lost and only remain a pointer to the 
     * neighbor), so you have the spatial relation with the center cell, 
     * and not only bag of elements representing the elements that 
     * are the neighborhoods.
     */
    void calculateNormalNeighborhood(){
        //create the ceros vector
        std::vector<int> ceros;
        for(int i=0;i<dimension;i++){
            ceros.push_back(0);
        }
        // use the vector to calculate the normal coordinates
        calculateNeighborhood(ceros);
        //keep the coordinates
        neighborsNormalCoordinates = neighborsPositions;
    }
};

#endif
