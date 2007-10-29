#ifndef TopologyTest_h
#define TopologyTest_h

#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Topology.h"

class TopologyTest : public CppUnit::TestFixture{

    Topology *top;
    Topology *top1;
    Topology *top2;
    Topology *top3;
    Topology *top4;
public:

  // two constructors
  TopologyTest() {}
  
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
  //method to test the dimensions in the topology
  void testDimensions();
  //method to thest if some coordinate is in bounds or a null
  //object in this topology
  void testisOutOfBoundsMethod();
  //method to test the transform of coordinates of a given 
  //vector in the coordinates of the same vect in this topology
  //this is the main method of the topology class
  void testgetPos();
  //----------------------------------------------------
  
  
  /* method to create a suite of tests, create a suite for
  topology test, and add to it all the prove methods
  */
  static CppUnit::Test *suite ();

};
#endif
