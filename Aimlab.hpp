#ifndef AIMLAB_CLASS
#define AIMLAB_CLASS

#include "Entity.hpp"

#include "ScreenConstraints.h"
#include "castle.cpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "LightSource.hpp"

#include "Particles.hpp"
#include "RandomBox.cpp"

class Gun;

class Player {
	friend class AimlabGame;
	static std::vector<Player*> players;

public:
	int hit_count;
	Entity* playerEntity;
	Camera* playerView;
	PositionMovement* playerMovement;
	Gun* playerGun;

	Player() {
		RandomBox* box_model = new RandomBox(5, 5, 5);
		box_model->setMat(Material::get("mat_general"));

		playerMovement = new PositionMovement(glm::vec3(0, 5, 10), 0.4f,90);
		playerView = new Camera(75,playerMovement);
		playerView->updatePerspective(90, 0);
		
		playerEntity = new Entity(playerMovement);
		playerEntity->addModel(box_model);

		playerView->bindMovementOrientations(playerMovement, true,false, false,false);
	}
	void grabGun(Gun* gun);
	static void End(){
		for (Player* g : players) delete g;
	}
};

class Projectile {
public:
	static std::vector<Projectile*> projectiles_list;
	//particle
	//directional
	DirectedParticle* projectileParticle;
	Projectile(Gun* gun);

	static void End() {
		for (Projectile* g : projectiles_list) delete g;
	}
};

class Gun{
	static std::vector<Gun*> gun_instances;
public:
	std::list<Projectile*> fired_projectiles;
	Entity* gunEntity;
	float projectile_speed;
	Gun(const float projectile_speed);
	void fire();
	static void End(){
		for (Gun* g : gun_instances) delete g;
	}
};

class Target{
	static std::vector<Target*> targets_list;

public:
	static int player_hits;
	Entity* targetEntity;
	Target() {
		targets_list.push_back(this);
		RandomBox* targ_model = new RandomBox(1, 1, 1);
		targ_model->enableMaterials(false);
		targ_model->enableTextures(false);
		targetEntity = new Entity();
		targetEntity->addModel(targ_model);
	}
	static void check_hit(glm::vec3 Position, glm::vec3 direction);
	void hit();
	void reset();

	static void End() {
		for (Target* g : targets_list) delete g;
	}
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
	GenericLight* main_scene_light;

public:
	static glm::vec3 env_gravity;
	static Player* player;
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

	static void End() {
		Gun::End();
		Player::End();
		Projectile::End();
		Target::End();
		//Scoreboard::End();
	}
};
void AimlabGame_glSpcDown(int);
void AimlabGame_glSpcUp(int);
void AimlabGame_glKeyDown(unsigned char);
void AimlabGame_glKeyUp(unsigned char);

void AimlabGame_mouseClickReceive(int button, int state, int x, int y);
void AimlabGame_mouseMovementReceive(int ox, int oy);
void AimlabGame_mouseWheelReceive(int button, int dir, int x, int y);

#endif