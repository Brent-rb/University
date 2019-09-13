#include "scene.h"


Scene::Scene(Vec3 eye, ShapeList* shapeList, PointLightList* lights) {
    $eye = eye;
    $shapeList = shapeList;
    $lights = lights;
    $ambientIntensity = RGB_Color(0, 0, 0);
}

Scene::~Scene() {
    clear();
}

void Scene::clear() {
    $shapeList->DeleteAllShapes();
    delete $lights;
    delete $shapeList;
}

