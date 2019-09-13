#include "cg_MainWindow.h"
#include <QPainter>
#include <stdio.h>
#include "sphereobj.h"
#include "pointlight.h"
#include "aabobj.h"
#include <QKeyEvent>
#include <iostream>
//--------------------------------------------------------------------
cg_MainWindow::cg_MainWindow()
{
	ui = new Ui_CG_Window();
	ui->setupUi(this);

	m_RayTracer = new RayTracer(ui->drawCanvas);
	m_UseMultipleRays = false;
    $list = new ShapeList();
    PointLightList* list = new PointLightList();
    $scene = new Scene(Vec3(0, 0, 300), $list, list);
    $scene->setAmbientLight(RGB_Color(0.2, 0.2, 0.2));
    $light = new PointLight(Vec3(-100, 80, 1200), RGB_Color(1.0, 1.0, 1.0));
    $light->setAtt(0.0001, 0.00001, 0.000001);
    list->AddPointLight($light);

    SphereObj* sphere = new SphereObj();
    sphere->SetPosition(Vec3(0, 0, 100));
    sphere->SetVectors(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1));
    sphere->setRadius(30.0);
    sphere->SetColor(RGB_Color(1.0, 0, 0));
    sphere->SetKa(0.5);
    sphere->SetKd(0.5);
    $list->AddShape(sphere);
    sphere = new SphereObj();
    sphere->SetPosition(Vec3(-20, 30, 160));
    sphere->SetVectors(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1));
    sphere->setRadius(10.0);
    sphere->SetColor(RGB_Color(1.0, 1.0, 0));
    sphere->SetKa(0.4);
    sphere->SetKd(0.6);
    $list->AddShape(sphere);


    AABObj* aab = new AABObj();
    /*
    aab->SetColor(RGB_Color(0, 1.0, 1.0));
    aab->SetCorners(Vec3(-10, -50, 150), Vec3(30, -30, 170));
    aab->SetVectors(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1));
    aab->SetKa(0.2);
    aab->SetKd(0.8);
    $list->AddShape(aab);
    aab = new AABObj();
    */
    /*
    aab->SetColor(RGB_Color(0.5, 1.0, 1.0));
    aab->SetCorners(Vec3(20, -50, 80), Vec3(50, -30, 110));
    aab->SetVectors(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1));
    aab->SetKa(0.2);
    aab->SetKd(0.8);
    $list->AddShape(aab);
    */
    m_RayTracer->SetScene($scene);



	connect(ui->pushButton_Save, SIGNAL(clicked()), ui->drawCanvas, SLOT(slotSaveImage()));
	connect(ui->pushButton_Render, SIGNAL(clicked()), m_RayTracer, SLOT(slotRender()));
	connect(ui->pushButton_Mode, SIGNAL(clicked()), this, SLOT(slotChangeMode()));
	connect(ui->drawCanvas, SIGNAL(signalSizeChanged(int, int)), m_RayTracer, SLOT(slotSizeChanged(int, int)));
	
}

void cg_MainWindow::keyPressEvent(QKeyEvent *k) {

    std::cout << "Key pressed" << std::endl;
    switch(k->key()) {
        case 'D':
            std::cout << "D" << std::endl;
            $light->addPosition(5, 0, 0);
        break;
        case 'Q':
            std::cout << "Q" << std::endl;
            $light->addPosition(-5, 0, 0);
        break;
    }

     m_RayTracer->slotRender();
}

//--------------------------------------------------------------------
cg_MainWindow::~cg_MainWindow()
{
	delete ui;
	delete m_RayTracer;
    delete $scene;
}
//--------------------------------------------------------------------
void cg_MainWindow::slotChangeMode()
{
	m_UseMultipleRays = !m_UseMultipleRays;
	printf("Sample mode changed.\n");
	if(m_UseMultipleRays)
	{
		m_RayTracer->useMultipleRays(true);
		ui->pushButton_Mode->setText("  multiple samples / pixel   ");	
	}
	else
	{
		m_RayTracer->useMultipleRays(false);
		ui->pushButton_Mode->setText("  1 sample / pixel   ");
		
	}
}
//--------------------------------------------------------------------
