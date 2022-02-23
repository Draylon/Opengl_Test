#include "Entity.hpp"

std::vector<Entity*> Entity::entity_list;

void Entity::addModel(Model* m) {
	models.push_back(m);
}

void Entity::init() {
	std::vector<Model*>::iterator it = models.begin();
	while (it != models.end()) {
		(*it)->init();
		it++;
	}
}

void Entity::render(){
	glPushMatrix();
	this->movement->translate();
	this->movement->rotate();
	std::vector<Model*>::iterator it = models.begin();
	while (it != models.end()) {
		(*it)->render();
		it++;
	}
	glPopMatrix();
}

void Entity::render_all() {
	std::vector<Entity*>::iterator it = entity_list.begin();
	while (it != entity_list.end()) {
		(*it)->render();
		it++;
	}
}