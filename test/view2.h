#ifndef View2_H
#define View2_H



#include "celula.h"
#include "valores.h"
//*********************************TODO EL VIAJE DE COIN3D Y SOWIN **********

#include <qapplication.h>
#include <qsplitter.h>
#include <qmainwindow.h>
#include <qlistview.h>
#include <qapplication.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <QApplication>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QTableView>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QtGui>

#include <Inventor/Qt/SoQt.h>

#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>
#include <Inventor/SoPath.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoGroup.h>

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoTranslation.h>

#include <Inventor/nodes/SoFaceSet.h>

#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoBaseColor.h>

#include <Inventor/sensors/SoIdleSensor.h>


#include <Inventor/nodes/SoLineSet.h>
//*************************************************************************
// *************************************************************************

#define EDT_MESSAGE            2



// este valor es necesario para actualizar las series (alternar la socoordinate3)
 static bool banderita = true;
 static float diferencia = float(ymax)/5;
 static float numero = float(-ymax - diferencia);
 static int banderaSeleccionado;

 static bool isIdle = false;


// Global data.
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

static void play(){
	corre = true;
 
}
static void detente(){
	corre = false;
}
static void limpia(){
	if(!corre){
		limpiaTodo();
	}
}
static void llena(){
	if(!corre){
		init();
	}
}

static void myFunc(void* classPtr, SoSensor *)
{
    printf("******************* IDLE*****************\n");
    isIdle = true; // A variable you add to SoOsInterface
}
// Callback function triggered for selection / deselection.
static void made_selection(void * userdata, SoPath * path)
{	
	path->truncate(path->getLength()-1);
	celula *cel = (celula*)path->getTail();
	int flag =0;

}
static void made_deselection(void * userdata, SoPath * path){
}
class View: public QWidget{
	Q_OBJECT

public:
 SoSelection * selection;
 SoTexture2 *texturas[3];
 celula *grid[xmax][ymax];
 SoSeparator* root;

 SoBaseColor * col;
 
 SoBaseColor *coco;
 SoSeparator *fondo;

//este es para evitar cambiar la imagen cuando no es necesario
 int copiaStatesMatrix[xmax][ymax];

//\\\\\\\\\\\\ veriables para la series de tiempo \\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\



	int jjj;
	QPushButton *botonPlay;
	QPushButton *botonStop;
	QPushButton *botonLimpia;
	QPushButton *botonLLena;
		

	void cargaImagenes();

	void creaBotones();
	View();
	SoSelection* createRoot();




public: 
	bool soRendering;
	
	
	void doUpdates();
};
#endif //View2_H
