// Basic stuff
#include <stdio.h>
// QT includes
#include <qapplication.h>
// My stuff
#include "CG1_Window.h"

int main (int argc, char* argv[])
{
	//create application
	QApplication qapp(argc, argv);
	
	CG1_DrawTool* TheDrawTool = new CG1_DrawTool();	// create drawtool
	CG1_Window Main_Window(TheDrawTool);		// create window
	Main_Window.resize(320, 320);			// set view size
//	qapp.setMainWidget(&Main_Window);
	Main_Window.show();

	return qapp.exec();

	delete TheDrawTool;
}
