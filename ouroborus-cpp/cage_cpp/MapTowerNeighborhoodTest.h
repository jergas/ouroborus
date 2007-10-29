#ifndef MapTowerNeighborhoodTest_h
#define MapTowerNeighborhoodTest_h

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include <vector> 

#include "Map.h"
#include "Topology.h"
#include "Neighborhood.h"
#include "TowerNeighborhood.h"


class MapTowerNeighborhoodTest : public CppUnit::TestFixture  {
    
    Topology *top1d;
    Topology *top2d;
    Topology *top3d;
    
    Neighborhood *hood1D; 
    Neighborhood *hood2D; 
    Neighborhood *hood3D; 
    
    Map *map1d;
    Map *map2d;
    Map *map3d;
    
public:

  // constructorº
  MapTowerNeighborhoodTest() {}
  
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
  
  //the method to test the created edge creation are to big so
  //they must be separated en tree diferents methods
  void testGetEdgeOneDimension();
  void testGetEdgeTwoDimensions();
  void testGetEdgeTreeDimensions();
  //----------------------------------------------------
  
  
  /* method to create a suite of tests, create a suite for
  Dimension test, and add to it all the prove methods
  */
  static CppUnit::Test *suite ();

};
#endif
