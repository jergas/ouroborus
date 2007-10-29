#include "TopologyTest.h"


  void TopologyTest::setUp(){     
     top = new Topology(3,0);
     top1 = new Topology(3,1);
     top2 = new Topology(3,2);
     top3 = new Topology(3,3);
  }//--------TopologyTest::setUp()-------
  
  void TopologyTest::tearDown(){
    delete top;
    delete top1;
    delete top2;
    delete top3;
  }//--------TopologyTest::tearDown----------
  
  // method to test the constructor
  void TopologyTest::testConstructor(){ 
    // check that the object is constructed correctly
    
    //first test the number of dimensions, number of dim
    //normalized, and the check the values given when you
    //ask one dimension by one
    int top_dim = int(top->getDimensionality());
    CPPUNIT_ASSERT_EQUAL(3, top_dim);
    int top_normalized = top->getDimNormalized();
    CPPUNIT_ASSERT_EQUAL(0, top_normalized);  
    int top_sizeX = top->getDimensionSize(0);
    int top_sizeY = top->getDimensionSize(1);
    int top_sizez = top->getDimensionSize(2);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeX);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeY);
    CPPUNIT_ASSERT_EQUAL(100, top_sizez);
    bool isNormalizedX = top->getDimensionNormalized(0);
    bool isNormalizedY = top->getDimensionNormalized(1);
    bool isNormalizedZ = top->getDimensionNormalized(2);
    CPPUNIT_ASSERT_EQUAL(false, isNormalizedX);
    CPPUNIT_ASSERT_EQUAL(false, isNormalizedY);
    CPPUNIT_ASSERT_EQUAL(false, isNormalizedZ);
      
    top_dim = int(top1->getDimensionality());
    CPPUNIT_ASSERT_EQUAL(3, top_dim);
    top_normalized = top1->getDimNormalized();
    CPPUNIT_ASSERT_EQUAL(1, top_normalized);
    top_sizeX = top1->getDimensionSize(0);
    top_sizeY = top1->getDimensionSize(1);
    top_sizez = top1->getDimensionSize(2);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeX);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeY);
    CPPUNIT_ASSERT_EQUAL(100, top_sizez);
    isNormalizedX = top1->getDimensionNormalized(0);
    isNormalizedY = top1->getDimensionNormalized(1);
    isNormalizedZ = top1->getDimensionNormalized(2);
    CPPUNIT_ASSERT_EQUAL(true, isNormalizedX);
    CPPUNIT_ASSERT_EQUAL(false, isNormalizedY);
    CPPUNIT_ASSERT_EQUAL(false, isNormalizedZ);
    
    top_dim = int(top2->getDimensionality());
    CPPUNIT_ASSERT_EQUAL(3, top_dim);
    top_normalized = top2->getDimNormalized();
    CPPUNIT_ASSERT_EQUAL(2, top_normalized);
    top_sizeX = top2->getDimensionSize(0);
    top_sizeY = top2->getDimensionSize(1);
    top_sizez = top2->getDimensionSize(2);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeX);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeY);
    CPPUNIT_ASSERT_EQUAL(100, top_sizez);
    isNormalizedX = top2->getDimensionNormalized(0);
    isNormalizedY = top2->getDimensionNormalized(1);
    isNormalizedZ = top2->getDimensionNormalized(2);
    CPPUNIT_ASSERT_EQUAL(true, isNormalizedX);
    CPPUNIT_ASSERT_EQUAL(true, isNormalizedY);
    CPPUNIT_ASSERT_EQUAL(false, isNormalizedZ);
    
  
    top_dim = int(top3->getDimensionality());
    CPPUNIT_ASSERT_EQUAL(3, top_dim);
    top_normalized = top3->getDimNormalized();
    CPPUNIT_ASSERT_EQUAL(3, top_normalized);
    top_sizeX = top3->getDimensionSize(0);
    top_sizeY = top3->getDimensionSize(1);
    top_sizez = top3->getDimensionSize(2);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeX);
    CPPUNIT_ASSERT_EQUAL(100, top_sizeY);
    CPPUNIT_ASSERT_EQUAL(100, top_sizez);
    isNormalizedX = top3->getDimensionNormalized(0);
    isNormalizedY = top3->getDimensionNormalized(1);
    isNormalizedZ = top3->getDimensionNormalized(2);
    CPPUNIT_ASSERT_EQUAL(true, isNormalizedX);
    CPPUNIT_ASSERT_EQUAL(true, isNormalizedY);
    CPPUNIT_ASSERT_EQUAL(true, isNormalizedZ);
  
  }//------TopologyTest::testConstructor()-------
  
  void TopologyTest::testDimensions(){
    //check that the number, size and normalized of the 
    //dimension objects is correct
    
    int dim_size = 100; //default size
    //value to thest the normailzation of a given dimension
    bool dim_normalized = true;
    //for all dimensions
    for(int i=0; i< int(top->getDimensionality()); ++i){
      //iff the value off the index is bigger than
      //number of dim's normalized the dim's has to have bounds
      if(i>(top->getDimNormalized()-1)){dim_normalized = false;}
      CPPUNIT_ASSERT_EQUAL(dim_size, top->getDimensionSize(i));
      CPPUNIT_ASSERT_EQUAL(dim_normalized, top->getDimensionNormalized(i));
      //CPPUNIT_ASSERT();  
    }//end for
    dim_normalized = true;
    //for all dimensions
    for(int i=0; i< int(top1->getDimensionality()); ++i){
      //iff the value off the index is bigger than
      //number of dim's normalized the dim's has to have bounds
      if(i>(top1->getDimNormalized()-1)){dim_normalized = false;}
      CPPUNIT_ASSERT_EQUAL(dim_size, top1->getDimensionSize(i));
      CPPUNIT_ASSERT_EQUAL(dim_normalized, top1->getDimensionNormalized(i));
      //CPPUNIT_ASSERT();  
    }//end for
    dim_normalized = true;
    //for all dimensions
    for(int i=0; i< int(top2->getDimensionality()); ++i){
      //iff the value off the index is bigger than
      //number of dim's normalized the dim's has to have bounds
      if(i>(top2->getDimNormalized()-1)){dim_normalized = false;}
      CPPUNIT_ASSERT_EQUAL(dim_size, top2->getDimensionSize(i));
      CPPUNIT_ASSERT_EQUAL(dim_normalized, top2->getDimensionNormalized(i));
      //CPPUNIT_ASSERT();  
    }//end for
    dim_normalized = true;
    //for all dimensions
    for(int i=0; i< int(top3->getDimensionality()); ++i){
      //iff the value off the index is bigger than
      //number of dim's normalized the dim's has to have bounds
      if(i>(top3->getDimNormalized()-1)){dim_normalized = false;}
      CPPUNIT_ASSERT_EQUAL(dim_size, top3->getDimensionSize(i));
      CPPUNIT_ASSERT_EQUAL(dim_normalized, top3->getDimensionNormalized(i));
      //CPPUNIT_ASSERT();  
    }//end for
  }//-------TopologyTest::testDimensions()-----
  
  void TopologyTest::testisOutOfBoundsMethod(){
    //test in bounds
    
    std::vector<int> positionVector1;
    positionVector1.push_back(50);
    positionVector1.push_back(50);
    positionVector1.push_back(50);
    
    //test one position out of bounds
    std::vector<int> positionVector2; 
    positionVector2.push_back(110);
    positionVector2.push_back(50);
    positionVector2.push_back(50);
    
    std::vector<int> positionVector3;
    positionVector3.push_back(50);
    positionVector3.push_back(110);
    positionVector3.push_back(50);
    
    std::vector<int> positionVector4;
    positionVector4.push_back(50);
    positionVector4.push_back(50);
    positionVector4.push_back(110);
    
    std::vector<int> positionVector5;
    positionVector5.push_back(-10);
    positionVector5.push_back(50);
    positionVector5.push_back(50);
    
    std::vector<int> positionVector6;
    positionVector6.push_back(50);
    positionVector6.push_back(-10);
    positionVector6.push_back(50);
    
    std::vector<int> positionVector7;
    positionVector7.push_back(50);
    positionVector7.push_back(50);
    positionVector7.push_back(-10);
    
    //test two positions out of bounds
    std::vector<int> positionVector8;
    positionVector8.push_back(110);
    positionVector8.push_back(110);
    positionVector8.push_back(50);
    
    std::vector<int> positionVector9;
    positionVector9.push_back(110);
    positionVector9.push_back(50);
    positionVector9.push_back(110);
    
    std::vector<int> positionVector10;
    positionVector10.push_back(50);
    positionVector10.push_back(110);
    positionVector10.push_back(110);
     
    std::vector<int> positionVector11;
    positionVector11.push_back(-10);
    positionVector11.push_back(-10);
    positionVector11.push_back(50);
     
    std::vector<int> positionVector12;
    positionVector12.push_back(-10);
    positionVector12.push_back(50);
    positionVector12.push_back(-10);
     
    std::vector<int> positionVector13;
    positionVector13.push_back(50);
    positionVector13.push_back(-10);
    positionVector13.push_back(-10);
     
    
    //test tree positions out of bounds
    std::vector<int> positionVector14;
    positionVector14.push_back(110);
    positionVector14.push_back(110);
    positionVector14.push_back(110);
     
    std::vector<int> positionVector15;
    positionVector15.push_back(-10);
    positionVector15.push_back(-10);
    positionVector15.push_back(-10);
    
    //for topology object dim=3,normalized=0,size=100
    CPPUNIT_ASSERT_EQUAL(false , top->isOutOfBounds(positionVector1));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector2));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector3));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector4));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector5));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector6));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector7));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector8));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector9));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector10));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector11));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector12));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector13));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector14));
    CPPUNIT_ASSERT_EQUAL(true , top->isOutOfBounds(positionVector15));
    //for topology1 object dim=3,normalized=1,size=100    
    CPPUNIT_ASSERT_EQUAL(false , top1->isOutOfBounds(positionVector1));
    CPPUNIT_ASSERT_EQUAL(false , top1->isOutOfBounds(positionVector2));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector3));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector4));
    CPPUNIT_ASSERT_EQUAL(false , top1->isOutOfBounds(positionVector5));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector6));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector7));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector8));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector9));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector10));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector11));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector12));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector13));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector14));
    CPPUNIT_ASSERT_EQUAL(true , top1->isOutOfBounds(positionVector15));
    
    //for topology2 object dim=3,normalized=2,size=100    
    CPPUNIT_ASSERT_EQUAL(false , top2->isOutOfBounds(positionVector1));
    CPPUNIT_ASSERT_EQUAL(false , top2->isOutOfBounds(positionVector2));
    CPPUNIT_ASSERT_EQUAL(false , top2->isOutOfBounds(positionVector3));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector4));
    CPPUNIT_ASSERT_EQUAL(false , top2->isOutOfBounds(positionVector5));
    CPPUNIT_ASSERT_EQUAL(false , top2->isOutOfBounds(positionVector6));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector7));
    CPPUNIT_ASSERT_EQUAL(false , top2->isOutOfBounds(positionVector8));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector9));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector10));
    CPPUNIT_ASSERT_EQUAL(false , top2->isOutOfBounds(positionVector11));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector12));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector13));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector14));
    CPPUNIT_ASSERT_EQUAL(true , top2->isOutOfBounds(positionVector15));
    //for topology3 object dim=3,normalized=3,size=100    
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector1));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector2));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector3));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector4));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector5));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector6));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector7));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector8));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector9));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector10));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector11));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector12));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector13));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector14));
    CPPUNIT_ASSERT_EQUAL(false , top3->isOutOfBounds(positionVector15));
    
  }//---------TopologyTest::testisOutOfBoundsMethod()---------
  
  void TopologyTest::testgetPos(){
    //test in bounds
    std::vector<int> positionVector1;
    positionVector1.push_back(50);
    positionVector1.push_back(50);
    positionVector1.push_back(50);
    
    //test one position out of bounds
    std::vector<int> positionVector2; 
    positionVector2.push_back(110);
    positionVector2.push_back(50);
    positionVector2.push_back(50);
    
    std::vector<int> positionVector3;
    positionVector3.push_back(50);
    positionVector3.push_back(110);
    positionVector3.push_back(50);
    
    std::vector<int> positionVector4;
    positionVector4.push_back(50);
    positionVector4.push_back(50);
    positionVector4.push_back(110);
    
    std::vector<int> positionVector5;
    positionVector5.push_back(-10);
    positionVector5.push_back(50);
    positionVector5.push_back(50);
    
    std::vector<int> positionVector6;
    positionVector6.push_back(50);
    positionVector6.push_back(-10);
    positionVector6.push_back(50);
    
    std::vector<int> positionVector7;
    positionVector7.push_back(50);
    positionVector7.push_back(50);
    positionVector7.push_back(-10);
    
    //test two positions out of bounds
    std::vector<int> positionVector8;
    positionVector8.push_back(110);
    positionVector8.push_back(110);
    positionVector8.push_back(50);
    
    std::vector<int> positionVector9;
    positionVector9.push_back(110);
    positionVector9.push_back(50);
    positionVector9.push_back(110);
    
    std::vector<int> positionVector10;
    positionVector10.push_back(50);
    positionVector10.push_back(110);
    positionVector10.push_back(110);
     
    std::vector<int> positionVector11;
    positionVector11.push_back(-10);
    positionVector11.push_back(-10);
    positionVector11.push_back(50);
     
    std::vector<int> positionVector12;
    positionVector12.push_back(-10);
    positionVector12.push_back(50);
    positionVector12.push_back(-10);
     
    std::vector<int> positionVector13;
    positionVector13.push_back(50);
    positionVector13.push_back(-10);
    positionVector13.push_back(-10);
     
    
    //test tree positions out of bounds
    std::vector<int> positionVector14;
    positionVector14.push_back(110);
    positionVector14.push_back(110);
    positionVector14.push_back(110);
     
    std::vector<int> positionVector15;
    positionVector15.push_back(-10);
    positionVector15.push_back(-10);
    positionVector15.push_back(-10);
     
    
    //first the topology with boundarys
    std::vector<int> vector = top->getPos(positionVector1);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    
    //toplogy1, 2 dims with bounds and one normalized
    vector = top1->getPos(positionVector1);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top1->getPos(positionVector2);    
    CPPUNIT_ASSERT_EQUAL(10, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]); 
    vector = top1->getPos(positionVector5);    
    CPPUNIT_ASSERT_EQUAL(90, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);     
          
    //toplogy2, 1 dims with bounds and two normalized
    vector = top2->getPos(positionVector1);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);
    vector = top2->getPos(positionVector2);    
    CPPUNIT_ASSERT_EQUAL(10, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top2->getPos(positionVector3);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(10, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top2->getPos(positionVector5);    
    CPPUNIT_ASSERT_EQUAL(90, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top2->getPos(positionVector6);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(90, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);              
    //toplogy3, 0 dims with bounds and tree normalized
    vector = top3->getPos(positionVector1);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top3->getPos(positionVector2);    
    CPPUNIT_ASSERT_EQUAL(10, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top3->getPos(positionVector3);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(10, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top3->getPos(positionVector4);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(10, vector[2]);      
    vector = top3->getPos(positionVector5);    
    CPPUNIT_ASSERT_EQUAL(90, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top3->getPos(positionVector6);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(90, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top3->getPos(positionVector7);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(90, vector[2]);      
    vector = top3->getPos(positionVector8);    
    CPPUNIT_ASSERT_EQUAL(10, vector[0]);
    CPPUNIT_ASSERT_EQUAL(10, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);
    vector = top3->getPos(positionVector9);    
    CPPUNIT_ASSERT_EQUAL(10, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(10, vector[2]);      
    vector = top3->getPos(positionVector10);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(10, vector[1]);
    CPPUNIT_ASSERT_EQUAL(10, vector[2]);      
    vector = top3->getPos(positionVector11);    
    CPPUNIT_ASSERT_EQUAL(90, vector[0]);
    CPPUNIT_ASSERT_EQUAL(90, vector[1]);
    CPPUNIT_ASSERT_EQUAL(50, vector[2]);      
    vector = top3->getPos(positionVector12);    
    CPPUNIT_ASSERT_EQUAL(90, vector[0]);
    CPPUNIT_ASSERT_EQUAL(50, vector[1]);
    CPPUNIT_ASSERT_EQUAL(90, vector[2]);      
    vector = top3->getPos(positionVector13);    
    CPPUNIT_ASSERT_EQUAL(50, vector[0]);
    CPPUNIT_ASSERT_EQUAL(90, vector[1]);
    CPPUNIT_ASSERT_EQUAL(90, vector[2]);      
    vector = top3->getPos(positionVector14);    
    CPPUNIT_ASSERT_EQUAL(10, vector[0]);
    CPPUNIT_ASSERT_EQUAL(10, vector[1]);
    CPPUNIT_ASSERT_EQUAL(10, vector[2]);      
    vector = top3->getPos(positionVector15);    
    CPPUNIT_ASSERT_EQUAL(90, vector[0]);
    CPPUNIT_ASSERT_EQUAL(90, vector[1]);
    CPPUNIT_ASSERT_EQUAL(90, vector[2]);     
          
  }//-------TopologyTest::testgetPos()-------
  
  CppUnit::Test *TopologyTest::suite(){
    // create a test suite
    CppUnit::TestSuite *TopologysuiteOfTests = 
    new CppUnit::TestSuite("TopologyTest");

    // add the tests
    TopologysuiteOfTests->addTest
    (new CppUnit::TestCaller<TopologyTest>
    ("testConstructor", &TopologyTest::testConstructor));

    // add the tests
    TopologysuiteOfTests->addTest
    (new CppUnit::TestCaller<TopologyTest>
    ("testDimensions", &TopologyTest::testDimensions));

    // add the tests
    TopologysuiteOfTests->addTest
    (new CppUnit::TestCaller<TopologyTest>
    ("testisOutOfBoundsMethod", &TopologyTest::testisOutOfBoundsMethod));
    
    // add the tests
    TopologysuiteOfTests->addTest
    (new CppUnit::TestCaller<TopologyTest>
    ("testgetPos", &TopologyTest::testgetPos));

    return TopologysuiteOfTests;
  }//-----------*TopologyTest::suite() -------
