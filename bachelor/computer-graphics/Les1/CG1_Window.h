// CG1_Window.h: interface for the CG1_Window class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RT_WINDOW_H__10834D1F_F989_44D5_B03B_1B3393AB4F81__INCLUDED_)
#define AFX_RT_WINDOW_H__10834D1F_F989_44D5_B03B_1B3393AB4F81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include "CG1_Canvas.h"
#include "CG1_DrawTool.h"

class CG1_Window : public QMainWindow 
{
	Q_OBJECT
		
public:
	
	//constructor & destructor
	CG1_Window(CG1_DrawTool* MyDrawTool);
	virtual ~CG1_Window();

public slots:
	void slotUpdate();

public:
	QToolBar*		m_pToolBar;
	QToolButton*	m_pButton;
	CG1_Canvas*		m_pRenderCanvas;
	CG1_DrawTool*	m_pDrawTool;
};

#endif // !defined(AFX_RT_WINDOW_H__10834D1F_F989_44D5_B03B_1B3393AB4F81__INCLUDED_)
