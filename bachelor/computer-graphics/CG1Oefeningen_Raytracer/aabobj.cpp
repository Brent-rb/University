#include "aabobj.h"
#include <iostream>

AABObj::AABObj() {

}

void AABObj::SetCorners(Vec3 leftLower, Vec3 rightUpper) {
    $lowerLeftBack = leftLower;
    $upperRightFront = rightUpper;
    SetPosition(leftLower + ((rightUpper - leftLower) / 2.0));
}

void AABObj::getIntersection(Ray* ray, ReturnObject* returnObject) {
    double tZUpper, tZLower;
    double tXFront, tXBack;
    double tYLeft, tYRight;
    double smallest;
    bool foundOne = false;

    Vec3 intersection;
    Vec3 smallestIntersection;
    Vec3 normal;
    Vec3 rayOrg = ray->getOrigin();
    Vec3 rayDir = ray->getDirection();

    tZUpper = ($upperRightFront.z - rayOrg.z) / rayDir.z;
    tZLower = ($lowerLeftBack.z - rayOrg.z) / rayDir.z;
    tXFront = ($upperRightFront.x - rayOrg.x) / rayDir.x;
    tXBack = ($lowerLeftBack.x - rayOrg.x) / rayDir.x;
    tYLeft = ($lowerLeftBack.y - rayOrg.y) / rayDir.y;
    tYRight = ($upperRightFront.y - rayOrg.y) / rayDir.y;

    intersection = rayOrg + (rayDir * tZUpper);
    if(isInside(intersection)) {
        foundOne = true;
        smallest = tZUpper;
        smallestIntersection = intersection;
        normal = Vec3(0, 0, 1);
    }

    intersection = rayOrg + (rayDir * tZLower);
    if(isInside(intersection)) {
        if(!foundOne || (smallest > tZLower)) {
            foundOne = true;
            smallest = tZLower;
            smallestIntersection = intersection;
            normal = Vec3(0, 0, -1);
        }
    }

    intersection = rayOrg + (rayDir * tXFront);
    if(isInside(intersection)) {
        if(!foundOne || (smallest > tXFront)) {
            foundOne = true;
            smallest = tXFront;
            smallestIntersection = intersection;
            normal = Vec3(1, 0, 0);
        }
    }

    intersection = rayOrg + (rayDir * tXBack);
    if(isInside(intersection)) {
        if(!foundOne || (smallest > tXBack)) {
            foundOne = true;
            smallest = tXBack;
            smallestIntersection = intersection;
            normal = Vec3(-1, 0, 0);
        }
    }

    intersection = rayOrg + (rayDir * tYLeft);
    if(isInside(intersection)) {
        if(!foundOne || (smallest > tYLeft)) {
            foundOne = true;
            smallest = tYLeft;
            smallestIntersection = intersection;
            normal = Vec3(0, -1, 0);
        }
    }

    intersection = rayOrg + (rayDir * tYRight);
    if(isInside(intersection)) {
        if(!foundOne || (smallest > tYRight)) {
            foundOne = true;
            smallest = tYLeft;
            smallestIntersection = intersection;
            normal = Vec3(0, 1, 0);
        }
    }

    if(foundOne) {
        std::cout << "Found AAB intersection: " << smallest << std::endl;
        returnObject->setIntersectionFound(true);
        returnObject->setIntersectionPoint(smallestIntersection);
        returnObject->setDistance(smallest);
        returnObject->setNormal(normal);
    }
    else {
        returnObject->setIntersectionFound(false);
    }
}

Vec3 AABObj::getLowerLeft() {
    return $lowerLeftBack;
}

Vec3 AABObj::getUpperRight() {
    return $upperRightFront;
}

bool AABObj::isInside(Vec3 position) {
    if((position.x + 0.00001) >= $lowerLeftBack.x && position.x <= ($upperRightFront.x + 0.00001)) {
        if((position.y + 0.00001) >= $lowerLeftBack.y && position.y <= ($upperRightFront.y + 0.00001)) {
            if((position.z + 0.00001) >= $lowerLeftBack.z && position.z <= ($upperRightFront.z + 0.00001)) {
                return true;
            }
        }
    }

    return false;
}
