#include "planetsview.h"
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include "navigation.h"


void solidSphere(GLdouble radius, GLint slices, GLint stacks)
 {
   glBegin(GL_LINE_LOOP);
   GLUquadricObj* quadric = gluNewQuadric();
 
   gluQuadricDrawStyle(quadric, GLU_FILL);
   gluSphere(quadric, radius, slices, stacks);
 
   gluDeleteQuadric(quadric);
   glEnd();

 }


PlanetsView::PlanetsView(QWidget *parent) : QGLWidget(parent)
{
	timer = new QTimer();
	connect( timer, SIGNAL(timeout()), this, SLOT(updateGL()) );

	setFocusPolicy(Qt::StrongFocus);

    nav = new Navigation();
    nav->setXYZ(3.0, 5.0, -25.0);
    prevX = 0;
    prevY = 0;
}

PlanetsView::~PlanetsView()
{
}

void PlanetsView::initializeGL ()
{
	this->dayOfYear = 0;
	this->hourOfDay = 0;

	// Initialize QGLWidget (parent)
	QGLWidget::initializeGL();

	glShadeModel(GL_SMOOTH);

	// Black canvas
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	// Place light
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable(GL_DEPTH_TEST);

	GLfloat light0_position [] = {0.1f, 0.1f, 0.1f, 0.1f};
	GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
	glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
	glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );


	timer->start(50);
}

void PlanetsView::resizeGL ( int width, int height )
{
	if ((width<=0) || (height<=0))
		return;

	//set viewport
	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set persepective
	//change the next line order to have a different perspective
	GLdouble aspect_ratio=(GLdouble)width/(GLdouble)height;
    gluPerspective(40.0f, aspect_ratio, 1.0, 400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void PlanetsView::paintGL ()
{

    int rX = QCursor::pos().rx() - 960;
    int rY = QCursor::pos().ry() - 540;
    int degreesX = (int)(rX / 30.0);
    int degreesY = (int)(rY / 30.0);

    nav->rotateX(-degreesY);
    nav->rotateY(-degreesX);
    QCursor::setPos(960, 540);


	this->dayOfYear = (this->dayOfYear+1);
    //std::cout << "Day: " << dayOfYear << std::endl;
	this->hourOfDay = (this->hourOfDay+1) % 24;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

    nav->apply();
    /*
	// store current matrix
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix( );


	gluLookAt(camPosx ,camPosy ,camPosz,
		camViewx,camViewy,camViewz,
		camUpx, camUpy, camUpz );
    */

	//Draw Axes
	glDisable( GL_LIGHTING );
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
	glEnable( GL_LIGHTING );

	// rotate the plane of the elliptic
    glRotated ( 5.0, 1.0, 0.0, 0.0 );

    //SUN//
    //SUN//
    //SUN//
    glPushMatrix();
    glRotated ((GLdouble) (360.0 * dayOfYear / 365.0), 0.0, 1.0, 0.0);
	// draw the sun
	GLfloat diff [] = { 0.7f , 0.5f , 0.0f };
	glMaterialfv ( GL_FRONT, GL_DIFFUSE, diff );
	//glutSolidSphere( 3.0, 25, 25 );
	solidSphere(3.0, 25, 25);
    glPopMatrix();

    //EARTH//
    //EARTH//
    //EARTH//
    glPushMatrix();
	// rotate the earth around the sun
	glRotated( (GLdouble)(360.0 * dayOfYear /365.0), 0.0, 1.0, 0.0 );
	glTranslated ( 4.0, 0.0, 0.0 );
	// rotate the earth around its axis
	glRotated( (GLdouble)(360.0 * hourOfDay/24.0), 0.0, 1.0, 0.0 );
	// draw the earth
	GLfloat diff2 [] = { 0.2f , 0.2f , 0.8f };
	glMaterialfv ( GL_FRONT, GL_DIFFUSE, diff2 );
	//glutSolidSphere( 0.3,  25, 25 );
	solidSphere(0.3, 25, 25);
    glPopMatrix();

    //BRENTUS//
    //BRENTUS//
    //BRENTUS//
    glPushMatrix();
    //Rorate Brentus around the sun
    glRotated((GLdouble)(360.0 * dayOfYear / 250), 0.0, 1.0, 0.0);
    glTranslated(6.0, 0.0, 0.0);
    GLfloat diff3[] = {0.4f, 0.4f, 0.8f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff3);
    solidSphere(0.4, 25, 25);
    glPopMatrix();

    //ASTEROIDE//
    //ASTEROIDE//
    //ASTEROIDE//
    glPushMatrix();
    glTranslated(5.0, 0.0, (GLdouble) (((dayOfYear % 100) * 2) -100.0));
    GLfloat diff4[] = {1.0f, 0.2f, 0.5f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff4);
    solidSphere(0.2, 25, 25);
    glPopMatrix();

	// restore current matrix
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix( );		

	//swapBuffers();
}

void PlanetsView::keyPressEvent( QKeyEvent * e ) {
    if(e->key() == Qt::Key_Z)
        this->nav->moveForward(0.5);
    if(e->key() == Qt::Key_S)
        this->nav->moveBackward(0.5);
    if(e->key() == Qt::Key_Q)
        this->nav->strafeLeft(0.5);
    if(e->key() == Qt::Key_D)
        this->nav->strafeRight(0.5);
    if(e->key() == Qt::Key_Space)
        this->nav->moveY(5);
    if(e->key() == Qt::Key_Shift)
        this->nav->moveY(-5);
    if(e->key() == Qt::Key_A)
        this->nav->rotateZ(-5);
    if(e->key() == Qt::Key_E)
        this->nav->rotateZ(5);

}

void PlanetsView::mouseMoveEvent(QMouseEvent *e) {

}
