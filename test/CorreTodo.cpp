#include "CorreTodo.h"
//--------------- threads---------------------
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>
//--------------- end threads---------------------


void creaThreadView(int argc, char ** argv){
	
	std::cout<<"thread creaddo"<<std::endl;
	
	// Set up scrollview window.
    	View * window = new View();
	std::cout<<"creada new view"<<std::endl;	    	
	// Map window.
    	window->show();
	std::cout<<"despues de main show"<<std::endl;	
    	// Set termination condition.
    	QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
  	std::cout<<"despues del conect de quit"<<std::endl;	
    	
   
}



int main(int argc, char **argv){
	std::cout<<"empezamos main"<<std::endl;
		
	//inicializa todos los estados del automata
	limpiaTodo();
	std::cout<<"despues de limpia todo"<<std::endl;	
	init();
	std::cout<<"despues de init"<<std::endl;
	SoQt::init((QWidget *)NULL);
	std::cout<<"despues de SOQT::init"<<std::endl;
 	//crea el thread de la vista
	std::cout<<"antes de la creacion del thread"<<std::endl;	
	boost::thread thrd( boost::bind(&creaThreadView, argc, argv));
	thrd.join(); 
		
// Start event loop.
   	SoQt::mainLoop();
	std::cout<<"despues del mainloop"<<std::endl;	
	
	//creaThreadView(argc, argv);
	std::cout<<"despues de la creacion del tread y fin de main"<<std::endl; 
	return 0; 
}
