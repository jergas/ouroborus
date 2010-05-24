#include "celula.h"
SO_NODE_SOURCE(celula);
void celula::initClass()
{
	std::cout<<"en celula initClass()"<<std::endl;	
		
   // Initialize type id variables. The arguments to the macro
   // are: the name of the node class, the class this is derived
   // from, and the name registered with the type of the parent
   // class.
   SO_NODE_INIT_CLASS(celula, SoSeparator, "Separator");
}
celula::celula(){
		//std::cout<<"constructor de celula"<<std::endl;	
		
		SO_NODE_CONSTRUCTOR(celula);
		//this->affectsState(true);
		/*SO_NODE_ADD_FIELD(textura, new SoTexture2);
		SO_NODE_ADD_FIELD(trans, new SoTranslation);
		SO_NODE_ADD_FIELD(coords, new SoCoordinate3);
		SO_NODE_ADD_FIELD(face, new SoFaceSet);   
		*/
		//std::cout<<"fin constructor de celula"<<std::endl;	
		
}
celula::celula(const celula& cel): textura(cel.textura), trans(cel.trans), coords(cel.coords), face(cel.face){
	
	// Do standard constructor tasks
		SO_NODE_CONSTRUCTOR(celula);
		this->addChild(textura);
		this->addChild(trans);
		this->addChild(coords);
		this->addChild(face);
}
celula::~celula(){}
//en init se crea la cara
void celula::init(){
		//std::cout<<"en celula init()"<<std::endl;	
		//std::cout<<"textura = "<<textura <<std::endl;	
	
		//pones la textura
		this->addChild(textura);
		//std::cout<<"puesta la textura en celula"<<std::endl;		
		trans = new SoTranslation;
		//pones las cordenadas de un cuadrado de lado uno
		coords = new SoCoordinate3;
		coords->point.set1Value(0, SbVec3f(0, 0, 0));
		coords->point.set1Value(1, SbVec3f(1, 0, 0));
		coords->point.set1Value(2, SbVec3f(1, 1, 0));
		coords->point.set1Value(3, SbVec3f(0, 1, 0));
		//std::cout<<"pueestas las coords en celula "<<std::endl;		
		
		face = new SoFaceSet;
		//std::cout<<"puesta la face en celula"<<std::endl;		
		
		//pones la cara, sus cordenadas y la tranlacion
		this->addChild(trans);
		this->addChild(coords);
		this->addChild(face);
		//y le diece a la car el numero de vertices aue tiene
		face->numVertices.setValue(4);
		SoBaseColor * col = new SoBaseColor;
		col->rgb = SbColor(1, 1, 0);
		this->addChild(col);
		//std::cout<<"fin de inti  celula"<<std::endl;		
			
}
void celula::setTexture(SoTexture2 *text){

	//std::cout<<"PONIENDO TEXTURA EN CELULA--------------------"<<std::endl;		
	textura = text;
	//std::cout<<"TEXTURA ="<<textura<<std::endl;		
	
}
void celula::SetPosition(SbVec3f pos){
	//printf(" set position\n");
	trans->translation = pos;
}

void celula::copyContents(const celula * from, SbBool copyconnections){

	SoSeparator::copyContents(from, copyconnections);
	this->textura = from->textura;
	this->trans = from->trans;
	this->coords = from->coords;
	this->face = from->face;
}
celula& celula::operator=(const celula& cel) {
    textura = cel.textura; 
	trans = cel.trans; 
	coords = cel.coords;
	face = cel.face;
	
	return *this;
  }
void celula::replaceChild(SoNode *oldchild, SoNode *newchild){
	SoSeparator::replaceChild(oldchild, newchild);
}
void celula::setCoordinates(int xx, int yy){
	x = xx;
	y = yy;
}
