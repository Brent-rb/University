// G1_DrawTool.cpp: implementation of the CG1_DrawTool class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_DrawTool.h"
#include "CG1_2DVector.h"
#include "CG1_EdgeTable.h"
#include "CG1_ActiveEdgeTable.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

CG1_DrawTool::CG1_DrawTool()
{
}

//--------------------------------------------------------------------

CG1_DrawTool::~CG1_DrawTool()
{
	
}

//--------------------------------------------------------------------

void CG1_DrawTool::DrawData()
{
	// HIER KAN JE AANGEVEN WAT GETEKEND MOET WORDEN
	// (= FUNCTIES AANROEPEN DIE BEPAALDE DINGEN TEKENEN )

	// VOORBEELDEN:
    DrawDDALine(CG1_Line(10,10,50,100), RGB_Color(1.0,0.0,0.0));
	//DrawMidPointLine(CG1_Line(-10,-10,-50,100), RGB_Color(1.0,1.0,0.0));
	//DrawMidPointCircle(10,10, 50, RGB_Color(0.0,0.0,1.0));
	//DrawSecondOrderMidPointCircle(-10,10, 50, RGB_Color(0.0,1.0,0.0));
	
	//CG1_Polygon MyPolygon;
	//MyPolygon.AddPoint(CG1_2DVector(55.0, 50.0));
	//MyPolygon.AddPoint(CG1_2DVector(100.0, 15.0));
	//MyPolygon.AddPoint(CG1_2DVector(25.0, -5.0));
	//MyPolygon.AddPoint(CG1_2DVector(20.0, 5.0));
	//MyPolygon.AddPoint(CG1_2DVector(-10.0, -5.0));

	//FillPolygon(&MyPolygon, RGB_Color(0.0,1.0,1.0));
	//UpdateWindow();
}

//--------------------------------------------------------------------

void CG1_DrawTool::DrawDDALine(CG1_Line Line, RGB_Color color)
{
    // ZELF IMPLEMENTEREN
    int x0 = Line.X0();
    int y0 = Line.Y0();
    int x1 = Line.X1();
    int y1 = Line.Y1();
    int temp;
    if(x1 < x0) {
        temp = x0;
        x0 = x1;
        x1 = temp;
    }
    if(y1 < y0) {
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int m = (y1 - y0) / (x1 - x0);
    int xLast, xNew;
    int yLast, yNew;

    xLast = x0;
    yLast = y0;

    while(xLast != x1 && yLast != y1) {
        PutPixel(xLast, yLast, color);
        xNew = xLast + 1;
        yNew = yLast + m;
    }
   
}

//--------------------------------------------------------------------

void CG1_DrawTool::DrawAllCirclePoints(int Midx, int Midy, int x, int y, RGB_Color color)
{
	PutPixel( Midx + x , Midy + y , color);
	PutPixel( Midx + y , Midy + x , color);
	PutPixel( Midx + y , Midy + -x, color);
	PutPixel( Midx + x , Midy + -y, color);
	PutPixel( Midx + -x, Midy + -y, color);
	PutPixel( Midx + -y, Midy + -x, color);
	PutPixel( Midx + -y, Midy + x , color);
	PutPixel( Midx + -x, Midy + y , color);
}

//--------------------------------------------------------------------

void CG1_DrawTool::FillPolygon(CG1_Polygon *Polygon, RGB_Color color)
{
	if(Polygon->GetSize() > 0)
	{
		int MinimumY = Polygon->GetLowestY();
		int MaximumY = Polygon->GetHighestY();
		CG1_EdgeTable ET;
		CG1_ActiveEdgeTable AET;

		// ZELF VERDER IMPLEMENTEREN
	}
}

//--------------------------------------------------------------------
