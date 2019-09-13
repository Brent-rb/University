// ShapeList.cpp: implementation of the ShapeList class.
//
//////////////////////////////////////////////////////////////////////

#include "ShapeList.h"
#include "returnobject.h"
#include "Shape.h"
#include "ray.h"
#include <iostream>
#include <cmath>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

ShapeList::ShapeList()
{

}

//--------------------------------------------------------------------

ShapeList::~ShapeList()
{

}

//--------------------------------------------------------------------

void ShapeList::AddShape(Shape *NewShape)
{
	Shapes.push_back(NewShape);
}

//--------------------------------------------------------------------

void ShapeList::DeleteAllShapes()
{
	Shape *CurrentShape = 0;
	for(ShapeIterator = Shapes.begin(); ShapeIterator != Shapes.end(); ShapeIterator++)
	{
		CurrentShape = *ShapeIterator;
		delete CurrentShape;
	}
	Shapes.erase(Shapes.begin(), Shapes.end());
}

//--------------------------------------------------------------------

int ShapeList::GetNrOfShapes()
{
	return Shapes.size();
}

//--------------------------------------------------------------------

Shape* ShapeList::getNearestIntersection(Ray* ray, ReturnObject* returnObject) {
    ShapeIterator = Shapes.begin();
    Shape* lastShape = 0;
    Shape* shape;
    ReturnObject tempRet, lastRet;
    lastRet.setIntersectionFound(false);
    double lastDistance;

    while(ShapeIterator != Shapes.end()) {
        shape = (*ShapeIterator);
        tempRet.setIntersectionFound(false);
        shape->getIntersection(ray, &tempRet);

        if(tempRet.getIntersectionFound()) {
            if(tempRet.getDistance() > 0.00001 && (lastShape == 0 || tempRet.getDistance() < lastDistance)) {
                lastShape = shape;
                lastDistance = tempRet.getDistance();
                lastRet = tempRet;
            }
        }
        ShapeIterator++;
    }

    if(lastShape != 0) {
        returnObject->setDistance(lastDistance);
        returnObject->setIntersectionFound(true);
        returnObject->setIntersectionPoint(lastRet.getIntersectionPoint());
        returnObject->setNormal(lastRet.getNormal());
    }

    return lastShape;
}

