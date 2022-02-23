
#include "Model.hpp"
#include <GL/freeglut_std.h>

class Teapot : public Model {
public:
	Teapot() :Model() {

	}
	virtual void render() {
        glColor3f(0, 0, 1);
		glScalef(1, 1, -1);
		//glutWireTeapot(1.2);
        glutSolidTeapot(1.2);
	}
};