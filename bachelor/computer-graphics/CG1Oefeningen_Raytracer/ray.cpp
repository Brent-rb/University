#include "ray.h"

Ray::Ray() {
    clear();
}

Ray::Ray(Vec3 origin, Vec3 direction) {
    setOrigin(origin);
    setDirection(direction);
}

Ray::Ray(double xOrigin, double yOrigin, double zOrigin, double xDir, double yDir, double zDir) {
    setOrigin(Vec3(xOrigin, yOrigin, zOrigin));
    setDirection(Vec3(xDir, yDir, zDir));
}

void Ray::setOrigin(Vec3 origin) {
    $origin = origin;
}

void Ray::setDirection(Vec3 direction) {
    $direction = direction;
    normalizeDirection();
}

void Ray::normalizeDirection() {
    $direction.Normalize();
}

void Ray::clear() {
    $direction = Vec3(0, 0, 0);
    $origin = Vec3(0, 0, 0);
}

Vec3& Ray::getOrigin() {
    return $origin;
}

Vec3& Ray::getDirection() {
    return $direction;
}
