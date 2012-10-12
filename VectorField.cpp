#include "VectorField.h"

#include "globals.h"
#include "utils.h"

#include "printOpenGLFBOError.h"

#include <iostream>

using namespace std;

VectorField::VectorField()
{
    model = NULL;
    fboId = 0;
}

VectorField::~VectorField()
{
    //dtor
}

void VectorField::init(GLuint* vectorFieldId, double xSpeed, double ySpeed, double zSpeed, double pressure)
{

    if(model == NULL)
    {
        model = getGlobal()->OH->loadObj("models/billboard.obj");
    }

    if(program == 0)
    {
        program = getGlobal()->SM->loadShaders("passThrough.vert", "initConstVectorField.frag");
    }

    if(fboId == 0)
    {
        createFBO(fboId);
        printOpenGLFBOError(fboId, "Create FBO in VectorField::init");

    }

    glUseProgram(program);

    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    glUniform1f(glGetUniformLocation(program, "xSpeed"), xSpeed);
    glUniform1f(glGetUniformLocation(program, "ySpeed"), ySpeed);
    glUniform1f(glGetUniformLocation(program, "zSpeed"), zSpeed);
    glUniform1f(glGetUniformLocation(program, "pressure"), pressure);

    for(int i = 0; i < getGlobal()->height; i++)
    {
        glBindTexture(GL_TEXTURE_2D, vectorFieldId[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vectorFieldId[i], 0);

        //Check status
        printOpenGLFBOError(fboId, "Drawing to texture in VectorField::init");

        getGlobal()->OH->drawModel(model);

        if (glGetError() != 0)
        {
            cout << "GLError in VectorField::init " << endl;
        }

    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return;
}
