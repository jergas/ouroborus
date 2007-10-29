#include "DimensionTest.h"

  void DimensionTest::setUp(){
    dim1 = new Dimension(100,true);
    dim2 = new Dimension(367,false);
  }
  void DimensionTest::tearDown(){
    delete dim1;
    delete dim2;
  }
// method to test the constructor
  void DimensionTest::testConstructor(){
	 // check that the object is constructed correctly
     CPPUNIT_ASSERT_EQUAL(100,dim1->getSize());
     CPPUNIT_ASSERT_EQUAL(367, dim2->getSize());
     bool dim1_normalized = dim1->getNormalized();
	 CPPUNIT_ASSERT_EQUAL(true, dim1_normalized );
     bool dim2_normalized = dim2->getNormalized();
     CPPUNIT_ASSERT_EQUAL(false, dim2_normalized); 
	 
  }//---------testConstructor()-----------
  
  void DimensionTest::testIsOutOfBounds(){
      
    //test the tree cases, upper bounds, in bounds and 
    //below bouns, in a dimension normalized (no bounds) (dim1)
    //and a dimension with bounds (dim2)
       
    bool dim1_OutOfBounds = dim1->isOutOfBounds(400);
    CPPUNIT_ASSERT(dim1_OutOfBounds == false);
    bool dim2_OutOfBounds = dim2->isOutOfBounds(400);
    CPPUNIT_ASSERT(dim2_OutOfBounds == true);
    
    dim1_OutOfBounds = dim1->isOutOfBounds(100);
    CPPUNIT_ASSERT(dim1_OutOfBounds == false);
    dim2_OutOfBounds = dim2->isOutOfBounds(367);
    CPPUNIT_ASSERT(dim2_OutOfBounds == true);
  
    dim1_OutOfBounds = dim1->isOutOfBounds(-10);
    CPPUNIT_ASSERT(dim1_OutOfBounds == false);
    dim2_OutOfBounds = dim2->isOutOfBounds(-10);
    CPPUNIT_ASSERT(dim2_OutOfBounds == true);
    
    dim1_OutOfBounds = dim1->isOutOfBounds(50);
    CPPUNIT_ASSERT(dim1_OutOfBounds == false);
    dim2_OutOfBounds = dim2->isOutOfBounds(50);
    CPPUNIT_ASSERT(dim2_OutOfBounds == false);
        
  }//------testIsOutsideOfBounds()-----------
  void DimensionTest::testGetPos(){
      
    //thest the tree diferent cases, when the position
    //given is in betwen bounds, upper bounds and below bounds  
    //in a normalized dimension (dim1), and with bounds (dim2)
    
     
    CPPUNIT_ASSERT_EQUAL(50, dim1->getPos(50));
    CPPUNIT_ASSERT_EQUAL(163, dim2->getPos(163));
    
    CPPUNIT_ASSERT_EQUAL(0, dim1->getPos(0)); 
    CPPUNIT_ASSERT_EQUAL(0, dim2->getPos(0)); 
    
    CPPUNIT_ASSERT_EQUAL(0, dim1->getPos(100)); 
    CPPUNIT_ASSERT_EQUAL(366, dim2->getPos(366)); 
    
    //tests in a normalized dim
    CPPUNIT_ASSERT_EQUAL(0, dim1->getPos(0)); 
    CPPUNIT_ASSERT_EQUAL(10, dim1->getPos(110)); 
    CPPUNIT_ASSERT_EQUAL(60, dim1->getPos(560)); 
    CPPUNIT_ASSERT_EQUAL(50, dim1->getPos(-50)); 
    CPPUNIT_ASSERT_EQUAL(90, dim1->getPos(-110)); 
    
    //To Do: implement the rise of eseptions
    //and the test of course
    
  }//-------------testGetPos()---------------
  
  CppUnit::Test *DimensionTest::suite() {
  // create a test suite
  CppUnit::TestSuite *DimensionsuiteOfTests = 
    new CppUnit::TestSuite("DimensionTest");

  // add the tests ---------
  DimensionsuiteOfTests->addTest
    (new CppUnit::TestCaller<DimensionTest>
     ("testConstructor", &DimensionTest::testConstructor));
  
  /*DimensionsuiteOfTests->addTest
    (new CppUnit::TestCaller<DimensionTest>
     ("testIsOutOfBounds", &DimensionTest::testIsOutOfBounds));
  */
  DimensionsuiteOfTests->addTest
    (new CppUnit::TestCaller<DimensionTest>
     ("testGetPos", &DimensionTest::testGetPos));
  //end add the tests-------  
   
  return DimensionsuiteOfTests;
  }//-------*DimensionTest::suite()-----------
  
