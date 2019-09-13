#ifndef SPHEREOBJ_H
#define SPHEREOBJ_H
#include "Shape.h"

class SphereObj : public Shape {
public:
    SphereObj();

    void setRadius(double radius);
    void getIntersection(Ray *ray, ReturnObject *returnObject);
    double getRadius();

private:
    double $radius;
};

#endif // SPHEREOBJ_H
