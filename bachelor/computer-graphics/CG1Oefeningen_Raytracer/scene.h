#ifndef SCENE_H
#define SCENE_H
#include "ShapeList.h"
#include "Vec3.h"
#include "pointlightlist.h"

class Scene
{
public:
    Scene(Vec3 eye, ShapeList* shapeList, PointLightList* lights);
    ~Scene();

    void addShape(Shape* shape) { $shapeList->AddShape(shape); }
    void setAmbientLight(RGB_Color color) { $ambientIntensity = color; }
    void clear();

    Vec3 getEye() { return $eye; }
    ShapeList* getShapeList() { return $shapeList; }
    PointLightList* getLightList() { return $lights; }
    RGB_Color getAmbientIntensity() { return $ambientIntensity; }

private:
    ShapeList* $shapeList;
    PointLightList* $lights;
    Vec3 $eye;
    RGB_Color $ambientIntensity;
};

#endif // SCENE_H
