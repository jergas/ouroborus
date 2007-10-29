#include "MapTowerNeighborhoodTest.h"

void MapTowerNeighborhoodTest::setUp(){
   
    //this create a default neighorhood size 1
    hood1D = new TowerNeighborhood(1);
    hood2D = new TowerNeighborhood(2);
    hood3D = new TowerNeighborhood(3);
    
    //this create a 1d default topology  
    //dimension size = 100 and with bounds
    top1d = new Topology(1);
    //this create a 2d default topology each 
    //dimension size = 100 and with bounds
    top2d = new Topology(2);
    //this create a 1d default topology  
    //dimension size = 100 and with bounds
    top3d = new Topology(3);
    
    map1d = new Map(top1d, hood1D);
    map2d = new Map(top2d, hood2D);
    map3d = new Map(top3d, hood3D);
}
void MapTowerNeighborhoodTest::tearDown(){
    
    delete hood1D;
    delete hood2D;
    delete hood3D;
    
    delete top1d;
    delete top2d;
    
    delete map1d;
    delete map2d;
}
void MapTowerNeighborhoodTest::testConstructor(){}

void MapTowerNeighborhoodTest::testGetEdgeOneDimension(){
    /////////////////////////////////////////////////////
    ///////first test a 1d toplogy with bounds////////////
    //////////////////////////////////////////////////////
    
    //test a position (position in the bounds)
    std::vector<int> position;
    position.reserve(1);
    position.push_back(50);
    
    //calculate the neighborhood
    map1d->setEdge(position);
    std::vector< std::vector<int> > neighborhood = map1d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    
    //test a position in the upper limit
    //remember topology default size = 100
    std::vector<int> position2;
    position2.reserve(1);
    position2.push_back(99);
    
    //calculate the neighborhood
    map1d->setEdge(position2);
    neighborhood = map1d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    
    
    //test a position in the lower limit
    //remember topology default size = 100
    std::vector<int> position3;
    position3.reserve(1);
    position3.push_back(0);
    
    //calculate the neighborhood
    map1d->setEdge(position3);
    neighborhood = map1d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    
    /////////////////////////////////////////////////////
    ///////end test a 1d toplogy with bounds////////////
    //////////////////////////////////////////////////////
    
    
    /////////////////////////////////////////////////////
    /////// test a 1d toplogy with one bounds////////////
    //////////////////////////////////////////////////////
        
    top1d->setDimensionNormalized(0);
    
    //test a position (position in the bounds)
    // position = (50)
    //calculate the neighborhood
    map1d->setEdge(position);
    neighborhood = map1d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    
    //test a position in the upper limit
    //remember topology default size = 100
    //position2 = (99)
    
    //calculate the neighborhood
    map1d->setEdge(position2);
    neighborhood = map1d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    
    
    //test a position in the lower limit
    //remember topology default size = 100
    //position3 = (0)
    
    //calculate the neighborhood
    map1d->setEdge(position3);
    neighborhood = map1d->getEdge();
    
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    
    
    /////////////////////////////////////////////////////
    ///////end test a 1d toplogy with no bounds////////////
    //////////////////////////////////////////////////////
    

}//---------testGetVertexOneDimension-------------------
  
void MapTowerNeighborhoodTest::testGetEdgeTwoDimensions(){
    
    //////////////////////////////////////////////////////
    ///////first test a 2d toplogy with bounds////////////
    //////////////////////////////////////////////////////
    
    
    //test a position (position in the bounds)
    std::vector<int> position;
    position.reserve(2);
    position.push_back(50);
    position.push_back(50);
    
    //calculate the neighborhood
    map2d->setEdge(position);
    std::vector< std::vector<int> > neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    
    //test a position ("x" in the bounds)
    //a neighbor is out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position2;
    position2.reserve(2);
    position2.push_back(99);
    position2.push_back(50);
    
    //calculate the neighborhood
    map2d->setEdge(position2);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[2][1]);
    
    //test a position ("y" in the bounds)
    //a neighbor is out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position3;
    position3.reserve(2);
    position3.push_back(50);
    position3.push_back(99);
    
    //calculate the neighborhood
    map2d->setEdge(position3);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[2][1]);
    
    
    //test a position ("x" in the bounds)
    //a neighbor is out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position4;
    position4.reserve(2);
    position4.push_back(0);
    position4.push_back(50);
    
    //calculate the neighborhood
    map2d->setEdge(position4);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[2][1]);
    
    //test a position ("y" in the bounds)
    //a neighbor is out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position5;
    position5.reserve(2);
    position5.push_back(50);
    position5.push_back(0);
    
    //calculate the neighborhood
    map2d->setEdge(position5);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    
    //test a position ("x, y" in the bounds)some neighbors
    //are out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position6;
    position6.reserve(2);
    position6.push_back(99);
    position6.push_back(99);
    
    //calculate the neighborhood
    map2d->setEdge(position6);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][1]);
    
    //test a position ("x, y" in the bounds)some neighbors
    //are out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position7;
    position7.reserve(2);
    position7.push_back(99);
    position7.push_back(0);
    
    //calculate the neighborhood
    map2d->setEdge(position7);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1][1]);
    
    //test a position ("x, y" in the bounds)some neighbors
    //are out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position8;
    position8.reserve(2);
    position8.push_back(0);
    position8.push_back(99);
    
    //calculate the neighborhood
    map2d->setEdge(position8);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][1]);

    
    //test a position ("x, y" in the bounds)some neighbors
    //are out of bounds, topology default is with bounds
    //remerber 100 is topology's default dimension size
    std::vector<int> position9;
    position9.reserve(2);
    position9.push_back(0);
    position9.push_back(0);
    
    //calculate the neighborhood
    map2d->setEdge(position9);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1][1]); 
      
    
    //////////////////////////////////////////////////
    ///////End test a 2d toplogy with bounds//////////
    //////////////////////////////////////////////////
    
    
    //////////////////////////////////////////////////
    /////////test a 2d toplogy one bound//////////
    //////////////////////////////////////////////////
    
    top2d->setDimensionNormalized(0);
    
    //test a position (position in the bounds)
    // a bound mean is in the midle of the grid
    
    //position was created before (50, 50)
    //calculate the neighborhood
    map2d->setEdge(position);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    
    
    //test a position ("x" in the bounds)
    //a neighbor is out of bounds, but is a dimension normalized
    //remerber 100 is topology's default dimension size
    
    // position2 = (99, 50)
    //calculate the neighborhood
    map2d->setEdge(position2);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    
    
    //test a position ("y" in the bounds)
    //a neighbor is out of bounds, but is a dimension normalized
    //remerber 100 is topology's default dimension size
    //position = (50, 99)
    
    //calculate the neighborhood
    map2d->setEdge(position3);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[2][1]);
    
    
    //test a position ("x" in the bounds)
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (0, 50)
    
    //calculate the neighborhood
    map2d->setEdge(position4);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    
    
    //test a position ("y" in the bounds)
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (50, 0)
    
    //calculate the neighborhood
    map2d->setEdge(position5);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (99, 99)
    
    //calculate the neighborhood
    map2d->setEdge(position6);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[2][1]);
    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //positions = (99, 0)
    
    //calculate the neighborhood
    map2d->setEdge(position7);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    
    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //poition = (0, 99)
    
    //calculate the neighborhood
    map2d->setEdge(position8);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[2][1]);

    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (0,0)
    
    //calculate the neighborhood
    map2d->setEdge(position9);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);   
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);   
    
    //////////////////////////////////////////////////
    ///////End test a 2d toplogy one bound////////////
    //////////////////////////////////////////////////
    
    
    //////////////////////////////////////////////////
    /////////test a 2d toplogy with no bounds//////////
    //////////////////////////////////////////////////
    
    //top2d->setDimensionNormalized(0);//this was did before
    top2d->setDimensionNormalized(1);
    
    //test a position (position in the bounds)
    // a bound mean is in the midle of the grid
    
    //position was created before (50, 50)
    //calculate the neighborhood
    map2d->setEdge(position);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    
    
    //test a position ("x" in the bounds)
    //a neighbor is out of bounds, but is a dimension normalized
    //remerber 100 is topology's default dimension size
    
    // position2 = (99, 50)
    //calculate the neighborhood
    map2d->setEdge(position2);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    
    
    //test a position ("y" in the bounds)
    //a neighbor is out of bounds, but is a dimension normalized
    //remerber 100 is topology's default dimension size
    //position = (50, 99)
    
    //calculate the neighborhood
    map2d->setEdge(position3);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][1]);
    
    
    //test a position ("x" in the bounds)
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (0, 50)
    
    //calculate the neighborhood
    map2d->setEdge(position4);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    
    
    //test a position ("y" in the bounds)
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (50, 0)
    
    //calculate the neighborhood
    map2d->setEdge(position5);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (99, 99)
    
    //calculate the neighborhood
    map2d->setEdge(position6);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][1]);
    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //positions = (99, 0)
    
    //calculate the neighborhood
    map2d->setEdge(position7);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    
    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //poition = (0, 99)
    
    //calculate the neighborhood
    map2d->setEdge(position8);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][1]);

    
    //test a position ("x, y" in the bounds)some neighbors
    //a neighbor is out of bounds, but one dimension is normalized
    //remerber 100 is topology's default dimension size
    //position = (0,0)
    
    //calculate the neighborhood
    map2d->setEdge(position9);
    neighborhood = map2d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(2, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);   
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);   
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    
    //////////////////////////////////////////////////
    /////////end 2d toplogy with no bounds////////////
    //////////////////////////////////////////////////
        
                
}///-------testGetVertexTwoDimensions-----------------

void MapTowerNeighborhoodTest::testGetEdgeTreeDimensions(){

    ///////////////////////////////////////////////////////
    ///////first test a 3d toplogy with bounds/////////////
    ///////////////////////////////////////////////////////
    
    //test a position (position in the bounds)
    std::vector<int> position;
    position.reserve(3);
    position.push_back(50);
    position.push_back(50);
    position.push_back(50);
    
    //calculate the neighborhood
    map3d->setEdge(position);
    std::vector< std::vector<int> > neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    //test a position with "x" in one limit
    std::vector<int> position2;
    position2.reserve(3);
    position2.push_back(99);
    position2.push_back(50);
    position2.push_back(50);
    
    //calculate the neighborhood
    map3d->setEdge(position2);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[4][2]);
    
    
    //test a position with "x" in one limit
    std::vector<int> position3;
    position3.reserve(3);
    position3.push_back(0);
    position3.push_back(50);
    position3.push_back(50);
    
    //calculate the neighborhood
    map3d->setEdge(position3);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[4][2]);
    
    
    //test a position with "y" in one limit
    std::vector<int> position4;
    position4.reserve(3);
    position4.push_back(50);
    position4.push_back(99);
    position4.push_back(50);
    
    //calculate the neighborhood
    map3d->setEdge(position4);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[4][2]);
    
    //test a position with "y" in one limit
    std::vector<int> position5;
    position5.reserve(3);
    position5.push_back(50);
    position5.push_back(0);
    position5.push_back(50);
    
    //calculate the neighborhood
    map3d->setEdge(position5);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[4][2]);
    
    
    //test a position with "z" in one limit
    std::vector<int> position6;
    position6.reserve(3);
    position6.push_back(50);
    position6.push_back(50);
    position6.push_back(99);
    
    //calculate the neighborhood
    map3d->setEdge(position6);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[4][2]);
    
    
    //test a position with "z" in one limit
    std::vector<int> position7;
    position7.reserve(3);
    position7.push_back(50);
    position7.push_back(50);
    position7.push_back(0);
    
    //calculate the neighborhood
    map3d->setEdge(position7);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[4][2]);
    
    //test a position with "x, y" in one limit
    std::vector<int> position8;
    position8.reserve(3);
    position8.push_back(0);
    position8.push_back(99);
    position8.push_back(50);
    
    //calculate the neighborhood
    map3d->setEdge(position8);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][2]);
    
    //test a position with "x, y" in one limit
    std::vector<int> position9;
    position9.reserve(3);
    position9.push_back(99);
    position9.push_back(0);
    position9.push_back(50);
    
    //calculate the neighborhood
    map3d->setEdge(position9);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][2]);
    
    //test a position with "x, z" in one limit
    std::vector<int> position10;
    position10.reserve(3);
    position10.push_back(99);
    position10.push_back(50);
    position10.push_back(0);
    
    //calculate the neighborhood
    map3d->setEdge(position10);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[3][2]);
    
    //test a position with "x, z" in one limit
    std::vector<int> position11;
    position11.reserve(3);
    position11.push_back(0);
    position11.push_back(50);
    position11.push_back(99);
    
    //calculate the neighborhood
    map3d->setEdge(position11);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][2]);
    
    
    //test a position with "y, z" in one limit
    std::vector<int> position12;
    position12.reserve(3);
    position12.push_back(50);
    position12.push_back(99);
    position12.push_back(0);
    
    //calculate the neighborhood
    map3d->setEdge(position12);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[3][2]);
    
    //test a position with "y, z" in one limit
    std::vector<int> position13;
    position13.reserve(3);
    position13.push_back(50);
    position13.push_back(0);
    position13.push_back(99);
    
    //calculate the neighborhood
    map3d->setEdge(position13);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(4, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][2]);
    
    //test a position with "x, y, z" in one limit
    std::vector<int> position14;
    position14.reserve(3);
    position14.push_back(0);
    position14.push_back(0);
    position14.push_back(0);
    
    //calculate the neighborhood
    map3d->setEdge(position14);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][2]);
    
    //test a position with "x, y, z" in one limit
    std::vector<int> position15;
    position15.reserve(3);
    position15.push_back(99);
    position15.push_back(99);
    position15.push_back(99);
    
    //calculate the neighborhood
    map3d->setEdge(position15);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[2][2]);
    
    ////////////////////////////////////////////////////////
    ///////end test a 3d toplogy with bounds////////////////
    ////////////////////////////////////////////////////////

    
    ////////////////////////////////////////////////////////
    ///////test a 3d toplogy with two bounds////////////////
    ////////////////////////////////////////////////////////
    
    top3d->setDimensionNormalized(0);
    
    //test a position (position in the bounds)
    //position = (50, 50, 50)
    
    //calculate the neighborhood
    map3d->setEdge(position);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    //test a position with "x" in one limit
    //position2 = (99, 50, 50);
    
    //calculate the neighborhood
    map3d->setEdge(position2);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    
    //test a position with "x" in one limit
    //position3 = (0, 50, 50);
    
    //calculate the neighborhood
    map3d->setEdge(position3);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    ////////////////////////////////////////////////////////
    ///////end test a 3d toplogy with two bounds////////////
    ////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    ///////test a 3d toplogy with one bound/////////////////
    ////////////////////////////////////////////////////////
    
    top3d->setDimensionNormalized(1);
    
    //test a position with "y" in one limit
    //position4 = (50, 99, 50);
    
    //calculate the neighborhood
    map3d->setEdge(position4);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    //test a position with "y" in one limit
    //position5 = (50, 0, 50);
    
    //calculate the neighborhood
    map3d->setEdge(position5);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    //test a position with "x, y" in one limit
    //position8; = (0, 99, 50);
    
    //calculate the neighborhood
    map3d->setEdge(position8);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    //test a position with "x, y" in one limit
    //position9 = (99, 0, 50);
    
    //calculate the neighborhood
    map3d->setEdge(position9);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    //test the position's of the neighbors
    
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(50, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(51, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(49, (int)neighborhood[5][2]);
    
    //test a position with "x, y, z" in one limit
    //position14 = (0, 0, 0);
    
    //calculate the neighborhood
    map3d->setEdge(position14);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[4][2]);
    
    //test a position with "x, y, z" in one limit
    //position15 = (99, 99, 99);
    
    //calculate the neighborhood
    map3d->setEdge(position15);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(5, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[4][2]);
    
    ///////////////////////////////////////////////////////
    ///////end test a 3d toplogy with one bound////////////
    ///////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////
    ///////test a 3d toplogy with no bounds/////////////////
    ////////////////////////////////////////////////////////
    top3d->setDimensionNormalized(2);
    
    //test a position with "x, y, z" in one limit
    //position14 = (0, 0, 0);
    
    //calculate the neighborhood
    map3d->setEdge(position14);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(1, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[5][2]);
    
    //test a position with "x, y, z" in one limit
    //position15 = (99, 99, 99);
    
    //calculate the neighborhood
    map3d->setEdge(position15);
    neighborhood = map3d->getEdge();
    
    //test the size of the neighborhood
    CPPUNIT_ASSERT_EQUAL(6, (int)neighborhood.size());
    //test the dimensionality of the neighbors
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[0].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[1].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[2].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[3].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[4].size());
    CPPUNIT_ASSERT_EQUAL(3, (int)neighborhood[5].size());
    
    //test the position's of the neighbors
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[0][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[0][2]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[1][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[1][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][0]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[2][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[2][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][0]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[3][1]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[3][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[4][1]);
    CPPUNIT_ASSERT_EQUAL(0, (int)neighborhood[4][2]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[5][0]);
    CPPUNIT_ASSERT_EQUAL(99, (int)neighborhood[5][1]);
    CPPUNIT_ASSERT_EQUAL(98, (int)neighborhood[5][2]);
    
    ///////////////////////////////////////////////////////
    ///////end test a 3d toplogy with no bounds////////////
    ///////////////////////////////////////////////////////
} 


CppUnit::Test *MapTowerNeighborhoodTest::suite() {
    
  // create a test suite
  CppUnit::TestSuite *MapTowerNeighborhoodsuiteOfTests = 
    new CppUnit::TestSuite("MapTowerNeighborhoodTest");

  // add the tests ---------
  MapTowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<MapTowerNeighborhoodTest>
     ("testConstructor", &MapTowerNeighborhoodTest::testConstructor));
  
  MapTowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<MapTowerNeighborhoodTest>
     ("testGetEdgeOneDimension", &MapTowerNeighborhoodTest::testGetEdgeOneDimension));
  
  MapTowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<MapTowerNeighborhoodTest>
     ("testGetEdgeTwoDimensions", &MapTowerNeighborhoodTest::testGetEdgeTwoDimensions));
  
  MapTowerNeighborhoodsuiteOfTests->addTest
    (new CppUnit::TestCaller<MapTowerNeighborhoodTest>
     ("testGetEdgeTreeDimensions", &MapTowerNeighborhoodTest::testGetEdgeTreeDimensions));
  
  //end add the tests-------  
   
  return MapTowerNeighborhoodsuiteOfTests;
}//-------*DimensionTest::suite()-----------
  
