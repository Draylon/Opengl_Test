#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <vector>
#include "Force.hpp"

class Physics {
private:
	static std::vector<Physics*> physics_actuators;

	std::vector<Force*> force_array;
	glm::vec3 frag_vector;
	void re_calculate();
public:
	static void End() {
		for (int i = 0; i < physics_actuators.size(); i++)
			delete physics_actuators[i];
	}
	void add_actuator(Force*);
	void remove_actuator(Force*);
	Physics() {
		physics_actuators.push_back(this);
	}

};

#endif