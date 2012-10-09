#ifndef UTILS_CPP_INCLUDED
#define UTILS_CPP_INCLUDED

#include <iostream>
#include <math.h>
#include "utils.h"

using namespace std;

//Generate projection/camera matrix
void buildPerspProjMat(float *m, float fov, float aspect, float znear, float zfar)
{
  float xymax = znear * tan(fov * 3.1415f/360.0f);
  float ymin = -xymax;
  float xmin = -xymax;

  float width = xymax - xmin;
  float height = xymax - ymin;

  float depth = zfar - znear;
  float C = -(zfar + znear) / depth;
  float D = -2 * (zfar * znear) / depth;

  float w = 2 * znear / width;
  w = w / aspect;
  float h = 2 * znear / height;

  m[0]  = w; m[1]  = 0; m[2]  = 0;  m[3]  = 0;
  m[4]  = 0; m[5]  = h; m[6]  = 0; m[7]  = 0;
  m[8]  = 0; m[9]  = 0; m[10] = C; m[11] = D;
  m[12] = 0; m[13] = 0; m[14] = -1; m[15] = 0;
}

//Generate 4x4 translation matrix
void Translate(float *m, float x, float y, float z)
{
	m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = x;
	m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = y;
	m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = z;
	m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

//Generate 4x4 rotation matrix around fixed axis
void Rotate(float *m, char axis, float alpha)
{
	if (axis == 'x')
	{
		m[0] = 1.0f; m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
		m[4] = 0.0f; m[5] = cos(alpha); m[6] = -sin(alpha); m[7] = 0.0f;
		m[8] = 0.0f; m[9] = sin(alpha); m[10] = cos(alpha); m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
	}
	else if (axis == 'y')
	{
		m[0] = cos(alpha); m[1] = 0.0f; m[2] = sin(alpha); m[3] = 0.0f;
		m[4] = 0.0f; m[5] = 1.0f; m[6] = 0.0f; m[7] = 0.0f;
		m[8] = -sin(alpha); m[9] = 0.0f; m[10] = cos(alpha); m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
	}

	else if (axis == 'z')
	{
		m[0] = cos(alpha); m[1] = -sin(alpha); m[2] = 0.0f; m[3] = 0.0f;
		m[4] = sin(alpha); m[5] = cos(alpha); m[6] = 0.0f; m[7] = 0.0f;
		m[8] = 0.0f; m[9] = 0.0f; m[10] = 1.0f; m[11] = 0.0f;
		m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
	}
}

//Generate 4x4 rotation matrix around arbitrary axis
void Rotate(float *m, Point axis, float alpha)
{
	//Normalize axis
	axis.normalize();

	float c = cos(alpha);
	float c0 = 1-c;
	float s = sin(alpha);

	float x = axis.coord[0];
	float y = axis.coord[1];
	float z = axis.coord[2];

	m[0] = x*x*c0 + c;
	m[1] = x*y*c0 - z*s;
	m[2] = x*z*c0 + y*s;
	m[3] = 0.0f;

	m[4] = x*y*c0 + z*s;
	m[5] = y*y*c0 + c;
	m[6] = y*z*c0 - x*s;
	m[7] = 0.0f;

	m[8] = x*z*c0 - y*s;
	m[9] = y*z*c0 + x*s;
	m[10] = z*z*c0 + c;
	m[11] = 0.0f;

	m[12] = 0.0f;
	m[13] = 0.0f;
	m[14] = 0.0f;
	m[15] = 1.0f;

}

//Hard coded 4x4 matrix multiplication
void multMatrix(float *m1, float* m2, float* m3)
{
	m3[0] = m1[0]*m2[0]+m1[1]*m2[4]+m1[2]*m2[8]+m1[3]*m2[12];
	m3[1] = m1[0]*m2[1]+m1[1]*m2[5]+m1[2]*m2[9]+m1[3]*m2[13];
	m3[2] = m1[0]*m2[2]+m1[1]*m2[6]+m1[2]*m2[10]+m1[3]*m2[14];
	m3[3] = m1[0]*m2[3]+m1[1]*m2[7]+m1[2]*m2[11]+m1[3]*m2[15];

	m3[4] = m1[4]*m2[0]+m1[5]*m2[4]+m1[6]*m2[8]+m1[7]*m2[12];
	m3[5] = m1[4]*m2[1]+m1[5]*m2[5]+m1[6]*m2[9]+m1[7]*m2[13];
	m3[6] = m1[4]*m2[2]+m1[5]*m2[6]+m1[6]*m2[10]+m1[7]*m2[14];
	m3[7] = m1[4]*m2[3]+m1[5]*m2[7]+m1[6]*m2[11]+m1[7]*m2[15];

	m3[8] = m1[8]*m2[0]+m1[9]*m2[4]+m1[10]*m2[8]+m1[11]*m2[12];
	m3[9] = m1[8]*m2[1]+m1[9]*m2[5]+m1[10]*m2[9]+m1[11]*m2[13];
	m3[10] = m1[8]*m2[2]+m1[9]*m2[6]+m1[10]*m2[10]+m1[11]*m2[14];
	m3[11] = m1[8]*m2[3]+m1[9]*m2[7]+m1[10]*m2[11]+m1[11]*m2[15];

	m3[12] = m1[12]*m2[0]+m1[13]*m2[4]+m1[14]*m2[8]+m1[15]*m2[12];
	m3[13] = m1[12]*m2[1]+m1[13]*m2[5]+m1[14]*m2[9]+m1[15]*m2[13];
	m3[14] = m1[12]*m2[2]+m1[13]*m2[6]+m1[14]*m2[10]+m1[15]*m2[14];
	m3[15] = m1[12]*m2[3]+m1[13]*m2[7]+m1[14]*m2[11]+m1[15]*m2[15];
}

//Generate 4x4 lookAt matrix
void lookAt(float px, float py, float pz,
	float lx, float ly, float lz,
	float vx, float vy, float vz,
	float *m)
{
	//Create n = p - l, normal vector
	float nx = px - lx;
	float ny = py - ly;
	float nz = pz - lz;
	//Normalize n
	float divide = sqrt(nx*nx + ny*ny + nz*nz);
	nx = nx/divide;
	ny = ny/divide;
	nz = nz/divide;

	//Create u = crossproduct(v,n), right vector
	float ux = vy*nz - vz*ny;
	float uy = vz*nx - vx*nz;
	float uz = vx*ny - vy*nx;
	//Normalize u
	divide = sqrt(ux*ux + uy*uy + uz*uz);
	ux = ux/divide;
	uy = uy/divide;
	uz = uz/divide;

	//Create v = crossproduct(n,u), up vector
	vx = ny*uz - nz*uy;
	vy = nz*ux - nx*uz;
	vz = nx*uy - ny*ux;

	//Create u*p
	float up = ux*px + uy*py + uz*pz;
	//Create v*p
	float vp = vx*px + vy*py + vz*pz;
	//Create n*p
	float np = nx*px + ny*py + nz*pz;

	m[0] = ux; m[1] = uy; m[2] = uz; m[3] = -up;
	m[4] = vx; m[5] = vy; m[6] = vz; m[7] = -vp;
	m[8] = nx; m[9] = ny; m[10] = nz; m[11] = -np;
	m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
}

void createFBOAndBindTexture(GLuint fboId, GLuint rboId, GLuint texId, const GLvoid* texData, const unsigned int width, const unsigned int height)
{
    GLenum status;

    //Create texture
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    //glBindTexture(GL_TEXTURE_2D, 0);

    //Renderbuffer
    glGenRenderbuffers(1, &rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //Framebuffer
    glGenFramebuffers(1, &fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);

    //Check status
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE)
        cout << "Framebuffer construction error" << endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
 }

#endif



