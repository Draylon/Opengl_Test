#include <GL/freeglut_std.h>
#include <GL/freeglut_ext.h>

#include "Aimlab.hpp"



AimlabGame* AimlabGame::instance;
glm::vec3 AimlabGame::env_gravity;
Player* AimlabGame::player;
std::vector<Projectile*> Projectile::projectiles_list;
std::vector<Target*> Target::targets_list;
int Target::player_hits;
std::vector<Player*> Player::players;
std::vector<Gun*> Gun::gun_instances;

void AimlabGame::init() {
	//initialize renderer
	//initialize scene
	//initialize player
	//initialize gun
	//initialize targets
	//initialize scoreboard
	//initialize o initialize

    GLfloat light_position[] = { -15.0, 9.0, 20.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 0.0,1.0 };
    GLfloat light_diffuse[] = { 0.50, 0.50, 0.5,1.0 };
    GLfloat mat_specular[] = { 0.8, 0.5, 0.5, 1.0 };
    GLfloat mat_shininess[] = { 5.0 };
    GLfloat mat_ambient[] = { 0.2, 0.4, 0.99, 1.0 };
    GLfloat mat_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };

    //Light Source
    // Light values and coordinates
    //GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    //GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    //GLfloat  sourceLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };

    //GLfloat  l_position[] = { 0.0f,5.0f,0.0f,0 };
    //GLfloat  ambient[] = { 0.25f, 0.25f, 0.25f };
    //GLfloat  diffuse[] = { 0.75f, 0.75f, 0.75f };
    //GLfloat  specular[] = {0.0f, 0.0f, 1.0f };
    //GLfloat mat_shininess = 15.0f;

    //light0 = new GenericLight(GL_LIGHT0, ambient, diffuse, specular, mat_shininess, 0, l_position);
    
    //main_scene_light = new GenericLight(GL_LIGHT0, mat_ambient, light_diffuse, light_specular, NULL, 0, light_position);
    main_scene_light = new GenericLight(GL_LIGHT0, NULL,
        new GLfloat[]{ 0.50, 0.50, 0.5,1.0 },
        new GLfloat[]{ 0.8, 0.5, 0.5, 1.0 }, NULL, 0, 
        new GLfloat[]{ 5.0, 5.0, 5.0, 1.0 });
    main_scene_light->bind_light();

    //Material* material1 = new Material(mat_ambient, mat_diffuse, mat_specular, mat_shininess);
    Material::create("mat_general");
    Material::setAmbient("mat_general", mat_ambient[0], mat_ambient[1], mat_ambient[2], mat_ambient[3]);
    Material::setDiffuse("mat_general", mat_diffuse[0], mat_diffuse[1], mat_diffuse[2], mat_diffuse[3]);
    Material::setSpecular("mat_general", mat_specular[0], mat_specular[1], mat_specular[2], mat_diffuse[3]);
    Material::setSpecularExp("mat_general", mat_shininess[0]);

    env_gravity = glm::vec3(0, -1, 0);

    //==========================

    RandomBox* box_model = new RandomBox(5, 5, 5);
    box_model->setMat(Material::get("mat_general"));
    box_model->setTexture(Texture::fetch("doge.jpg"));
    Entity* box_entity = new Entity();
    box_entity->addModel(box_model);
    box_entity->movement->resetPosition(-9, 2.5, -10);
    box_entity->movement->updateOrientation(-845, 0);
    
    RandomBox* box_model2 = new RandomBox(5, 5, 5);
    box_model2->setMat(Material::get("mat_general"));
    Entity* box_entity2 = new Entity();
    box_entity2->addModel(box_model2);
    box_entity2->movement->resetPosition(15, 2.5, -18);
    box_entity2->movement->updateOrientation(-260, 0);

    map= new Entity();
    //Model* map_model = new Model("Src/map/scene_centered.obj");
    Model* map_model = new Castle(30, 22, 2, glm::vec3(0.5f, 0.15f, 1.0f), 6, 25, 15);
    ((Castle*)map_model)->setMat(Material::get("mat_general"));
    ((Castle*)map_model)->setTexture(Texture::fetch("brick.jpg"));
    map->addModel(map_model);

    player = new Player();
    Renderer::setActiveCamera(player->playerView);
    
    //player->playerView

    Gun* g = new Gun(1);
    player->grabGun(g);

    setup_targets();
}

void AimlabGame::setup_targets() {
    for (int i = 0; i < 6; i++) {
        Target* t = new Target();
        t->targetEntity->movement->alterPosition(0, 7, 0);
        t->targetEntity->movement->alterPosition(gr(12), gr(7), 0);
    }
}

void AimlabGame_mouseMovementReceive(int ox,int oy){
    AimlabGame* inst= AimlabGame::getDefinedInstance();
    //printf("%d , %d \n", ox, oy);
    if (ox == SW2 && oy == SH2)return;
    ox -= SW2;
    oy -= SH2;
    //box_position->updateOrientation(-ox,-oy);
    inst->player->playerView->updatePerspective(ox, -oy);

    glutWarpPointer(SW2, SH2);
    //glutPostRedisplay();
}

void AimlabGame_mouseClickReceive(int button, int state, int x, int y){
    //player clicking == shoot?
    AimlabGame* inst = AimlabGame::getDefinedInstance();
    printf("c %i %i %i %i\n",button,state,x,y);
    if(inst->player->playerGun!=NULL)
        if (button == 0 && state == 0) {
            inst->player->playerGun->fire();
            Target::check_hit(inst->player->playerView->Position,inst->player->playerView->Front);
        }
}

void AimlabGame_mouseWheelReceive(int button, int dir, int x, int y){
    //player switch weapons?
    AimlabGame* inst = AimlabGame::getDefinedInstance();
    printf("s %i %i %i %i\n", button, dir, x, y);
}




void AimlabGame_glSpcDown(int key) {
    AimlabGame* inst = AimlabGame::getDefinedInstance();
    switch (key) {
    case GLUT_KEY_CTRL_L:
        //box_position->updatePosition(MovementDirection::DOWN);
        inst->player->playerMovement->updatePosition(MovementDirection::DOWN);
        break;
    case GLUT_KEY_SHIFT_L:
        inst->player->playerMovement->MovementSpeed += 0.2;
        break;
    default:break;
    }
}

void AimlabGame_glSpcUp(int key){
    AimlabGame* inst = AimlabGame::getDefinedInstance();
    switch (key) {
        case GLUT_KEY_SHIFT_L:
            inst->player->playerMovement->MovementSpeed -= 0.2;
            break;
        default:break;
    }
}

void AimlabGame_glKeyDown(unsigned char key) {
    AimlabGame* inst = AimlabGame::getDefinedInstance();
    switch (key) {
    case 'w':
        inst->player->playerMovement->updatePosition(MovementDirection::FORWARD);
        //cam->updatePosition(MovementDirection::FORWARD);
        //box_position->updatePosition(MovementDirection::FORWARD);
        break;
    case 's':
        inst->player->playerMovement->updatePosition(MovementDirection::BACKWARD);
        //cam->updatePosition(MovementDirection::BACKWARD);
        //box_position->updatePosition(MovementDirection::BACKWARD);
        break;
    case 'a':
        inst->player->playerMovement->updatePosition(MovementDirection::LEFT);
        //cam->updatePosition(MovementDirection::LEFT);
        //box_position->updatePosition(MovementDirection::LEFT);
        //box_position->updateOrientation(-15,0);
        break;
    case 'd':
        inst->player->playerMovement->updatePosition(MovementDirection::RIGHT);
        //cam->updatePosition(MovementDirection::RIGHT);
        //box_position->updatePosition(MovementDirection::RIGHT);
        //box_position->updateOrientation(15,0);
        break;
    case ' ':
        inst->player->playerMovement->updatePosition(MovementDirection::UP);
        //player jump
        //box_position->updatePosition(MovementDirection::UP);
        break;
    case 'r':
        //reload
        break;
    case 'f':
        //fleshlight?
        break;
    default:break;
    }
}

void AimlabGame_glKeyUp(unsigned char key) {
    switch (key) {
    default:break;
    }
}

//=============================================
//=============================================
//=============================================

void Player::grabGun(Gun* gun) {
    playerGun = gun;
    //playerEntity->movement->attachMovement(gun->gunEntity->movement);
    
    /*gun->gunEntity->movement->attachMovement(playerEntity->movement,
        glm::vec3(1,0,-1));*/
    playerView->bindViewMatrix(gun->gunEntity->movement);
    /*playerView->bindMovementOrientations(gun->gunEntity->movement,
        true,true,true,false);*/
    
    //playerMovement->attachMovement(gun->gunEntity->movement,glm::vec3(10,2,0));
    gun->gunEntity->movement->attachMovement(playerMovement,glm::vec3(3.5,-1.9,0.5));
}

//=============================================
//=============================================
//=============================================

Projectile::Projectile(Gun* gun){
    projectileParticle = new DirectedParticle(
        false, 100, 10, 0.15f, 0.05, glm::vec3(0.5, 0.5, 0),
        0.002f, 5.5f, AimlabGame::player->playerMovement->Position - glm::vec3(-2,1.8,0),
        AimlabGame::player->playerView->Front,//*gun->gunEntity->movement->getOrientationVector(0),
        0, 0, 0, 0.8f);

    projectileParticle->gravity = &AimlabGame::env_gravity;
    projectileParticle->animate();
}

//=============================================
//=============================================
//=============================================

Gun::Gun(const float projectile_speed) {
    this->projectile_speed = projectile_speed;
    gun_instances.push_back(this);

    /*RandomBox* m = new RandomBox(0.5f, 1, 4);
    m->setMat(Material::get("mat_general"));
    m->enableTextures(true);*/
    //Texture* t = Texture::fetch("gun1.jpg

    Model* m = new Model("Src/ak12/ak12.obj");
    m->enableMaterials(false);
    m->enableTextures(false);

    gunEntity = new Entity(
        new PositionMovement(glm::vec3(-2, 0, -1), 0)
    );
    gunEntity->addModel(m);
    gunEntity->movement->setUseMatrix(true);
    //gunEntity->movement

    //fired_projectiles
}

void Gun::fire() {
    // particula
    fired_projectiles.push_back(new Projectile(this));
    //printf("Shooting\n");
}

//=============================================
//=============================================
//=============================================

void Target::check_hit(glm::vec3 Position, glm::vec3 direction) {
    float highest = -1;
    Target* tt = NULL;
    for (Target* t : targets_list) {
        glm::vec3 targ = *t->targetEntity->movement->getPositionVec();
        glm::vec3 v1 = glm::normalize(targ - Position);
        //printf("%f %f %f\n", targ[0], targ[1], targ[2]);
        //printf("%f %f %f\n", Position[0], Position[1], Position[2]);
        //printf("%f %f %f\n", direction[0], direction[1], direction[2]);
        //printf("%f %f %f\n", v1[0], v1[1], v1[2]);
        float val = glm::dot(direction, v1);//glm::distance(direction, v1);
        printf("%f\n", val);
        if (val < 1.0f&&val>0.9971){
            if (highest < val) {
                highest = val;
                tt = t;
            }
        }
    }
    if (tt != NULL) {
        tt->hit();
    }
}

void Target::hit() {
    DotParticle* firework_explosion = new DotParticle(false, 400, 20, 0,
        glm::vec3(1,0.37,0), 0.02f, 0.45f,*this->targetEntity->movement->getPositionVec(),
        0, 0, 0.5f, 0.8f);
    firework_explosion->gravity = &AimlabGame::env_gravity;
    firework_explosion->animate();

    printf("HIT SOMETHING");
    player_hits++;
    reset();
}

void Target::reset() {
    targetEntity->movement->resetPosition(0, 7, 0);
    targetEntity->movement->alterPosition(gr(12), gr(7), 0);
}