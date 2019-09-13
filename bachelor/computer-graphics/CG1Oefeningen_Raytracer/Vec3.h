// Vec3.h: interface for the Vec3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEC3_H__6D658C37_A447_47A0_B535_6C67D0796D61__INCLUDED_)
#define AFX_VEC3_H__6D658C37_A447_47A0_B535_6C67D0796D61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Vec3  
{
public:
	float operator*(const Vec3 &v);
	Vec3& operator=(const Vec3 &v);
	Vec3& operator-();
	Vec3 operator%(const Vec3 &v);
	Vec3 operator-(const Vec3 &v);
	Vec3 operator+(const Vec3 &v);
	Vec3 operator*(double s);
    Vec3 operator/(double s);
	double DistanceTo(Vec3 v);
	void Normalize();

	//constructors & destructor
	Vec3();
	Vec3(double x, double y, double z);
	virtual ~Vec3();

public:
	Vec3 GetSmallestContibutionVector();
	void SetXYZ(double x, double y, double z);
	double x;
	double y;
	double z;
};

#endif // !defined(AFX_VEC3_H__6D658C37_A447_47A0_B535_6C67D0796D61__INCLUDED_)
