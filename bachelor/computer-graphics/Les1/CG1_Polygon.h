// CG1_Polygon.h: interface for the CG1_Polygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CG1_POLYGON_H__FD7FE34D_2B7B_40B7_B594_E8BDD93EB553__INCLUDED_)
#define AFX_CG1_POLYGON_H__FD7FE34D_2B7B_40B7_B594_E8BDD93EB553__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CG1_2DVector.h"
#include "RGB_Color.h"
#include <vector>
using namespace std;

class CG1_Polygon  
{
public:
	int GetLowestY();
	int GetHighestY();
	int GetSize();							// geeft het aantal punten terug
	void Clear();							// maakt de lijst leeg
	void AddPoint(CG1_2DVector NewPoint);	// voegt een punt achteraan toe
	CG1_2DVector GetPoint(int index);		// geeft het punt met de gegeven index terug
	
	CG1_Polygon& operator=(const CG1_Polygon &p);	// toekenningsoperator

	CG1_Polygon();
	virtual ~CG1_Polygon();

private:
	vector<CG1_2DVector> Points;					// STL-vector van punten (CG1_2DVectoren)
	vector<CG1_2DVector>::iterator PointIterator;	// iterator
};

#endif // !defined(AFX_CG1_POLYGON_H__FD7FE34D_2B7B_40B7_B594_E8BDD93EB553__INCLUDED_)
