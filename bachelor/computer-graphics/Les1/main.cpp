#include <QApplication>
#include "cg1oefeningen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
    CG1Oefeningen w;					// create window
	w.resize(320, 320);					// set view size
	a.setActiveWindow(&w);
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
