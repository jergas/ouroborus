#include "view2.h"

void View::cargaImagenes(){
	
		for(int i = 0; i < 3; ++i){
			texturas[i] = new SoTexture2();
			texturas[i]->ref();
		}
		texturas[0]->filename.setValue("./pelo.PNG");
		texturas[1]->filename.setValue("./sinPelo.PNG");
		texturas[2]->filename.setValue("./vacio.PNG");
		
}//fin carga imagenes()

void View::creaBotones(){
		std::cout<<"botooooooooooooooooones ------------------------------------------"<<std::endl;
		botonPlay = new QPushButton("play");  
		connect(this->botonPlay, SIGNAL(clicked()),this, SLOT(play()));
		botonStop = new QPushButton("detente");  
		connect(this->botonStop, SIGNAL(clicked()),this, SLOT(stop()));
		botonLimpia= new QPushButton("limpia");  
		connect(this->botonLimpia, SIGNAL(clicked()),this, SLOT(limpia()));
		botonLLena = new QPushButton("llena");  
		connect(this->botonLLena, SIGNAL(clicked()),this, SLOT(llena()));
}

View::View(){
		std::cout<<"constructor de view"<<std::endl;	
		jjj = 1;
		coco = new SoBaseColor;
      		std::cout<<"antes de crear la view interna del papa "<<std::endl;
		
		SoQtRenderArea * area = new SoQtRenderArea(this);	
		//SoQtExaminerViewer * area = new SoQtExaminerViewer(this);
      		std::cout<<"despues de crear la view interna del papa "<<std::endl;	
		
		//SoQtRenderArea * area = new SoQtRenderArea(viewthis);
		area->setSceneGraph(createRoot());
		std::cout<<"definimos la scenegraph"<<std::endl;	
		

		#ifndef __COIN__
		// IMPORTANT: make sure each GL context has a unique cache context
		// id.  this is needed for TGS/SGI Inventor. Coin handles this
		// automatically.
		static uint32_t contextcnt = 0;
		area->getGLRenderAction()->setCacheContext(contextcnt++);
		#endif // !__COIN__


		std::cout<<"pacheco coin terminado el constructor"<<std::endl;	
		
}
SoSelection* View::createRoot(){
		std::cout<<"en createRoot"<<std::endl;		
		init();
		std::cout<<"init() de valores.h"<<std::endl;		
		root = new SoSeparator;
		root->ref();
		selection = new SoSelection;
		selection->policy = SoSelection::SHIFT;
		selection->ref();
		cargaImagenes();
		std::cout<<"despues de carga imagenes()"<<std::endl;		
				
		//inicialisas las clases creadas
		celula::initClass();
		std::cout<<"despues de celula::initClass()"<<std::endl;		
		
		std::cout<<"xmax = "<< xmax <<" ymax="<< ymax <<std::endl;		
		int flag = 0;
		for(int i =0; i< xmax;++i)
			for(int j = 0; j < ymax; ++j){
				grid[i][j] = new celula();
				//std::cout<<"new celula()"<<std::endl;		
		
				flag =0;
				if(statesMatrix[i][j] == 1)
					grid[i][j]->setTexture(texturas[0]);
				else if(statesMatrix[i][j] == 2)
					grid[i][j]->setTexture(texturas[1]);
				//std::cout<<"statesMatrix["<<i<<"]["<<j<<"] == "<< statesMatrix[i][j]<<std::endl;		
				//std::cout<<"ya le puse textura a la pinchi celula"<<std::endl;		
			
				grid[i][j]->setCoordinates(i, j);
				//std::cout<<"le pusimos coordinadas"<<std::endl;		
				grid[i][j]->init();
				//std::cout<<"le dimos al init"<<std::endl;		
				grid[i][j]->SetPosition(SbVec3f(float(i), float(-j), .0f));
				//std::cout<<"le dimos un setposition"<<std::endl;		
		
				root->addChild(grid[i][j]);
				//std::cout<<"root->addChild(grid["<<i<<"]["<<j<<"]);"<<std::endl;		
		
			}//for j
		selection->addChild(root);
		selection->addSelectionCallback(made_selection, (void *)1L);
		selection->addDeselectionCallback(made_deselection, (void *)0L);

		
		std::cout<<"fin de createRoot"<<std::endl;		
		
		return selection;
}
void View::doUpdates()
	{
		//printf("  -- principio doUpdates --\n");
		
		int flag = 0;
		for(int i =0; i< xmax;++i)
			for(int j = 0; j < ymax; ++j){
				flag =0;
				if(statesMatrix[i][j] == 1){
					grid[i][j]->replaceChild(grid[i][j]->textura,texturas[0]);
					grid[i][j]->setTexture(texturas[0]);
						//iguala la matriz de estados con la guardada
						copiaStatesMatrix[i][j] = 0;
				}
				else if(statesMatrix[i][j] == 2)
				{
					grid[i][j]->replaceChild(grid[i][j]->textura,texturas[1]);
					grid[i][j]->setTexture(texturas[1]);
					//iguala la matriz de estados con la guardada
					copiaStatesMatrix[i][j] = 1;
				}//else if
				
			}//for j y i
			

		printf("  -- fin       doUpdates --\n");
			
}// FIN DO UPDATES
