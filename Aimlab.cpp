#include <GL/freeglut_std.h>
#include <GL/freeglut_ext.h>

#include "Aimlab.hpp"


AimlabGame* AimlabGame::instance;

void AimlabGame::init() {
	//initialize renderer
	//initialize scene
	//initialize player
	//initialize gun
	//initialize targets
	//initialize scoreboard
	//initialize o initialize

    map= new Entity();
    //Model* map_model = new Model("Src/map/scene_centered.obj");
    Model* map_model = new Castle(30, 12, 2, glm::vec3(0.5f, 0.15f, 1.0f), 6, 25, 15);
    map->addModel(map_model);

    player = new Player();
    Renderer::setActiveCamera(player->playerView);
    
    //player->playerView


}

void AimlabGame::setup_targets() {

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
}

void AimlabGame_mouseWheelReceive(int button, int dir, int x, int y){
    //player switch weapons?
    AimlabGame* inst = AimlabGame::getDefinedInstance();
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
