#ifndef SHADER_MANAGER_CPP
#define SHADER_MANAGER_CPP

#include <iostream>
#include <fstream>
#include <iomanip>
//#include <stdio.h>
#include <string.h>

#include "ShaderManager.h"

//using namespace std;

ShaderManager::ShaderManager(void)
{
}

ShaderManager::~ShaderManager(void)
{
}

GLuint ShaderManager::loadShaders(const string vert, const string frag)
{
	//Read shaders from file
	//----------------------
	const GLchar *vertFile = readFile(vert);
	const GLchar *fragFile = readFile(frag);

	if (*vertFile != 0 && *fragFile != 0) //No error during reading
	{
		//Create shaders and compile
		//--------------------------
		vs = glCreateShader(GL_VERTEX_SHADER);  //Fel!
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vs, 1, &vertFile, NULL);
		glShaderSource(fs, 1, &fragFile, NULL);
		glCompileShader(vs);
		glCompileShader(fs);

		//Shaders compiled successfully?
		//------------------------------

		GLint status;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &status);

        // Improving readability.
		cout << "//------------" << endl;
		cout << "Shaders: " << vert << endl << "         " << frag << endl;

		if (status)
		   cout << "Vertex shader compiled successfully	-	OK\n";
		else
		{
			cout << "Vertex shader compiled unsuccessfully	-	0\n";
			printShaderInfoLog(vs);
		}
		glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
		if (status)
		   cout << "Fragment shader compiled successfully	-	OK\n";
		else
		{
			cout << "Fragment shader compiled unsuccessfully	-	0\n";
			printShaderInfoLog(fs);
		}

		//Attach shaders and link program
		//-------------------------------
		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		//Program compiled and linked successfully?
		//-----------------------------------------
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status)
			cout << "Shader program linked successfully	-	OK\n";
		else
		{
			cout << "Shader program unsuccessfully linked	-	0\n";
			printProgramInfoLog(program);
		}

        // To improve readability
		cout << "//------------" << endl << endl;
	}
	else
	{
		cout << "ShaderManager Error: Could not read shader files";
	}

	//delete(vertFile);
	//delete(fragFile);

	return program;
}

GLuint ShaderManager::loadShaders(const string vert,  const string geom, const string frag)
{
	//Read shaders from file
	//----------------------
	const GLchar *vertFile = readFile(vert);
	const GLchar *geomFile = readFile(geom);
	const GLchar *fragFile = readFile(frag);

	if (*vertFile != 0 && *geomFile != 0 && *fragFile != 0) //No error during reading
	{
		//Create shaders and compile
		//--------------------------
		vs = glCreateShader(GL_VERTEX_SHADER);
		gs = glCreateShader(GL_GEOMETRY_SHADER);
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vs, 1, &vertFile, NULL);
		glShaderSource(gs, 1, &geomFile, NULL);
		glShaderSource(fs, 1, &fragFile, NULL);
		glCompileShader(vs);
		glCompileShader(gs);
		glCompileShader(fs);

		//Shaders compiled successfully?
		//------------------------------
		GLint status;
		glGetShaderiv(vs, GL_COMPILE_STATUS, &status);

		cout << "Shaders: " << vert << endl << "         " << geom << endl << "         " << frag << endl;
		cout << "//------------" << endl;

		if (status)
		   cout << "Vertex shader compiled successfully	-	OK\n";
		else
		{
			cout << "Vertex shader compiled unsuccessfully	-	0\n";
			printShaderInfoLog(vs);
		}
		glGetShaderiv(gs, GL_COMPILE_STATUS, &status);
		if (status)
		   cout << "Gemoetry shader compiled successfully	-	OK\n";
		else
		{
			cout << "Gemoetry shader compiled unsuccessfully	-	0\n";
			printShaderInfoLog(gs);
		}
		glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
		if (status)
		   cout << "Fragment shader compiled successfully	-	OK\n";
		else
		{
			cout << "Fragment shader compiled unsuccessfully	-	0\n";
			printShaderInfoLog(fs);
		}

		//Attach shaders and link program
		//-------------------------------
		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, gs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		//Program compiled and linked successfully?
		//-----------------------------------------
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status)
			cout << "Shader program linked successfully	-	OK\n";
		else
		{
			cout << "Shader program unsuccessfully linked	-	0\n";
			printProgramInfoLog(program);
		}

        // To improve readability
		cout << "//------------" << endl << endl;
	}
	else
	{
		cout << "ShaderManager Error: Could not read shader files";
	}

	return program;
}

void ShaderManager::printShaderInfoLog(GLuint object)
{
	int infoLength = 0;
	char *infoLog;

	glGetShaderiv(object, GL_INFO_LOG_LENGTH, &infoLength);

	if (infoLength > 0)
	{
		infoLog = (char *)malloc(infoLength);
		glGetShaderInfoLog(object, infoLength, &infoLength, infoLog);
		cout << infoLog;
		free(infoLog);
	}
}

void ShaderManager::printProgramInfoLog(GLuint object)
{
	int infoLength = 0;
	char *infoLog;

	glGetProgramiv(object, GL_INFO_LOG_LENGTH, &infoLength);

	if (infoLength > 0)
	{
		infoLog = (char *)malloc(infoLength);
		glGetProgramInfoLog(object, infoLength, &infoLength, infoLog);
		cout << infoLog;
		free(infoLog);
	}
}

GLchar* ShaderManager::readFile(const string filename)
{
	ifstream file(filename.c_str());
	//int count = 0;
	char *buf;
	string fileContents = "";
	string tempLine = "";

	if (file.is_open() == true)
	{
	    while(file.good())
	    {
	        getline(file, tempLine);
            fileContents.append(tempLine);
            fileContents.append("\n");
	    }

	    buf = new char [fileContents.size() + 1];
	    strcpy(buf, fileContents.c_str());

	    return buf;
	}

	else
	{
        cerr << "ShaderManager Error: Could not read shader file " << filename << endl;
		return 0;
	}
}

#endif
