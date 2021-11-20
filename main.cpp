#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Input.hpp"
#include "Environment.hpp"
#include "Camera.hpp"

#include "Renderer.hpp"


#define SCR_WIDTH 1280
#define SCR_HEIGHT 720
#define SW2 SCR_WIDTH/2
#define SH2 SCR_HEIGHT/2

Environment env = Environment::getInstance();
Input ui_in = Input::getInstance();
Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));

void glMouseWheel(int button, int dir, int x, int y){
    
    glutPostRedisplay();
}

void glMouseClick(int button, int state, int x, int y) {
    //mouse click
}


void glMouse(int ox, int oy) {
    if (ox == SW2 && oy == SH2)return;
    cam.ProcessMouseMovement(ox-SW2, SH2-oy);
    glutPostRedisplay();
    glutWarpPointer(SW2, SH2);
}

void glSpecialKeys(int key, int x, int y,bool down) {
    switch (key) {
    case GLUT_KEY_CTRL_L:
        cam.ProcessKeyboard(CameraMovement::DOWN, 0.3f);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void glSpecialDown(int key, int x, int y) {
    glSpecialKeys(key, x, y, true);
}
void glSpecialUp(int key, int x, int y) {
    glSpecialKeys(key, x, y, false);
}

void glKeys(unsigned char key, int x, int y, bool down) {
    switch (key) {
    case 'w':
        cam.ProcessKeyboard(CameraMovement::FORWARD, 0.3f);
        break;
    case 's':
        cam.ProcessKeyboard(CameraMovement::BACKWARD, 0.3f);
        break;
    case 'a':
        cam.ProcessKeyboard(CameraMovement::LEFT, 0.3f);
        break;
    case 'd':
        cam.ProcessKeyboard(CameraMovement::RIGHT, 0.3f);
        break;
    case ' ':
        cam.ProcessKeyboard(CameraMovement::UP, 0.3f);
        break;
    default:break;
    }
    glutPostRedisplay();
}

void glKeyDown(unsigned char key, int x, int y) {
    glKeys(key, x, y, true);
}
void glKeyUp(unsigned char key, int x, int y) {
    glKeys(key, x, y, false);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam.updateCameraLookAt();

    glPushMatrix();

    Renderer::render();

    glPopMatrix();
    glFlush();
}


void reshape(GLint w, GLint h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, GLfloat(w) / GLfloat(h), 1.0, 100.0);
}


void init() {
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    env.init();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1920/2-SW2, 1080/2-SH2);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutCreateWindow("Big Yikes");
    
    GLenum err = glewInit();
    if (GLEW_OK != err){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glutWarpPointer(SW2, SH2);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMotionFunc(glMouse);
    glutPassiveMotionFunc(glMouse);

    glutMouseFunc(glMouseClick);
    glutMouseWheelFunc(glMouseWheel);

    glutSpecialFunc(Input::specialKeyDownReceiver);
    glutSpecialUpFunc(Input::specialKeyUpReceiver);
    glutKeyboardFunc(Input::keyDownReceiver);
    glutKeyboardUpFunc(Input::keyUpReceiver);

    Input::keyUpCallback(glKeyUp);
    Input::keyDownCallback(glKeyDown);
    Input::specialKeyDownCallback(glSpecialDown);
    Input::specialKeyUpCallback(glSpecialUp);

    init();
    glutMainLoop();
}