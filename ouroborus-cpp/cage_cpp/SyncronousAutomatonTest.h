#ifndef SyncronousAutomatonTest_H
#define SyncronousAutomatonTest_H

#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>


#include "SyncronousAutomaton.h"

class SyncronousAutomatonTest : public CppUnit::TestFixture{
  
	SyncronousAutomaton<int> *automaton1d;
	SyncronousAutomaton<int> *automaton2d;
	SyncronousAutomaton<int> *automaton3d;
  
	static const int x = 30, y = 30, z = 10;
	static const int dimencions1D = 1;
	int dimSizes1D[dimencions1D];
	int grid1d[x];
	int grid1d2[x];
	int grid1dNt1[x];
	int grid1d2Nt1[x];
	static const int dimencions2D = 2;
	int dimSizes2D[dimencions2D];
	int grid2d[x][y];
	int grid2d2[x][y];
	int grid2dNt1[x][y];
	int grid2d2Nt1[x][y];
	static const int dimencions3D = 3;
	int dimSizes3D[dimencions3D];
	int grid3d[x][y][z];
	int grid3d2[x][y][z];
    int grid3dNt1[x][y][z];
	int grid3d2Nt1[x][y][z];
    
	  public:
	  
	//override cppuni method for the creation of the
	//instances to use
	void setUp();
  
	//override cppuni method for the destruction of the
	//instances used
	void tearDown();
	//--------------------------------------------------
	/*you have to create the methods to put all the 
	ASSERT'S of cppunit, one for all the caracteristic you 
	want to prove :-P */
	void testConstructor();
	//test void Automaton<T>::getNodePointer() method
	void testGetNodePointerMethod();
	//test void Automaton<T>::getNodePointer(vector<int> position) method
	void testGetNodePointerMethod2();
	//test void Automaton<T>::getNodePointer(int position[]) method
	void testGetNodePointerMethod3();
	//test iterateOverTheSatesArray(int index) method
	void testIterateOverTheSatesArray();
	//test createNode() method
	void testCreateNode();
	//--------------------------------------------------
  
	/* method to create a suite of tests, create a suite for
	Dimension test, and add to it all the prove methods
	*/
	static CppUnit::Test *suite ();
	
};
#endif //SyncronousAutomatonTest_H