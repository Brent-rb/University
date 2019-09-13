#ifndef POINTLIGHTLIST_H
#define POINTLIGHTLIST_H
#include <list>
#include "pointlight.h"

class PointLightList
{
public:
    PointLightList();
    ~PointLightList() { DeleteAllLights(); }
    PointLight* GetLight(int index);
    void DeleteAllLights();
    void AddPointLight(PointLight* newLight) { $lights.push_back(newLight); }
    int GetNrOfLights() { return $lights.size(); }

private:
    std::list<PointLight*> $lights;
};

#endif // POINTLIGHTLIST_H
