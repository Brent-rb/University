#ifndef NAVIGATION_H
#define NAVIGATION_H
#include <math.h>
#include <iostream>

#define RADIAL_LOOP 6.28318530718
#define DEGREE_TO_RAD 0.01745329251
#define RAD_TO_DEGREE 57.2957795131

class Navigation
{
public:
    Navigation();
    ~Navigation();
    void rotateX(double radial);
    void rotateX(int degree);
    void rotateY(double radial);
    void rotateY(int degree);
    void rotateZ(double radial);
    void rotateZ(int degree);
    void rotateXYZ(double x, double y, double z);
    void rotateXYZ(int x, int y, int z);
    void moveX(double distance);
    void moveY(double distance);
    void moveZ(double distance);
    void moveForward(double distance);
    void moveBackward(double distance);
    void strafeLeft(double distance);
    void strafeRight(double distance);
    void moveXYZ(double x, double y, double z);
    void setX(double x) { $x = x; }
    void setY(double y) { $y = y; }
    void setZ(double z) { $z = z; }
    void setXYZ(double x, double y, double z) { $x = x; $y = y; $z = z; }
    void setRotationX(int degrees) { $xRot = degrees * DEGREE_TO_RAD; }
    void setRotationY(int degrees) { $yRot = degrees * DEGREE_TO_RAD; }
    void apply();

private:
    double $xRot;
    double $yRot;
    double $zRot;

    double $x;
    double $y;
    double $z;
};

#endif // NAVIGATION_H
