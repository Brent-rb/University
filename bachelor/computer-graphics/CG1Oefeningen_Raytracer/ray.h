#ifndef RAY_H
#define RAY_H
#include "Vec3.h"

class Ray
{
public:
    Ray();
    Ray(Vec3 origin, Vec3 direction);
    Ray(double xOrigin, double yOrigin, double zOrigin, double xDir, double yDir, double zDir);

    void setOrigin(Vec3 origin);
    void setDirection(Vec3 direction);
    void normalizeDirection();
    void clear();

    Vec3& getOrigin();
    Vec3& getDirection();

private:
    Vec3 $origin;
    Vec3 $direction;
};

#endif // RAY_H
