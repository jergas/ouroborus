
#include "MyMainWindow.h"

int main(int argc, char* argv[]) { 

  SoQt::init((QWidget *)NULL);
  // Set up scrollview window.
  MyMainWindow * window = new MyMainWindow();
  // Map window.
  window->show();
  // Set termination condition.
  QObject::connect(qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()));
  // Start event loop.
  SoQt::mainLoop();

	return 0; 
} 
