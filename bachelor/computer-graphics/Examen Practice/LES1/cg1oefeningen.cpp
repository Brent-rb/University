#include "cg1oefeningen.h"

CG1Oefeningen::CG1Oefeningen(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
	ui.setupUi(this);
	m_pRenderCanvas = new CG1_Canvas(this);
	setCentralWidget(m_pRenderCanvas);

	m_pDrawTool = new CG1_DrawTool();	// create drawtool

	m_pToolBar = new QToolBar(this);
	m_pButton = new QPushButton("save button", m_pToolBar);

	connect(m_pButton, SIGNAL(clicked()), m_pRenderCanvas, SLOT(slotSaveImage()));
	connect(m_pRenderCanvas, SIGNAL(SizeChanged()), this, SLOT(slotUpdate()));
	connect(m_pDrawTool, SIGNAL(PutPixel(int,int,RGB_Color)), m_pRenderCanvas, SLOT(slotGetPixelColor(int,int,RGB_Color)));
}

CG1Oefeningen::~CG1Oefeningen()
{
	delete m_pDrawTool;
}

void CG1Oefeningen::slotUpdate()
{
	m_pRenderCanvas->Clear();
	m_pDrawTool->DrawData();
	m_pRenderCanvas->update();
}
