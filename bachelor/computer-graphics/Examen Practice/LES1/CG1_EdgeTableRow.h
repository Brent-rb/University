// CG1_EdgeTableRow.h: interface for the CG1_EdgeTableRow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CG1_EDGETABLEROW_H__600AA174_6BAA_4B41_BB79_56F42F3B93FE__INCLUDED_)
#define AFX_CG1_EDGETABLEROW_H__600AA174_6BAA_4B41_BB79_56F42F3B93FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CG1_Edge.h"
#include <list>
using namespace std;

class CG1_EdgeTableRow  
{
public:
	void WriteData(int index);
	CG1_EdgeTableRow();
	virtual ~CG1_EdgeTableRow();
	void AddEdge(CG1_Edge* Newedge);

public:
	list<CG1_Edge*> Edges;
	list<CG1_Edge*>::iterator EdgeIterator;
};

#endif // !defined(AFX_CG1_EDGETABLEROW_H__600AA174_6BAA_4B41_BB79_56F42F3B93FE__INCLUDED_)
