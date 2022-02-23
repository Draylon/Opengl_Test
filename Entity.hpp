#ifndef OBJECT_H
#define OBJECT_H

#include "Texture.hpp"
#include "Model.hpp"
#include "Physics.hpp"
#include "Movement.hpp"

class Entity {
public:
	static std::vector<Entity*> entity_list;

	static void End() {
		for (int i = 0; i < entity_list.size(); i++)
			delete entity_list[i];
	}

	Entity(Movement* move=NULL){
		if (move != NULL)
			this->movement = move;
		else
			this->movement = PositionMovement::defaultBuild();
		entity_list.push_back(this);
	}

	~Entity() {
		printf("entity destructor called\n");
	}

	Movement* movement;
	std::vector<Model*> models;

	void addModel(Model* m);

	virtual void init();
	virtual void render();
	static void render_all();
};

#endif // !OBJECT_H