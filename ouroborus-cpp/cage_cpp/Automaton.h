#ifndef Automaton_H
#define Automaton_H

#include "Map.h"
#include "Topology.h"
#include "Neighborhood.h"
#include "AlfilNeighborhood.h"

#include <vector>

///The Automaton class is the main class in the Cellular automata library, represents a Cellular Automata type. 
/** 
* This class uses a type of neighbourhood, and a type of 
* topology, in a map object, to create the final CA graph, 
* this graph is a net of references to a matrix, 
* the base element matrix (the elements to modify in the iteration process). 
* This class contain the next step function, the method to calculate the next 
* inner  of the elements in the base element matrix, 
* tnx to the graph form (the map) and the change state algorithm given by the method. 
*/

template<class T> class Automaton{
	
public:
    //--------------------start of the inner variables--------------------------
	//TODO:
	///This vector is used in createNode() method for a lack of compatibility with the Map class, soon is going to be eliminated. 
	std::vector<int> position;    
	///This structure represent a vertex in graph with all is properties.
	/**
	* The Node objects represent the node in the graph, 
	* it has a pointer to a element in the values matrix,
	* the inner value of the node. And the start and end 
	* index, for the neighbourhood pointer container, 
	* representing the edges structure of the graph.
	*/
	typedef struct  Node{
      
     public:
          
     ///The pointer to the game board (a element in the values matrix)
     T* centerCell;
     ///The end index in the vector of Neighbour's pointer
     int endNeighbor;
     ///The begin index in the vector of Neighbour's pointer
     int beginNeighbor;
     ///The constructor.
     /** The constructor arguments, are a pointer to the  matrix, 
     * (the inner state of the vertex in the graph), and two ints variables representing 
     * the start and end index of the Neighbors pointers container, 
     * this is the representation of the edges for this graph element 
     */
    Node(T* cell, int begin, int end):centerCell(cell), beginNeighbor(begin), endNeighbor(end){}
    };
    /********************************************************/

    ///The pointer to the  matrix.
    /**
    * This pointer is used to move across the  matrix, in this 
    * way the program works independently of the dimension of the 
    *  matrix. 
    */
    T *pointerToNodes;
    ///This is the pointer that is actually moved across the state matrix. 
    /**
    * Is used to keep intact the reference to the start of the matrix given
    * by pointerToNodes variable.
    */
    T *copyPointerToNodes;
    ///In createNode()there is a need to an extra copy of copyPointerToNodes variable.
    T *copyPointerToNodes2;
    ///The pointers container to the state matrix. 
    /** Represents the edges in the graph, the neighbors in the cellular automata */
    std::vector<T*> neighbors;
    ///the Node container.
    /**
    * The Node structure is equal to the node of a graph, has inner state value 
    * and edges to other elements, the graph vector is the container of Node 
    * structures.
    */ 
    std::vector<Node> graph;    
    /// The maximum dimensions number.
    /**
    * To accomplish all the calculations and maintain the possibility to use 
    * n-dimensional matrixes, we create an array to keep all the dimension sizes, 
    * this array need an initial size value a const int variable type; 
    * The maxDimensions is this type, so for now we have the possibility to use a 
    * maximum dimensions number of 100.  
    */
    static const int maxDimensions = 100;
    /// The array of dimensions sizes.
    /**
    * Every element in the dimSizes array represents a size of some 
    * dimension (remember the dimension are finite); 
    * The dimSizes array has fixed long size, is the dimension possible 
    * size of the entire system (maxDimensions variable), the array size is 
    * set to 100 by default but can be changed if you need more dimensions 
    * or if you want to save profile (change maxDimensions variable).
    * Is Set to 100 to avoid problems with dimensionality, and if the 
    * dimension for this Automaton object is smaller than the size of 
    * this array, each element that pass the dimension number is not taken 
    * account and is ignored in all calculations (remember the Automaton 
    * dimension can’t be bigger than the size of this array).
    */   
    int dimSizes[maxDimensions];
    ///A copy of dimSizes array is used to apply some changes in the dimSizes array without lost is information.
    int copyDimSizes[maxDimensions];
    ///The number of dimensions in the Automaton.
    int dimension;
    ///Index value to accomplish the calculations for calculate the start and end int values in the Node structure.
    /**
    * This int value is to accomplish the calculations and keep track 
    * of where starts, and where end a neighborhood in the edge's 
    * vector container, saved in the start and end variables 
    * in the structure Node (used in the createNode() method).
    */
    int indexHood;    
    ///The Automaton needs a Map object to determine the actual form of the graph, the mixture between the topology and the neighbour objects. 
    /** 
    * With this object the form of the graph is developed in base of the 
    * "desired" form of the Neighbourhood object and the "possible" 
    * form delimited by the topology form. 
    */
    Map *map;
    ///The Topology object determines the possible form of the graph,in a very basic way the possible edges in the graph.
    Topology *topology;
    ///The Neighbourhood object determines the desired form of the graph, restricted or alluded by the topology form. 
    Neighborhood *neighborhood;     
    
    //--------------end of the inner variables-----------------------------
                
public:
	///The constructor 
    Automaton(T *gridPointer, int Dsizes[], int dimesions):pointerToNodes(gridPointer), dimension(dimesions){
    /*T *gridPointer() is the pointer used to move over the
	grid(states matrix), used like an iterator in "ndimensional arrays",
	Dsizes[] is the pointer to the dimension sizes array,
	and int dimension, is the number of dimensions of this 
	Cellular Automata */

	//set ready the index neighbours (for set the end and start of neighbours pointer vector)
	indexHood = 0;

	//create the dimension objects
	//one for each dimension
	for(int i=0;i < dimension; ++i){
            dimSizes[i] = Dsizes[i];              
	}
	//then create a topology object, and put inside the dimension objects
        topology = new Topology(dimension);
        for(int i=0;i<dimension;++i){
			topology->setDimensionSize(i, Dsizes[i]);
	}
	//last create a neighbourhood object and create the map to mix 
	//the for given by the topology and neighbourhood objects
        neighborhood = new TowerNeighborhood(dimension, 1); 
        map = new Map(topology, neighborhood);

	//Reserve space to avoid copy a lot memory if the size of the graph result to big
	int graphSize = 1;
	for(int i=0;i < dimension; ++i){
            graphSize = graphSize * dimSizes[i];
	}
	graph.reserve(graphSize);
    }
    
    /// The copy-constructor:
    Automaton(const Automaton& a){
	//copy all the inner variables of the “input” object
	//and set the starting values ready
	pointerToNodes = a.pointerToNodes; 
	dimension = a.dimension;
	topology = a.topology;
	dimSizes = a.dimSizes;
	neighborhood = a.neighborhood;
	map = a.map;
	graph.reserve(a.graph.size());
	//set the index of neighbors to 0
	indexHood = 0;

    }
    
    ///Overwrite the = operator to avoid problems when you forget initialize whit the constructor  
    Automaton& operator=(const Automaton& a) {
	//copy all the inner variables of the “input” object
	//and set the starting values ready
	pointerToNodes = a.pointerToNodes; 
	dimension = a.dimension;
	topology = a.topology;
	dimSizes = a.dimSizes;
	neighborhood = a.neighborhood;
	map = a.map;
	graph.reserve(a.graph.size());
	//set the index of neighbors to 0
	indexHood = 0;
        return *this;
    }   
    ///Set the Map objects. Unifies the form of the graph given by the Topology and the Neighbourhood
    void setMap();
    ///Return the Map (topology and neighbourhood "mixer") object of this Automaton.
    void getMap();
    ///Set the Neighbourhood type for this Cellular automata 
    void setNeighborhood();
    ///Return the Neighborhood object of this Cellular automata 
    void getNeighborhood();
    ///With this function you iterate over the state matrix independently of the dimension and element type of the array, ending as result with the graph form (all the node and edges relations).
    /**this is done tanks to the pointer to the first element of the 
    * array (pointerToNodes), and the dimension sizes array (dimSizes[maxDimensions]) set previously 
    * in the constructor.
    * with the pointer as the starting point reference and the array of dimensions sizes, 
    * you can know how many places move the pointer to go from one position to 
    * other in the matrix, because to avoid problems, the multidimensional arrays 
    * are keep has memory places one next to the other (one dimension vector).
    * In this method when a iteration occurs is called the createNode() method, for 
    * each element in the array, each element define a "center cell" a node in the graph.
    * All the edges and final graph structure is set when the createNode() method is 
    * called for all elements in the array.
    */
    void iterateOverTheSatesArray(int index=0);
    //ToDo:
    void nextStep();
    ///This method is for creating the Node structure container (the couple's node and edges, center cell and neighbours)
    /** 
    * The Node container is the graph. A Node consist of a center cell or node, 
    * a pointer to the state matrix, and two index for the beginning and end index 
    * in the neighbours vector container, the edges (pointers to elements in the 
    * states matrix).
    *
    * This method use the copyDimSizes position array, this array is used to 
    * calculate the node coordinates in the grid, with this coordinates the Map class 
    * find if the edge exist and in the case generate is absolutes coordinates, 
    * Map uses the Topology and Neighbourhood class to make all the calculations and
    * generate an edge (pointer to element in the state array) 
    * this pointer is keep, in the neighbours vector container, and because a new 
    * neighbourhood is added the index values in the Node structure in particular 
    * the end index is modify Adding one to the count.
    */
    void createNode();
    /// This method change the copyPointerToNodes pointer to point a element in the array given by the position argument.
    /**
    * If you want to access any element in a multi-dimensional array, 
    * use a pointer to the first element and advance the pointer to
    * the position of the element that you want to change/access. 
    * The reference pointer is pointerToNodes variable, this pointer mark the 
    * start bunch of memory used by the states array.
    * And thanks to dimSizes array, is know how much positions move to pass 
    * from one dimension to the next one.
    * At the end the pointer copyPointerToNodes finish pointing to the desired 
    * position in the array.
    */
    void getNodePointer(std::vector<int> position);	
    ///This method is equal to getNodePointer but use an array as input instead a vector
    /**
    * Watch the getNodePointer method documentation.
    */
    void getNodePointer(int position[]);
    ///This method do the same that getNodePointer(int position[]) but use copyDimSizes array instead input(avoids input object creation).
    /**
    * Use the copyDimSizes array as the coordinates of 
    * the element in the state array to point to
    */
    void getNodePointer();
        
};
template<class T>
void Automaton<T>::getNodePointer()
    {
    
        //first point the copy pointer to the [0][0][0]...[0]
        //position, the begining element of the states array
        copyPointerToNodes = pointerToNodes; 
        /*whe need a int to count the positions 
		to move the pointer */
        //TODO: podria hacer la variable a nivel de clase, que no cree cada ves que la funcion se llame
		int move = 0 ;
        
        /*for all the elements (number of dimensions) in the position 
		* array (copyDimSizes[i]), calculate how many position move 
		* the pointer (copyPointerToNodes) in the one dimensional 
		* bunch of memory, occupied by the multidimensional states array */
        for(int i=0; i<dimension; i++ ){
            //if is not the last element
            if( (i+1) < dimension){
                /*multiply all the position index's for each dimension size,
				* to know the number of places to move the pointer in the 
				* bunch of memory */   
                move = copyDimSizes[i];
                for(int j = (i+1); j < dimension; j++){        
                    move = (move)*(dimSizes[j]);
                }
				//and move the pointer
                copyPointerToNodes += move;
            }
            /*if is the last element move the pointer the position
			* number, because you don’t have to jump inter elements 
			*in the bunch of memory*/  
            else
                copyPointerToNodes += copyDimSizes[i];
        } 
}//---------------getNodePointer()--------------------------
template<class T>   
void Automaton<T>::getNodePointer(std::vector<int> position)
    {
    
        //first point the copy pointer to the [0][0][0]...[0]
        //position, the begining element of the states array
        copyPointerToNodes = pointerToNodes; 
        /*whe need a int to count the positions 
		to move the pointer */
        //TODO: podria hacer la variable a nivel de clase, que no cree cada ves que la funcion se llame
		int move = 0 ;
        
        /*for all the elements (number of dimensions) in the position 
		* vector (vector<int> position argument), calculate how many position move 
		* the pointer (copyPointerToNodes) in the one dimensional 
		* bunch of memory, occupied by the multidimensional states array */
        for(int i=0; i<dimension; i++ ){
            //if is not the last element
            if( (i+1) < dimension ){
                /*multiply all the position index's for each dimension size,
				* to know the number of places to move the pointer in the 
				* bunch of memory */   
                move = position[i];
                for(int j = (i+1); j < dimension; j++){        
                    move = (move)*(dimSizes[j]);
                }
                //and move the pointer
                copyPointerToNodes += move;
            }
            /*if is the last element move the pointer the position
			* number, because you don’t have to jump inter elements 
			*in the bunch of memory*/  
            else
                copyPointerToNodes += position[i];
        } 
    }//---------------getNodePointer(vector<int> position)--------------------------

template<class T>   
void Automaton<T>::getNodePointer(int position[])
    {
       
        //first point the copy pointer to the [0][0][0]...[0]
        //position, the begining element of the states array
        copyPointerToNodes = pointerToNodes; 
        /*whe need a int to count the positions 
		to move the pointer */
        //TODO: podria hacer la variable a nivel de clase, que no cree cada ves que la funcion se llame
		int move = 0 ;
        
        /*for all the elements (number of dimensions) in the position 
		* array (int position[] argument), calculate how many position move 
		* the pointer (copyPointerToNodes) in the one dimensional 
		* bunch of memory, occupied by the multidimensional states array */
        for(int i=0; i<dimension; i++ ){
            //if is not the last element
            if( (i+1) < dimension ){
                /*multiply all the position index's for each dimension size,
				* to know the number of places to move the pointer in the 
				* bunch of memory */   
                move = position[i];
                for(int j = (i+1); j < dimension; j++){        
                    move = (move)*(dimSizes[j]);
                }
                //and move the pointer
                copyPointerToNodes += move;
            }
            /*if is the last element move the pointer the position
			* number, because you don’t have to jump inter elements 
			*in the bunch of memory*/  
            else
                copyPointerToNodes += position[i];
        } 
    }//---------------getNodePointer(int position[])--------------------------   

template<class T>
void Automaton<T>::createNode(){
    
    /*first gets the pointer to the node, the "center cell"
    this pointer is keep for now in the copyPointerToNodes variable*/
    getNodePointer();
    //because whe are goin to change copyPointerToNodes pointer
    //copy the pointing direction
    copyPointerToNodes2 = copyPointerToNodes;
	
	
    //TODO: avoid this transformation 
    //you have to transform the position vector, the array copyDimSizes[]
    //to a vector container for use for the map object
    position.clear();
    position.reserve(dimension);
    for(int i=0;i<dimension;++i){
        position.push_back(copyDimSizes[i]);
    }
    //TODO:
    //se puede evitar el crear este vector para cada nodo no manches
    //calculate the neighborhood
    map->setEdge(position);
    std::vector< std::vector<int> > hood = map->getEdge();
	
    //next keep the edges(pointers to the states matrix) in the neighbors pointer container
    
    //for all calculated neighbors positions(calculated by map object)
    for(int i=0;i<int(hood.size());++i){
        //move the pointer to the element given by the position
        getNodePointer(hood[i]);
	//and push the pointer in the container
        neighbors.push_back(copyPointerToNodes);    
    }
    //with all the calculations ready create the node 
    Node cell(copyPointerToNodes2, indexHood, (indexHood + int(hood.size())-1));
    
    //change the index for neigbours array (the edges)
    //so the next time this method is called, the index 
    //representing the end of the positions for this node
    //will be the beginning for the next
    indexHood = indexHood + int(hood.size());
        
    //and keep the generated Node structure in the grahp vector container
    graph.push_back(cell);
    
}//------------createNode()-----------------

template<class T>
void Automaton<T>::iterateOverTheSatesArray(int index){    
    //(this method works with recursion)

         //iterate over the first dimension or the dimension given by the index (remember the recursion)
        for( int i=0; i<dimSizes[index] ; ++i ){
            
			//now modify a copy of the dimension sizes array,
			//to uses like the new position vector
			copyDimSizes[index] = i;                
                
                //if isn't the last dimension 
                if( (index + 1) < dimension){
                    /*use recursion to modify the copy of 
					the dimension sizes array, and start again
					for the nexts dimensions
					*/
                    iterateOverTheSatesArray(index+1);                               
                }
                //if is the last dimension
                else{					
			/*modify a copy of the dimension sizes array,
			to use has the new position vector
            */
					copyDimSizes[index] = i;
                    //and use the index (the new position vector)
                    //to create the Node and edge structure the base for the graph
                    createNode();
                }
        }       
}//----------iterateOverTheSatesArray-----------------

template<class T>
void Automaton<T>::nextStep(){
    
}//-----------nextStep()--------------------

#endif
