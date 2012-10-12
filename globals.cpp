#ifndef GLOBALS_CPP
#define GLOBALS_CPP

#include "globals.h"
#include "ShaderManager.h"
#include "ObjHandler.h"
#include "InputHandler.h"
#include "DrawHandler.h"
#include "SimulateHandler.h"

Global::Global()
{
    SM = new ShaderManager();
    OH = new ObjHandler();
    IH = new InputHandler();
    DH = new DrawHandler();
    SH = new SimulateHandler();

    projMatrix = Mat();
    worldToView = Mat();

    cam = new camera();

    width = 32;
    breadth = 32;
    height = 32;

    shaderProgram = 0;
    vectorFieldSpeedPressure = new GLuint[height];
    vectorFieldSpeedPressureResult = new GLuint[height];

    deltaT = 0.1;
}

Global::~Global()
{

}

Global* getGlobal()
{
    static Global* currentGlobal = new Global();
    return currentGlobal;
}


#endif
