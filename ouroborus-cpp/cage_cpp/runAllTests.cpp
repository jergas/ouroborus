#include <iostream>
#include <cppunit/ui/text/TestRunner.h>

//inlcude all the tester class
#include "DimensionTest.h"
#include "TopologyTest.h"
#include "TowerNeighborhoodTest.h"
#include "MapTowerNeighborhoodTest.h"
#include "AutomatonTest.h"
#include "SyncronousAutomatonTest.h"

int main (int argc, char* argv[]) {
/*The main method is to run all the metod's to test, if 
you create a new class this is the place to add the suite
that represents the tester of the class
*/ 
   std::cout<<"Main()----------tttt"<<std::endl;   
  //create the object to run all the test's  
  CppUnit::TextUi::TestRunner runner;
  
  //add all the test to by runn------------------------
  std::cout<<"add Dimension tests"<<std::endl;
  runner.addTest(DimensionTest::suite());
  
  std::cout<<"add Topology tests"<<std::endl;
  runner.addTest(TopologyTest::suite());
  
  std::cout<<"add TowerNeighborhood tests"<<std::endl;
  runner.addTest(TowerNeighborhoodTest::suite());
  
  std::cout<<"add MapTowerNeighborhood tests"<<std::endl;
  runner.addTest(MapTowerNeighborhoodTest::suite());
				
  std::cout<<"add Automaton tests"<<std::endl;
  runner.addTest(AutomatonTest::suite());
  
  std::cout<<"add SyncronousAutomaton tests"<<std::endl;
  runner.addTest(SyncronousAutomatonTest::suite());

  //---------------------------------------------------
  //run all the test's
  std::cout<<"run runner -----------------"<<std::endl;
  runner.run();
  std::cout<<"listo calisto --------------"<<std::endl;
  return 0;
}
