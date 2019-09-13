// RT_Canvas.cpp: implementation of the RT_Canvas class.
//
//////////////////////////////////////////////////////////////////////

#include "CG1_Canvas.h"
#include <QRect>
#include <QColor>
#include <QPainter>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------

CG1_Canvas::CG1_Canvas(QWidget *parent) : QWidget(parent)
{
	m_Image = new QImage(width(), height(), QImage::Format_RGB32);
	uint c = QColor(255, 255, 255).rgb();
	m_Image->fill(c);
}

//--------------------------------------------------------------------

CG1_Canvas::~CG1_Canvas()
{
	delete m_Image;
}

//--------------------------------------------------------------------

void CG1_Canvas::PutPixel(int x, int y, RGB_Color color)
{
	int half_w = width() / 2;
	int half_h = height() / 2;
	
	int Xpos = x + half_w;
	int Ypos = -y + half_h;
	
	if(Xpos > 0 && Ypos > 0 && Xpos < width() && Ypos < height())
	{
		color.r *= 255;
		color.g *= 255;
		color.b *= 255;
		
		uint c = QColor((int)color.r, (int)color.g, (int)color.b).rgb();

		m_Image->setPixel(Xpos, Ypos, c);
		
		//bitBlt(this, Xpos, Ypos, m_Image, Xpos, Ypos, 1, 1);
	}
}

//--------------------------------------------------------------------

void CG1_Canvas::paintEvent(QPaintEvent *e)
{
	QPainter paint(this);
	QRect r = m_Image->rect();
    paint.drawImage(r, *m_Image);
}

//--------------------------------------------------------------------

void CG1_Canvas::resizeEvent(QResizeEvent *e)
{
	QWidget::resizeEvent(e);
	
	int w = width() > m_Image->width() ? width() : m_Image->width();
	int h = height() > m_Image->height() ? height() : m_Image->height();
	
	delete m_Image;
	m_Image = new QImage(w, h, QImage::Format_RGB32);
	uint c = QColor(255, 255, 255).rgb();
	m_Image->fill(c);

	SizeChanged();
}

//--------------------------------------------------------------------

void CG1_Canvas::mousePressEvent(QMouseEvent *e)
{
	
}

//--------------------------------------------------------------------

void CG1_Canvas::slotSaveImage()
{
	//PutPixel(0, 0, RGB_Color(0,0,0));
	if(m_Image->save("Image.bmp", "BMP"))
		printf("Image saved as \"Image.bmp\"\n");
	else
		printf("an error occured while writing to \"Image.bmp\"\n");
	//PutPixel(0, 0, RGB_Color(1,1,1));
}

//--------------------------------------------------------------------

void CG1_Canvas::slotGetPixelColor(int x, int y, RGB_Color c)
{
	PutPixel(x, y, c);
}

//--------------------------------------------------------------------

void CG1_Canvas::Clear()
{
	uint c = QColor(255, 255, 255).rgb();
	m_Image->fill(c);
}

//--------------------------------------------------------------------
