#include "returnobject.h"

ReturnObject::ReturnObject() {
    setIntersectionFound(false);
    setIntersectionPoint(Vec3(0, 0, 0));
    setNormal(Vec3(0, 0, 0));
    setDistance(0);
}

ReturnObject::ReturnObject(Vec3 intersectionPoint, Vec3 normal, double distance) {
    setIntersectionFound(true);
    setIntersectionPoint(intersectionPoint);
    setNormal(normal);
    setDistance(distance);
}


void ReturnObject::setIntersectionFound(bool found) {
    $intersectionFound = found;
}

void ReturnObject::setNormal(Vec3 normal) {
    $normal = normal;
}

void ReturnObject::setIntersectionPoint(Vec3 intersection) {
    $intersectionPoint = intersection;
}

void ReturnObject::setDistance(double distance) {
    $distanceFromOrigin = distance;
}


bool ReturnObject::getIntersectionFound() {
    return $intersectionFound;
}

Vec3& ReturnObject::getNormal() {
    return $normal;
}

Vec3& ReturnObject::getIntersectionPoint() {
    return $intersectionPoint;
}

double ReturnObject::getDistance() {
    return $distanceFromOrigin;
}
