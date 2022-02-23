#ifndef LIGHT_SOURCE
#define LIGHT_SOURCE

#include "Entity.hpp"
#include "Camera.hpp"

#include <map>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>


class GenericLight{
protected:
	static std::map<unsigned int, GenericLight*> light_list;// = std::map<int, GenericLight>(8);
public:

	static void enable_lighting();
	static GenericLight* get_light(GLenum);
	virtual void bind_light();
	virtual void reposition_light();
	static void reposition_lights();
	
	GLenum id;
	Entity* bind_to_entity;
	GLfloat* light_position;
	GLfloat* ambient;
	GLfloat* diffuse;
	GLfloat* specular;
	GLfloat shininess;
	GLfloat fog;

	GenericLight(GLenum id,GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess, GLfloat fog, GLfloat* position) {
		this->id = id;
		this->ambient=ambient;
		//printf("%f %f %f %f\n", position[0], position[1], position[2], position[3]);
		this->diffuse = diffuse;
		this->specular=specular;
		this->shininess = shininess;
		this->fog = fog;
		this->light_position=position;
		light_list.emplace(id, this);
	}
	GenericLight(GLenum id,Entity* trace_entity, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess, GLfloat fog) {
		//this->bind_to_camera = follow_camera;
		this->ambient = ambient;
		//printf("%f %f %f %f\n", this->ambient[0], this->ambient[1], this->ambient[2], this->ambient[3]);
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
		this->fog = fog;
		light_list.emplace(id, this);
		//this->light_position = ambient;
		//this->light_position[0] = follow_camera->getPosition(0);
		//this->light_position[1] = follow_camera->getPosition(1);
		//this->light_position[2] = follow_camera->getPosition(2);
		//this->light_position[3] = 1;
	}
	~GenericLight() {
		printf("GenericLight deleted\n");
	}
	static void End() {
		light_list.begin();
		for (auto e = light_list.begin(); e != light_list.end();e++) {
			delete (*e).second;
		}
		//for (int i = 0; i < light_list.size(); i++)
			//delete light_list[i];
	}
};

class Spotlight : public GenericLight{
	GLfloat* spot_position;
	GLfloat spot_cutoff;
	GLfloat spot_aperture;

	Spotlight(GLenum id, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess, GLfloat fog, GLfloat* position,
		GLfloat* spot_position, GLfloat spot_cutoff, GLfloat spot_aperture)
		:GenericLight(id,ambient,diffuse,specular,shininess,fog,position){
		this->spot_position = spot_position;
		this->spot_cutoff = spot_cutoff;
		this->spot_aperture = spot_aperture;
	}

	/*static void enable_lighting();
	static void bind_light(GLenum light_number);
	static void bind_light(GenericLight* light);
	void reposition_light();
	static void reposition_light(GenericLight* l);
	static void reposition_light(GLenum light_number);
	static void enable(GLenum light_num);
	static void enable(GenericLight*);
	static void disable(GenericLight*);
	static void disable(GLenum light_num);*/
};


class DirectedLight : public GenericLight{

};

#endif // !LIGHT_SOURCE