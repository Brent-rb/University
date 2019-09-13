#ifndef CG_CANVAS_H
#define CG_CANVAS_H

#include <QWidget>
#include "RGB_Color.h"


class cg_Canvas: public QWidget  
{
	Q_OBJECT

public:
	cg_Canvas(QWidget *parent = 0);
	virtual ~cg_Canvas();

	void PutPixel(int x, int y, RGB_Color c);
	void updateCanvas();
	void Clear();

protected:
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);

public slots:
	void slotSaveImage();

signals:
	void signalSizeChanged(int width, int height);

public:	
	QImage* image;


};

#endif
