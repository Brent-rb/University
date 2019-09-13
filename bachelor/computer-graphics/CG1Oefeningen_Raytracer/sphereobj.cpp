#include "sphereobj.h"
#include "ray.h"
#include "returnobject.h"
#include <cmath>
#include <iostream>

SphereObj::SphereObj(): Shape() {
    setRadius(0);
}

void SphereObj::setRadius(double radius) {
    $radius = radius;
}

double SphereObj::getRadius() {
    return $radius;
}

void SphereObj::getIntersection(Ray *ray, ReturnObject *returnObject) {
    Vec3 rayDir = ray->getDirection();
    Vec3 rayOrg = ray->getOrigin();
    double b = 2 * ((rayDir.x * (rayOrg.x - m_Position.x)) + (rayDir.y * (rayOrg.y - m_Position.y)) + (rayDir.z * (rayOrg.z - m_Position.z)));
    double c = ((rayOrg.x - m_Position.x) * (rayOrg.x - m_Position.x)) + ((rayOrg.y - m_Position.y) * (rayOrg.y - m_Position.y)) + ((rayOrg.z - m_Position.z) * (rayOrg.z - m_Position.z)) - ($radius * $radius);
    double disc = (b * b) - (4 * c);

    if(disc < 0) {
        returnObject->setIntersectionFound(false);
    }
    else {
        //std::cout << "Intersection" << std::endl;
        double t0;

        t0 = (-b - (sqrt((b * b) - (4 * c)))) / 2.0;
        if(t0 <= 0) {
             t0 = (-b + (sqrt((b * b) - (4 * c)))) / 2.0;
        }

        Vec3 intersect(rayDir);
        Vec3 normal;
        intersect = intersect * t0;
        intersect = intersect + rayOrg;

        returnObject->setDistance(t0);
        returnObject->setIntersectionFound(true);
        returnObject->setIntersectionPoint(intersect);
        normal = intersect - m_Position;
        normal.Normalize();
        returnObject->setNormal(normal);
    }
}
