#include "Physics.hpp"

std::vector<Physics*> Physics::physics_actuators;

void Physics::add_actuator(Force* f) {
	this->force_array.push_back(f);
}

void Physics::remove_actuator(Force* f) {
}

void Physics::re_calculate() {
	
}
