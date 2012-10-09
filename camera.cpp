#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "camera.h"
#include "globals.h"

camera::camera()
{
    pos = *new Point(0.0f, 0.0f, -2.0f);			//Camera start position.
    lookAt = *new Point(0.0f, 0.0f, 0.0f);          //Camera start focus point.

    angleHorizontal = (float)3.1415/4;
	angleVertical =   (float)3.1415/4;
	radius = 3.0;
}

void camera::update()
{
    pos[0] = lookAt[0] + radius*cos(angleHorizontal)*sin(angleVertical);
    pos[1] = lookAt[1] + radius*cos(angleVertical);
    pos[2] = lookAt[2] + radius*sin(angleHorizontal)*sin(angleVertical);
}

void camera::rotate(GLfloat aH, GLfloat aV)
{
    angleHorizontal += aH;
    angleVertical += aV;

    update();
}

void camera::zoom(GLfloat scaling)
{
    radius = radius*scaling;
    pos = lookAt - (lookAt - pos)*scaling;

    //Zooming to a point, will have to give possibility of setting lookAt
}

void camera::pan(GLfloat dx, GLfloat dy)
{
    Point c1 = Point(getGlobal()->worldToView[0], getGlobal()->worldToView[1], getGlobal()->worldToView[2]);
    Point c2 = Point(getGlobal()->worldToView[4], getGlobal()->worldToView[5], getGlobal()->worldToView[6]);

    pos    = pos    - c1*dx - c2*dy;
    lookAt = lookAt - c1*dx - c2*dy;
}

#endif
