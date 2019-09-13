#include <QApplication>
#include "planets.h"
//#include "freeglut.h"

int main(int argc, char *argv[])
{
	//glutInit(&argc, argv);
	QApplication a(argc, argv);
    a.setOverrideCursor(QCursor(Qt::BlankCursor));
	PlanetsApp *planets=new PlanetsApp();
	a.setActiveWindow(planets);
	planets->show();
	return a.exec();
}
