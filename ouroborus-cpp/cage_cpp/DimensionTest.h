#ifndef DimensionTest_h
#define DimensionTest_h

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Dimension.h"

// This class is for test all the properties of the dimension class.
/********************************************************************
* In this class is tested the size and normalization of the dimension. 
********************************************************************/
class DimensionTest : public CppUnit::TestFixture  {


    Dimension *dim1;
    Dimension *dim2;
    
public:

  // two constructor
  DimensionTest() {}
  
  //Override cppunit method for the creation of the instances to use.
  void setUp();
  
  //Override cppunit method for the destruction of the instances used.
  void tearDown();
  //--------------------------------------------------
  /*you have to create the methods to put all the 
  ASSERT'S of cppunit, one for all the caracteristic you 
  want to prove :-P */
  
  // method to test the constructor
  void testConstructor();
  
  //method to test the detection of the bounds for a cordanate
  void testIsOutOfBounds();
  
  //method to test position asigner 
  void testGetPos();
  //----------------------------------------------------
  
  
  /* method to create a suite of tests, create a suite for
  Dimension test, and add to it all the prove methods
  */
  static CppUnit::Test *suite ();

};

#endif
