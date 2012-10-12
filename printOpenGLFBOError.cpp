#include "printOpenGLFBOError.h"


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

#include <iostream>

using namespace std;

void printOpenGLFBOError(const GLuint fbo, string userComment)
{
    GLuint glStatus = glGetError();
    GLuint fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if(fboStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        cout << endl << endl;
        cout << "---------------------------" << endl;
        cout << "  FBO Error! in fbo: " << fbo << endl;
        cout << userComment << endl;
        cout << "---------------------------" << endl;
        if(fboStatus == 0)
        {
            cout << "gl Error: " << glStatus << endl;
        }
        if(fboStatus == GL_FRAMEBUFFER_UNDEFINED)
        {
            cout << "Target is the default framebuffer, but the default framebuffer does not exist." << endl;
        }
        else if(fboStatus == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
        {
            cout << "Any of the framebuffer attachment points are framebuffer incomplete." << endl;

        }
        else if(fboStatus == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
        {
            cout << "No images are attached to the framebuffer." << endl;
        }
        else if(fboStatus == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
        {
            cout << "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "<< endl;
            cout << " for any color attachment point(s) named by GL_DRAWBUFFERi." << endl;
        }
        else if(fboStatus == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
        {
            cout << "GL_READ_BUFFER is not GL_NONE and the value of " << endl;
            cout << " GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE " << endl;
            cout << " for the color attachment point named by GL_READ_BUFFER." << endl;
        }
        else if(fboStatus == GL_FRAMEBUFFER_UNSUPPORTED)
        {
            cout << "The combination of internal formats of the " << endl;
            cout << " attached images violates an implementation-dependent " << endl;
            cout << " set of restrictions." << endl;
        }
        else if(fboStatus == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
        {
            cout << "The value of GL_RENDERBUFFER_SAMPLES is not the same " << endl;
            cout << " for all attached renderbuffers; if the value of" << endl;
            cout << " GL_TEXTURE_SAMPLES is the not same for all attached " << endl;
            cout << " textures; or, if the attached images are a mix of " << endl;
            cout << " renderbuffers and textures, the value of " << endl;
            cout << " GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES." << endl;
            cout << " OR "<< endl;
            cout << "The value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all "<< endl;
            cout << "attached textures; or, if the attached images are a mix of renderbuffers"<< endl;
            cout << "and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not " << endl;
            cout << "GL_TRUE for all attached textures." << endl;
        }
        else if(fboStatus == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)
        {
            cout << "Any framebuffer attachment is layered, and any populated attachment is not layered," << endl;
            cout << " or if all populated color attachments are not from textures of the same target." << endl;
        }
        else if(fboStatus == GL_FRAMEBUFFER_UNSUPPORTED)
        {
            cout << "The combination of internal formats of the attached images violates an implementation-dependent set of restrictions." << endl;
        }
        else
        {
            cout << "WHAT DID YOU DO!?" << endl;
            cout << "FBO status = " << fboStatus << endl;
            cout << "(Undocumented error). Shame on Khronos group, not us..." << endl;
        }
        cout << endl;
        cout << "---------------------------" << endl;
        cout << endl << endl;
    }
}
