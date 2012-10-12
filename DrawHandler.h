#ifndef DRAW_HANDLER_H
#define DRAW_HANDLER_H

#include <iostream>
#include <stdio.h>
#include "model.h"

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

using namespace std;

class DrawHandler
{
    public:
        DrawHandler();
        ~DrawHandler();

        void init();
        void render();
        void reshape(int w, int h);

    protected:
    private:

        GLuint shaderProgram;
        Mat modelToWorld;
        Model* model;
        Mat projMatrix;

        //Lights
        // Color r, g, b and specularity
        float lightSourcesColors[16];

        // Light source direction x, y, z and a component used for indicating positional or directional light
        float lightSourcesDirections[16];

        // Toggle lightsources on or off
        bool lightSourcesOn[4];
};

#endif // DRAW_H
