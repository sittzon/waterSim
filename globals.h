#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include "ShaderManager.h"
#include "ObjHandler.h"
#include "InputHandler.h"
#include "vectorUtils.h"
#include "camera.h"


class Global
{
    public:
        Global();
        ~Global();

        ShaderManager* SM;
        ObjHandler* Load;
        InputHandler* IH;


        GLuint program;
        GLuint spriteProgram;
        GLuint showTextureProgram;
        GLuint pointsProgram;
        GLuint normalsProgram;
        // Shadows !
        GLuint shadowMapsLightRenderProgram;
        GLuint shadowMapsProgram;
        GLuint shadowMapsApplyProgram;
        GLuint shadowMapsSmoothProgram;

        GLuint currentProgram;

        Model* m1;
        vector<Model*> allModels;

        Model* spriteModel;

        int FrameCount;
        int windowSizeX, windowSizeY;

        Mat projMatrix;
        Mat worldToView;

        // Object containing all variables and methods assosciated with moving the camera
        camera cam;

        //Lights
        // Color r, g, b and specularity
        float lightSourcesColors[16];

        // Light source direction x, y, z and a component used for indicating positional or directional light
        float lightSourcesDirections[16];

        // Toggle lightsources on or off
        bool lightSourcesOn[4];

        bool perspectiveOn;
        int shaderProgram;

        float deltaT;
};

Global* getGlobal();

#endif
