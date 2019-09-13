// CG1_2DVector.h: interface for the CG1_2DVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CG1_2DVECTOR_H__255C7E36_76EA_4FFB_AC8A_9E0DDF92BA80__INCLUDED_)
#define AFX_CG1_2DVECTOR_H__255C7E36_76EA_4FFB_AC8A_9E0DDF92BA80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CG1_2DVector  
{
public:

	float GetY();
	float GetX();
	void SetXY(float NewX, float NewY);
	
	CG1_2DVector();
	CG1_2DVector(float X, float Y);
	virtual ~CG1_2DVector();

	float operator*(const CG1_2DVector &v);			//dotproduct
	CG1_2DVector& operator=(const CG1_2DVector &v);	//toekenning
	CG1_2DVector operator-();						//negatie

private:
	float x;
	float y;
	
};

#endif // !defined(AFX_CG1_2DVECTOR_H__255C7E36_76EA_4FFB_AC8A_9E0DDF92BA80__INCLUDED_)
