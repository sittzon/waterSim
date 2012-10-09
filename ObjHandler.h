#ifndef OBJ_HANDLER_H
#define OBJ_HANDLER_H

//---------------------------------------------------------------------------------
//ObjHandler.h, ObjHandler.cpp
//
//Reads and writes vertex, normal, texture and face information from/to a .obj file.
//
//v - Vertex, specified as three floats
//vn - Vertex normal vector
//vt - Texture coordinate
//f - Face
//---------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include <glew.h>

//#include <GL/gl.h>
//#include <freeglut.h>
//#include <GL/glut.h>

#include "model.h"
#include "vectorUtils.h"

using namespace std;

class Model;
class gpuModel;

class face
{
    public:
    face();
    ~face();
    face(const face &in);

    int nr;

    Indice vertIndex, normIndex, texIndex;

    void setVertValue(int index, int value);
    void setNormValue(int index, int value);
    void setTexValue(int index, int value);

};

class ObjHandler
{
	public:
		ObjHandler();
		ObjHandler(string filename);
		~ObjHandler();

		Model* loadObj(const string filename);

        void loadObjectsNamed(vector<string> names);

        void createObj(int type, Point* pos, float scale);
        void loadObjAt(const string filename, Point* pos, float scale);

		void writeObj(string filename, Model *m);
		void drawModel(Model *m);

	private:
		int init(const string filename);

		Point setVertex(string file);
		Point setNormal(string file);
		Point setTexCoord(string file);
		int setMaterial(string materialFileName);

		face* createFace(string file, int numNormals, int numTexCoords);
		void createNormals();       //Create Normals Function

        void clearAllData();

		float* getVertices();		//Returns vertices as a float array, sets size as vertices size
		float* getTexCoords();		//Returns texture coordinates as a float array, sets size as texCoords size
		float* getNormals();		//Returns normals as a float array, sets size as normals size
		int* getIndices();		    //Returns faces as a float array, sets size as faces size

		//Class member variables
		vector<Point> vertices, normals, texCoords;
		vector<face*> faces;
};

#endif
