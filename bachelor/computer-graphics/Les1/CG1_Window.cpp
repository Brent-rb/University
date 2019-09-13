// CG1_Window.cpp: implementation of the CG1_Window class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_Window.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

CG1_Window::CG1_Window(CG1_DrawTool* MyDrawTool)
{
	m_pRenderCanvas = new CG1_Canvas(this);
	setCentralWidget(m_pRenderCanvas);

	m_pDrawTool = MyDrawTool;

	m_pToolBar = new QToolBar(this);
	//m_pButton = new QToolButton(QPixmap(), "save button", "save button", m_pRenderCanvas, SLOT(slotSaveImage()), m_pToolBar);
	//m_pButton->setText("Save");

	connect(m_pDrawTool, SIGNAL(UpdateWindow()), this, SLOT(slotUpdate()));
	connect(m_pRenderCanvas, SIGNAL(SizeChanged()), this, SLOT(slotUpdate()));
	connect(m_pDrawTool, SIGNAL(PutPixel(int,int,RGB_Color)), m_pRenderCanvas, SLOT(slotGetPixelColor(int,int,RGB_Color)));
}

//--------------------------------------------------------------------

CG1_Window::~CG1_Window()
{

}

//--------------------------------------------------------------------

void CG1_Window::slotUpdate()
{
	m_pRenderCanvas->Clear();
	m_pDrawTool->DrawData();
	m_pRenderCanvas->update();
}

//--------------------------------------------------------------------