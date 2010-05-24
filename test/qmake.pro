CONFIG += qt

DEFINES+= SOQT_DLL COIN_DLL SIMAGE_DLL HAVE_INT8_T


HEADERS +=  estadointerno.h valores.h celula.h  view2.h CorreTodo.h  
SOURCES +=  celula.cpp view2.cpp CorreTodo.cpp 

INCLUDEPATH = /usr/include/boost/thread/ 
INCLUDEPATH = /usr/include/Inventor/annex -D_REENTRANT 
INCLUDEPATH = /usr/share/qt4/include
INCLUDEPATH = /usr/share/qt4/include/Qt 
INCLUDEPATH = /usr/share/qt4/include/QtGui

LIBS += /usr/lib/libboost_thread.so -lSoQt4 -lQtOpenGL -lQtGui -lQt3Support -lXmu -lXi -lCoin -lGL -lXext -lSM -lICE -lX11 -ldl -lpthread -lsimage 








TARGET = blablabla


