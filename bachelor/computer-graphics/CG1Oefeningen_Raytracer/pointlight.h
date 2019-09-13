#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Vec3.h"
#include "RGB_Color.h"

class PointLight
{
public:
    PointLight();
    PointLight(Vec3 position, RGB_Color light): $light(light), $position(position) {}

    void setPosition(Vec3 position) { $position = position; }
    void setColor(RGB_Color color) { $light = color; }

    RGB_Color getColor() { return $light; }
    Vec3 getPosition() { return $position; }
    void addPosition(float x, float y, float z) { $position = $position + Vec3(x, y, z); }
    void setAtt1(double value) { $lightAtt.x = value; }
    void setAtt2(double value) { $lightAtt.y = value; }
    void setAtt3(double value) { $lightAtt.z = value; }
    void setAtt(double c1, double c2, double c3) { setAtt1(c1); setAtt2(c2); setAtt3(c3); }
    void setAtt(Vec3 vec) { setAtt(vec.x, vec.y, vec.z); }

    double getAtt1() { return $lightAtt.x; }
    double getAtt2() { return $lightAtt.y; }
    double getAtt3() { return $lightAtt.z; }
    Vec3 getAtt() { return Vec3($lightAtt); }

private:
    Vec3 $position;
    RGB_Color $light;
    Vec3 $lightAtt;
};

#endif // POINTLIGHT_H
