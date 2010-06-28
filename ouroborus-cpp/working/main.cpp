
#include "MyMainWindow.h"
#include <stdio.h>

int main(int argc, char* argv[]) { 
	
  	std::cout<<"main"<<std::endl;
  
	SoQt::init((QWidget *)NULL);
	std::cout<<"SoQt::init((QWidget *)NULL);"<<std::endl;
  	
	// Set up scrollview window.
	MyMainWindow * window = new MyMainWindow();
  	std::cout<<"MyMainWindow * window = new MyMainWindow();"<<std::endl;		
	
	// Map window.
  	window->show();
  	std::cout<<"window->show();"<<std::endl;		
	
	// Set termination condition.
  	QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
  	std::cout<<"QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()))"<<std::endl;		
	
	// Start event loop.
  	SoQt::mainLoop();
	
	return 0; 
} 
