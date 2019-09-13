#ifndef AABOBJ_H
#define AABOBJ_H
#include "Shape.h"
#include "Vec3.h"
#include "ray.h"
#include "returnobject.h"

class AABObj : public Shape
{
public:
    AABObj();

    void SetCorners(Vec3 leftLower, Vec3 rightUpper);
    void getIntersection(Ray* ray, ReturnObject* returnObject);

    Vec3 getLowerLeft();
    Vec3 getUpperRight();

    bool isInside(Vec3 position);

private:
    Vec3 $lowerLeftBack;
    Vec3 $upperRightFront;
};

#endif // AABOBJ_H
