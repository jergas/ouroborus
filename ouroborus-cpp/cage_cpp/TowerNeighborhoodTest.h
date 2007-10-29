#ifndef NeighborhoodTest_h
#define NeighborhoodTest_h

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector>

#include "TowerNeighborhood.h"

class TowerNeighborhoodTest : public CppUnit::TestFixture {

  //the Neighborhood's to be tested  
  Neighborhood *hood1D;
  Neighborhood *hood2D;
  Neighborhood *hood3D;    
  public:
  
  // two constructors
  TowerNeighborhoodTest() {}
  
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
  
  // method to test the constructor
  void testConstructor();
  
  
  //method to test the calculateNeigborhood method, this is 
  //the main method in the class, and makes all the calculations
  //in N dimensions
  //first test the default size
  void testCalculateNeighborhoodSizeOne();
  
  //then test size two
  void testCalculateNeighborhoodSizeTwo();
  
  //then test size tree
  void testCalculateNeighborhoodSizeTree();
     
  //test the arranged neighborhood
  void testArrangedNeighborhood();
  //----------------------------------------------------
  
  /* method to create a suite of tests, create a suite for
  Dimension test, and add to it all the prove methods
  */
  static CppUnit::Test *suite ();

};

#endif
