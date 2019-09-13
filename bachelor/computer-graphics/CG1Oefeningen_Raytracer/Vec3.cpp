// Vec3.cpp: implementation of the Vec3 class.
//
//////////////////////////////////////////////////////////////////////

#include "Vec3.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

Vec3::Vec3()
{
	
}

//--------------------------------------------------------------------

Vec3::Vec3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;	
}

//--------------------------------------------------------------------

Vec3::~Vec3()
{
	
}

//--------------------------------------------------------------------

void Vec3::SetXYZ(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//--------------------------------------------------------------------

Vec3 Vec3::operator%(const Vec3 &v)	// CROSSPRODUCT
{
	Vec3 Cross;
	
	Cross.x = (y * v.z) - (z * v.y);
	Cross.y = (z * v.x) - (x * v.z);
	Cross.z = (x * v.y) - (y * v.x);
	
	return Cross;
}

//--------------------------------------------------------------------

Vec3& Vec3::operator=(const Vec3 &v) // TOEKENNING
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

//--------------------------------------------------------------------

Vec3& Vec3::operator-() // NEGATIE
{
	x = -x;
	y = -y;
	z = -z;
	
	return *this;
}

//--------------------------------------------------------------------

Vec3 Vec3::operator-(const Vec3 &v) // AFTREKKEN
{
	Vec3 Neg;
	Neg.x = x - v.x;
	Neg.y = y - v.y;
	Neg.z = z - v.z;
	
	return Neg;
}

//--------------------------------------------------------------------

Vec3 Vec3::operator+(const Vec3 &v) // SOM
{
	Vec3 Sum;
	Sum.x = x + v.x;
	Sum.y = y + v.y;
	Sum.z = z + v.z;
	
	return Sum;
}

//--------------------------------------------------------------------

float Vec3::operator*(const Vec3 &v) // DOT-PRODUKT
{
	return (float)((x * v.x) + (y * v.y) + (z * v.z));
}

//--------------------------------------------------------------------

Vec3 Vec3::operator*(double s) // SCALAIR PRODUKT
{
	Vec3 Prod;
	Prod.x = x * s;
	Prod.y = y * s;
	Prod.z = z * s;
	
	return Prod;
}

Vec3 Vec3::operator/(double s) // SCALAIR PRODUKT
{
    Vec3 Prod;
    Prod.x = x / s;
    Prod.y = y / s;
    Prod.z = z / s;

    return Prod;
}


//--------------------------------------------------------------------

void Vec3::Normalize() //LENGTE VAN DE VECTOR NORMALIZEREN
{
	double length;
	length = 1 / sqrt((x * x) + (y * y) + (z * z));
	x *= length;
	y *= length;
	z *= length;
}

//--------------------------------------------------------------------

double Vec3::DistanceTo(Vec3 v)
{
	return sqrt( (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) + (z - v.z)*(z - v.z) );
}

//--------------------------------------------------------------------

Vec3 Vec3::GetSmallestContibutionVector()
{
	if(x <= y && x <= z)
		return Vec3(1.0, 0.0, 0.0);
	else if (y <= x && y <= z)
		return Vec3(0.0, 1.0, 0.0);
	else
		return Vec3(0.0, 0.0, 1.0);
}

//--------------------------------------------------------------------
