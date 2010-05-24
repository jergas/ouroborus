#ifndef celula_H
#define celula_H

#include <iostream>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoTranslation.h>

#include <Inventor/nodes/SoFaceSet.h>

#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/nodes/SoBaseColor.h>
/*****************************************************************************/

class celula: public SoSeparator{
	SO_NODE_HEADER(celula);
public:
	SoTexture2 * textura;
	SoTranslation * trans;
	SoCoordinate3 * coords;
	int x, y;
	SoFaceSet * face;
	virtual ~celula();
	static void    initClass();

	
	celula();
	/// The copy-constructor:
	celula(const celula& cel);
	celula& operator=(const celula& cel);

	//en init se crea la cara
	void init();
	void setTexture(SoTexture2 *text);
	void SetPosition(SbVec3f pos);
	void copyContents(const celula * from, SbBool copyconnections);
	void replaceChild(SoNode *oldchild, SoNode *newchild);
	void setCoordinates(int xx, int yy);
};

#endif //celula_H