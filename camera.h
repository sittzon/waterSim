#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>

#include "utils.h"


using namespace std;

class camera
{
	public:
		camera();

        void update();
		void rotate(GLfloat aH, GLfloat aV);
        void zoom(GLfloat scaling);
        void pan(GLfloat dx, GLfloat dy);

        Point pos;
        Point lookAt;

        float angleHorizontal;
        float angleVertical;
        float radius;

};

#endif
