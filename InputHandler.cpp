#ifndef INPUT_HANDLER_CPP
#define INPUT_HANDLER_CPP

#include "utils.h"
#include "globals.h"
#include "InputHandler.h"
#include "camera.h"

//#include <freeglut.h>

using namespace std;

InputHandler::InputHandler()
{
	mouseLeftDown = false;
	mouseMiddleDown = false;
	cStart = 0;
	rStart = 0;
}

InputHandler::~InputHandler()
{

}

void InputHandler::handleKeyboard(unsigned char key, int c, int r)
{
	int specialKey = glutGetModifiers();

    vector<keyboardEvent>::iterator event;

    // Iterate through every keyboard event, and if the criterium is met, execute the event function.
    for(event = keyboardFunctions.begin(); event < keyboardFunctions.end(); ++event)
    {
        if(event->activation(key, specialKey, c, r, this)) // Check if criterium is met.
        {
            event->function(key, specialKey, c, r, this);  // Execute the function.
        }
    }

    if (key == 'w')
    {
        getGlobal()->cam.radius *= 0.98;
    }
    else if (key == 's')
    {
        getGlobal()->cam.radius *= 1.02;
    }
    else if (key == 'a')
    {
        getGlobal()->cam.pan(0.05, 0.0);

    }
    else if (key == 'd')
    {
        getGlobal()->cam.pan(-0.05, 0.0);
    }
    else if (key == 'q')
    {
        getGlobal()->cam.pan(0.0, 0.1);
    }
        else if (key == 'e')
    {
        getGlobal()->cam.pan(0.0, -0.1);
    }

}

void InputHandler::handleMouse(int button, int state, int c, int r)
{
	int specialKey = glutGetModifiers();

    bool pressedButton = false;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //pressedButton = getGlobal()->BH->checkAndPressButton(r, c);
    }

    vector<mouseEvent>::iterator event;

    // If pressed button, don't do anything else.
    if(!pressedButton)
    {
        // Iterate through every mouse event, and if the criterium is met, execute the event function.
        for(event = mouseFunctions.begin(); event < mouseFunctions.end(); ++event)
        {
            if(event->activation(button, state, specialKey, c, r, this)) // Check if criterium is met.
            {
                event->function(button, state, specialKey, c, r, this);  // Execute the function.
            }
        }

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)// && (specialKey & GLUT_ACTIVE_ALT || specialKey & 0x0006))
        {
            mouseLeftDown = true;
            mouseMiddleDown = false;
            cStart = c;
            rStart = r;
        }
        else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)// && (specialKey & GLUT_ACTIVE_ALT || specialKey & 0x0006))
        {
            mouseMiddleDown = true;
            mouseLeftDown = false;
            cStart = c;
            rStart = r;
        }
        else if (state == GLUT_UP)
        {
            mouseLeftDown = false;
            mouseMiddleDown = false;
        }
    }
}

void InputHandler::handleMotion(int c, int r)
{
    //Global* cameraPos = &getGlobal()->cameraPos;
    vector<motionEvent>::iterator event;

    // Iterate through every motion event, and if the criterium is met, execute the event function.
    for(event = motionFunctions.begin(); event < motionFunctions.end(); ++event)
    {
        if(event->activation(c, r, this)) // Check if criterium is met.
        {
            event->function(c, r, this);  // Execute the function.
        }
    }

	if (mouseLeftDown == true)
	{
	    GLfloat angleHorizontal = (c - cStart) * 0.005f;
	    GLfloat angleVertical = (rStart - r) * 0.005f;

	     getGlobal()->cam.pan(angleHorizontal, angleVertical);
        //getGlobal()->angleHorizontal += (x - xStart) * 0.005f;
        //getGlobal()->cameraAngleVertical -= (y - yStart) * 0.005f;

        cStart = c;
        rStart = r;

        getGlobal()->cam.rotate(angleHorizontal, angleVertical);
	}
	else if (mouseMiddleDown == true)
	{
        GLfloat dx = -(cStart-c)*getGlobal()->cam.radius*0.0025f;
        GLfloat dy = (rStart-r)*getGlobal()->cam.radius*0.0025f;

        getGlobal()->cam.pan(dx, dy);

		cStart = c;
        rStart = r;
	}
}

void InputHandler::handleScroll(int dir)
{
    int specialKey = glutGetModifiers();

    if (specialKey & GLUT_ACTIVE_ALT || specialKey & 0x0006)
    {

        if (dir < 0)
            getGlobal()->cam.zoom(1.05f);
        else
            getGlobal()->cam.zoom(0.95f);

    }
}

void InputHandler::addKeyboardFunction(keyboardFunction fn, keyboardActivationFunction criteriumFn)
{
    keyboardEvent addedEvent;                   // New event.
    addedEvent.function = fn;                   // Set event function.
    addedEvent.activation = criteriumFn;        // Set event criterium function.
    keyboardFunctions.push_back(addedEvent);    // Add copy of new event.

    return;
}

void InputHandler::addMouseFunction(mouseFunction fn, mouseActivationFunction criteriumFn)
{

    mouseEvent addedEvent;                   // New event.
    addedEvent.function = fn;                // Set event function.
    addedEvent.activation = criteriumFn;     // Set event criterium function.
    mouseFunctions.push_back(addedEvent);    // Add copy of new event.

    return;
}

void InputHandler::addMotionFunction(motionFunction fn, motionActivationFunction criteriumFn)
{
    motionEvent addedEvent;                   // New event.
    addedEvent.function = fn;                 // Set event function.
    addedEvent.activation = criteriumFn;      // Set event criterium function.
    motionFunctions.push_back(addedEvent);    // Add copy of new event.

    return;
}

void InputHandler::addScrollFunction(scrollFunction fn, scrollActivationFunction criteriumFn)
{
    scrollEvent addedEvent;                   // New event.
    addedEvent.function = fn;                 // Set event function.
    addedEvent.activation = criteriumFn;      // Set event criterium function.
    scrollFunctions.push_back(addedEvent);    // Add copy of new event.

    return;
}

#endif
