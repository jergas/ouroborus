//--------------- threads---------------------
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
//--------------- end threads---------------------
/***********************************************************************/

#include <QSlider>
#include <QSpinBox>
#include <QtGui>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <qapplication.h>
#include <qgroupbox.h>
#include <qlayout.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSeparator.h>
#include <qapplication.h>
#include <qsplitter.h>
#include <qmainwindow.h>
#include <qlistview.h>
//#include <qgl.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QTableView>
#include <QWidget>
#include <QObject>
#include <iostream>

/******************************************************/
//aca va simage creo
#include <Inventor/nodes/SoTexture2.h>
/*****************************************************/


class MyMainWindow : public QWidget{
	Q_OBJECT

private:
	// Make a Qt renderarea as a child widget of viewthis, adding the
	// scene under common and a camera with the given orientation.

	
void add_view(QWidget * viewthis, SoGroup * common, SbRotation cameraorientation);

private slots:
	void botonazo();

public:
	
	QPushButton *play;
	MyMainWindow(void);
};


 
