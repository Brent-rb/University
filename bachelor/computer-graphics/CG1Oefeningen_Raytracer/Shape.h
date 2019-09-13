// Shape.h: interface for the Shape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHAPE_H__C940BC4B_0929_492E_9A24_EDB049FB10B6__INCLUDED_)
#define AFX_SHAPE_H__C940BC4B_0929_492E_9A24_EDB049FB10B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vec3.h"
#include <math.h>
#include "RGB_Color.h"

//forard decl
class Ray;
class ReturnObject;

class Shape {
public:
	void SetColor(RGB_Color color);
	void SetPosition(Vec3 position);
	void SetUpVector(Vec3 Up);
	void SetVectors(Vec3 X, Vec3 Y, Vec3 Z);
    void SetKa(double ka) { m_Ka = ka; }
    void SetKd(double kd) { m_Kd = kd; }
	RGB_Color GetColor();
    double GetKa() { return m_Ka; }
    double GetKd() { return m_Kd; }

    virtual void getIntersection(Ray* ray, ReturnObject* returnObject) = 0;

	// constructor & destructor
	Shape();
	virtual ~Shape();

protected:
	Vec3		m_Position;
	Vec3		m_XVec;
	Vec3		m_YVec;
	Vec3		m_ZVec;
	RGB_Color	m_Color;
    double m_Ka;
    double m_Kd;
};

#endif // !defined(AFX_SHAPE_H__C940BC4B_0929_492E_9A24_EDB049FB10B6__INCLUDED_)
