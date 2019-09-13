// G1_DrawTool.cpp: implementation of the CG1_DrawTool class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_DrawTool.h"
#include "CG1_2DVector.h"
#include "CG1_EdgeTable.h"
#include "CG1_ActiveEdgeTable.h"
#include <stdio.h>
#include <cmath>

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
    //DrawDDALine(CG1_Line(55.0,50.0,100.0,15.0), RGB_Color(1.0,0.0,0.0));
    //DrawDDALine(CG1_Line(100.0,15.0, 25.0, -5.0), RGB_Color(1.0,0.0,0.0));
    //DrawDDALine(CG1_Line(25.0, -5.0, 20.0, 5.0), RGB_Color(1.0,0.0,0.0));
    //DrawDDALine(CG1_Line(20.0, 5.0, -10.0, -5.0), RGB_Color(1.0,0.0,0.0));
    //DrawDDALine(CG1_Line(55.0,50.0,-10.0, -5.0), RGB_Color(1.0,0.0,0.0));

    //DrawMidPointLine(CG1_Line(10, 10, 100, 40), RGB_Color(1.0, 0.0, 0.0));
    //DrawMidPointCircle(10,10, 50, RGB_Color(0.0,0.0,1.0));
    //DrawSecondOrderMidPointCircle(-10,10, 50, RGB_Color(0.0,1.0,0.0));
	
    CG1_Polygon MyPolygon;
    MyPolygon.AddPoint(CG1_2DVector(55.0, 50.0));
    MyPolygon.AddPoint(CG1_2DVector(100.0, 15.0));
    MyPolygon.AddPoint(CG1_2DVector(25.0, -5.0));
    MyPolygon.AddPoint(CG1_2DVector(20.0, 5.0));
    MyPolygon.AddPoint(CG1_2DVector(-10.0, -5.0));

    FillPolygon(&MyPolygon, RGB_Color(0.0,1.0,1.0));
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
    float m = (float)(y1 - y0) / (float)(x1 - x0);

    this->PutPixel(x0, y0, color);
    if(m > 1.0 || m < -1.0) {
        printf("In < 1.0\n");
        int help;
        if(y0 > y1) {
            help = y0;
            y0 = y1;
            y1 = help;
            help = x0;
            x0 = x1;
            x1 = help;
        }

        m = (float) (x1 - x0) / (float)(y1 - y0);
        printf("M: %f X0: %d X1: %d Y0: %d Y1: %d\n", m, x0, x1, y0, y1);

        float x = x0;
        for(int y = y0 + 1; y <= y1; y++) {
            x += m;
            PutPixel((int) round(x), y, color);
        }
    }
    else {
        printf("In else\n");
        int help;
        if(x0 > x1) {
            help = x0;
            x0 = x1;
            x1 = help;

            help = y0;
            y0 = y1;
            y1 = help;
        }

        float y = y0;
        for(int x = x0 + 1; x <= x1; x++) {
            y += m;
            PutPixel(x, (int) round(y), color);
        }
    }
   
}

void CG1_DrawTool::DrawMidPointLine(CG1_Line line, RGB_Color color) {
    int x0, x1, y0, y1, x, dx, dy, y, d;

    x0 = line.X0();
    x1 = line.X1();
    y0 = line.Y0();
    y1 = line.Y1();
    dx = x1 - x0;
    dy = y1 - y0;

    d = dy * 2 - dx;

    PutPixel(x0, y0, color);
    y = y0;
    for(x = x0; x < x1; ) {
        if(d <= 0) {
            d += dy * 2;
        }
        else {
            d += (dy - dx) * 2;
            y++;
        }
        x++;

        PutPixel(x, y, color);
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

        ET.Initialize(Polygon);

        for(int y = MinimumY; y < MaximumY; y++) {
            AET.Add(ET.GetEdgeTableRow(y));
            AET.ActiveEdgeIterator = AET.ActiveEdges.begin();
            CG1_Edge* first;
            CG1_Edge* second;


            while(AET.ActiveEdgeIterator != AET.ActiveEdges.end()) {
                first = *AET.ActiveEdgeIterator;
                AET.ActiveEdgeIterator++;
                if(AET.ActiveEdgeIterator == AET.ActiveEdges.end())
                    break;
                second = *AET.ActiveEdgeIterator;
                AET.ActiveEdgeIterator++;
                for(int x = (int) round(first->Current_X); x < (int) round(second->Current_X); x++) {
                    PutPixel(x, y, color);
                }
            }

            AET.RemoveObsoleteEdges(y + 1);
            AET.Update_CurrentX_Values();
            //Vul pixels
            //Verhoog y met 1
            //Clear AET
            //Verhoog x voor nieuwe Y
        }
	}
}

//--------------------------------------------------------------------
