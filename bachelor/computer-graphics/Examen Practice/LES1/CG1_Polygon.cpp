// CG1_Polygon.cpp: implementation of the CG1_Polygon class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_Polygon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

CG1_Polygon::CG1_Polygon()
{

}

//--------------------------------------------------------------------

CG1_Polygon::~CG1_Polygon()
{

}

//--------------------------------------------------------------------

void CG1_Polygon::AddPoint(CG1_2DVector NewPoint)			// PUNT TOEVOEGEN
{
	Points.reserve(Points.size() + 1);
	Points.push_back(NewPoint);
}

//--------------------------------------------------------------------

CG1_2DVector CG1_Polygon::GetPoint(int index)				// PUNT OPVRAGEN
{
	return Points[index];
}

//--------------------------------------------------------------------

int CG1_Polygon::GetSize()									// GROOTTE OPVRAGEN
{
	return Points.size();
}

//--------------------------------------------------------------------

void CG1_Polygon::Clear()									// LEEG MAKEN
{
	Points.clear();
}

//--------------------------------------------------------------------

CG1_Polygon &CG1_Polygon::operator=(const CG1_Polygon &p)	// TOEKENNINGS-OPERATOR
{
	Points.clear();
	int NrOfPoints = p.Points.size();
	Points.reserve(NrOfPoints);
	
	for(int i=0; i<NrOfPoints; i++)
	{
		CG1_2DVector CurrentVector;
		CurrentVector = p.Points[i];
		AddPoint(CurrentVector);	
	}
	return *this;
}

//--------------------------------------------------------------------

int CG1_Polygon::GetLowestY()
{
	int NrOfPoints = Points.size();
	int lowestY = 100000;
	for(int i=0; i<NrOfPoints; i++)
	{
		CG1_2DVector CurrentVector;
		CurrentVector = Points[i];
		int y = CurrentVector.GetY();
		if(y < lowestY)
			lowestY = y;
	}
	return lowestY;
}

//--------------------------------------------------------------------

int CG1_Polygon::GetHighestY()
{
	int NrOfPoints = Points.size();
	int highestY = -100000;
	for(int i=0; i<NrOfPoints; i++)
	{
		CG1_2DVector CurrentVector;
		CurrentVector = Points[i];
		int y = CurrentVector.GetY();
		if(y > highestY)
			highestY = y;
	}
	return highestY;
}

//--------------------------------------------------------------------
