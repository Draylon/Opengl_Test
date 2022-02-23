#ifndef RENDERER_ENTITY
#define RENDERER_ENTITY
#include "Camera.hpp"
#include "Material.hpp"
#include <thread>

//#include "blender_snowman.cpp"

class Renderer {
public:

	//static Material* singular_material;

	static Renderer* getInstance();
	
	static void render_3D(void);
	//static void render_2D(void);
	static void render_HUD(void);

	static void setActiveCamera(Camera* cam) { activeCamera = cam; }
	static Camera* getActiveCamera() { return activeCamera; }

	static void updateScreen(void (*callback)());
	static void init(GLint*, GLint*);
	
	static void Stop();
	static unsigned int frames;
private:
	static bool fps_stop;
	static unsigned int fps;
	static std::thread fps_thread;
	static void fps_function();

	static GLint* width;
	static GLint* height;
	~Renderer() {
		fps_stop = true;
		if (fps_thread.joinable())
			fps_thread.join();
		printf("fps clock has been stopped\n");
	}

	Renderer(){ 
		fps_stop = false;
		frames = 0;
		fps = 0;
		fps_thread = std::thread(fps_function);
	}
	static Renderer* instance;
	static Camera* activeCamera;

	//idéia pra fazer depois
	//talvez aumente muito o n° de instruções
	
	static void reshape();
	static void display();
};

#endif
