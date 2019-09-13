// RayTracer.cpp: implementation of the RayTracer class.
//
//////////////////////////////////////////////////////////////////////

#include "RayTracer.h"
#include <stdio.h>
#include "scene.h"
#include "ray.h"
#include "returnobject.h"
#include "pointlightlist.h"
#include "pointlight.h"
#include <iostream>
#include <cmath>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

RayTracer::RayTracer()
{
	m_ImageWidth = 0;
	m_ImageHeight = 0;

	m_UseMultipleRays = false;
}
//--------------------------------------------------------------------
RayTracer::RayTracer(cg_Canvas* canv)
{
	m_ImageWidth = 0;
	m_ImageHeight = 0;

	m_UseMultipleRays = false;

	canvas = canv;
}
//--------------------------------------------------------------------
RayTracer::~RayTracer()
{
	
}
//--------------------------------------------------------------------
void RayTracer::slotRender()
{
	TraceView();
}

void RayTracer::GetFirstRay(Ray* newRay, double x, double y) {
    newRay->setOrigin(m_pSceneToTrace->getEye());
    Vec3 temp = Vec3(x, y, 0) - m_pSceneToTrace->getEye();
    temp.Normalize();
    newRay->setDirection(temp);
}

void RayTracer::TraceRay(Ray* ray, RGB_Color* color) {
    ShapeList* list = m_pSceneToTrace->getShapeList();
    ReturnObject ret;
    Shape* shape = list->getNearestIntersection(ray, &ret);
    if(ret.getIntersectionFound()) {
        //std::cout << "Found Collision" << std::endl;
        AddAmbientComponent(color, shape);
        AddLightComponent(color, shape, &ret);
        //(*color) = shape->GetColor();
    }
    else {
        //std::cout << "No collision" << std::endl;
        color->SetRGB(0, 0, 0);
    }
}

void RayTracer::AddAmbientComponent(RGB_Color* color, Shape* shape) {
    RGB_Color objColor = shape->GetColor();
    RGB_Color ambientIntensity = m_pSceneToTrace->getAmbientIntensity();
    double ka = shape->GetKa(), kd = shape->GetKd();

    color->r = ambientIntensity.r * ka * objColor.r;
    color->g = ambientIntensity.g * ka * objColor.g;
    color->b = ambientIntensity.b * ka * objColor.b;

    //std::cout << color->r << " " << color->g << " " << color->b << std::endl;
}

void RayTracer::AddLightComponent(RGB_Color* color, Shape* shape, ReturnObject* returnObj) {
    PointLightList* list = m_pSceneToTrace->getLightList();
    Vec3 normal = returnObj->getNormal();
    PointLight* point;
    double dotProduct, kd = shape->GetKd();
    double fAtt;
    Vec3 temp;
    double distance;
    RGB_Color objColor = shape->GetColor();


    for(int i = 0; i < list->GetNrOfLights(); i++) {

        point = list->GetLight(i);

        distance = returnObj->getIntersectionPoint().DistanceTo(point->getPosition());
        if(InShadow(returnObj->getIntersectionPoint(), point->getPosition(), distance, shape)) {
            //(*color) = RGB_Color(0.3, 0.5, 0.2);
            continue;
        }


        temp = point->getPosition() - returnObj->getIntersectionPoint();
        temp.Normalize();
        dotProduct = normal * temp;
        if(dotProduct > 0) {
            //std::cout << "Found light" << std::endl;
            double c1, c2, c3;
            c1 = point->getAtt1();
            c2 = point->getAtt2() * (distance);
            c3 = point->getAtt3() * (distance * distance);
            fAtt = 1.0 / (c1 + c2 + c3);
            if(fAtt > 1.0)
                fAtt = 1.0;

            //std::cout << "C1: " << c1 << " C2: " << c2 << "C3: " << c3 << "Fatt: " << fAtt << std::endl;
            color->r += (point->getColor().r * kd * objColor.r * dotProduct) * fAtt;
            color->g += (point->getColor().g * kd * objColor.g * dotProduct) * fAtt;
            color->b += (point->getColor().b * kd * objColor.b * dotProduct) * fAtt;
            color->RespectBoundaries();
        }
    }
}

bool RayTracer::InShadow(Vec3 testPoint, Vec3 lightVector, double lightDistance, Shape* shape) {
    ShapeList* list = m_pSceneToTrace->getShapeList();
    ReturnObject ret;
    Ray ray;
    ray.setOrigin(testPoint);
    ray.setDirection(lightVector - testPoint);

    Shape* shape2 = list->getNearestIntersection(&ray, &ret);
    if(ret.getIntersectionFound()) {
        if(ret.getDistance() < lightDistance)
            return true;
    }

    return false;
}

//--------------------------------------------------------------------
void RayTracer::TraceView()
{
	printf("Tracing... ");
	for(int y = m_ImageHalfHeight; y > -m_ImageHalfHeight; y--)
	{
		for(int x = -m_ImageHalfWidth; x < m_ImageHalfWidth; x++)
		{			
			if(m_UseMultipleRays)
			{
				// nog niet van toepassing
			}
			else
			{
				RGB_Color Pixelcolor = RGB_Color(0,0,0);	//AANPASSEN!
                Ray ray;
                GetFirstRay(&ray, x, y);
                TraceRay(&ray, &Pixelcolor);

                signalSetColor(x, y, Pixelcolor);
				// kleur van de pixel doorgeven aan de canvas:
				canvas->PutPixel(x, y, Pixelcolor);
				// pixel onder de huidige positie rood kleuren om progress te tonen:
				if(y > -m_ImageHalfHeight + 1)
				{
					canvas->PutPixel(x, y-1, RGB_Color(1,0,0));
				}
			}
			//canvas->repaint(); //pixel per pixel update: SLOW 
		}
		canvas->repaint(); //line per line update: MEDIUM SPEED 
	}
	//canvas->repaint(); // update complete image once: FASTER 
	printf("done.\n");
}
//--------------------------------------------------------------------
void RayTracer::slotSizeChanged(int NewW, int NewH)
{
	m_ImageWidth = NewW;
	m_ImageHeight = NewH;
	m_ImageHalfWidth = m_ImageWidth / 2;
	m_ImageHalfHeight = m_ImageHeight / 2;
}

//--------------------------------------------------------------------
