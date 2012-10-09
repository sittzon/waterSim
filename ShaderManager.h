#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

//---------------------------------------------------------------------------
//ShaderManager.h, ShaderManager.cpp
//
//Manages shader information, compiles and links vertex and fragment shaders.
//
//
//---------------------------------------------------------------------------

#include <string>
#include <cstdlib>

#include <glew.h>

//#include <freeglut.h>
/*
#ifdef _WIN32
    #include <windows.h>
   #define GLEW_STATIC
    #include <glew.h>
    #include <wglew.h>
    #include <freeglut.h>
#elif __APPLE__
    #include <OpenGL/gl3.h>
    #include <freeglut.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
#endif
*/

using namespace std;

class ShaderManager
{
	public:
		ShaderManager(void);
		~ShaderManager(void);

		GLuint loadShaders(const string vert, const string frag);	                    //Returns a program handle for vertex and fragment shader
		GLuint loadShaders(const string vert,  const string geom, const string frag);   //Returns a program handle for vertex, geometry and fragment shader
		GLchar* readFile(const string filename);					                    //Returns a char pointer of a shader file from disk
		void printShaderInfoLog(GLuint object);						                    //Prints shader info log
		void printProgramInfoLog(GLuint object);					                    //Prints program info log

	private:
		GLuint vs;		//Vertex Shader
		GLuint gs;		//Geometry Shader
		GLuint fs;		//Fragment Shader
		GLuint program; //Shader Program
};

#endif
