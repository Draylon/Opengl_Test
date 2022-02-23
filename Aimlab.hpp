#ifndef AIMLAB_CLASS
#define AIMLAB_CLASS

#include "Entity.hpp"

#include "ScreenConstraints.h"
#include "castle.cpp"
#include "Camera.hpp"
#include "Renderer.hpp"

#include "Particles.hpp"
#include "RandomBox.cpp"

class Player {
	friend class AimlabGame;
	static std::vector<Player*> players;
public:
	Entity* playerEntity;
	
	Camera* playerView;
	PositionMovement* playerMovement;
public:
	Player() {
		RandomBox* box_model = new RandomBox(5, 5, 5);
		box_model->setMat(Material::get("mat_general"));

		playerMovement = new PositionMovement(glm::vec3(0, 0, 3), 0.4f);
		playerView = new Camera(75,playerMovement);
		
		playerEntity = new Entity(playerMovement);
		playerEntity->addModel(box_model);
	}

};

class Projectile {
	//particle
	//directional
	DirectedParticle* projectileParticle;

};

class Gun {
	Entity* gunEntity;
public:
	Gun(const float projectile_speed) {

	}
	void fire();

};

class Target {

	Entity* targetEntity;

};

class Scoreboard{

	std::map<Player*,GLfloat> players_scoreboard;
public:

	void reset();
	void add_to(Player*);

};

class Multiplayer {
	//mikewazowski
};

class AimlabGame {

	
	AimlabGame(){}
	static AimlabGame* instance;
public:
	Player* player;
	Entity* map;
	static AimlabGame* getInstance(){
		if (instance == NULL)
			instance = new AimlabGame();
		return instance;
	}
	static AimlabGame* getDefinedInstance() {
		return instance;
	}
	void init();
	void setup_targets();


};
void AimlabGame_glSpcDown(int);
void AimlabGame_glSpcUp(int);
void AimlabGame_glKeyDown(unsigned char);
void AimlabGame_glKeyUp(unsigned char);

void AimlabGame_mouseClickReceive(int button, int state, int x, int y);
void AimlabGame_mouseMovementReceive(int ox, int oy);
void AimlabGame_mouseWheelReceive(int button, int dir, int x, int y);

#endif