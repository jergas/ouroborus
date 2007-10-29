CC = g++
CFLAGS = -c
OBJS = runAllTests.o Automaton.o SyncronousAutomaton.o SyncronousAutomatonTest.o AutomatonTest.o Dimension.o DimensionTest.o Topology.o TopologyTest.o Neighborhood.o TowerNeighborhood.o TowerNeighborhoodTest.o Map.o MapTowerNeighborhoodTest.o
INCLUDE = -I/usr/local/include
LIBS = -L/usr/local/lib -lcppunit
TARGET = cageCpp.exe 
$(TARGET): $(OBJS) 
	$(CC) -o $@ $(OBJS) $(LIBS) 

.cpp.o: 
	$(CC) $(INCLUDE) $(CFLAGS) $*.cpp 


Dimension.o: Dimension.h

DimensionTest.o: Dimension.h DimensionTest.h

Topology.o: Dimension.h Topology.h

TopologyTest.o: Dimension.h Topology.h TopologyTest.h

Neighborhood.o: Neighborhood.h
	
TowerNeighborhood.o: Neighborhood.h TowerNeighborhood.h

TowerNeighborhoodTest.o: Neighborhood.h TowerNeighborhood.h TowerNeighborhoodTest.h

Map.o: Dimension.h Topology.h Neighborhood.h TowerNeighborhood.h Map.h

MapTowerNeighborhoodTest.o: Dimension.h Topology.h Neighborhood.h TowerNeighborhood.h Map.h MapTowerNeighborhoodTest.h

Automaton.o: Dimension.h Topology.h Neighborhood.h TowerNeighborhood.h Map.h MapTowerNeighborhoodTest.h Automaton.h

AutomatonTest.o:Dimension.h Topology.h Neighborhood.h TowerNeighborhood.h Map.h MapTowerNeighborhoodTest.h Automaton.h AutomatonTest.h

SyncronousAutomaton.o: Dimension.h Topology.h Neighborhood.h TowerNeighborhood.h Map.h MapTowerNeighborhoodTest.h SyncronousAutomaton.h

SyncronousAutomatonTest.o: Dimension.h Topology.h Neighborhood.h TowerNeighborhood.h Map.h MapTowerNeighborhoodTest.h SyncronousAutomaton.h SyncronousAutomatonTest.h

runAllTests: Dimension.h DimensionTest.h Topology.h  TopologyTest.h Neighborhood.h TowerNeighborhood.h TowerNeighborhoodTest.h  Map.h MapTowerNeighborhoodTest.h Automaton.h AutomatonTest.h SyncronousAutomatonTest.h

clean: 
	rm -f *.o 
	rm -f tester.exe

