#include "Entity.hpp"
#include <list>
#include <thread>
#include <map>
#ifndef BOIDS_HPP
#define BOIDS_HPP

enum BoidSwarmBehaviour {
	SEEK_EACHOTHER, FLEE_EACHOTHER, SEEK_RANDOM, FLEE_RANDOM
};

class Boid {
	friend class ControlBoid;

	static std::vector<Boid*> boids_list;
	static std::list<Boid*> rendering_list;
	static std::thread boids_update;
	static bool boids_update_active;

	void add_seeker(Boid* b) { seek.push_back(b); }
	void add_fleeing(Boid* b) { flee.push_back(b); }

	//BoidParticle* boids;
	//glm::vec3 velocity;
	//glm::vec3 position;

	//boid can be chased around
	float seek_strength;
	float flee_strength;

	//boid 'gravitational pull/push' range
	float seek_range;
	float flee_range;
	bool auto_avoid_collision;

	static void updateGeneralTrajectory(); // boid controlado pelo algoritmo

	

	

	glm::vec3 color;
	Model* model;
	Physics* physics;
protected:
	std::vector<Boid*> seek;
	std::vector<Boid*> flee;

	glm::vec3 defaultPosition;
	glm::vec3* Position;
	
	glm::vec3 defaultFront;
	//glm::vec3 Up;
	glm::vec3 *Front;
	//glm::vec3 Right;
public:
	static void add_boid(Boid* boid) { boids_list.push_back(boid); }
	static void render_all();

	virtual void updatePosition(glm::vec3 pos) { *Position = pos; } // boid controlado por input
	virtual void updateFront(glm::vec3 pos) { *Front = pos; } // boid controlado por input
	virtual void updateTrajectory();

	Boid(glm::vec3 position,glm::vec3 front,glm::vec3 color,Model* model,Physics* physics,
		float seek_strength, float flee_strength,
		float seek_range, float flee_range,
		bool auto_avoid_collision = false)
	:model(model), physics(physics),color(color),
		seek_strength(seek_strength), flee_strength(flee_strength),
		seek_range(seek_range),flee_range(flee_range),
		auto_avoid_collision(auto_avoid_collision) {
		
		this->defaultPosition = position;
		this->defaultFront=front;
		this->Position = &defaultPosition;
		this->Front = &defaultFront;

		boids_list.push_back(this);
	}
	~Boid() {
		printf("Boid destructor called!\n");
		rendering_list.remove(this);
		//printf("deleting partc\n");
		//printf("deleted partc\n");
		if (rendering_list.size() == 0&& !boids_update_active) {
			boids_update_active = false;
			if (boids_update.joinable()) boids_update.join();
		}
	}
	virtual void render();
	static void animate();
	static void stop_animate();
	std::list<Boid*> generate_boid_swarm(unsigned int ammount);
	void set_swarm_behaviour(std::list<Boid*>,BoidSwarmBehaviour);
	

	static void End(){
		boids_update_active = false;
		if (boids_update.joinable()) boids_update.join();
		for (int i = 0; i < boids_list.size(); i++)
			delete boids_list[i];
	}
};

class ControlBoid : public Boid{
protected:
	PositionMovement* position;

public:
	ControlBoid(PositionMovement* positionObject, glm::vec3 color, Model* model, Physics* physics,
		float seek_strength, float flee_strength,
		float seek_range, float flee_range,
		bool auto_avoid_collision = false)
	:Boid(glm::vec3(0,0,0), glm::vec3(0, 0, 0),color,model,physics,seek_strength,flee_strength,seek_range,flee_range,auto_avoid_collision) {
		this->position = positionObject;
		this->Position = position->getPositionVec();
		this->Front = position->getOrientationVector(0);
	}


	void render();

	void updateTrajectory();

};
//

//
//class BoidSwarmGenerator {
//public:
//	//Boids* create_boid(Boids* control_boid);
//	void add_boid(Boid* control_boid);
//};


#endif