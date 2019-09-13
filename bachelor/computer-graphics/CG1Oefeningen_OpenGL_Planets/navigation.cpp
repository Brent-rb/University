#include "navigation.h"
#include <GL/glu.h>

Navigation::Navigation()
{
    $x = 0;
    $y = 0;
    $z = 0;
    $xRot = 0;
    $yRot = 0;
    $zRot = 0;
}

Navigation::~Navigation()
{

}

void Navigation::moveX(double distance) {
    $x += distance;
}

void Navigation::moveY(double distance) {
    $y += distance;
}

void Navigation::moveZ(double distance) {
    $z += distance;
}

void Navigation::moveXYZ(double x, double y, double z) {
    moveX(x);
    moveY(y);
    moveZ(z);
}

void Navigation::rotateX(double radial) {
    $xRot += radial;
    //$xRot %= RADIAL_LOOP;
}

void Navigation::rotateX(int degree) {
    rotateX(degree * DEGREE_TO_RAD);
}

void Navigation::rotateY(double radial) {
    $yRot += radial;
    //$yRot %= RADIAL_LOOP;
}

void Navigation::rotateY(int degree) {
    rotateY(degree * DEGREE_TO_RAD);
}

void Navigation::rotateZ(double radial) {
    $zRot += radial;
    //$zRot %= RADIAL_LOOP;
}

void Navigation::rotateZ(int degree) {
    rotateZ(degree * DEGREE_TO_RAD);
}

void Navigation::rotateXYZ(double x, double y, double z) {
    rotateX(x);
    rotateY(y);
    rotateZ(z);
}

void Navigation::rotateXYZ(int x, int y, int z) {
    rotateX(x);
    rotateY(y);
    rotateZ(z);
}

void Navigation::apply() {
    glLoadIdentity();
    //Store current matrix;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    glRotated(-$xRot * RAD_TO_DEGREE, 1.0, 0, 0);
    glRotated(-$yRot * RAD_TO_DEGREE, 0, 1.0, 0);
    glRotated(-$zRot * RAD_TO_DEGREE, 0, 0, 1.0);
    glScaled(1, 1, -1);
    glTranslatef(-$x, -$y, -$z);
}

void Navigation::moveForward(double distance) {
    double xForward = sin(-$yRot) * distance;
    double yForward = sin($xRot) * distance;
    double zForward = cos(-$yRot) * distance;

    moveXYZ(xForward, yForward, zForward);
}

void Navigation::moveBackward(double distance) {
    moveForward(-distance);
}

void Navigation::strafeLeft(double distance) {
    double xForward = sin(-($yRot + (90 * DEGREE_TO_RAD))) * distance;
    double yForward = sin($zRot) * distance;
    double zForward = cos(-($yRot + (90 * DEGREE_TO_RAD))) * distance;

    moveXYZ(xForward, yForward, zForward);
}

void Navigation::strafeRight(double distance) {
    strafeLeft(-distance);
}

