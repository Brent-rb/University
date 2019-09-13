
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "planets.h"

PlanetsApp::PlanetsApp()
{
	setWindowTitle("CG1 Planets");
	resize(640, 480);
	initView();
}

PlanetsApp::~PlanetsApp()
{
}

void PlanetsApp::initView()
{
	view=new PlanetsView(this);
	setCentralWidget(view);
    setMouseTracking(true);
}
