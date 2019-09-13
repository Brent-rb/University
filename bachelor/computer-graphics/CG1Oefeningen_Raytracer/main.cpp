#include <QApplication>
#include "cg_MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	cg_MainWindow window;
	window.show();

	return a.exec();
}
