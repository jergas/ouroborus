#include  "TowerNeighborhoodTest.h"

void TowerNeighborhoodTest::setUp(){     
    hood1D = new TowerNeighborhood(1);
    hood2D = new TowerNeighborhood(2);
    hood3D = new TowerNeighborhood(3);    
}//--------NeighborhoodTest::setUp()-------

void TowerNeighborhoodTest::tearDown(){
    delete hood1D;
    delete hood2D;
    delete hood3D;
}//--------NeighborhoodTest::tearDown----------  

// method to test the constructor
void TowerNeighborhoodTest::testConstructor(){ 
     // check that the object is constructed correctly
     CPPUNIT_ASSERT_EQUAL(1, hood1D->getSize());
     
     hood1D->setSize(10);
     // check that the object is constructed correctly
     CPPUNIT_ASSERT_EQUAL(10, hood1D->getSize());
     
     hood1D->setSize(0);
     // check that the object is constructed correctly
     CPPUNIT_ASSERT_EQUAL(0, hood1D->getSize());
     
     hood1D->setSize(-5);
     // check that the object is constructed correctly
     CPPUNIT_ASSERT_EQUAL(-5, hood1D->getSize());

}//-----------testConstructor------------

void TowerNeighborhoodTest::testCalculateNeighborhoodSizeOne(){
    
    
    //create a vector to contain the elements in the
    //neigborhood
    std::vector< std::vector<int> > neigborhood;
    
    //create a position vector to calculate is
    //neigborhood
    
    // a 1d vector positive value
    std::vector<int> position0;
    position0.reserve(1);
    position0.push_back(5);
    
    
    hood1D->calculateNeighborhood(position0);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[1][0]);
    
    // a 1d vector negative value
    std::vector<int> position01;
    position01.reserve(1);
    position01.push_back(-7);
    
    hood1D->calculateNeighborhood(position01);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[1][0]);
    
    
    // a 1d vector cero value
    std::vector<int> position02;
    position02.reserve(1);
    position02.push_back(0);
    
    hood1D->calculateNeighborhood(position02);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[1][0]);
    
    // a 2d vector positive values
    std::vector<int> position1;
    position1.reserve(2);
    position1.push_back(5);
    position1.push_back(5);
    
    hood2D->calculateNeighborhood(position1);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][1]);
    
    // a 2d vector one positive value and one negative
    std::vector<int> position11;
    position11.reserve(2);
    position11.push_back(8);
    position11.push_back(-6);
    
    hood2D->calculateNeighborhood(position11);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[3][1]);
    
    // a 2d vector one positive value and one negative
    std::vector<int> position12;
    position12.reserve(2);
    position12.push_back(-8);
    position12.push_back(9);
    
    hood2D->calculateNeighborhood(position12);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[3][1]);

    // a 2d vector two negative values
    std::vector<int> position13;
    position13.reserve(2);
    position13.push_back(-40);
    position13.push_back(-2);
    
    hood2D->calculateNeighborhood(position13);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(-39, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-41, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-40, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-40, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[3][1]);
    
    // a 2d  0 vector 
    std::vector<int> position14;
    position14.reserve(2);
    position14.push_back(0);
    position14.push_back(0);
    
    hood2D->calculateNeighborhood(position14);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[3][1]);
            
    //a 3d vector with tree positive values
    std::vector<int> position2;
    position2.reserve(3);
    position2.push_back(5);
    position2.push_back(5);
    position2.push_back(5);
    
    hood3D->calculateNeighborhood(position2);
    neigborhood = hood3D->getNeighborhood();    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[5][2]);
    
    //a 3d vector two positives values and one negative
    std::vector<int> position21;
    position21.reserve(3);
    position21.push_back(10);
    position21.push_back(30);
    position21.push_back(-5);
    
    hood3D->calculateNeighborhood(position21);
    neigborhood = hood3D->getNeighborhood();    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(11, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(30, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(30, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(31, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(29, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(30, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(30, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[5][2]);
    
    //a 3d vector two positives values and one negative
    std::vector<int> position22;
    position22.reserve(3);
    position22.push_back(-5);
    position22.push_back(10);
    position22.push_back(45);
    
    hood3D->calculateNeighborhood(position22);
    neigborhood = hood3D->getNeighborhood();    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(11, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(46, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[5][2]);
    
    //a 3d vector two negatives values and one positive
    std::vector<int> position23;
    position23.reserve(3);
    position23.push_back(-5);
    position23.push_back(-10);
    position23.push_back(45);
    
    hood3D->calculateNeighborhood(position23);
    neigborhood = hood3D->getNeighborhood();    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-11, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(46, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[5][2]);
    
    //a 3d vector two negatives values and one positive
    std::vector<int> position24;
    position24.reserve(3);
    position24.push_back(-5);
    position24.push_back(50);
    position24.push_back(-10);
    
    hood3D->calculateNeighborhood(position24);
    neigborhood = hood3D->getNeighborhood();    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-11, (int)neigborhood[5][2]);
    
    //a 3d vector tree negatives values 
    std::vector<int> position25;
    position25.reserve(3);
    position25.push_back(-5);
    position25.push_back(-50);
    position25.push_back(-10);
    
    hood3D->calculateNeighborhood(position25);
    neigborhood = hood3D->getNeighborhood();    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-50, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-50, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-49, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-51, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-50, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-50, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-11, (int)neigborhood[5][2]);
    
    //a 3d  0 vector 
    std::vector<int> position26;
    position26.reserve(3);
    position26.push_back(0);
    position26.push_back(0);
    position26.push_back(0);
    
    hood3D->calculateNeighborhood(position26);
    neigborhood = hood3D->getNeighborhood();    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[5][2]);
    
}//---------------testCalculateNeighborhoodSizeOne--------

void TowerNeighborhoodTest::testCalculateNeighborhoodSizeTwo(){
    
    //change the size of the towerNeigborhood
    hood1D->setSize(2);
    hood2D->setSize(2);
    hood3D->setSize(2);
    //create a vector to contain the elements in the
    //neigborhood
    std::vector< std::vector<int> > neigborhood;
    
    //create a position vector to calculate is
    //neigborhood
    
    // a 1d vector positive value
    std::vector<int> position0;
    position0.reserve(1);
    position0.push_back(5);
    hood1D->calculateNeighborhood(position0);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3][0]);
        
    // a 1d vector negative value
    std::vector<int> position01;
    position01.reserve(1);
    position01.push_back(-6);
    hood1D->calculateNeighborhood(position01);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[3][0]);
    
    // a 1d 0 vector 
    std::vector<int> position02;
    position02.reserve(1);
    position02.push_back(0);
    hood1D->calculateNeighborhood(position02);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[3].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[3][0]);
    
    // a 2d vector positive value
    std::vector<int> position2;
    position2.reserve(2); 
    position2.push_back(6);
    position2.push_back(16);
    
    hood1D->calculateNeighborhood(position2);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[2][1]);    
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[3][1]); 
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(17, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(15, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(14, (int)neigborhood[7][1]);
        
    // a 2d vector, one positive value one negative
    std::vector<int> position20;
    position20.reserve(2); 
    position20.push_back(6);
    position20.push_back(-16);
    hood2D->calculateNeighborhood(position20);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[2][1]);    
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[3][1]); 
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-15, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-14, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-17, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-18, (int)neigborhood[7][1]);
    
    // a 2d vector two negative values
    std::vector<int> position21;
    position21.reserve(2); 
    position21.push_back(-6);
    position21.push_back(-16);
    hood2D->calculateNeighborhood(position21);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[2][1]);    
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[3][1]); 
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-15, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-14, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-17, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-18, (int)neigborhood[7][1]);
    
    // a 2d 0 vector 
    std::vector<int> position23;
    position23.reserve(2); 
    position23.push_back(0);
    position23.push_back(0);
    hood2D->calculateNeighborhood(position23);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][1]);    
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][1]); 
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[7][1]);
    
    // a 3d vector positive value
    std::vector<int> position3;
    position3.reserve(3); 
    position3.push_back(6);
    position3.push_back(16);
    position3.push_back(16);
    
    hood3D->calculateNeighborhood(position3);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(17, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(15, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(14, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(17, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(15, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(14, (int)neigborhood[11][2]);
    
    // a 3d vector two positive values and one negative
    std::vector<int> position30;
    position30.reserve(3); 
    position30.push_back(-6);
    position30.push_back(16);
    position30.push_back(16);
    
    hood3D->calculateNeighborhood(position30);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(17, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(15, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(14, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(17, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(15, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(14, (int)neigborhood[11][2]);
    
    // a 3d vector two negative values and one positive 
    std::vector<int> position31;
    position31.reserve(3); 
    position31.push_back(-6);
    position31.push_back(16);
    position31.push_back(-16);
    
    hood3D->calculateNeighborhood(position31);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(17, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(15, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(14, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(-15, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(-14, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(-17, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(16, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(-18, (int)neigborhood[11][2]);
    
    // a 3d vector tree negative values 
    std::vector<int> position32;
    position32.reserve(3); 
    position32.push_back(-6);
    position32.push_back(-10);
    position32.push_back(-16);
    
    hood3D->calculateNeighborhood(position32);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-11, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-12, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(-16, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(-15, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(-14, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(-17, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(-18, (int)neigborhood[11][2]);
    
    // a 3d 0 vector 
    std::vector<int> position33;
    position33.reserve(3); 
    position33.push_back(0);
    position33.push_back(0);
    position33.push_back(0);
    
    hood3D->calculateNeighborhood(position33);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[11][2]);
     
}//---------------testCalculateNeighborhoodSizeTwo--------
    
     
void TowerNeighborhoodTest::testCalculateNeighborhoodSizeTree(){
    
     //create a vector to contain the elements in the
    //neigborhood
    std::vector< std::vector<int> > neigborhood;
    
    //create a position vector to calculate is
    //neigborhood
    //change the size of the towerNeigborhood
    hood1D->setSize(3);
    hood2D->setSize(3);
    hood3D->setSize(3);
    
    //create a position vector to calculate is
    //neigborhood
    
    // a 1d vector positive value
    std::vector<int> position0;
    position0.reserve(1);
    position0.push_back(5);
    hood1D->calculateNeighborhood(position0);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5][0]);
    
    // a 1d vector negative value
    std::vector<int> position01;
    position01.reserve(1);
    position01.push_back(-6);
    hood1D->calculateNeighborhood(position01);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[5][0]);
    
    // a 1d 0 vector 
    std::vector<int> position02;
    position02.reserve(1);
    position02.push_back(0);
    hood1D->calculateNeighborhood(position02);
    neigborhood = hood1D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[5].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[5][0]);
    
    // a 2d vector positive value
    std::vector<int> position1;
    position1.reserve(2);
    position1.push_back(5);
    position1.push_back(7);
    hood2D->calculateNeighborhood(position1);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[11][1]);
    
    // a 2d vector one positive value one negative
    std::vector<int> position10;
    position10.reserve(2);
    position10.push_back(-5);
    position10.push_back(7);
    hood2D->calculateNeighborhood(position10);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[11][1]);
    
    // a 2d vector two negative values
    std::vector<int> position11;
    position11.reserve(2);
    position11.push_back(-5);
    position11.push_back(-7);
    hood2D->calculateNeighborhood(position11);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[11][1]);
    
    // a 2d 0 vector 
    std::vector<int> position12;
    position12.reserve(2);
    position12.push_back(0);
    position12.push_back(0);
    hood2D->calculateNeighborhood(position12);
    neigborhood = hood2D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(12, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[11].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[11][1]);
    
    // a 3d vector positive values
    std::vector<int> position2;
    position2.reserve(3);
    position2.push_back(5);
    position2.push_back(7);
    position2.push_back(44);
    hood3D->calculateNeighborhood(position2);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[12].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[13].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[14].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[15].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[16].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[17].size());
    
    //5, 7, 44
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[11][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[12][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[12][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[12][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[13][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[13][1]);
    CPPUNIT_ASSERT_EQUAL(46, (int)neigborhood[13][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[14][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[14][1]);
    CPPUNIT_ASSERT_EQUAL(47, (int)neigborhood[14][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[15][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[15][1]);
    CPPUNIT_ASSERT_EQUAL(43, (int)neigborhood[15][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[16][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[16][1]);
    CPPUNIT_ASSERT_EQUAL(42, (int)neigborhood[16][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[17][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[17][1]);
    CPPUNIT_ASSERT_EQUAL(41, (int)neigborhood[17][2]);
    
    // a 3d vector two positive values one negative
    std::vector<int> position20;
    position20.reserve(3);
    position20.push_back(5);
    position20.push_back(-7);
    position20.push_back(44);
    hood3D->calculateNeighborhood(position20);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[12].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[13].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[14].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[15].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[16].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[17].size());
    
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(44, (int)neigborhood[11][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[12][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[12][1]);
    CPPUNIT_ASSERT_EQUAL(45, (int)neigborhood[12][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[13][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[13][1]);
    CPPUNIT_ASSERT_EQUAL(46, (int)neigborhood[13][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[14][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[14][1]);
    CPPUNIT_ASSERT_EQUAL(47, (int)neigborhood[14][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[15][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[15][1]);
    CPPUNIT_ASSERT_EQUAL(43, (int)neigborhood[15][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[16][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[16][1]);
    CPPUNIT_ASSERT_EQUAL(42, (int)neigborhood[16][2]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[17][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[17][1]);
    CPPUNIT_ASSERT_EQUAL(41, (int)neigborhood[17][2]);
    
    // a 3d vector one positive value two negative values
    std::vector<int> position21;
    position21.reserve(3);
    position21.push_back(-5);
    position21.push_back(7);
    position21.push_back(-44);
    hood3D->calculateNeighborhood(position21);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[12].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[13].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[14].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[15].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[16].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[17].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(8, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(9, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(10, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(6, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(5, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(4, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[11][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[12][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[12][1]);
    CPPUNIT_ASSERT_EQUAL(-43, (int)neigborhood[12][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[13][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[13][1]);
    CPPUNIT_ASSERT_EQUAL(-42, (int)neigborhood[13][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[14][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[14][1]);
    CPPUNIT_ASSERT_EQUAL(-41, (int)neigborhood[14][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[15][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[15][1]);
    CPPUNIT_ASSERT_EQUAL(-45, (int)neigborhood[15][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[16][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[16][1]);
    CPPUNIT_ASSERT_EQUAL(-46, (int)neigborhood[16][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[17][0]);
    CPPUNIT_ASSERT_EQUAL(7, (int)neigborhood[17][1]);
    CPPUNIT_ASSERT_EQUAL(-47, (int)neigborhood[17][2]);
    
    // a 3d vector tree negative values
    std::vector<int> position22;
    position22.reserve(3);
    position22.push_back(-5);
    position22.push_back(-7);
    position22.push_back(-44);
    hood3D->calculateNeighborhood(position22);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[12].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[13].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[14].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[15].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[16].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[17].size());
    
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(-6, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(-4, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(-8, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(-9, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(-10, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(-44, (int)neigborhood[11][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[12][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[12][1]);
    CPPUNIT_ASSERT_EQUAL(-43, (int)neigborhood[12][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[13][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[13][1]);
    CPPUNIT_ASSERT_EQUAL(-42, (int)neigborhood[13][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[14][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[14][1]);
    CPPUNIT_ASSERT_EQUAL(-41, (int)neigborhood[14][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[15][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[15][1]);
    CPPUNIT_ASSERT_EQUAL(-45, (int)neigborhood[15][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[16][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[16][1]);
    CPPUNIT_ASSERT_EQUAL(-46, (int)neigborhood[16][2]);
    CPPUNIT_ASSERT_EQUAL(-5, (int)neigborhood[17][0]);
    CPPUNIT_ASSERT_EQUAL(-7, (int)neigborhood[17][1]);
    CPPUNIT_ASSERT_EQUAL(-47, (int)neigborhood[17][2]);
    
    // a 3d 0 vector 
    std::vector<int> position23;
    position23.reserve(3);
    position23.push_back(0);
    position23.push_back(0);
    position23.push_back(0);
    hood3D->calculateNeighborhood(position23);
    neigborhood = hood3D->getNeighborhood();
    CPPUNIT_ASSERT_EQUAL(18, (int)neigborhood.size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[5].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[6].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[7].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[9].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[10].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[11].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[12].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[13].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[14].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[15].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[16].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[17].size());
    
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[5][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[6][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[6][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[6][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[7][0]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[7][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[7][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[8][0]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[8][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[8][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[9][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[9][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[9][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[10][0]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[10][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[10][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[11][0]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[11][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[11][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[12][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[12][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neigborhood[12][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[13][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[13][1]);
    CPPUNIT_ASSERT_EQUAL(2, (int)neigborhood[13][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[14][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[14][1]);
    CPPUNIT_ASSERT_EQUAL(3, (int)neigborhood[14][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[15][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[15][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)neigborhood[15][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[16][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[16][1]);
    CPPUNIT_ASSERT_EQUAL(-2, (int)neigborhood[16][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[17][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neigborhood[17][1]);
    CPPUNIT_ASSERT_EQUAL(-3, (int)neigborhood[17][2]);
    
}//--------------testCalculateNeighborhoodSizeTwo--------

void TowerNeighborhoodTest::testArrangedNeighborhood(){
    //only test neighborhood size 1
    hood1D->setSize(1);
    hood2D->setSize(1);
    hood3D->setSize(1);
    hood1D->calculateNormalNeighborhood();
    //first test ths size of the normal coordinates is correct
    CPPUNIT_ASSERT_EQUAL(2, (int)hood1D->neighborsNormalCoordinates.size());
    //then test the rigth elements are in it
    CPPUNIT_ASSERT_EQUAL(1, (int)(hood1D->neighborsNormalCoordinates[0].size()));
    CPPUNIT_ASSERT_EQUAL(1, (int)(hood1D->neighborsNormalCoordinates[1].size()));
    
    CPPUNIT_ASSERT_EQUAL(1, (int) hood1D->neighborsNormalCoordinates[0][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)hood1D->neighborsNormalCoordinates[1][0]);
    
    hood2D->calculateNormalNeighborhood();
    //first test ths size of the normal coordinates is correct
    CPPUNIT_ASSERT_EQUAL(4, (int)hood2D->neighborsNormalCoordinates.size());
    //then test the rigth elements are in it
    CPPUNIT_ASSERT_EQUAL(2, (int)(hood2D->neighborsNormalCoordinates[0].size()));
    CPPUNIT_ASSERT_EQUAL(2, (int)(hood2D->neighborsNormalCoordinates[1].size()));
    CPPUNIT_ASSERT_EQUAL(2, (int)(hood2D->neighborsNormalCoordinates[2].size()));
    CPPUNIT_ASSERT_EQUAL(2, (int)(hood2D->neighborsNormalCoordinates[3].size()));

    CPPUNIT_ASSERT_EQUAL(1, (int)hood2D->neighborsNormalCoordinates[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood2D->neighborsNormalCoordinates[0][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)hood2D->neighborsNormalCoordinates[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood2D->neighborsNormalCoordinates[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood2D->neighborsNormalCoordinates[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)hood2D->neighborsNormalCoordinates[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood2D->neighborsNormalCoordinates[3][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)hood2D->neighborsNormalCoordinates[3][1]);
    
    hood3D->calculateNormalNeighborhood();
    //first test ths size of the normal coordinates is correct
    CPPUNIT_ASSERT_EQUAL(6, (int)hood3D->neighborsNormalCoordinates.size());
    //then test the rigth elements are in it
    CPPUNIT_ASSERT_EQUAL(3, (int)(hood3D->neighborsNormalCoordinates[0].size()));
    CPPUNIT_ASSERT_EQUAL(3, (int)(hood3D->neighborsNormalCoordinates[1].size()));
    CPPUNIT_ASSERT_EQUAL(3, (int)(hood3D->neighborsNormalCoordinates[2].size()));
    CPPUNIT_ASSERT_EQUAL(3, (int)(hood3D->neighborsNormalCoordinates[3].size()));
    CPPUNIT_ASSERT_EQUAL(3, (int)(hood3D->neighborsNormalCoordinates[4].size()));
    CPPUNIT_ASSERT_EQUAL(3, (int)(hood3D->neighborsNormalCoordinates[5].size()));
    
    CPPUNIT_ASSERT_EQUAL(1, (int)hood3D->neighborsNormalCoordinates[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[0][2]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)hood3D->neighborsNormalCoordinates[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)hood3D->neighborsNormalCoordinates[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[3][0]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)hood3D->neighborsNormalCoordinates[3][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[4][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)hood3D->neighborsNormalCoordinates[4][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[5][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)hood3D->neighborsNormalCoordinates[5][1]);
    CPPUNIT_ASSERT_EQUAL(-1, (int)hood3D->neighborsNormalCoordinates[5][2]);
}

CppUnit::Test *TowerNeighborhoodTest::suite() {
  // create a test suite
  CppUnit::TestSuite *TowerNeighborhoodsuiteOfTests = 
    new CppUnit::TestSuite("TowerNeighborhoodTest");

  // add the tests ---------
  TowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<TowerNeighborhoodTest>
     ("testConstructor", &TowerNeighborhoodTest::testConstructor));
  
  TowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<TowerNeighborhoodTest>
     ("testCalculateNeighborhoodSizeOne", &TowerNeighborhoodTest::testCalculateNeighborhoodSizeOne));
  
  TowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<TowerNeighborhoodTest>
     ("testCalculateNeighborhoodSizeTwo", &TowerNeighborhoodTest::testCalculateNeighborhoodSizeTwo));
       
  TowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<TowerNeighborhoodTest>
     ("testCalculateNeighborhoodSizeTree", &TowerNeighborhoodTest::testCalculateNeighborhoodSizeTree));
  
  TowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<TowerNeighborhoodTest>
     ("testArrangedNeighborhood", &TowerNeighborhoodTest::testArrangedNeighborhood));
  
    //end add the tests-------  
   
  return TowerNeighborhoodsuiteOfTests;
  }//-------*NeighborhoodTest::suite()-----------
