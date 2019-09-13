// Shape.cpp: implementation of the Shape class.
//
//////////////////////////////////////////////////////////////////////

#include "Shape.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

Shape::Shape()
{
    m_Ka = 0;
    m_Kd = 0;
}

//--------------------------------------------------------------------

Shape::~Shape()
{

}

//--------------------------------------------------------------------

void Shape::SetPosition(Vec3 position)
{
 	m_Position = position;
}

//--------------------------------------------------------------------

void Shape::SetVectors(Vec3 X, Vec3 Y, Vec3 Z)
{
	m_XVec = X;
	m_YVec = Y;
	m_ZVec = Z;
}

//--------------------------------------------------------------------

void Shape::SetUpVector(Vec3 Up)
{
	m_YVec = Up;
	m_YVec.Normalize();

	Vec3 Temp = Up.GetSmallestContibutionVector();
	Temp.Normalize();

	m_XVec = Up % Temp;
	m_XVec.Normalize();
	
	m_ZVec = m_XVec % m_YVec;
	m_ZVec.Normalize();
}

//--------------------------------------------------------------------

void Shape::SetColor(RGB_Color color)
{
    m_Color = color;
}

//--------------------------------------------------------------------

RGB_Color Shape::GetColor()
{
	return m_Color;
}
