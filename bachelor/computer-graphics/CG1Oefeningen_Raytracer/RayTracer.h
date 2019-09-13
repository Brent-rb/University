// RayTracer.h: interface for the RayTracer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAYTRACER_H__4313F443_876D_42FD_9AF2_3A0332F80ABF__INCLUDED_)
#define AFX_RAYTRACER_H__4313F443_876D_42FD_9AF2_3A0332F80ABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <qobject.h>
#include "RGB_Color.h"
#include "cg_Canvas.h"
#include "Vec3.h"	// Added by ClassView

class Ray;

class Scene;
class Shape;
class ReturnObject;

class RayTracer : public QObject
{
	Q_OBJECT

public:
	void TraceView();

	//constructor & destructor
	RayTracer();
	RayTracer(cg_Canvas* canvas);
	virtual ~RayTracer();

    void useMultipleRays(bool modus) {m_UseMultipleRays = modus;}
    void SetScene(Scene* sceneToTrace) { m_pSceneToTrace = sceneToTrace; }
    void GetFirstRay(Ray* newRay, double x, double y);
    void TraceRay(Ray* ray, RGB_Color* color);
    void AddAmbientComponent(RGB_Color* color, Shape* shape);
    void AddLightComponent(RGB_Color* color, Shape* shape, ReturnObject* returnObj);
    bool InShadow(Vec3 testPoint, Vec3 lightVector, double lightDistance, Shape* shape);

public slots:	
	void slotRender();
	void slotSizeChanged(int NewW, int NewH);

signals:
	void signalSetColor(int x, int y, RGB_Color c);

private:
	cg_Canvas* canvas;
	int m_ImageWidth;
	int m_ImageHeight;
	int m_ImageHalfWidth;
	int m_ImageHalfHeight;
	bool m_UseMultipleRays;
    Scene* m_pSceneToTrace;
};

#endif // !defined(AFX_RAYTRACER_H__4313F443_876D_42FD_9AF2_3A0332F80ABF__INCLUDED_)
