// CG1_Edge.h: interface for the CG1_Edge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CG1_EDGE_H__2CA429BD_BBE0_4AA9_925C_6DFFAABDB2E5__INCLUDED_)
#define AFX_CG1_EDGE_H__2CA429BD_BBE0_4AA9_925C_6DFFAABDB2E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CG1_Edge  
{
public:
	void SetData(int x0, int y0, int x1, int y1);
	CG1_Edge();
	virtual ~CG1_Edge();

	int x_down;
	int y_down;
	int x_up;
	int y_up;
	float Reversed_M;
	float Current_X;
};

#endif // !defined(AFX_CG1_EDGE_H__2CA429BD_BBE0_4AA9_925C_6DFFAABDB2E5__INCLUDED_)
