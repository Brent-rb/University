// ShapeList.h: interface for the ShapeList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPELIST_H__2A5815F1_47C7_400D_91D5_500E0AA5CE52__INCLUDED_)
#define AFX_SHAPELIST_H__2A5815F1_47C7_400D_91D5_500E0AA5CE52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"
#include <list>
using namespace std;

class Ray;
class ReturnObject;

class ShapeList  
{
public:
	int GetNrOfShapes();
	void DeleteAllShapes();
	void AddShape(Shape* NewShape);
	ShapeList();
	virtual ~ShapeList();

    Shape* getNearestIntersection(Ray* ray, ReturnObject* returnObject);

private:
	list<Shape*> Shapes;
	list<Shape*>::iterator ShapeIterator;
};

#endif // !defined(AFX_SHAPELIST_H__2A5815F1_47C7_400D_91D5_500E0AA5CE52__INCLUDED_)
