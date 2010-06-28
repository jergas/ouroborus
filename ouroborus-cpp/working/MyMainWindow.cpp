#include "MyMainWindow.h"

void MyMainWindow::botonazo(){
	std::cout << "apachurraste un boton, ñero" << std::endl;
}
void MyMainWindow::add_view(QWidget * viewthis, SoGroup * common, SbRotation cameraorientation){

	SoSeparator * root = new SoSeparator;

	SoPerspectiveCamera * camera = new SoPerspectiveCamera;
	camera->orientation = cameraorientation;
	root->addChild(camera);

	root->addChild(common);
		
	SoQtExaminerViewer * area = new SoQtExaminerViewer(viewthis);
      
	//SoQtRenderArea * area = new SoQtRenderArea(viewthis);
	area->setSceneGraph(root);

	#ifndef __COIN__
	// IMPORTANT: make sure each GL context has a unique cache context
	// id.  this is needed for TGS/SGI Inventor. Coin handles this
	// automatically.
	static uint32_t contextcnt = 0;
	area->getGLRenderAction()->setCacheContext(contextcnt++);
	#endif // !__COIN__

	camera->viewAll(root, area->getViewportRegion());
}

MyMainWindow::MyMainWindow(void){

	//	QWidget * this = new QWidget;
  
	this->setMinimumSize(400, 300);


	// Set up the Qt widget layout data.

	QHBoxLayout * hlayout = new QHBoxLayout(this);

	QVBoxLayout * vlayout_right = new QVBoxLayout();
	vlayout_right->heightForWidth(285);	
	hlayout->addLayout(vlayout_right, 0.33);
	
	QVBoxLayout * vlayout_left = new QVBoxLayout();
	hlayout->addLayout(vlayout_left, 0.33);
	
	
	QGroupBox * view0 = new QGroupBox(this);
	vlayout_left->addWidget(view0, 0.66);
	
	QGroupBox * view1 = new QGroupBox(this);
	vlayout_left->addWidget(view1, 0.66);
	

	QSpinBox *spinBox = new QSpinBox;
	QSlider *slider = new QSlider(Qt::Horizontal);
	spinBox->setRange(0, 130);
	slider->setRange(0, 130);
	//slider->QSize(28, 20);	
	vlayout_right->addWidget(spinBox, 0.20);
	
	
	boton1 = new QPushButton("boton 1");
	//boton1->QSize(28, 20);  
	connect(this->boton1, SIGNAL(clicked()),this, SLOT(botonazo()));
	vlayout_right->addWidget(boton1, 0.20);
	QPushButton *boton2 = new QPushButton("boton 2");
	//boton2->QSize(28, 20);
	vlayout_right->addWidget(boton2, 0.20);
	// Construct the common part of the scenegraph.

	SoGroup * commonroot = new SoGroup;
	SoDirectionalLight * light = new SoDirectionalLight;
	light->direction.setValue(-0.5, -0.5, -0.8);
	commonroot->addChild(light);
	SoRotation * scenerotate = new SoRotation;
	commonroot->addChild(scenerotate);

    /****************************************************************************************/
    //aca va simage creo
    
	 SoTexture2 * textura1;
	 textura1 = new SoTexture2();
	 textura1->filename.setValue("baboon.png"); 
	 commonroot->addChild(textura1);
        
    //***************************************************************************************/
    SoCube * cube = new SoCube;
    commonroot->addChild(cube);
    /****************************************************************************************/
    //aca va simage creo
    
	 SoTexture2 * textura2;
	 textura2 = new SoTexture2();
	 textura2->filename.setValue("pelo.PNG"); 
	 commonroot->addChild(textura2);
        
    //***************************************************************************************/

    SoTranslation * trans = new SoTranslation;
    trans->translation.setValue(0, 0, 1);
    commonroot->addChild(trans);

    SoSphere * sphere = new SoSphere;
    sphere->radius = 0.5;
    commonroot->addChild(sphere);

	// Add the 3 renderareas.

	add_view(view0, commonroot, SbRotation(SbVec3f(0, 0, 1), 0));
	add_view(view1, commonroot, SbRotation(SbVec3f(0, 1, 0), M_PI / 2.0f));

 }
