#ifndef _MAIN_CPP
#define _MAIN_CPP

#ifdef _WIN32
    //#include <windows.h>
    #ifndef GLEW_STATIC
    #define GLEW_STATIC
    #endif
    #include <glew.h>
    //#include <wglew.h>
    #include <freeglut.h>
#elif __APPLE__
    #include <OpenGL/gl3.h>
    #include <freeglut.h>
#else
    #include <freeglut.h>
    //#include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glext.h>
    //#include <GL/glut.h>
    //#include <GL/gl.h>
#endif

#include <iostream>
#include <stdio.h>

#include "ShaderManager.h"
#include "ObjHandler.h"
#include "InputHandler.h"
#include "DrawHandler.h"
#include "utils.h"
#include "camera.h"
#include "globals.h"

using namespace std;

//Globals
//----------------------------------------------------------
Global* Glob = getGlobal();
ObjHandler* OH = Glob->OH;
InputHandler* IH = Glob->IH;
DrawHandler* DH = Glob->DH;
SimulateHandler* SH = Glob->SH;
ShaderManager* SM = Glob->SM;
camera* cam = Glob->cam;
//----------------------------------------------------------

void init()
{
	//Display opengl version information
	cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "Max GLSL version supported: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl << endl;
	//cout << "OpenGL extensions: " << glGetString(GL_EXTENSIONS) << endl;

    DH->init();
    SH->init();

    //Set camera position
    cam->update();

	//GL Inits
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_TEXTURE_3D);
}

void reshape(int w, int h)
{
    DH->reshape(w, h);
}

void display()
{
    //Render results to screen
    DH->render();

    //Errors in render to screen?
    if (glGetError() != 0)
        cout << "GLError in screenrender" << endl;

    //Simulate flow
    SH->simulate();

    //Errors in simulate flow?
    if (glGetError() != 0)
        cout << "GLError in simulate" << endl;
}

void timerFunc(int i)
{
	glutTimerFunc(20, timerFunc, 1);
	glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
	IH->handleMouse(button, state, x, y);
}

void motionFunc(int x, int y)
{
	IH->handleMotion(x, y);
}

void keyboard(unsigned char key, int x, int y)
{
    IH->handleKeyboard(key, x, y);
}

void mouseWheel(int button, int dir, int x, int y)
{
	IH->handleScroll(dir);
}

void glInit(int &argc, char **argv, int xwidth, int ywidth)
{
    //Init Window and Misc
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(400,200);
    glutInitWindowSize(xwidth, ywidth);
    glutCreateWindow("Awesome Water Simulator");

    //Establish Callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timerFunc, 0);

    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutKeyboardFunc(keyboard);
    glutMouseWheelFunc(mouseWheel);

    // Add keyboard functions
    // ----------------------
    /*
    ih->addKeyboardFunction(&perspectiveToggle, &perspectiveToggleActivation);
    ih->addKeyboardFunction(&shadingToggle, &shadingToggleActivation);
    ih->addKeyboardFunction(&setFocus, &setFocusActivation);
    ih->addKeyboardFunction(&toggleDrawingNormals, &toggleDrawingNormalsActivation);
    ih->addKeyboardFunction(&lightToggle, &lightToggleActivation);
    */

    // Add mouse functions
    // -------------------
    //IH->addMouseFunction(&leftClickFunction, &leftClickActivationFunction);
    //IH->addMouseFunction(&leftReleaseFunction, &leftReleaseActivationFunction);

    // Add motion functions
    // -------------------
    //ih->addMotionFunction(&toolMoveFunction, &toolMoveActivationFunction);

}

int main(int argc, char **argv)
{
    glInit(argc, argv, 1680/2, 1050/2);
    #ifdef GLEW_STATIC
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
    }
    #endif

    init();
    glutMainLoop();
    cout << "Process exited normally" << endl;

    return 0;
}

#endif
