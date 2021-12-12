#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include <glm/glm.hpp>
#include <GL/glut.h>

#include "Texture.hpp"
#include "Model.hpp"
#include <list>
#include <thread>

//polygon
	//particle type
		//particle poligon
			//particle texture
		//particle color
	//environment gravity
	//weight
	//start velocity

enum EmitterType {
	BIDIMENSIONAL,TRIDIMENSIONAL
};

struct SingularParticle {
	float x, y, z, vx, vy, vz;
	unsigned int lifetime;

} ;

class GenericParticle {
private:
	
public:
	unsigned int ammount;
	unsigned int lifetime;
	GLfloat randomness;
	GLfloat emiter_radius;
	glm::vec3 color;
	glm::vec3 position;
	GLfloat weight;
	GLfloat start_velocity;
	glm::vec3 direction;
	GLfloat swirl;
	GLfloat displacement;
	GenericParticle(unsigned int ammount,unsigned int lifetime,GLfloat randomness,GLfloat emiter_radius,glm::vec3 color, GLfloat weight, GLfloat start_velocity,glm::vec3 position,glm::vec3 direction, GLfloat swirl, GLfloat displacement) {
		this->position = position;
		this->ammount = ammount;
		this->lifetime = lifetime;
		this->randomness=randomness;
		this->emiter_radius = emiter_radius;
		this->color = color;
		this->weight = weight;
		this->start_velocity = start_velocity;
		this->direction = direction;
		this->swirl = swirl;
		this->displacement = displacement;
	}

	void createParticleArray();
	void drawParticles();
};

class DotParticle :public GenericParticle {
private:
	static std::list<DotParticle*> rendering_list;
	static std::thread particle_update;
	static bool particle_update_active;

	glm::vec3 normal,plane;
public:
	SingularParticle* particles;
	GLfloat dot_radius;
	DotParticle(unsigned int ammount, unsigned int lifetime, GLfloat randomness, GLfloat emiter_radius, glm::vec3 color, GLfloat weight, GLfloat start_velocity,glm::vec3 position, glm::vec3 direction, GLfloat swirl, GLfloat displacement,
		GLfloat dot_radius)
		:GenericParticle(ammount,lifetime,randomness,emiter_radius, color, weight, start_velocity,position, direction, swirl, displacement) {
		this->dot_radius = dot_radius;
		particles = (SingularParticle*) malloc(sizeof(SingularParticle)*ammount);
		rendering_list.push_back(this);
		if (!particle_update_active) {
			particle_update_active = true;
			particle_update = std::thread(updateParticles);
		}
	}
	~DotParticle() {
		free(particles);
		rendering_list.remove(this);
		if (rendering_list.size() == 0) {
			particle_update_active = false;
			if(particle_update.joinable()) particle_update.join();
		}
	}
	void createParticleArray();
	void drawParticles();
	static void updateParticles();
	void resetParticle(int);
	static void render_all();
};

class PolygonParticle : public GenericParticle{
private:
	Texture* texture;
	Model* shape;
public:
	PolygonParticle(unsigned int ammount,unsigned int lifetime,GLfloat randomness, GLfloat emiter_radius,glm::vec3 color,GLfloat weight,GLfloat start_velocity, glm::vec3 position,glm::vec3 direction,GLfloat swirl,GLfloat displacement,
		Texture* texture,Model* shape)
		:GenericParticle(ammount,lifetime,randomness,emiter_radius,color, weight, start_velocity, position, direction, swirl, displacement) {
		this->texture = texture;
		this->shape = shape;
	}

};

/*class Smoke {
};

class Snow {
};

class Firework {
};*/

#endif