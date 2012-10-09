#ifndef GLOBALS_CPP
#define GLOBALS_CPP

#include "globals.h"

Global::Global()
{
    SM = new ShaderManager();
    Load = new ObjHandler();
    IH = new InputHandler();

    FrameCount = 0;
    projMatrix = *new Mat();
    worldToView = *new Mat();

    cam = camera();

 //   lightSourcesColors[0] = base_gray;   lightSourcesColors[1] = base_gray;       lightSourcesColors[2] = base_gray;       lightSourcesColors[3] = base_shade;
 //   lightSourcesColors[4] = base_gray;   lightSourcesColors[5] = base_gray;       lightSourcesColors[6] = base_gray;       lightSourcesColors[7] = base_shade;
 //   lightSourcesColors[8] = base_gray;   lightSourcesColors[9] = base_gray;       lightSourcesColors[10] = base_gray;      lightSourcesColors[11] = base_shade;
 //   lightSourcesColors[12] = base_gray;  lightSourcesColors[13] = base_gray;      lightSourcesColors[14] = base_gray;      lightSourcesColors[15] = base_shade;

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

    perspectiveOn = true;
    shaderProgram = 0;

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
