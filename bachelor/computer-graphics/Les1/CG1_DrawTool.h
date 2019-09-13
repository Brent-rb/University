// G1_DrawTool.h: interface for the CG1_DrawTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G1_DRAWTOOL_H__EAC1E35F_BAF4_4ECF_957A_D5DEF2B21C31__INCLUDED_)
#define AFX_G1_DRAWTOOL_H__EAC1E35F_BAF4_4ECF_957A_D5DEF2B21C31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QObject>
#include <QRect>
#include "RGB_Color.h"
#include "CG1_Line.h"
#include "CG1_Polygon.h"


class CG1_DrawTool : public QObject 
{

	Q_OBJECT

public:
	void DrawData();
	void DrawDDALine(CG1_Line Line, RGB_Color color);
	void FillPolygon(CG1_Polygon *Polygon, RGB_Color color);
	void DrawAllCirclePoints(int Midx, int Midy, int x, int y, RGB_Color color);

	CG1_DrawTool();
	virtual ~CG1_DrawTool();

signals:
	void PutPixel(int x, int y, RGB_Color color);
	void UpdateWindow();

};

#endif // !defined(AFX_G1_DRAWTOOL_H__EAC1E35F_BAF4_4ECF_957A_D5DEF2B21C31__INCLUDED_)
