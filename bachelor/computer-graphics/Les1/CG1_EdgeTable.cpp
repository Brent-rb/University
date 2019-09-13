// CG1_EdgeTable.cpp: implementation of the CG1_EdgeTable class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_EdgeTable.h"
#include "CG1_2DVector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

CG1_EdgeTable::CG1_EdgeTable()
{

}

//--------------------------------------------------------------------

CG1_EdgeTable::~CG1_EdgeTable()
{
	if(EdgeTableRows.size() > 0)
	{
		DeleteAll();
		EdgeTableRows.clear();
	}
}

//--------------------------------------------------------------------

void CG1_EdgeTable::Initialize(CG1_Polygon *Polygon)
{
	MinimumY = Polygon->GetLowestY();
	MaximumY = Polygon->GetHighestY();
	int NrOfEdgeRows = MaximumY - MinimumY + 1;

	// een lege ET opstellen met Null pointers naar de edge-rijen
	if(EdgeTableRows.size() > 0)
	{
		DeleteAll();
		EdgeTableRows.clear();
	}
	for(int a=0; a<NrOfEdgeRows; a++)
	{
		CG1_EdgeTableRow* NewRow = new CG1_EdgeTableRow();
		EdgeTableRows.push_back(NewRow);
	}

	CG1_Edge* CurrentEdge;
	int NrOfPoints = Polygon->GetSize();
	CG1_2DVector FirstPoint;
	CG1_2DVector SecondPoint;
	FirstPoint = Polygon->GetPoint(0);
	for(int i=1; i<NrOfPoints; i++)
	{
		SecondPoint = Polygon->GetPoint(i);
		CurrentEdge = new CG1_Edge();
		CurrentEdge->SetData(FirstPoint.GetX(), FirstPoint.GetY(), SecondPoint.GetX(), SecondPoint.GetY());
		AddEdge(CurrentEdge);
		FirstPoint = SecondPoint;
	}
	SecondPoint = Polygon->GetPoint(0);
	CurrentEdge = new CG1_Edge();
	CurrentEdge->SetData(FirstPoint.GetX(), FirstPoint.GetY(), SecondPoint.GetX(), SecondPoint.GetY());
	AddEdge(CurrentEdge);
	
}

//--------------------------------------------------------------------

void CG1_EdgeTable::AddEdge(CG1_Edge *edge)
{
	int Ydown = edge->y_down;
	int index = Ydown - MinimumY;
	EdgeTableRows[index]->AddEdge(edge);
}

//--------------------------------------------------------------------

CG1_EdgeTableRow* CG1_EdgeTable::GetEdgeTableRow(int y_value)
{
	int index = y_value - MinimumY;
	return EdgeTableRows[index];
}

//--------------------------------------------------------------------

void CG1_EdgeTable::DeleteAll()
{
	CG1_EdgeTableRow *CurrentRow = 0;
	for(EdgeTableRowIterator = EdgeTableRows.begin(); EdgeTableRowIterator != EdgeTableRows.end(); EdgeTableRowIterator++)
	{
		CurrentRow = *EdgeTableRowIterator;
		delete CurrentRow;
	}
	EdgeTableRows.erase(EdgeTableRows.begin(), EdgeTableRows.end());
}

//--------------------------------------------------------------------

void CG1_EdgeTable::Writedata()
{
	int NrOfEdgeRows = EdgeTableRows.size();
	CG1_EdgeTableRow *CurrentRow = 0;
	for(int i=(NrOfEdgeRows-1); i>=0; i--)
	{
		CurrentRow = EdgeTableRows[i];
		CurrentRow->WriteData(i + MinimumY);
	}
}

//--------------------------------------------------------------------
