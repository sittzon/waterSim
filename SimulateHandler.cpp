#ifndef SIMULATEHANDLER_CPP
#define SIMULATEHANDLER_CPP

#include "SimulateHandler.h"
#include "globals.h"
#include "printOpenGLFBOError.h"

SimulateHandler::SimulateHandler()
{
    vectorFieldFbo = 0;
    vectorFieldRenderBuffer = 0;

    fieldWidth = 32;
    fieldHeight = 32;
    fieldBreadth = 32;

    vectorFieldClass = new VectorField();
}

SimulateHandler::~SimulateHandler()
{
    //dtor
}

void SimulateHandler::init()
{
    velocityFieldProgram = getGlobal()->SM->loadShaders("velFieldComp.vert", "velFieldComp.frag");

    //Read raw image texture data
    ifstream file("testField.raw", ios::binary);
    int size = ifstreamLength(&file);
    char buf[size];
    file.read(buf, size);
    file.close();

    //Create FBO to do texture calculations = velocity field computations
    createFBOAndBindTexture(vectorFieldFbo, vectorFieldRenderBuffer, getGlobal()->vectorFieldSpeedPressure, getGlobal()->vectorFieldSpeedPressureResult, buf);

    // Init the fields
    vectorFieldClass->init(getGlobal()->vectorFieldSpeedPressure, 0.5, 1.0, 0.0, 1.0);
    vectorFieldClass->init(getGlobal()->vectorFieldSpeedPressureResult, 0.0, 0.0, 1.0, 1.0);
}

void SimulateHandler::simulate()
{
    //Render to texture FBO = Do calculations!
    //-----------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, vectorFieldFbo);
    glUseProgram(velocityFieldProgram);

    for(int i = 1; i < getGlobal()->height-1; i++)
    {
        //Bind result texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getGlobal()->vectorFieldSpeedPressureResult[i], 0);

        //Check status
        printOpenGLFBOError(vectorFieldFbo, "Init fbo in SimulateHandler::simulate");

        //Bind input textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, getGlobal()->vectorFieldSpeedPressure[i+1]);
        glUniform1i(glGetUniformLocation(velocityFieldProgram, "upperTex"), 0);
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, getGlobal()->vectorFieldSpeedPressure[i]);
        glUniform1i(glGetUniformLocation(velocityFieldProgram, "middleTex"), 1);
        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D, getGlobal()->vectorFieldSpeedPressure[i-1]);
        glUniform1i(glGetUniformLocation(velocityFieldProgram, "lowerTex"), 2);

        //Swap buffers - redraw
        glutSwapBuffers();
    }

    // Swap old and new
    GLuint* temp = getGlobal()->vectorFieldSpeedPressure;
    getGlobal()->vectorFieldSpeedPressure = getGlobal()->vectorFieldSpeedPressureResult;
    getGlobal()->vectorFieldSpeedPressureResult = temp;
}

#endif
