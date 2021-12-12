#ifndef LIGHT_SOURCE
#define LIGHT_SOURCE

#include <map>
#include <GL/freeglut.h>
#include "Camera.hpp"


class GenericLight{
public:
	static std::map<int, GenericLight*> light_list;// = std::map<int, GenericLight>(8);

	static void enable_lighting();
	void bind_light(GLenum light_number);
	static void reposition_light(GLenum light_number);

	Camera* bind_to_camera;
	GLfloat* light_position;
	GLfloat* ambient;
	GLfloat* diffuse;
	GLfloat* specular;
	GLfloat shininess;
	GLfloat fog;

	GenericLight(GLfloat ambient[],GLfloat diffuse[],GLfloat specular[],GLfloat shininess,GLfloat fog,GLfloat position[]) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
		this->fog = fog;
		this->light_position = position;

	}
	GenericLight(Camera* follow_camera, GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess, GLfloat fog) {
		//this->bind_to_camera = follow_camera;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
		this->fog = fog;
		//this->light_position = ambient;
		//this->light_position[0] = follow_camera->getPosition(0);
		//this->light_position[1] = follow_camera->getPosition(1);
		//this->light_position[2] = follow_camera->getPosition(2);
		//this->light_position[3] = 1;
	}
};

class Spotlight : public GenericLight{
	GLfloat* spot_position;
	GLfloat spot_cutoff;
	GLfloat spot_aperture;

	Spotlight(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess, GLfloat fog, GLfloat position[],
		GLfloat spot_position[], GLfloat spot_cutoff, GLfloat spot_aperture
		):GenericLight(ambient,diffuse,specular,shininess,fog,position){
		this->spot_position = spot_position;
		this->spot_cutoff = spot_cutoff;
		this->spot_aperture = spot_aperture;
	}
};


class DirectedLight : public GenericLight{

};

#endif // !LIGHT_SOURCE
