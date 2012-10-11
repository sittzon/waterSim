#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <math.h>
#include "model.h"

//#include <freeglut.h>

void buildPerspProjMat(float *m, float fov, float aspect, float znear, float zfar);
void Translate(float *m, float x, float y, float z);
void Rotate(float *m, char axis, float alpha);
void Rotate(float *m, Point axis, float alpha);
void multMatrix(float *m1, float* m2, float* m3);
void lookAt(float px, float py, float pz,
            float lx, float ly, float lz,
            float vx, float vy, float vz,
            float *m);
void createFBOAndBindTexture(unsigned int fboId, unsigned int rboId, unsigned int texId, const void* texData,
                             const unsigned int width, const unsigned int height);
int ifstreamLength(ifstream *is);

#endif
