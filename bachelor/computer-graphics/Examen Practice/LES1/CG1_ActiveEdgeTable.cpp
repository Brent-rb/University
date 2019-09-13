// CG1_ActiveEdgeTable.cpp: implementation of the CG1_ActiveEdgeTable class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_ActiveEdgeTable.h"
#include <stdio.h>
#include <algorithm>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

CG1_ActiveEdgeTable::CG1_ActiveEdgeTable()
{
	
}

//--------------------------------------------------------------------

CG1_ActiveEdgeTable::~CG1_ActiveEdgeTable()
{
	
}

//--------------------------------------------------------------------

void CG1_ActiveEdgeTable::Add(CG1_Edge *Edge)
{
    ActiveEdges.push_back(Edge);
}

//--------------------------------------------------------------------

void CG1_ActiveEdgeTable::Add(CG1_EdgeTableRow *EdgeRow)
{
	CG1_Edge* CurrentEdge;
	for(EdgeRow->EdgeIterator = EdgeRow->Edges.begin(); EdgeRow->EdgeIterator != EdgeRow->Edges.end(); EdgeRow->EdgeIterator++)
	{
		CurrentEdge = *(EdgeRow->EdgeIterator);					
		CurrentEdge->Current_X = (float)CurrentEdge->x_down;	// initializeren op de laagste waarde
		Add(CurrentEdge);										// MOET JE ZELF IMPLEMENTEREN
	}

    sortCurrentRow();
}

//--------------------------------------------------------------------

void CG1_ActiveEdgeTable::Writedata(int y_value)
{
	if(ActiveEdges.size() > 0)
	{
		printf("%d: ", y_value);
		CG1_Edge* CurrentEdge;
		for(ActiveEdgeIterator = ActiveEdges.begin(); ActiveEdgeIterator != ActiveEdges.end(); ActiveEdgeIterator++)
		{
			CurrentEdge = *ActiveEdgeIterator;
			printf(" x = %.2f ", CurrentEdge->Current_X);
		}
		printf("\n");
	}
	else
	{
		printf("%d: empty\n", y_value);
	}
}

//--------------------------------------------------------------------

void CG1_ActiveEdgeTable::Update_CurrentX_Values()
{
    ActiveEdgeIterator = ActiveEdges.begin();

    while(ActiveEdgeIterator != ActiveEdges.end()) {
        CG1_Edge* edge = *ActiveEdgeIterator;
        edge->Current_X += edge->Reversed_M;
        ActiveEdgeIterator++;
    }

    sortCurrentRow();
}

void CG1_ActiveEdgeTable::sortCurrentRow() {
    int n = ActiveEdges.size();
    ActiveEdgeIterator = ActiveEdges.begin();
    CG1_Edge* one;
    CG1_Edge* two;

    while(n != 0) {
        int newn = 0;

        for(int i = 1; i < n; i++) {
            one = ActiveEdges[i - 1];
            two = ActiveEdges[i];

            if(two->Current_X < one->Current_X) {
                ActiveEdges[i - 1] = two;
                ActiveEdges[i] = one;
                newn = i;
            }
        }

        n = newn;
    }
}

//--------------------------------------------------------------------

void CG1_ActiveEdgeTable::RemoveObsoleteEdges(int y)
{
    ActiveEdgeIterator = ActiveEdges.begin();

    while(ActiveEdgeIterator != ActiveEdges.end()) {
        CG1_Edge* edge = *ActiveEdgeIterator;
        if(edge->y_up == y) {
            ActiveEdgeIterator = ActiveEdges.erase(ActiveEdgeIterator);
        }
        else
            ActiveEdgeIterator++;
    }
}

//--------------------------------------------------------------------
