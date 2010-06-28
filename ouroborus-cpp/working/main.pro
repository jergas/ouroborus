INCLUDEPATH = /usr/include/boost/thread/ 
INCLUDEPATH = /usr/include/Inventor/annex -D_REENTRANT 
INCLUDEPATH = /usr/share/qt4/include
INCLUDEPATH = /usr/share/qt4/include/Qt 
INCLUDEPATH = /usr/share/qt4/include/QtGui
LIBS += /usr/lib/libboost_thread.so -lSoQt4 -lQtOpenGL -lQtGui -lQt3Support -lXmu -lXi -lCoin -lGL -lXext -lSM -lICE -lX11 -ldl -lpthread -lsimage 
CONFIG +=  sqt
HEADERS += MyMainWindow.h
SOURCES += main.cpp
SOURCES += MyMainWindow.cpp




 




