#ifndef VECTORFIELD_H
#define VECTORFIELD_H

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

#include "model.h"

class VectorField
{
    public:
        VectorField();
        ~VectorField();

        void init(GLuint* vectorFieldId, double xSpeed, double ySpeed, double zSpeed, double pressure);
    protected:

    private:
        Model* model;
        GLuint fboId;
        GLuint program;
};

#endif // VECTORFIELD_H
