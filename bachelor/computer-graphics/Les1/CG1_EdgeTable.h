// CG1_EdgeTable.h: interface for the CG1_EdgeTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CG1_EDGETABLE_H__7A242F46_54CB_40E7_90C9_862B234D121D__INCLUDED_)
#define AFX_CG1_EDGETABLE_H__7A242F46_54CB_40E7_90C9_862B234D121D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CG1_Edge.h"
#include "CG1_Polygon.h"
#include "CG1_EdgeTableRow.h"

#include <vector>
using namespace std;

class CG1_EdgeTable  
{
public:
	void Writedata();
	void DeleteAll();
	CG1_EdgeTableRow* GetEdgeTableRow(int y_value);
	void Initialize(CG1_Polygon* Polygon);
	CG1_EdgeTable();
	virtual ~CG1_EdgeTable();

private:
	void AddEdge(CG1_Edge* edge);
	int MinimumY;
	int MaximumY;

	vector<CG1_EdgeTableRow*> EdgeTableRows;
	vector<CG1_EdgeTableRow*>::iterator EdgeTableRowIterator;
};

#endif // !defined(AFX_CG1_EDGETABLE_H__7A242F46_54CB_40E7_90C9_862B234D121D__INCLUDED_)
