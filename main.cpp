#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "ScreenConstraints.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Input.hpp"

#include "Renderer.hpp"
#include "LightSource.hpp"
#include "Boid.hpp"
#include "Particles.hpp"

#include "Aimlab.hpp"

//GenericLight* light0;


//==========================

//Environment* env = Environment::getInstance();
Input* inputController = Input::getInstance();

Renderer* rendererController = Renderer::getInstance();


/*
void glMouseWheel(int button, int dir, int x, int y){
    cam->ProcessMouseScroll(dir);
}

void glMouseClick(int button, int state, int x, int y) {
    //mouse click
}


void glMouse(int ox, int oy) {
    //printf("%d , %d \n", ox, oy);
    if (ox == SW2 && oy == SH2)return;
    ox -= SW2;
    oy -= SH2;
    //box_position->updateOrientation(-ox,-oy);
    cam->updatePerspective(ox,-oy);
    
    glutWarpPointer(SW2, SH2);
    //glutPostRedisplay();
}

void glSpcDown(int key){
    switch (key) {
        case GLUT_KEY_CTRL_L:
            cam->updatePosition(MovementDirection::DOWN);
            //box_position->updatePosition(MovementDirection::DOWN);
            break;
        case GLUT_KEY_SHIFT_L:
            if(cam->MovementSpeed!=1.0f)
                cam->MovementSpeed = 1.0f;
            break;
        default:break;
    }
}

void glSpcUp(int key) {
    switch (key) {
    case GLUT_KEY_SHIFT_L:
        cam->MovementSpeed = 0.1f;
        break;
    default:break;
    }
}

void glKeyDown(unsigned char key) {
    switch (key) {
    case 'k':
        boid_position->updatePosition(MovementDirection::LEFT);
        break;
    case 'o':
        boid_position->updatePosition(MovementDirection::FORWARD);
        break;
    case 'l':
        boid_position->updatePosition(MovementDirection::BACKWARD);
        break;
    case ';':
        boid_position->updatePosition(MovementDirection::RIGHT);
        break;
    case 'i':
        boid_position->updatePosition(MovementDirection::UP);
        break;
    case 'p':
        boid_position->updatePosition(MovementDirection::DOWN);
        break;
    case ',':
        ganyu_move->updateOrientation(8, 0);
        break;
    case '.':
        ganyu_move->updateOrientation(-8, 0);
        break;
    case 'q':
        //box_position->updateOrientation(2);
        cam->updateOrientation(2);
        break;
    case 'e':
        //box_position->updateOrientation(-2);
        cam->updateOrientation(-2);
        break;
    case 'w':
        cam->updatePosition(MovementDirection::FORWARD);
        //box_position->updatePosition(MovementDirection::FORWARD);
        break;
    case 's':
        cam->updatePosition(MovementDirection::BACKWARD);
        //box_position->updatePosition(MovementDirection::BACKWARD);
        break;
    case 'a':
        cam->updatePosition(MovementDirection::LEFT);
        //box_position->updatePosition(MovementDirection::LEFT);
        //box_position->updateOrientation(-15,0);
        break;
    case 'd':
        cam->updatePosition(MovementDirection::RIGHT);
        //box_position->updatePosition(MovementDirection::RIGHT);
        //box_position->updateOrientation(15,0);
        break;
    case ' ':
        cam->updatePosition(MovementDirection::UP);
        //box_position->updatePosition(MovementDirection::UP);
        break;
    case 'g':
        light0->light_position[0] -= 0.5f;
        break;
    case 'y':
        light0->light_position[2] -= 0.5f;
        break;
    case 'h':
        light0->light_position[2] += 0.5f;
        break;
    case 'j':
        light0->light_position[0] += 0.5f;
        break;
    case 't':
        light0->light_position[1] -= 0.5f;
        break;
    case 'u':
        light0->light_position[1] += 0.5f;
        break;
    case 'r':
        //snowman_entity->angulo_bracos += 2.0f;
        //if (snowman_entity->angulo_bracos >= 70.0f) snowman_entity->angulo_bracos = 70.0f;
        glDisable(light0->id);
        break;
    case 'f':
        //snowman_entity->angulo_bracos -= 2.0f;
        //if (snowman_entity->angulo_bracos <= -70.0f) snowman_entity->angulo_bracos = -70.0f;
        glEnable(light0->id);
        break;
    case 'z':
        //flame->swirl_cycle++;
        break;
    case 'x':
        //if(flame->swirl_cycle>1)
        //    flame->swirl_cycle--;
        break;
    default:break;
    }
    //glutPostRedisplay();
}

void glKeyUp(unsigned char key){
    switch (key) {
    case ',':
        ganyu_move->updateOrientation(0, 0);
        break;
    case '.':
        ganyu_move->updateOrientation(0, 0);
        break;
    case 'q':
        cam->updateOrientation(0);
        //box_position->updateOrientation(0);
        break;
    case 'e':
        cam->updateOrientation(0);
        //box_position->updateOrientation(0);
        break;
    default:break;
    }
    //glutPostRedisplay();
}
*/


void display(){
    Renderer::frames++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Renderer::getActiveCamera()->fov, GLfloat(sWidth) / GLfloat(sHeight), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Renderer::getActiveCamera()->updateCameraLookAt();
    //cam->updateCameraLookAt();
    GenericLight::reposition_lights();
    //light0->reposition_light();
    glPushMatrix();

    Renderer::render_3D();

    glPopMatrix();
    //glFlush();?

    //glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCR_WIDTH, 0, SCR_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    Renderer::render_HUD();
    glPopMatrix();

    glFlush();
}


void reshape(GLint w, GLint h){
    glViewport(0, 0, w, h);
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, GLfloat(w) / GLfloat(h), 1.0, 100.0);*/
    sWidth = w;
    sHeight = h;
    s2Width = w / 2;
    s2Height = h / 2;
    //glutPostRedisplay();
}


/*
// TO-DO

Movement:
    Vector-based movement direction
    Euler-based orientation
                                                 
Movement has entity collision parameters         
(reference? reference to models list(models having collision param)?)
            ---------------------------------------------------------

finish lighting
    |start shading
    |START TEXTURES!!!

create terrain mechanism

z-buffer camera ( is default? )

don't render off camera angles ( is default? )

search ocluded objects ( probably not default!!! )

Export blender
    bones
    animation
    collision mesh
    uv mapping

Textures:
    Shading
    displacement map

*/


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);

    
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-SW2, glutGet(GLUT_SCREEN_HEIGHT)/2-SH2);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutCreateWindow("Big Yikes");
    
    GLenum err = glewInit();
    if (GLEW_OK != err){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }


    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);     // Do not calculate inside

    /*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex.GetId());
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);*/
    
    //glDepthFunc(GL_LEQUAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    /*========================*/
    /*=====   DEFAULT   ======*/
    /*========================*/
    
    GenericLight::enable_lighting();
    //light0->bind_light();
    
    AimlabGame* gameClass = AimlabGame::getInstance();
    gameClass->init();
    //gameClass->setup_targets();

    

    

    //Environment::init();
    Renderer::init(&sWidth, &sHeight);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(SW2, SH2);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    // Bind dos Inputs de mouse

    glutMotionFunc(AimlabGame_mouseMovementReceive);
    glutPassiveMotionFunc(AimlabGame_mouseMovementReceive);

    glutMouseFunc(AimlabGame_mouseClickReceive);
    glutMouseWheelFunc(AimlabGame_mouseWheelReceive);

    // Bind de Teclado

    glutSpecialFunc(Input::spcDownReceiver);
    glutSpecialUpFunc(Input::spcUpReceiver);
    glutKeyboardFunc(Input::keyDownReceiver);
    glutKeyboardUpFunc(Input::keyUpReceiver);

    Input::keyDownCallback(AimlabGame_glKeyDown);
    Input::keyUpCallback(AimlabGame_glKeyUp);
    Input::spcDownCallback(AimlabGame_glSpcDown);
    Input::spcUpCallback(AimlabGame_glSpcUp);

    glutMainLoop();
    //for(int iii=0;iii < 10;iii++) glutMainLoopEvent(); // uma iteração só

    //https://www.google.com/search?q=opengl+texture+basic
    //https://learnopengl.com/Getting-started/Textures

    AimlabGame::End();

    Boid::stop_animate();
    Firework::EndAnimation();
    DirectedParticle::EndAnimation();
    GenericParticle::End();

    Texture::End();
    Material::End();
    GenericLight::End();
    Boid::End();
    Camera::End();
    Physics::End();
    Movement::End();
    Texture::End();
    Model::End();
    Entity::End();

    Input::Stop();
    //Environment::Stop();
    Renderer::Stop();
}