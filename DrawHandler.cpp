#ifndef DRAW_HANDLER_CPP
#define DRAW_HANDLER_CPP

#include "DrawHandler.h"
#include "ShaderManager.h"
#include "globals.h"

#include <math.h>

DrawHandler::DrawHandler()
{
    float base_gray = 0.6f;
    float base_shade = 10.0f;

    lightSourcesColors[0] = base_gray;   lightSourcesColors[1] = base_gray;       lightSourcesColors[2] = base_gray;       lightSourcesColors[3] = base_shade;
    lightSourcesColors[4] = base_gray;   lightSourcesColors[5] = base_gray;       lightSourcesColors[6] = base_gray;       lightSourcesColors[7] = base_shade;
    lightSourcesColors[8] = base_gray;   lightSourcesColors[9] = base_gray;       lightSourcesColors[10] = base_gray;      lightSourcesColors[11] = base_shade;
    lightSourcesColors[12] = base_gray;  lightSourcesColors[13] = base_gray;      lightSourcesColors[14] = base_gray;      lightSourcesColors[15] = base_shade;

    lightSourcesDirections[0] = 4.0f;   lightSourcesDirections[1] = 1.0f;       lightSourcesDirections[2] = 0.0f;       lightSourcesDirections[3] = 0.0f;
    lightSourcesDirections[4] = -2.0f;   lightSourcesDirections[5] = 1.0f;       lightSourcesDirections[6] = 2.0f;       lightSourcesDirections[7] = 0.0f;
    lightSourcesDirections[8] = -2.0f;  lightSourcesDirections[9] = 1.0f;      lightSourcesDirections[10] = -2.0f;      lightSourcesDirections[11] = 0.0f;
    lightSourcesDirections[12] = 0.0f;  lightSourcesDirections[13] = -1.0f;      lightSourcesDirections[14] = 0.0f;      lightSourcesDirections[15] = 0.0f;

    lightSourcesOn[0] = 1; lightSourcesOn[1] = 1; lightSourcesOn[2] = 1; lightSourcesOn[3] = 1;

    modelToWorld.makeEye();
    modelToWorld[5] = 0;    modelToWorld[6] = 1.0;
    modelToWorld[9] = 1.0;   modelToWorld[10] = 0.0;

}

DrawHandler::~DrawHandler()
{
    //dtor
}

void DrawHandler::init()
{

    model = new Model();

    model = getGlobal()->OH->loadObj("models/billboard.obj");

    shaderProgram = getGlobal()->SM->loadShaders("standard.vert", "standard.frag");
    glUseProgram(shaderProgram);

    //Build perpective projection matrix
	buildPerspProjMat(projMatrix.m, 60.0f, 1.778f, 0.1f, 500.0f);



	//Send projection matrix to GPU
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_TRUE, projMatrix.m);

	//Send light colors and positions to GPU
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "lightSourcesColors"), 1, GL_FALSE, lightSourcesColors);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "lightSourcesDirections"), 1, GL_TRUE, lightSourcesDirections);
	glUniform4f(glGetUniformLocation(shaderProgram, "lightSourcesOn"), lightSourcesOn[0],lightSourcesOn[1], lightSourcesOn[2], lightSourcesOn[3]);
}

void DrawHandler::render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(shaderProgram);

	camera* cam = getGlobal()->cam;
    cam->update();

    //Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cam->rotate(0.02, 0.0);

	//Send camera position to GPU
	glUniform3f(glGetUniformLocation(shaderProgram, "cameraPos"), cam->pos[0], cam->pos[1], cam->pos[2]);
	// Calculate world to view matrix
	lookAt(cam->pos[0],cam->pos[1],cam->pos[2], cam->lookAt[0],cam->lookAt[1],cam->lookAt[2], 0.0f,1.0f,0.0f, getGlobal()->worldToView.m);
    //Send worldToView matrix to GPU
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "worldToView"), 1, GL_TRUE, getGlobal()->worldToView.m);
    //Send camerapos matrix to GPU
    glUniform3f(glGetUniformLocation(shaderProgram, "cameraPos"), cam->pos[0], cam->pos[1], cam->pos[2]);
	// Update which lights to show
	glUniform4f(glGetUniformLocation(shaderProgram, "lightSourcesOn"), lightSourcesOn[0],lightSourcesOn[1], lightSourcesOn[2], lightSourcesOn[3]);

    //Draw model
    glActiveTexture(GL_TEXTURE0);

    Point* origin = new Point(0.0, 0.0, 0.0);
    Point* oneUp = new Point(0.0, 2.0/((double)getGlobal()->height), 0.0);
    modelToWorld.setTranslate(origin);

    for(int i = 0; i < getGlobal()->height; i++)
    {
        modelToWorld.addTranslate(oneUp);
        //Send modelToWorld matrix to GPU
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelToWorld"), 1, GL_TRUE, modelToWorld.m);

        glBindTexture(GL_TEXTURE_2D, getGlobal()->vectorFieldSpeedPressure[i]);
        glUniform1i(glGetUniformLocation(shaderProgram, "texUnit"), 0);
        getGlobal()->OH->drawModel(model);

        if (glGetError() != 0)
        {
            cout << "GLError in Draw" << endl;
        }
    }

	//Swap buffers - redraw
	glutSwapBuffers();
}

void DrawHandler::reshape(int w, int h)
{
    int windowSizeX, windowSizeY;
	windowSizeX = w;
    windowSizeY = h;
    glViewport(0, 0, w, h);
	cout << windowSizeX << " : " << windowSizeY << endl;

	//Build and send projection matrix to GPU
	buildPerspProjMat(projMatrix.m, 60.0f, (float)w/h, 0.1f, 500.0f);
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_TRUE, projMatrix.m);

    glutPostRedisplay();
}

#endif
