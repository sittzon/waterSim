#ifndef SIMULATEHANDLER_H
#define SIMULATEHANDLER_H

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

#include "VectorField.h"

class SimulateHandler
{
    public:
        SimulateHandler();
        ~SimulateHandler();

        void init();
        void simulate();

    protected:

    private:

        GLuint velocityFieldProgram;
        GLuint vectorFieldFbo, vectorFieldRenderBuffer;

        GLuint fieldWidth, fieldHeight, fieldBreadth;

        VectorField* vectorFieldClass;

};

#endif // SIMULATEHANDLER_H
