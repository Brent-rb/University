// CG1_ActiveEdgeTable.h: interface for the CG1_ActiveEdgeTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CG1_ACTIVEEDGETABLE_H__8F397EA5_17E6_4A7B_91D4_D2F28C808234__INCLUDED_)
#define AFX_CG1_ACTIVEEDGETABLE_H__8F397EA5_17E6_4A7B_91D4_D2F28C808234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CG1_Edge.h"
#include "CG1_EdgeTableRow.h"

#include <list>
using namespace std;

class CG1_ActiveEdgeTable  
{
public:
	void Writedata(int y_value);
	void Add(CG1_Edge *Edge);
	void Add(CG1_EdgeTableRow* EdgeRow);
	CG1_ActiveEdgeTable();
	virtual ~CG1_ActiveEdgeTable();

public:	
	void RemoveObsoleteEdges(int y);
	void Update_CurrentX_Values();
	list<CG1_Edge*> ActiveEdges;
	list<CG1_Edge*>::iterator ActiveEdgeIterator;

};

#endif // !defined(AFX_CG1_ACTIVEEDGETABLE_H__8F397EA5_17E6_4A7B_91D4_D2F28C808234__INCLUDED_)
