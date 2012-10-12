#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "vectorUtils.h"
#include "camera.h"
#include "ShaderManager.h"
#include "ObjHandler.h"
#include "InputHandler.h"
#include "DrawHandler.h"
#include "SimulateHandler.h"




/*
class ShaderManager;
class ObjHandler;
class InputHandler;
class DrawHandler;
class SimulateHandler;*/

class Global
{
    public:
        Global();
        ~Global();

        ShaderManager* SM;
        ObjHandler* OH;
        InputHandler* IH;
        DrawHandler* DH;
        SimulateHandler* SH;

        int windowSizeX, windowSizeY;
        unsigned int width, breadth, height;

        Mat projMatrix;
        Mat worldToView;

        // Object containing all variables and methods assosciated with moving the camera
        camera* cam;

        GLuint shaderProgram;
        GLuint* vectorFieldSpeedPressure;
        GLuint* vectorFieldSpeedPressureResult;

        float deltaT;
};

Global* getGlobal();

#endif
