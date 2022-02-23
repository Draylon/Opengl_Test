#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM


#include "Texture.hpp"
#include "Model.hpp"
#include <list>
#include <thread>

#include <glm/glm.hpp>
#include <GL/glut.h>

#define PI180 0.01745329

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
	glm::vec3 velocity;
	glm::vec3 position;
	unsigned int lifetime;
};

struct FireworkParticle {
	glm::vec3 velocity;
	glm::vec3 position;
	unsigned int lifetime;
	unsigned int status;
};

class GenericParticle {
protected:
	unsigned int swirl_cycles;
public:
	bool reset_particle;
	unsigned int default_ammount;
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
	unsigned int swirl_cycle;
	GLfloat displacement;
	glm::vec3* gravity;

	GenericParticle* clone() {
		return new GenericParticle(*this);
	}
	GenericParticle(bool reset_particles,unsigned int ammount,unsigned int lifetime,
		GLfloat randomness,GLfloat emiter_radius, glm::vec3 color, GLfloat weight, 
		GLfloat start_velocity,glm::vec3 position,glm::vec3 direction, 
		GLfloat swirl,unsigned int swirl_cycle, GLfloat displacement){
		this->position = position;
		this->ammount = ammount;
		this->default_ammount = ammount;
		this->lifetime = lifetime;
		this->randomness=randomness;
		this->emiter_radius = emiter_radius;
		this->color = color;
		this->weight = weight;
		this->start_velocity = start_velocity;
		this->direction = glm::normalize(direction);
		this->swirl = swirl;
		this->swirl_cycle = swirl_cycle;
		this->displacement = displacement;
		this->reset_particle = reset_particles;
		swirl_cycle = 0;

		GenericParticle::part_list.push_back(this);
	}
	~GenericParticle() {
		printf("Particle removed\n");
	}

	static void End() {
		for (int i = 0; i < part_list.size(); i++) {
			delete part_list[i];
		}
	}
	virtual void EndAnimation() {
		//particle_update_active = false;
		//if (particle_update.joinable()) particle_update.join();
	}

	void createParticleArray();
	void drawParticles();

private:
	static std::vector<GenericParticle*> part_list;
};

class DirectedParticle :public GenericParticle {
private:
	static std::list<DirectedParticle*> rendering_list;
	static std::thread particle_update;
	static bool particle_update_active;

	glm::vec3 normal,plane;
protected:
public:
	SingularParticle* particles;
	GLfloat dot_radius;
	DirectedParticle(bool reset_particles,unsigned int ammount, unsigned int lifetime, GLfloat randomness, GLfloat emiter_radius, glm::vec3 color, GLfloat weight, GLfloat start_velocity,glm::vec3 position, glm::vec3 direction, GLfloat swirl,unsigned int swirl_cycle, GLfloat displacement,
		GLfloat dot_radius)
		:GenericParticle(reset_particles,ammount,lifetime,randomness,emiter_radius, color, weight, start_velocity,position, direction, swirl,swirl_cycle, displacement) {
		this->dot_radius = dot_radius;
		particles = NULL;
	}
	DirectedParticle* clone() {
		return new DirectedParticle(*this);
	}
	void animate();
	void pre_animate();
	void stop_animation(){
		if (particles != NULL) {
			rendering_list.remove(this);
			free(particles);
		}
	}
	~DirectedParticle(){
		if (particles != NULL) {
			//printf("leaving list\n");
			rendering_list.remove(this);
			//printf("deleting partc\n");
			free(particles);
			//printf("deleted partc\n");
			if (rendering_list.size() == 0) {
				particle_update_active = false;
				if (particle_update.joinable()) particle_update.join();
			}
		}
	}
	static void EndAnimation() {
		if (particle_update_active) {
			particle_update_active = false;
			if (particle_update.joinable()) particle_update.join();
		}
	}
	void createParticleArray();
	void drawParticles();
	static void updateParticles();
	void resetParticle(int);
	static void render_all();
};

class DotParticle : public DirectedParticle {
public:
	
	DotParticle(bool reset_particles,unsigned int ammount, unsigned int lifetime, GLfloat randomness, glm::vec3 color, GLfloat weight, GLfloat start_velocity, glm::vec3 position, GLfloat swirl,unsigned int swirl_cycle, GLfloat displacement,GLfloat dot_radius)
		:DirectedParticle(reset_particles,ammount, lifetime, randomness, 0, color, weight, start_velocity, position, glm::vec3(0,0,0), swirl,swirl_cycle, displacement, dot_radius) {
		//construtor
	}
	~DotParticle() {}
	DotParticle* clone(){
		return new DotParticle(*this);
	}
};

class PolygonParticle : public GenericParticle{
private:
	Texture* texture;
	Model* shape;
public:
	PolygonParticle(bool reset_particles,unsigned int ammount,unsigned int lifetime,GLfloat randomness,
		GLfloat emiter_radius,glm::vec3 color,GLfloat weight,GLfloat start_velocity,
		glm::vec3 position,glm::vec3 direction,GLfloat swirl,
		unsigned int swirl_cycle,GLfloat displacement,Texture* texture,Model* shape)
		:GenericParticle(reset_particles,ammount,lifetime,randomness,emiter_radius,color, weight, start_velocity, position, direction, swirl,swirl_cycle, displacement) {
		this->texture = texture;
		this->shape = shape;
	}
};

class Smoke: public DirectedParticle {
	Smoke(): DirectedParticle(true,300, 30, 0.15f, 0.2f,
		glm::vec3(1, 0.6, 0.2), -0.00001f, 0.2f,
		glm::vec3(5, 0, -4), glm::vec3(0, 1, 0),
		0,0, 0.08f, 0.8f){}
};

class Snow: public DirectedParticle{
	Snow():DirectedParticle(true,300, 30, 0.15f, 0.2f,
		glm::vec3(1, 0.6, 0.2), -0.00001f, 0.2f,
		glm::vec3(5, 0, -4), glm::vec3(0, 1, 0),
		0,0, 0.08f, 0.8f){}
};


class Firework {
private:
	std::vector<DotParticle*> trail_particles;
	std::vector<DotParticle*> explosion_particles;
	FireworkParticle* firework_particle;
	DotParticle* trail_template;
	DotParticle* explosion_template;

	static std::list<Firework*> rendering_list;
	static std::thread firework_update;
	static bool firework_update_active;

	glm::vec3 normal, plane;
protected:
	bool reset_firework;
public:
	unsigned int ammount;
	unsigned int lifetime;
	GLfloat emiter_radius;
	glm::vec3 position;
	GLfloat start_velocity;
	glm::vec3 direction;
	glm::vec3* gravity;
	
	Firework(DotParticle* trail,DotParticle* explosion,bool reset_fireworks,
		unsigned int ammount, unsigned int lifetime, GLfloat emiter_radius, 
		GLfloat start_velocity,glm::vec3 position, glm::vec3 direction){
		this->trail_template= trail;
		this->explosion_template= explosion;
		this->reset_firework = reset_fireworks;

		this->position = position;
		this->ammount = ammount;
		this->lifetime = lifetime;
		this->emiter_radius = emiter_radius;
		this->start_velocity = start_velocity;
		this->direction = glm::normalize(direction);

		trail_particles = std::vector<DotParticle*>(ammount);
		explosion_particles= std::vector<DotParticle*>(ammount);
	}
	//void func_animation();
	void stop_animation() {
		if (firework_particle != NULL){
			rendering_list.remove(this);
			free(firework_particle);
			for (int i = 0; i < ammount; i++) {
				delete trail_particles[i];
				delete explosion_particles[i];
			}
		}
	}
	static void EndAnimation() {
		if (firework_update_active) {
			firework_update_active = false;
			if (firework_update.joinable()) firework_update.join();
		}
	}
	~Firework() {
		if (firework_particle != NULL){
			rendering_list.remove(this);
			free(firework_particle);
			for (int i = 0; i < ammount; i++) {
				delete trail_particles[i];
				delete explosion_particles[i];
			}

			if (rendering_list.size() == 0) {
				firework_update_active = false;
				if (firework_update.joinable()) firework_update.join();
			}
		}
		printf("Firework removed\n");
	}
	void animate();
	void createFireworkArray();
	static void updateFireworks();
	void resetFirework(int);
};

#endif