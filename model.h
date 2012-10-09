#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "ObjHandler.h"
#include "vectorUtils.h"

using namespace std;

class face;

class gpuModel
{
    public:
        gpuModel(float* verts, int vertSize, float* norms, int normSize, float* texCoords, int texCoordSize, int* inds, int indsSize, vector<face*> facesIn,
                 unsigned int vao, unsigned int vboVertex, unsigned int vboNormal, unsigned int vboTexture, unsigned int vboIndicies);
        ~gpuModel();

        float* vertices;
        float* normals;
        float* texCoords;

        int* indices;

        unsigned int verticesSize;
        unsigned int normalsSize;
        unsigned int texCoordsSize;
        unsigned int facesSize;

		vector<face*> faces;

        unsigned int vao, vboVertex, vboNormal, vboTexture, vboIndicies;
        unsigned int drawNormalsVao, drawNormalsVboVertex, drawNormalsVboNormal, drawNormalsVboIndicies;

        void uploadToGPU();
        void uploadToGPUforDrawingNormals();
};

class Model
{
    public:
        Model();
        ~Model();

    //private:
        float* vertices;
        float* normals;
        float* texCoords;

        int* indices;

		vector<face*> faces;

        string name;

        Mat modelMatrix;

        void setModelMat(Mat newMat);
        void multModelMat(Mat newMat);

        Point getVertex(int vertexID);
        void setVertex(int vertexID, Point newVertex);
        gpuModel* makeGPUModel();
        void reBindBufferObject();

        unsigned int verticesSize, normalsSize, texCoordsSize, facesSize;

        unsigned int vao, vboVertex, vboNormal, vboTexture, vboIndicies;
        unsigned int drawNormalsVao, drawNormalsVboVertex, drawNormalsVboNormal, drawNormalsVboIndicies;

        float kAmb, kDiff, kSpec;

        bool drawNormals;

        void startDrawingModelsNormals();
        void stopDrawingModelsNormals();

};

#endif
