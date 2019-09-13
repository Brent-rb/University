
#ifndef PLANETS_H
#define PLANETS_H

// include files for QT
#include <QMainWindow>

// application specific includes
#include "planetsview.h"

class PlanetsApp : public QMainWindow
{
	Q_OBJECT

public:
	/** construtor */
	PlanetsApp();
	/** destructor */
	~PlanetsApp(); 
	/** setup the mainview*/
	void initView();

	public slots:

private:
	PlanetsView *view;
};
#endif 

