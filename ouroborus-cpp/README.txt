cage_cpp is an engine which generates agents on top of a cellular automaton. It is written in c++,with qt based visualization thanks to coin3d. The modules which implement the agents are under development, and the viewer is currently being ported from Windows to Linux.


Directories Content
cage_cpp/
Cage engine c++ working on win32.
education/
A CD from photosynthesis project (java) and a evolution-activity directory prepared for win32.
natural-selection/
empty at this time.
working/
A test of GUI and viewer for cage_cpp, primarily on Qt and Coin3d.


To compile the viewer, you first need to change to working directory and meet the following dependencies.


List of dependencies for this test:

- g++
- make
- coin3d libcoin60-dev (only in squeeze/testing at this moment) or
  libcoin40-dev (on lenny/stable)
- soqt4 libsoqt4-dev
- simage libsimage-dev
- qmake qt4-qmake
- boost libboost1.42-all-dev (only in squeeze/testing at this moment) or
  libboost1.35-dev (on lenny/stable)


To compile and run the test:

1.- Go to the ouroborus-cpp/working/ directory
2.- Type "qmake" (without the brackets here, and heceforth)
3.- Type "make"
4.- Type "./main