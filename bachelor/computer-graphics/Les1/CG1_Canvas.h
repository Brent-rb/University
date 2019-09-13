// RT_Canvas.h: interface for the RT_Canvas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RT_CANVAS_H__FD3F59D4_9E02_4C41_8690_CA25FE0EAE58__INCLUDED_)
#define AFX_RT_CANVAS_H__FD3F59D4_9E02_4C41_8690_CA25FE0EAE58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QWidget>
#include <QImage>
#include "RGB_Color.h"

class CG1_Canvas: public QWidget  
{
	Q_OBJECT

public:
	CG1_Canvas(QWidget *parent = 0);
	void PutPixel(int x, int y, RGB_Color rgb);
	void Clear();
	virtual ~CG1_Canvas();

protected:
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
	void mousePressEvent(QMouseEvent *e);

public:	
	QImage* m_Image;

// signals and slots:
public slots:
	void slotGetPixelColor(int x, int y, RGB_Color c);
	void slotSaveImage();

signals:
	void SizeChanged();

};

#endif // !defined(AFX_RT_CANVAS_H__FD3F59D4_9E02_4C41_8690_CA25FE0EAE58__INCLUDED_)
