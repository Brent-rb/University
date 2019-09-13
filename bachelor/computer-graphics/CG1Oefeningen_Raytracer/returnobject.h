#ifndef RETURNOBJECT_H
#define RETURNOBJECT_H
#include "Vec3.h"

class ReturnObject
{
public:
    ReturnObject();
    ReturnObject(bool intersectionFound);
    ReturnObject(Vec3 intersectionPoint, Vec3 normal, double distance);

    void setIntersectionFound(bool found);
    void setNormal(Vec3 normal);
    void setIntersectionPoint(Vec3 intersection);
    void setDistance(double distance);

    bool getIntersectionFound();
    Vec3& getNormal();
    Vec3& getIntersectionPoint();
    double getDistance();

private:
    bool $intersectionFound;
    Vec3 $normal;
    Vec3 $intersectionPoint;
    double $distanceFromOrigin;
};

#endif // RETURNOBJECT_H
