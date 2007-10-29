#include "AutomatonTest.h"

void AutomatonTest::setUp(){
    
}

void AutomatonTest::tearDown(){
   /* delete automaton1d;
    delete automaton2d;
    delete automaton3d;
*/
	}

void AutomatonTest::testConstructor(){ 
  ///------all the elements of a 1D automaton---------------
    dimSizes1D[0] = x;
    int kk = 0;
    for(int i = 0; i < x; ++i){
        kk = kk + 1;
        grid1d[i] = kk;
    }
    for(int i = 0; i < x; ++i){
        grid1d2[i] = grid1d[i];
    }
    ///----end all the elements of a 1D automaton---------------
    
	//first create all the structure of the net and test is properties
    automaton1d = new Automaton<int>(&grid1d[0], dimSizes1D, dimencions1D); 
    //automaton1d

}//----------------------------------end testConstructor1d() ------------

//test void Automaton<T>::getNodePointer() method	
void AutomatonTest::testGetNodePointerMethod(){

	//---------------1D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes1D[0] = x;
  
	//the t states matrix
    int kk = 0;
	for(int i = 0; i < x; ++i){
        kk = kk + 1;
        grid1d[i] = kk;
    }
	//and de t+1 state matrix
	for(int i = 0; i < x; ++i){
        grid1d2[i] = grid1d[i];
    }
    //then create the automaton
    automaton1d = new Automaton<int>(&grid1d[0], dimSizes1D, dimencions1D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton1d->dimSizes[0];++i){

		//set te position vector to test
		automaton1d->copyDimSizes[0] = i;
		//move the vector copyPointerToNodes to the specific
		//direction
		automaton1d->getNodePointer();
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid1d[i],*(automaton1d->copyPointerToNodes));
	}
	//---------------END 1D case-----------------------

	//---------------2D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes2D[0] = x;
    dimSizes2D[1] = y;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        kk = kk + 1;
        grid2d[i][j] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        grid2d2[i][j] = grid2d[i][j];
    }
    //then create the automaton
    automaton2d = new Automaton<int>(&grid2d[0][0], dimSizes2D, dimencions2D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton2d->dimSizes[0];++i)
	for(int j = 0; j < automaton2d->dimSizes[0];++j){

		//set te position vector to test
		automaton2d->copyDimSizes[0] = i;
		automaton2d->copyDimSizes[1] = j;
		//move the vector copyPointerToNodes to the specific
		//direction
		automaton2d->getNodePointer();
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid2d[i][j],*(automaton2d->copyPointerToNodes));
	}
	//---------------END 2D case-----------------------
	
	//---------------3D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes3D[0] = x;
    dimSizes3D[1] = y;
    dimSizes3D[2] = z;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        kk = kk + 1;
        grid3d[i][j][k] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        grid3d2[i][j][k] = grid3d[i][j][k];
    }
    //then create the automaton
    automaton3d = new Automaton<int>(&grid3d[0][0][0], dimSizes3D, dimencions3D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton3d->dimSizes[0];++i)
	for(int j = 0; j < automaton3d->dimSizes[0];++j)
	for(int k = 0; k < automaton3d->dimSizes[0];++k){

		//set te position vector to test
		automaton3d->copyDimSizes[0] = i;
		automaton3d->copyDimSizes[1] = j;
		automaton3d->copyDimSizes[2] = k;
		//move the vector copyPointerToNodes to the specific
		//direction
		automaton3d->getNodePointer();
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid3d[i][j][k],*(automaton3d->copyPointerToNodes));
	}
	//---------------END 3D case-----------------------
	
}

//test void Automaton<T>::getNodePointer(vector<int> position) method
void AutomatonTest::testGetNodePointerMethod2(){
	//test void Automaton<T>::getNodePointer(vector<int> position) method
	
	//---------------1D case-----------------------
	//first initialize all the variables
    
	//the position vector
	std::vector<int> position1d;

	//the dimencions's sizeses vector
	dimSizes1D[0] = x;
  
	//the t states matrix
    int kk = 0;
	for(int i = 0; i < x; ++i){
        kk = kk + 1;
        grid1d[i] = kk;
    }
	//and de t+1 state matrix
	for(int i = 0; i < x; ++i){
        grid1d2[i] = grid1d[i];
    }
    //then create the automaton
    automaton1d = new Automaton<int>(&grid1d[0], dimSizes1D, dimencions1D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton1d->dimSizes[0];++i){

		//set te position vector to test
		position1d.clear();
		position1d.push_back(i);
		position1d.reserve(1);

		//move the vector copyPointerToNodes to the specific
		//direction
		automaton1d->getNodePointer(position1d);
		//test if the pointer is rigth
		
		CPPUNIT_ASSERT_EQUAL(grid1d[i],*(automaton1d->copyPointerToNodes));
	}
	//---------------END 1D case-----------------------

	//---------------2D case-----------------------
	//first initialize all the variables
    
	//the position vector
	std::vector<int> position2d;

	//the dimencions's sizeses vector
	dimSizes2D[0] = x;
    dimSizes2D[1] = y;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        kk = kk + 1;
        grid2d[i][j] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        grid2d2[i][j] = grid2d[i][j];
    }
    //then create the automaton
    automaton2d = new Automaton<int>(&grid2d[0][0], dimSizes2D, dimencions2D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton2d->dimSizes[0];++i)
	for(int j = 0; j < automaton2d->dimSizes[0];++j){

		position2d.clear();
		//set te position vector to test
		position2d.push_back(i);
		position2d.push_back(j);
		
		position2d.reserve(2);
		
		//move the vector copyPointerToNodes to the specific
		//direction
		automaton2d->getNodePointer(position2d);
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid2d[i][j],*(automaton2d->copyPointerToNodes));
	}
	//---------------END 2D case-----------------------
	
	//---------------3D case-----------------------
	//first initialize all the variables
    

	//the position vector
	std::vector<int> position3d;

	//the dimencions's sizeses vector
	dimSizes3D[0] = x;
    dimSizes3D[1] = y;
    dimSizes3D[2] = z;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        kk = kk + 1;
        grid3d[i][j][k] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        grid3d2[i][j][k] = grid3d[i][j][k];
    }
    //then create the automaton
    automaton3d = new Automaton<int>(&grid3d[0][0][0], dimSizes3D, dimencions3D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton3d->dimSizes[0];++i)
	for(int j = 0; j < automaton3d->dimSizes[0];++j)
	for(int k = 0; k < automaton3d->dimSizes[0];++k){

		position3d.clear();
		//set te position vector to test
		position3d.push_back(i);
		position3d.push_back(j);
		position3d.push_back(k);
		
		position3d.reserve(3);

		//move the vector copyPointerToNodes to the specific
		//direction
		automaton3d->getNodePointer(position3d);
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid3d[i][j][k],*(automaton3d->copyPointerToNodes));
	}
	//---------------END 3D case-----------------------
	
}
//test void Automaton<T>::getNodePointer(int position[]) method	
void AutomatonTest::testGetNodePointerMethod3(){
	//test void Automaton<T>::getNodePointer(int position[]) method
	//---------------1D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes1D[0] = x;
  
	//the t states matrix
    int kk = 0;
	for(int i = 0; i < x; ++i){
        kk = kk + 1;
        grid1d[i] = kk;
    }
	//and de t+1 state matrix
	for(int i = 0; i < x; ++i){
        grid1d2[i] = grid1d[i];
    }
    //then create the automaton
    automaton1d = new Automaton<int>(&grid1d[0], dimSizes1D, dimencions1D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton1d->dimSizes[0];++i){

		//set te position vector to test
		automaton1d->copyDimSizes[0] = i;
		//move the vector copyPointerToNodes to the specific
		//direction
		automaton1d->getNodePointer(automaton1d->copyDimSizes);
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid1d[i],*(automaton1d->copyPointerToNodes));
	}
	//---------------END 1D case-----------------------

	//---------------2D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes2D[0] = x;
    dimSizes2D[1] = y;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        kk = kk + 1;
        grid2d[i][j] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        grid2d2[i][j] = grid2d[i][j];
    }
    //then create the automaton
    automaton2d = new Automaton<int>(&grid2d[0][0], dimSizes2D, dimencions2D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton2d->dimSizes[0];++i)
	for(int j = 0; j < automaton2d->dimSizes[0];++j){

		//set te position vector to test
		automaton2d->copyDimSizes[0] = i;
		automaton2d->copyDimSizes[1] = j;
		//move the vector copyPointerToNodes to the specific
		//direction
		automaton2d->getNodePointer(automaton2d->copyDimSizes);
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid2d[i][j],*(automaton2d->copyPointerToNodes));
	}
	//---------------END 2D case-----------------------
	
	//---------------3D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes3D[0] = x;
    dimSizes3D[1] = y;
    dimSizes3D[2] = z;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        kk = kk + 1;
        grid3d[i][j][k] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        grid3d2[i][j][k] = grid3d[i][j][k];
    }
    //then create the automaton
    automaton3d = new Automaton<int>(&grid3d[0][0][0], dimSizes3D, dimencions3D);    
	
	//test the method for all the elements in the states
	//matrix
	//the copyDimSizes[] array is the position vector to test
	//and the copyPointerToNodes pointer is the moved pointer
	//we have to test that the pointer is really pointing
	//to the desaired direction (specify by copyDimSizes[] array)
	
	
	//for all the element in the states matrix
	for(int i = 0; i < automaton3d->dimSizes[0];++i)
	for(int j = 0; j < automaton3d->dimSizes[0];++j)
	for(int k = 0; k < automaton3d->dimSizes[0];++k){

		//set te position vector to test
		automaton3d->copyDimSizes[0] = i;
		automaton3d->copyDimSizes[1] = j;
		automaton3d->copyDimSizes[2] = k;
		//move the vector copyPointerToNodes to the specific
		//direction
		automaton3d->getNodePointer(automaton3d->copyDimSizes);
		//test if the pointer is rigth
		CPPUNIT_ASSERT_EQUAL(grid3d[i][j][k],*(automaton3d->copyPointerToNodes));
	}
	//---------------END 3D case-----------------------
	
}

//test iterateOverTheSatesArray(int index) method
void AutomatonTest::testIterateOverTheSatesArray(){	
	//---------------1D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes1D[0] = x;
  
	//the t states matrix
    int kk = 0;
	for(int i = 0; i < x; ++i){
        kk = kk + 1;
        grid1d[i] = kk;
    }
	//and de t+1 state matrix
	for(int i = 0; i < x; ++i){
        grid1d2[i] = grid1d[i];
    }
    //then create the automaton
    automaton1d = new Automaton<int>(&grid1d[0], dimSizes1D, dimencions1D);    
	
	//create the graph 
	automaton1d->iterateOverTheSatesArray();
	
	//modify all the states matrix with the new onedimensional
	//container, the graph
	for(size_t i = 0; i < automaton1d->graph.size(); ++i){
		*(automaton1d->graph[i].centerCell) = -10;
	}
	//and tests the correctnes of the method 	
	//for all the element in the states matrix
	for(int i = 0; i < automaton1d->dimSizes[0];++i){

	CPPUNIT_ASSERT_EQUAL(-10,*(automaton1d->copyPointerToNodes));
	}
	//---------------END 1D case-----------------------
	
	//---------------2D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes2D[0] = x;
    dimSizes2D[1] = y;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        kk = kk + 1;
        grid2d[i][j] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        grid2d2[i][j] = grid2d[i][j];
    }
    //then create the automaton
    automaton2d = new Automaton<int>(&grid2d[0][0], dimSizes2D, dimencions2D);    
	
	//create the graph 
	automaton2d->iterateOverTheSatesArray();
	
	//modify all the states matrix with the new onedimensional
	//container, the graph
	for(size_t i = 0; i < automaton2d->graph.size(); ++i){
		*(automaton2d->graph[i].centerCell) = -10;
	}
	//and tests the correctnes of the method 	
	//for all the element in the states matrix
	for(int i = 0; i < automaton2d->dimSizes[0];++i)
	for(int j = 0; j < automaton2d->dimSizes[0];++j){

		CPPUNIT_ASSERT_EQUAL(-10,*(automaton2d->copyPointerToNodes));
	}
	//---------------END 2D case-----------------------
	
	//---------------3D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizes vector
	dimSizes3D[0] = x;
    dimSizes3D[1] = y;
    dimSizes3D[2] = z;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        kk = kk + 1;
        grid3d[i][j][k] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        grid3d2[i][j][k] = grid3d[i][j][k];
    }
    //then create the automaton
    automaton3d = new Automaton<int>(&grid3d[0][0][0], dimSizes3D, dimencions3D);    
	
	//create the graph 
	automaton3d->iterateOverTheSatesArray();
	
	//modify all the states matrix with the new onedimensional
	//container, the graph
	for(size_t i = 0; i < automaton3d->graph.size(); ++i){
		*(automaton3d->graph[i].centerCell) = -10;
	}
	//and tests the correctnes of the method 	
	//for all the element in the states matrix
	for(int i = 0; i < automaton3d->dimSizes[0];++i)
	for(int j = 0; j < automaton3d->dimSizes[0];++j)
	for(int k = 0; k < automaton3d->dimSizes[0];++k){
		CPPUNIT_ASSERT_EQUAL(-10,*(automaton3d->copyPointerToNodes));
	}
	//---------------END 3D case-----------------------
	
}

//test createNode() method
void AutomatonTest::testCreateNode(){
//---------------1D case-----------------------
	//first initialize all the variables
    
	//the dimencions sizeses vector
	dimSizes1D[0] = x;
  
	//the t states matrix
    int kk = 0;
	for(int i = 0; i < x; ++i){
        kk = kk + 1;
        grid1d[i] = kk;
    }
	//and de t+1 state matrix
	for(int i = 0; i < x; ++i){
        grid1d2[i] = grid1d[i];
    }
    //then create the automaton
    automaton1d = new Automaton<int>(&grid1d[0], dimSizes1D, dimencions1D);    
	
	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton1d->indexHood = 0;

	//first set the position vector to test
	automaton1d->copyDimSizes[0] = 0;
	
	//use the method
	automaton1d->createNode();
	
	//test the if the results are rigth

	CPPUNIT_ASSERT_EQUAL(1,int(automaton1d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(1,*(automaton1d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(1,int(automaton1d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(0,automaton1d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(0,automaton1d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(2,*(automaton1d->neighbors[automaton1d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(2,*(automaton1d->neighbors[automaton1d->graph[0].endNeighbor]));
	
	
	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton1d->indexHood = 0;
	//and clear all the containers
	automaton1d->graph.clear();
	automaton1d->neighbors.clear();
	
	//first set the position vector to test
	automaton1d->copyDimSizes[0] = 10;
	
	//use the method
	automaton1d->createNode();
	
	//test the if the results are rigth
	
	//test if the pointer is rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton1d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(11,*(automaton1d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(2,int(automaton1d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(0,automaton1d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(1,automaton1d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(12,*(automaton1d->neighbors[automaton1d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(10,*(automaton1d->neighbors[automaton1d->graph[0].endNeighbor]));
	
	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton1d->indexHood = 0;
	//and clear all the containers
	automaton1d->graph.clear();
	automaton1d->neighbors.clear();
	
	//first set the position vector to test
	automaton1d->copyDimSizes[0] = 29;
	
	//use the method
	automaton1d->createNode();
	
	//test the if the results are rigth
	
	//test if the pointer is rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton1d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(30,*(automaton1d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(1,int(automaton1d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(0,automaton1d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(0,automaton1d->graph[0].endNeighbor);
    CPPUNIT_ASSERT_EQUAL(29,*(automaton1d->neighbors[automaton1d->graph[0].beginNeighbor]));
	
    //---------------END 1D case-----------------------

    //---------------2D case-----------------------
    //first initialize all the variables
    
    //the dimencions's sizeses vector
    dimSizes2D[0] = x;
    dimSizes2D[1] = y;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        kk = kk + 1;
        grid2d[i][j] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j){
        grid2d2[i][j] = grid2d[i][j];
    }
    //then create the automaton
    automaton2d = new Automaton<int>(&grid2d[0][0], dimSizes2D, dimencions2D);    
	
    // because indexHood  is static for testing proposes is
    //set to 0 fisrt time we use it
    automaton2d->indexHood = 0;
    //and clear all the containers
    automaton2d->graph.clear();
    automaton2d->neighbors.clear();
	
    //first set the position vector to test
    for(int i=0;i<automaton2d->dimension;++i){
        automaton2d->copyDimSizes[i] = 0;
    }
    //run the method
    automaton2d->createNode();
    
    //and test if the results are rigth
    CPPUNIT_ASSERT_EQUAL(1,int(automaton2d->graph.size()));
    CPPUNIT_ASSERT_EQUAL(2,int(automaton2d->neighbors.size()));
    CPPUNIT_ASSERT_EQUAL(1,*(automaton2d->graph[0].centerCell));
    CPPUNIT_ASSERT_EQUAL(0,automaton2d->graph[0].beginNeighbor);
    CPPUNIT_ASSERT_EQUAL(1,automaton2d->graph[0].endNeighbor);
    CPPUNIT_ASSERT_EQUAL(31,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor]));
    CPPUNIT_ASSERT_EQUAL(2,*(automaton2d->neighbors[automaton2d->graph[0].endNeighbor]));	
    
    // because indexHood  is static for testing proposes is
    //set to 0 fisrt time we use it
    automaton2d->indexHood = 0;
    //and clear all the containers
    automaton2d->graph.clear();
	automaton2d->neighbors.clear();
	
	//first set the position vector to test
	for(int i=0;i<automaton2d->dimension;++i){
		automaton2d->copyDimSizes[i] = 29;
	}
	//run the method
	automaton2d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton2d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(2,int(automaton2d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(900,*(automaton2d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton2d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(1,automaton2d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(870,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(899,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor+1]));
	
	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton2d->indexHood = 0;
	//and clear all the containers
	automaton2d->graph.clear();
	automaton2d->neighbors.clear();
	
	//first set the position vector to test
	for(int i=0;i<automaton2d->dimension;++i){
		automaton2d->copyDimSizes[i] = 10;
	}
	//run the method
	automaton2d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton2d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(4,int(automaton2d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(311,*(automaton2d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton2d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(3,automaton2d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(341,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(281,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor+1]));
	CPPUNIT_ASSERT_EQUAL(312,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor+2]));
	CPPUNIT_ASSERT_EQUAL(310,*(automaton2d->neighbors[automaton2d->graph[0].endNeighbor]));	

	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton2d->indexHood = 0;
	//and clear all the containers
	automaton2d->graph.clear();
	automaton2d->neighbors.clear();
	
	//first set the position vector to test
	
	automaton2d->copyDimSizes[0] = 10;
	automaton2d->copyDimSizes[1] = 0;
	
	//run the method
	automaton2d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton2d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(3,int(automaton2d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(301,*(automaton2d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton2d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(2,automaton2d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(331,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(271,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor+1]));
	CPPUNIT_ASSERT_EQUAL(302,*(automaton2d->neighbors[automaton2d->graph[0].endNeighbor]));	

	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton2d->indexHood = 0;
	//and clear all the containers
	automaton2d->graph.clear();
	automaton2d->neighbors.clear();
	
	//first set the position vector to test
	
	automaton2d->copyDimSizes[0] = 29;
	automaton2d->copyDimSizes[1] = 0;
	
	//run the method
	automaton2d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton2d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(2,int(automaton2d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(871,*(automaton2d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton2d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(1,automaton2d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(841,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(872,*(automaton2d->neighbors[automaton2d->graph[0].endNeighbor]));	

	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton2d->indexHood = 0;
	//and clear all the containers
	automaton2d->graph.clear();
	automaton2d->neighbors.clear();
	
	//first set the position vector to test
	
	automaton2d->copyDimSizes[0] = 0;
	automaton2d->copyDimSizes[1] = 29;
	
	//run the method
	automaton2d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton2d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(2,int(automaton2d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(30,*(automaton2d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton2d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(1,automaton2d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(60,*(automaton2d->neighbors[automaton2d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(29,*(automaton2d->neighbors[automaton2d->graph[0].endNeighbor]));	

	//---------------END 2D case-----------------------
	
	//---------------3D case-----------------------
	//first initialize all the variables
    
	//the dimencions's sizeses vector
	dimSizes3D[0] = x;
    dimSizes3D[1] = y;
    dimSizes3D[2] = z;
	
	//the t states matrix
    kk = 0;
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        kk = kk + 1;
        grid3d[i][j][k] = kk;
    }
	//and de t+1 state matrix
    for(int i = 0; i < x; ++i)
    for(int j = 0; j < y; ++j)
    for(int k = 0; k < z; ++k){
        grid3d2[i][j][k] = grid3d[i][j][k];
    }
    //then create the automaton
    automaton3d = new Automaton<int>(&grid3d[0][0][0], dimSizes3D, dimencions3D);    
	
	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton3d->indexHood = 0;
	//and clear all the containers
	automaton3d->graph.clear();
	automaton3d->neighbors.clear();
	
	//first set the position vector to test
	
	automaton3d->copyDimSizes[0] = 0;
	automaton3d->copyDimSizes[1] = 0;
	automaton3d->copyDimSizes[2] = 0;
	
	//run the method
	automaton3d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton3d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(3,int(automaton3d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(1,*(automaton3d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton3d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(2,automaton3d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(301,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(11,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+1]));
	CPPUNIT_ASSERT_EQUAL(2,*(automaton3d->neighbors[automaton3d->graph[0].endNeighbor]));	

	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton3d->indexHood = 0;
	//and clear all the containers
	automaton3d->graph.clear();
	automaton3d->neighbors.clear();
	
	//first set the position vector to test
	
	automaton3d->copyDimSizes[0] = 2;
	automaton3d->copyDimSizes[1] = 2;
	automaton3d->copyDimSizes[2] = 2;
	
	//run the method
	automaton3d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton3d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(6,int(automaton3d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(623,*(automaton3d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton3d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(5,automaton3d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(923,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(323,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+1]));
	CPPUNIT_ASSERT_EQUAL(633,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+2]));
	CPPUNIT_ASSERT_EQUAL(613,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+3]));
	CPPUNIT_ASSERT_EQUAL(624,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+4]));
	CPPUNIT_ASSERT_EQUAL(622,*(automaton3d->neighbors[automaton3d->graph[0].endNeighbor]));	

	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton3d->indexHood = 0;
	//and clear all the containers
	automaton3d->graph.clear();
	automaton3d->neighbors.clear();
	
	//first set the position vector to test
	
	automaton3d->copyDimSizes[0] = 29;
	automaton3d->copyDimSizes[1] = 2;
	automaton3d->copyDimSizes[2] = 2;
	
	//run the method
	automaton3d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton3d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(5,int(automaton3d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(8723,*(automaton3d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton3d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(4,automaton3d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(8423,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(8733,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+1]));
	CPPUNIT_ASSERT_EQUAL(8713,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+2]));
	CPPUNIT_ASSERT_EQUAL(8724,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+3]));
	CPPUNIT_ASSERT_EQUAL(8722,*(automaton3d->neighbors[automaton3d->graph[0].endNeighbor]));	

	// because indexHood  is static for testing proposes is
	//set to 0 fisrt time we use it
	automaton3d->indexHood = 0;
	//and clear all the containers
	automaton3d->graph.clear();
	automaton3d->neighbors.clear();
	
	//first set the position vector to test
	
	automaton3d->copyDimSizes[0] = 0;
	automaton3d->copyDimSizes[1] = 2;
	automaton3d->copyDimSizes[2] = 2;
	
	//run the method
	automaton3d->createNode();
	
	//and test if the results are rigth
	CPPUNIT_ASSERT_EQUAL(1,int(automaton3d->graph.size()));
	CPPUNIT_ASSERT_EQUAL(5,int(automaton3d->neighbors.size()));
	CPPUNIT_ASSERT_EQUAL(23,*(automaton3d->graph[0].centerCell));
	CPPUNIT_ASSERT_EQUAL(0,automaton3d->graph[0].beginNeighbor);
	CPPUNIT_ASSERT_EQUAL(4,automaton3d->graph[0].endNeighbor);
	CPPUNIT_ASSERT_EQUAL(323,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor]));
	CPPUNIT_ASSERT_EQUAL(33,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+1]));
	CPPUNIT_ASSERT_EQUAL(13,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+2]));
	CPPUNIT_ASSERT_EQUAL(24,*(automaton3d->neighbors[automaton3d->graph[0].beginNeighbor+3]));
	CPPUNIT_ASSERT_EQUAL(22,*(automaton3d->neighbors[automaton3d->graph[0].endNeighbor]));	

	//---------------END 3D case-----------------------
	
}
CppUnit::Test *AutomatonTest::suite() {
  
  // create a test suite
  CppUnit::TestSuite *AutomatonsuiteOfTests = 
	  new CppUnit::TestSuite("AutomatonTest");

  // add the tests ---------
  AutomatonsuiteOfTests->addTest
  (new CppUnit::TestCaller<AutomatonTest>
  ("testConstructor", &AutomatonTest::testConstructor));
  
  AutomatonsuiteOfTests->addTest
  (new CppUnit::TestCaller<AutomatonTest>
  ("testGetNodePointerMethod", &AutomatonTest::testGetNodePointerMethod));
  
  
  AutomatonsuiteOfTests->addTest
  (new CppUnit::TestCaller<AutomatonTest>
  ("testGetNodePointerMethod2", &AutomatonTest::testGetNodePointerMethod2));
   
  
  AutomatonsuiteOfTests->addTest
  (new CppUnit::TestCaller<AutomatonTest>
  ("testGetNodePointerMethod3", &AutomatonTest::testGetNodePointerMethod3)); 
	
  AutomatonsuiteOfTests->addTest
  (new CppUnit::TestCaller<AutomatonTest>
  ("testIterateOverTheSatesArray", &AutomatonTest::testIterateOverTheSatesArray));

  AutomatonsuiteOfTests->addTest
  (new CppUnit::TestCaller<AutomatonTest>
  ("testCreateNode", &AutomatonTest::testCreateNode));

/*AutomatonsuiteOfTests->addTest
  (new CppUnit::TestCaller<AutomatonTest>
  ("testVertexCreation", &AutomatonTest::testVertexCreation));
*/  
  return AutomatonsuiteOfTests;
}//-------*AutomatonTest::suite()-----------
