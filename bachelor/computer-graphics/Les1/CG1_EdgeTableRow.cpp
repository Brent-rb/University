// CG1_EdgeTableRow.cpp: implementation of the CG1_EdgeTableRow class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_EdgeTableRow.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

CG1_EdgeTableRow::CG1_EdgeTableRow()
{

}

//--------------------------------------------------------------------

CG1_EdgeTableRow::~CG1_EdgeTableRow()
{
	CG1_Edge *CurrentEdge = 0;
	for(EdgeIterator = Edges.begin(); EdgeIterator != Edges.end(); EdgeIterator++)
	{
		CurrentEdge = *EdgeIterator;
		delete CurrentEdge;
	}
	Edges.erase(Edges.begin(), Edges.end());	
}

//--------------------------------------------------------------------

void CG1_EdgeTableRow::AddEdge(CG1_Edge* Newedge)
{
	bool inserted = false;
	CG1_Edge* CurrentEdge;
	for(EdgeIterator = Edges.begin(); EdgeIterator != Edges.end() && !inserted; EdgeIterator++)
	{
		CurrentEdge = *EdgeIterator;
		if(CurrentEdge->x_down > Newedge->x_down)
		{
			Edges.insert(EdgeIterator, Newedge);
			inserted = true;
		}
	}
	if(!inserted)
	{
		Edges.push_back(Newedge);
	}
}

//--------------------------------------------------------------------

void CG1_EdgeTableRow::WriteData(int index)
{
	if(Edges.size() > 0)
	{
		printf("%d: ", index);
		CG1_Edge* CurrentEdge;
		for(EdgeIterator = Edges.begin(); EdgeIterator != Edges.end(); EdgeIterator++)
		{
			CurrentEdge = *EdgeIterator;
			printf(" x = %d ", CurrentEdge->x_down);
		}
		printf("\n");
	}
	else
	{
		printf("%d: empty\n", index);
	}
}
