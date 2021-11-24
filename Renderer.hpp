#ifndef RENDERER_ENTITY
#define RENDERER_ENTITY
#include "Camera.hpp"

//#include "blender_snowman.cpp"

class Renderer {
public:
	static Renderer& getInstance();
	
	static void render_3D(void);
	//static void render_2D(void);
	static void render_HUD(void);

	static void setActiveCamera(EulerCamera* cam) { activeCamera = cam; }
	static EulerCamera getActiveCamera() { return activeCamera; }
private:
	static GLint width, height;
	Renderer(){}
	static Renderer* instance;
	static EulerCamera* activeCamera;

	//idéia pra fazer depois
	//talvez aumente muito o n° de instruções
	static void init(GLint, GLint);
	static void reshape(GLint, GLint);
	static void display();
};

#endif
