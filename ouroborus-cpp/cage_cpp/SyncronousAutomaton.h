#ifndef SyncronousAutomaton_H
#define SyncronousAutomaton_H

#include "Map.h"
#include "Topology.h"
#include "Neighborhood.h"
#include "TowerNeighborhood.h"
#include "AlfilNeighborhood.h"
#include <vector>

///The SyncronousAutomaton is almost the same that the Automaton class but with the elements to accomplish synchronicity.
/**
* This class have all the characteristics that Automaton class, the only 
* difference is the modification in the SyncronousNode structure, and in the dynamics 
* of the methods to set the pointers and modify the values of the base 
* element matrix copy to accomplish the synchronization.  
*/ 
template<class T> class SyncronousAutomaton{
    
    //--------------------start of the inner variables--------------------------
	///ToDo:
	std::vector<int> position;    
	public:
	
	///This structure represent a vertex in synchronous graph with all is properties.
	/**
	* The SyncronousNode objects represents the node in the synchronous graph, has
	* a pointer to a state value in the values matrix, and a pointer to a state 
	* value in the states plus one matrix, to accomplish the synchrony when change 
	* the states values.
	* And a pointers to other states in the matrix representing 
	* the edges structures.
	*/
    typedef struct  SyncronousNode{
      
      public:
          
      ///The pointer to the game board
      T* centerCell;
	  ///The pointer to the game board time t+1
      T* centerCellTPlusOne;
      ///The end index in the vector of Neighbor's pointer
      int endNeighbor;
      ///The begin index in the vector of Neighbor's pointer
      int beginNeighbor;
	  ///ToDo:
	  SyncronousNode(T* cell, T* cellTPlusOne, int begin, int end):centerCell(cell), centerCellTPlusOne(cellTPlusOne), beginNeighbor(begin), endNeighbor(end){}
      
    };
    /********************************************************/

    //the pointer to the grid states and grid t+1
    T *pointerToNodes;
    ///ToDo:
	T *copyPointerToNodes;
	///ToDo:
	T *pointerToNodesTPlusOne;
	///ToDo:
	T *copyPointerToNodesTPlusOne;

	///this is used in createNode method
	T *copyPointerToNodes2;
	///ToDo:
	T *copyPointerToNodesTPlusOne2;
    
    //the cointainer of all the pointer's ("edges") 
	//representing the neighbor's
    ///ToDo:
	std::vector<T*> neighbors;
    
    //the graph container (SyncronousNode structure container)
    ///ToDo:
	std::vector<SyncronousNode> graph;
    
    /**
	* this array's represents the dimensionality of the Automaton
	* (the size of the array's dimension's)the number of the i 
	* element in the array represent the number of "cell's" in the 
	* i dimension
	*/
    static const int maxDimensions = 100;
    ///ToDo:
	int dimSizes[maxDimensions];
    ///ToDo:
	int copyDimSizes[maxDimensions];
	//-----------------------------------------------
    
	///ToDo:
	int dimension;
	////////////////////////////////////////////

	/**
	* this int value is to "remember where starts, and finish"
	* some neighborhood in the vertex's vector
	*/
    int indexHood;
    /*********************************************************/

    /**
	* the map is the objet who correlate the topology of the 
	* graph, and the creation of the neighborhood's(the vertex of 
	* the graphs)
	*/
    Map *map;
    /********************************************************/
	///ToDo:
    Topology *topology;
    ///ToDo:
	Neighborhood *neighborhood; 
    
    /*The states variable is for combinatory*/
    ///ToDo:
	int states;
    //--------------end of the inner variables-----------------------------
                
    
	///The constructor 
    SyncronousAutomaton(T *gridPointer, T *gridTPlusOnePointer ,int Dsizes[], int dimesions):pointerToNodes(gridPointer), pointerToNodesTPlusOne(gridTPlusOnePointer), dimension(dimesions){
    /*
	T *gridPointer() is the moving pointer over the
	grid, used like an iterator, in "ndimensional arrays",
	Dsizes[] is the pointer to the dimension sizes array,
	and int dimension is the number of dimensions of the 
	array 
	*/
			
		//set the index of neighbors to 0
		indexHood = 0;

		//create the dimension objects
		//one for each domension
		for(int i=0;i < dimension; ++i){
			dimSizes[i] = Dsizes[i];              
		}
		//then create a toppolgy objects and put in 
		//the dimension objects
        topology = new Topology(dimension);
        for(int i=0;i<dimension;++i){
			topology->setDimensionSize(i, Dsizes[i]);
		}
		//last create a neighborhood object and create
		//the map with the topology and neighborhood objects
        neighborhood = new TowerNeighborhood(dimension); //new  AlfilNeighborhood();
        map = new Map(topology, neighborhood);

		//Reserve space to avoid copy a lot memory if the size of the graph result to big.
		int graphSize = 1;
		for(int i=0;i < dimension; ++i){
			graphSize = graphSize * dimSizes[i];
		}
		graph.reserve(graphSize);
	}
    
    /// The copy-constructor:
    SyncronousAutomaton(const SyncronousAutomaton& a){
		pointerToNodes = a.pointerToNodes; 
		pointerToNodesTPlusOne = a.pointerToNodesTPlusOne;
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
    SyncronousAutomaton& operator=(const SyncronousAutomaton& a) {
        pointerToNodes = a.pointerToNodes; 
		pointerToNodesTPlusOne = a.pointerToNodesTPlusOne;
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
	///ToDo:
	void setMap();
    ///ToDo:
	void getMap();
	/// Change the borthers in the topology
	void setNormalizedDimencion(int dim){
		map->setNormalizedDimencion(dim);
	}
    ///ith this method you can set another neighborhood in the automaton 
	void setNeighborhood(Neighborhood *hood){
		map->setNeighborhood(hood);
	}
    ///ToDo:
	void getNeighborhood();

	
    /**
	* In this function are created all the neigbor's, and
    * and set the pointers to the states matrix, the
    * structure of the net is glue by union structures, they
    * consist of one pointer to a cell (the center cell), and
    * the index (index of a vector or array 
    * container) of the pointer's  list, list of pointers to the 
    * elements in the game board, the pointers represent 
    * neighbor's of the center cells, the index represents
    * the start, and end of a neighborhood of a the center 
    * cell of the union
	*/
    void iterateOverTheSatesArray(int index=0);
	/*******************************************************/
	///ToDo:
	void nextStep();
    ///ToDo: Document
	void createNode();
    

	/**
	* If you want to access any element in the multi-dimensional
    * array, the states array; use the pointer to the first element 
    * and advance the pointer to the position array of the 
    * element to acces 
	*/
    void getNodePointer(std::vector<int> position);
    ///ToDo:
	void getNodePointer(int position[]);
    ///ToDo:
	void getNodePointer();
    /****************************************************/    
    
};

/*This method change the copy pointer(copyP) to a element in 
    the states array given by the position argument*/
template<class T>
void SyncronousAutomaton<T>::getNodePointer()
    {
    /* If you want to access any element in a multi-dimensional
    array, use a pointer to the first element and advance 
    the pointer to the position of the element that you want
    to change/access. 
	This method change the copy pointer(copyPointerToNodes) 
	global variable to point a element in the states array given by 
	the one dimenssional array, the position vector, the global 
	array copyDimSizes*/
    
        //first point the copy pointer to the [0][0][0]...[0]
        //position, the begining element of the array
        copyPointerToNodes = pointerToNodes; 
		copyPointerToNodesTPlusOne = pointerToNodesTPlusOne;
        /*whe need a int to count the positions 
		to move the pointer */
        int move = 0 ;
        
        //for all the elements in the given position
		//(the copyDimSizes position variable)
		//the copyDimSizes size is = dimension 
        for(int i=0; i<dimension; i++ ){
            //if is not the last element
            if( (i+1) < dimension){
                //multiply all the position index's for 
                //each dimension size    
                move = copyDimSizes[i];
                for(int j = (i+1); j < dimension; j++){        
                    move = (move)*(dimSizes[j]);
                }
                  copyPointerToNodes += move;
				  copyPointerToNodesTPlusOne += move;
            }
            //if is the last element move the pointer the position
            //number     
			else{
                copyPointerToNodes += copyDimSizes[i];
				copyPointerToNodesTPlusOne += copyDimSizes[i];
			}
        } 
}//---------------getNodePointer()--------------------------

template<class T>
void SyncronousAutomaton<T>::getNodePointer(std::vector<int> position)
    {
    /* If you want to access any element in a multi-dimensional
    array, use a pointer to the first element and advance 
    the pointer to the position of the element that you want
    to change/access. 
	This method change the copy pointer(copyPointerToNodes) 
	global variable to point a element in the states array given by 
	the vector<int> position argument*/
    
        //first point the copy pointer to the [0][0][0]...[0]
        //position, the begining element of the array
        copyPointerToNodes = pointerToNodes;
		copyPointerToNodesTPlusOne = pointerToNodesTPlusOne;
        /*whe need a int to count the positions 
		to move the pointer */
        int move = 0 ;
        
        //for all the elements in the given position
		//(vector<int> position argument)
		//the position size is = dimension 
        for(int i=0; i<dimension; i++ ){
            //if is not the last element
            if( (i+1) < dimension ){
                //multiply all the position index's for 
                //each dimension size    
                move = position[i];
                for(int j = (i+1); j < dimension; j++){        
                    move = (move)*(dimSizes[j]);
                }
                //and move that number of times the pointer                                    
                copyPointerToNodes += move;
				copyPointerToNodesTPlusOne += move;
            }
            //if is the last element move the pointer the position
            //number     
			else{
                copyPointerToNodes += position[i];
				copyPointerToNodesTPlusOne += position[i];
			}
		} 
    }//---------------getNodePointer(vector<int> position)--------------------------

template<class T>
void SyncronousAutomaton<T>::getNodePointer(int position[])
    {
        //cout << "getNodePointer (int position[]), pointerToNodes "<<*pointerToNodes<<endl;
        /* If you want to access any element in a multi-dimensional
     array, pass a pointer to the first element and advance 
     the pointer to the position of the element that you want
     to change */
        
     /*this method change the copy pointer(copyP) to a element in 
    the states array given by the position argument*/
    
        //first point the copy pointer to the [0][0][0]...[0]
        //position, the begining element of the array
        copyPointerToNodes = pointerToNodes;
		copyPointerToNodesTPlusOne = pointerToNodesTPlusOne;
        //whe need a int to count the positions to move the
        //pointer 
        int move = 0 ;
        
        //for all the elements in the given positions
        for(int i=0; i<dimension; i++ ){
            //if is not the last element
            if( (i+1) < dimension ){
                //multiply all index of the position for the 
                //dimension of is respective dimension in the array     
                move = position[i];
                for(int j = (i+1); j < dimension; j++){        
                    move = (move)*(dimSizes[j]);
                }
                //and move that number of times the pointer                                    
                copyPointerToNodes += move;
				copyPointerToNodesTPlusOne += move;
            }
            //if is the last element move the pointer the position
            //number     
			else{
                copyPointerToNodes += position[i];
				copyPointerToNodesTPlusOne += position[i];
			}
        } 
    }//---------------getNodePointer(int position[])--------------------------
    
template<class T>
void SyncronousAutomaton<T>::createNode(){
    /*This method is for create the structure container of the
	couples SyncronousNode and edge/s,the "structure" container is the graph,
	the structure consist of a center pointer to the states matrix,
	the SyncronousNode,and two index for the begining and end of the 
	neighbor's vector container,the edge's(links to the 
	neighborhoods)*/
    
	/*This method use the copyDimSizes position array, this
	vector define the SyncronousNode coordinates in the grid, and the 
	setEdge(position) method from Map class is used to 
	find the edge, map is the mixin betwem the topology class 
	and the neighborhood class.
	The generated edge(pointers to elements in the states arrays) 
	are keep, in the neighbors vector container, and is size 
	determine the index for the SyncronousNode*/
	
	//first get the pointer to the SyncronousNode "center cell"
	//copyPointerToNodes pointer
	getNodePointer();
	//because whe are goin to change copyPointerToNodes pointer
	//first keep the pointing direction
	copyPointerToNodes2 = copyPointerToNodes;
	copyPointerToNodesTPlusOne2 = copyPointerToNodesTPlusOne;
	
	//yo have to transform the position vector, the arraycopyDimSizes[]
	//to a vector container for use for the map
    position.clear();
    position.reserve(dimension);
    for(int i=0;i<dimension;++i){
        position.push_back(copyDimSizes[i]);
    }
	//calculate the neighborhood
    map->setEdge(position);
    std::vector< std::vector<int> > hood = map->getEdge();
	
	//next keep the edge (the pointer) in the neighbors container

	//for all the neighbors directions
    for(int i=0;i<int(hood.size());++i){
		//move the pointer to the element given by the direction
        getNodePointer(hood[i]);
		//and push the pointer in the container
        neighbors.push_back(copyPointerToNodes);    
    }
	//create the SyncronousNode
    SyncronousNode cell(copyPointerToNodes2, copyPointerToNodesTPlusOne2, indexHood, (indexHood + int(hood.size())-1));
    //and laste change the index array for the next time
	indexHood = indexHood + int(hood.size());
    
	//keep the structure in the grahp vector container
    graph.push_back(cell);
    
}//------------createNode()-----------------

template<class T>
void SyncronousAutomaton<T>::iterateOverTheSatesArray(int index){    
    /*With this function you can iterate over an array independently
	of the dimension and element type of the array, this is done 
	tnx to the pointer to the first element of the array
	pointerToNodes, and the dimension sizes array dimSizes[maxDimensions];
    */   
	/*In this method you iterate over the states array to point
	all the elements independently of the dimension of the array
	and call the createNode() method, for each element in the array
	, heach element in the array are  "center cell", the "SyncronousNode" in 
	the graph, but in the array there is no asociation betwen the
	elements, so in createNode() method, the pointer to the 
	element is keep and the edge structure of the SyncronousNode is set and
	keep, in the structure, for each element is create a SyncronousNode 
	structure, and the structures are push in a vector container,
	the graph, now the relationships betwen the edges and nodes 
	are set, and the iteration over the array is done in the one
	dimencional	vector container, the graph, tnx to the 
	structures elements.
	*/
    
         //iterate over the first dimension 
        for( int i=0; i<dimSizes[index] ; ++i ){
            
			//now modify a copy of the dimension sizes array,
			//to use has the new position vector
			copyDimSizes[index] = i;                
                
                //if isn't the last dimension 
                if( (index + 1) < dimension){
                    /*use recursion to modify the copy of 
					the dimension sizes array, and start again
					but for the nexts dimensions
					*/
                    iterateOverTheSatesArray(index+1);                               
                }
                //if is the last dimension
                else{					
			/*modify a copy of the dimension sizes array,
			to use has the new position vector
            in the last dimension*/
					copyDimSizes[index] = i;
                    //and use the index (the new position vector)
                    //to create the SyncronousNode and edge structure
                    createNode();
                }
        }       
}//----------iterateOverTheSatesArray-----------------

template<class T>
void SyncronousAutomaton<T>::nextStep(){
    
}//-----------nextStep()--------------------

#endif //SyncronousAutomaton_H
