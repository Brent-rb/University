#include "pointlightlist.h"

PointLightList::PointLightList()
{

}

void PointLightList::DeleteAllLights() {
    std::list<PointLight*>::iterator it = $lights.begin();

    while(it != $lights.end()) {
        delete (*it);
        it++;
    }
}

PointLight* PointLightList::GetLight(int index) {
    std::list<PointLight*>::iterator it = $lights.begin();
    std::advance(it, index);

    return (*it);
}
