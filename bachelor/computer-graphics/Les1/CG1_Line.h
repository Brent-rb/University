// CG1_Line.h: interface for the CG1_Line class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CG1_LINE_H__237A76C8_3BC6_4FB4_99A9_7D39667ADF53__INCLUDED_)
#define AFX_CG1_LINE_H__237A76C8_3BC6_4FB4_99A9_7D39667ADF53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CG1_Line  
{
public:
	int X0();
	int Y0();
	int X1();
	int Y1();
	void SetData(int x0, int y0, int x1, int y1);
	CG1_Line(int X0, int Y0, int X1, int Y1);
	CG1_Line();
	virtual ~CG1_Line();

private:
	int x0;
	int y0;
	int x1;
	int y1;
};

#endif // !defined(AFX_CG1_LINE_H__237A76C8_3BC6_4FB4_99A9_7D39667ADF53__INCLUDED_)
