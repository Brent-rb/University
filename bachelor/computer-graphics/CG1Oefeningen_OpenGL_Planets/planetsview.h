
#ifndef PLANETSVIEW_H
#define PLANETSVIEW_H

// include files for QT
#include <QGLWidget>
#include <QTimer>
#include <QKeyEvent>

#if WIN32
#pragma comment (lib, "Opengl32.lib")
#pragma comment (lib, "glu32.lib")
#endif

class Navigation;

class PlanetsView : public QGLWidget
{
	Q_OBJECT
public:
	PlanetsView(QWidget *parent=0);
	~PlanetsView();

protected:
	void initializeGL ();
	void resizeGL ( int width, int height );
	void paintGL ();

	void keyPressEvent(QKeyEvent * e);
    void mouseMoveEvent(QMouseEvent* e);

private:
	int dayOfYear, hourOfDay;
	double camPosx,camPosy,camPosz;
	double camUpx,camUpy,camUpz;
	double camViewx,camViewy,camViewz;
	QTimer* timer;
    Navigation* nav;

    int prevX, prevY;
};

#endif
