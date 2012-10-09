#ifndef MODEL_CPP
#define MODEL_CPP
/*
#ifdef _WIN32
    //#include <windows.h>
   #define GLEW_STATIC
    #include <glew.h>
    #include <wglew.h>
    #include <freeglut.h>
#elif __APPLE__
    #include <OpenGL/gl3.h>
    #include <freeglut.h>
#else
*/

    //#include <GL/gl.h>
    //#include <GL/glut.h>

//#endif

#include "model.h"
#include <vector>

using namespace std;


gpuModel::gpuModel(float* verts, int vertSize, float* norms, int normSize, float* texc, int texcSize, int* inds, int indsSize, vector<face*> facesIn,
                 unsigned int vaoIn, unsigned int vboVertexIn, unsigned int vboNormalIn, unsigned int vboTextureIn, unsigned int vboIndiciesIn)
{

    // Set some values

    vao = vaoIn;
    vboVertex = vboVertexIn;
    vboNormal = vboNormalIn;
    vboTexture = vboTextureIn;
    vboIndicies = vboIndiciesIn;

    // Copy all relevant data to the GPU version

    verticesSize    = vertSize;
    normalsSize     = normSize;
    texCoordsSize   = texcSize;
    facesSize       = facesIn.size();

    // Copy vertices
    vertices = new float[vertSize*3];
    for(int i = 0; i < vertSize*3 ; i++)
    {
        vertices[i] = verts[i];
    }

    // Copy normals
    normals = new float[normSize*3];
    for(int i = 0; i < normSize*3 ; i++)
    {
        normals[i] = norms[i];
    }

    // Copy texture coordinates.
    texCoords = new float[texcSize*2];
    for(int i = 0; i < texcSize*2 ; i++)
    {
        texCoords[i] = texc[i];
    }

    // Copy indices.
    indices = new int[indsSize*3];
    for(int i = 0; i < indsSize*3 ; i++)
    {
        indices[i] = inds[i];
    }

    //Copy faces.
    faces = facesIn;


    // If the data is in the vrong format, e.i. not one normal per vertex, fix this.

    if(normalsSize > verticesSize)
	{

        //One vertex per normal.
	    vector<Point> newVerticies (facesSize*3, Point(0.0f, 0.0f, 0.0f));
	    vector<Point> newNormals (facesSize*3, Point(0.0f, 0.0f, 0.0f));

        face *f;

        for (unsigned int i = 0; i < facesSize; i++)
        {
            f = faces[i];
            for (int j = 0; j < 3; j++)
            {
                // Create multiple verticies to handle more than one normal

                (newVerticies[3*i+j])[0]     = vertices[3*(f->vertIndex.vert[j])+0];
                (newVerticies[3*i+j])[1]     = vertices[3*(f->vertIndex.vert[j])+1];
                (newVerticies[3*i+j])[2]     = vertices[3*(f->vertIndex.vert[j])+2];

                (newNormals[3*i+j])[0]       = normals[3*(f->normIndex.vert[j])+0];
                (newNormals[3*i+j])[1]       = normals[3*(f->normIndex.vert[j])+1];
                (newNormals[3*i+j])[2]       = normals[3*(f->normIndex.vert[j])+2];
                indices[3*i+j] = 3*i+j;
            }

        }

        vertices = new float[newVerticies.size()*3];
        normals = new float[newNormals.size()*3];

        // Set the new vertices.
        for (unsigned int i = 0; i < newVerticies.size(); i++)
        {
            Point tempVert = newVerticies[i];
            for (int j = 0; j < 3; j++)
            {
                vertices[3*i+j] = tempVert.coord[j];
            }
        }

        // Set the new normals.
        for (unsigned int i = 0; i < newNormals.size(); i++)
        {
            Point tempNormal = newNormals[i];
            for (int j = 0; j < 3; j++)
            {
                normals[3*i+j] = tempNormal.coord[j];
            }
        }

        // Update sizes.
        normalsSize = newNormals.size();
        verticesSize = newVerticies.size();
	}

}

gpuModel::~gpuModel()
{
    // Deletes all pointers, and sets them to NULL.

    if(vertices != NULL)
    {
        delete vertices;
        vertices = NULL;
    }
    if(normals != NULL)
    {
        delete normals;
        normals = NULL;
    }
    if(texCoords != NULL)
    {
        delete texCoords;
        texCoords = NULL;
    }
    if(indices != NULL)
    {
        delete indices;
        indices = NULL;
    }
}

void gpuModel::uploadToGPU()
{

    //Uploads the this model (modified to fit OpenGl standard) to the GPU.

	glBindVertexArray(vao);

	//VBO for vertex data
	//-------------------
	glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
	glBufferData(GL_ARRAY_BUFFER, verticesSize*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	/*
	glVertexAttribPointer(glGetAttribLocation(program, pos), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, pos));
    */

	//VBO for texture data
	//--------------------
	if(texCoordsSize > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboTexture);
		glBufferData(GL_ARRAY_BUFFER, texCoordsSize*2*sizeof(GLfloat), texCoords, GL_STATIC_DRAW);
        /*
        if(glGetAttribLocation(program, texture) == -1)
        {
            // No code for handeling texture in shader, may be declared but optimised out.
        } else {
            // Code for handeling texture in shader, upload texture coordinates.
            glVertexAttribPointer(glGetAttribLocation(program, texture), 2, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(glGetAttribLocation(program, texture));
        }
        */
	}

	//VBO for normal data
	//-------------------
	if(normalsSize > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
		glBufferData(GL_ARRAY_BUFFER, normalsSize*3*sizeof(GLfloat), normals, GL_STATIC_DRAW);
        /*
        if(glGetAttribLocation(program, normal) == -1)
        {
            // No code for handeling normals in shader, may be declared but optimised out.
        } else {
            // Code for handeling normals in shader, upload normals.
            glVertexAttribPointer(glGetAttribLocation(program, normal), 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(glGetAttribLocation(program, normal));
        }
        */
	}

	//VBO for indices data
	//--------------------
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicies);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesSize*3*sizeof(GLuint), indices, GL_STATIC_DRAW);

    return;
}

/*
void gpuModel::uploadToGPUforDrawingNormals(unsigned int program, char* pos, char* normal)
{

    // Uploads the this model (modified to fit OpenGl standard) to the GPU.

	glBindVertexArray(vao);
	glEnableClientState(GL_VERTEX_ARRAY);

	//VBO for vertex data
	//-------------------
	glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
	glBufferData(GL_ARRAY_BUFFER, verticesSize*3*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, pos), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(glGetAttribLocation(program, pos));

	//VBO for normal data
	//-------------------
	if(normalsSize > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
		glBufferData(GL_ARRAY_BUFFER, normalsSize*3*sizeof(GLfloat), normals, GL_STATIC_DRAW);
		glVertexAttribPointer(glGetAttribLocation(program, normal), 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(glGetAttribLocation(program, normal));
	}

	//VBO for indices data
	//--------------------
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicies);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesSize*3*sizeof(GLuint), indices, GL_STATIC_DRAW);

    return;

}
*/

Model::Model()
{
    //Initialize unity matrix
    modelMatrix = *new Mat;
    modelMatrix[0]  = 1.0f;
    modelMatrix[5]  = 1.0f;
    modelMatrix[10] = 1.0f;
    modelMatrix[15] = 1.0f;

    drawNormals = false;
}

Model::~Model()
{
    if (vertices != NULL)
    {
        delete vertices;
        vertices = NULL;
    }

    if (normals != NULL)
    {
        delete normals;
        normals = NULL;
    }

    if (texCoords != NULL)
    {
        delete texCoords;
        texCoords = NULL;
    }

    if (indices != NULL)
    {
        delete indices;
        indices = NULL;
    }

    if(drawNormals)
    {
        //getGlobal()->DNH->removeModel(this);
        drawNormals = false;
    }
}

void Model::setModelMat(Mat newMat)
{
    modelMatrix = newMat;
    return;
}

void Model::multModelMat(const Mat newMat)
{
    modelMatrix *= newMat;
    return;
}


Point Model::getVertex(int vertexID)
{
    Point res = *new Point(3);

    res[0] = vertices[3*vertexID + 0];
    res[1] = vertices[3*vertexID + 1];
    res[2] = vertices[3*vertexID + 2];

    return res;
}


void Model::setVertex(int vertexID, Point newVertex)
{
    vertices[3*vertexID + 0] = newVertex[0];
    vertices[3*vertexID + 1] = newVertex[1];
    vertices[3*vertexID + 2] = newVertex[2];

    return;
}

gpuModel* Model::makeGPUModel()
{
    return new gpuModel(vertices, verticesSize, normals, normalsSize, texCoords, texCoordsSize, indices, facesSize, faces,
                                  vao, vboVertex, vboNormal, vboTexture, vboIndicies);
}

void Model::reBindBufferObject()
{

    // Creates a special GPU version of this model, since OpenGL doesn't handle our internal format.

    // Create gpu version.
    gpuModel *gpum = new gpuModel(vertices, verticesSize, normals, normalsSize, texCoords, texCoordsSize, indices, facesSize, faces,
                                  vao, vboVertex, vboNormal, vboTexture, vboIndicies);


    // Upload the gpu version.
    gpum->uploadToGPU();

    // Delete the GPU version.
    if(NULL != gpum)
    {
        delete gpum;
        gpum = NULL;
    }

    // The following is for drawing normals
    /*
    if(drawNormals)
    {
        gpuModel *drawNormalsGpum = new gpuModel(vertices, verticesSize, normals, normalsSize, texCoords, texCoordsSize, indices, facesSize, faces,
                                        drawNormalsVao, drawNormalsVboVertex, drawNormalsVboNormal, 0, drawNormalsVboIndicies);
//      glUseProgram(getGlobal()->normalsProgram);
        drawNormalsGpum->uploadToGPUforDrawingNormals(getGlobal()->normalsProgram, "inPosition", "inNormal");

        // Delete the draw normals GPU version.
        if(NULL != drawNormalsGpum)
        {
            delete drawNormalsGpum;
            drawNormalsGpum = NULL;
        }
    }
    */

    return;
}


void Model::startDrawingModelsNormals()
{
    if(!drawNormals)
    {
        //getGlobal()->DNH->addModel(this);
    }
    drawNormals = true;
}

void Model::stopDrawingModelsNormals()
{
    if(drawNormals)
    {
        //getGlobal()->DNH->removeModel(this);
    }
    drawNormals = false;
}

#endif
