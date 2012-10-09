#ifndef _MAIN_CPP
#define _MAIN_CPP

#ifdef _WIN32
    //#include <windows.h>
    //#define GLEW_STATIC
    #include <glew.h>
    #include <wglew.h>
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
#include "utils.h"
#include "camera.h"
#include "globals.h"
#include "leaves.h"


using namespace std;

//Globals
//----------------------------------------------------------
Global* Glob = getGlobal();
ObjHandler* OH = Glob->Load;
InputHandler* IH = Glob->IH;
GLuint shaderProgram, velocityFieldProgram;
Mat projMatrix, modelToWorld, worldToView, lightSourcesColors, lightSourcesDirections, lightSourcesOn;
ShaderManager* SM = Glob->SM;
Model* model = new Model();
camera* cam = &Glob->cam;
GLuint vectorField, scalarField;
GLuint fieldWidth = width;
GLuint fieldHeight = height;
GLuint vectorFieldFbo, vectorFieldRenderBuffer;
//----------------------------------------------------------

void init()
{
	//Display opengl version information
	cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "Max GLSL version supported: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl << endl;
	//cout << "OpenGL extensions: " << glGetString(GL_EXTENSIONS) << endl;

	//Build perpective projection matrix
	buildPerspProjMat(projMatrix.m, 60.0f, 1.778f, 0.1f, 500.0f);

	lightSourcesColors.m = getGlobal()->lightSourcesColors;
	lightSourcesDirections.m = getGlobal()->lightSourcesDirections;

    modelToWorld.makeEye();
    Glob->worldToView.makeEye();

    /*
    lightSourcesColors.makeEye();
    lightSourcesColors[12] = 1.0;
    lightSourcesColors[13] = 1.0;
    lightSourcesColors[14] = 1.0;
    lightSourcesDirections.makeEye();
    */
    lightSourcesOn[0] = 1;
    lightSourcesOn[1] = 1;
    lightSourcesOn[2] = 1;
    lightSourcesOn[3] = 1;

	//Load, compile and link shaders to shadershaderProgram
	shaderProgram = SM->loadShaders("standard.vert", "standard.frag");
	velocityFieldProgram = SM->loadShaders("velFieldComp.vert", "velFieldComp.frag");
    glUseProgram(shaderProgram);

    //model = OH->loadObj("models/stdSphere.obj");
    model = OH->loadObj("models/billboard.obj");

    //Set camera position
    cam->update();

    //Create FBO to do texture calculations = velocity field computations
    createFBOAndBindTexture(vectorFieldFbo, vectorFieldRenderBuffer, vectorField, header_data, fieldWidth, fieldHeight);

	//Send projection matrix to GPU
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_TRUE, projMatrix.m);

	//Send light colors and positions to GPU
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "lightSourcesColors"), 1, GL_FALSE, lightSourcesColors.m);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "lightSourcesDirections"), 1, GL_TRUE, lightSourcesDirections.m);
	glUniform4f(glGetUniformLocation(shaderProgram, "lightSourcesOn"), lightSourcesOn[0],lightSourcesOn[1], lightSourcesOn[2], lightSourcesOn[3]);

	//GL Inits
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_TEXTURE_3D);
}

void reshape(int w, int h)
{
    int windowSizeX, windowSizeY;
	windowSizeX = w;
    windowSizeY = h;
    glViewport(0, 0, w, h);
	cout << windowSizeX << " : " << windowSizeY << endl;
/*
	//Build and send projection matrix to GPU
	buildPerspProjMat(projMatrix.m, 60.0f, (float)w/h, 0.5f, 5000.0f);
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_TRUE, projMatrix.m);

	glUseProgram(spriteProgram);
	glUniformMatrix4fv(glGetUniformLocation(spriteProgram, "projection"), 1, GL_TRUE, projMatrix.m);

	glUseProgram(pointsProgram);
	glUniformMatrix4fv(glGetUniformLocation(pointsProgram, "projection"), 1, GL_TRUE, projMatrix.m);

	glUseProgram(normalsProgram);
	glUniformMatrix4fv(glGetUniformLocation(normalsProgram, "projection"), 1, GL_TRUE, projMatrix.m);

    // ShadowMaps
	glUseProgram(shadowMapsLightRenderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shadowMapsLightRenderProgram, "projection"), 1, GL_TRUE, projMatrix.m);

	glUseProgram(shadowMapsProgram);
	glUniformMatrix4fv(glGetUniformLocation(shadowMapsProgram, "projection"), 1, GL_TRUE, projMatrix.m);
*/

    glutPostRedisplay();
}

void display()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(shaderProgram);


    //Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cam->rotate(0.02, 0.0);

	cam->update();

	//Send camera position to GPU
	glUniform3f(glGetUniformLocation(shaderProgram, "cameraPos"), cam->pos[0], cam->pos[1], cam->pos[2]);
	// Calculate world to view matrix
	lookAt(cam->pos[0],cam->pos[1],cam->pos[2], cam->lookAt[0],cam->lookAt[1],cam->lookAt[2], 0.0f,1.0f,0.0f, Glob->worldToView.m);
    //Send worldToView matrix to GPU
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "worldToView"), 1, GL_TRUE, Glob->worldToView.m);
	//Send modelToWorld matrix to GPU
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelToWorld"), 1, GL_TRUE, modelToWorld.m);
    //Send camerapos matrix to GPU
    glUniform3f(glGetUniformLocation(shaderProgram, "cameraPos"),  cam->pos[0], cam->pos[1], cam->pos[2]);
	// Update which lights to show
	glUniform4f(glGetUniformLocation(shaderProgram, "lightSourcesOn"), lightSourcesOn[0],lightSourcesOn[1], lightSourcesOn[2], lightSourcesOn[3]);

    //Draw model
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texUnit"), 0);
    OH->drawModel(model);

	//Swap buffers - redraw
	glutSwapBuffers();

    //Render to texture FBO = Do calculations!
    //-----------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, vectorFieldFbo);
    glUseProgram(velocityFieldProgram);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(velocityFieldProgram, "texUnit"), 0);

	//Swap buffers - redraw
	glutSwapBuffers();

    if (glGetError() != 0)
        cout << "GLError" << endl;
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
    //cam.update();
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

    init();

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
    glutMainLoop();

    return 0;
}

#endif
