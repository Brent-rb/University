#ifndef CG1OEFENINGEN_H
#define CG1OEFENINGEN_H

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>
#include "ui_cg1oefeningen.h"
#include "CG1_Canvas.h"
#include "CG1_DrawTool.h"

class CG1Oefeningen : public QMainWindow
{
    Q_OBJECT

public:
    CG1Oefeningen(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CG1Oefeningen();

public slots:
	void slotUpdate();

private:
	Ui::CG1OefeningenClass ui;
	QToolBar*		m_pToolBar;
	QPushButton*	m_pButton;
	CG1_Canvas*		m_pRenderCanvas;
	CG1_DrawTool*	m_pDrawTool;
};

#endif // CG1OEFENINGEN_H
