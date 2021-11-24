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

static GLint sWidth=SCR_WIDTH,sHeight=SCR_HEIGHT,s2Width=sWidth/2,s2Height=sHeight/2;




//Controle do boneco de neve
#include "Gambiarra.hpp"


Environment env = Environment::getInstance();
Input ui_in = Input::getInstance();
std::list<char> input_chars = { 'q', 'e', 'w', 's', 'a', 'd', ' ','t','g' };
std::list<int> spc_chars = { GLUT_KEY_CTRL_L };

EulerCamera cam = EulerCamera(true,false,glm::vec3(0.0f, 0.0f, 3.0f));
Renderer renderer = Renderer::getInstance();

void glMouseWheel(int button, int dir, int x, int y){
    cam.ProcessMouseScroll(dir);
    glutPostRedisplay();
}

void glMouseClick(int button, int state, int x, int y) {
    //mouse click
}


void glMouse(int ox, int oy) {
    if (ox == SW2 && oy == SH2)return;
    cam.updatePerspective(ox-SW2, SH2-oy);
    glutPostRedisplay();
    glutWarpPointer(SW2, SH2);
}

void glSpecialKeys(int key, int x, int y,bool down) {
    switch (key) {
    case GLUT_KEY_CTRL_L:
        cam.updatePosition(CameraMovement::DOWN);
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
    case 'q':
        if(down) cam.updateOrientation(2);
        else cam.updateOrientation(0);
        break;
    case 'e':
        if(down)cam.updateOrientation(-2);
        else cam.updateOrientation(0);
        break;
    case 'w':
        cam.updatePosition(CameraMovement::FORWARD);
        break;
    case 's':
        cam.updatePosition(CameraMovement::BACKWARD);
        break;
    case 'a':
        cam.updatePosition(CameraMovement::LEFT);
        break;
    case 'd':
        cam.updatePosition(CameraMovement::RIGHT);
        break;
    case ' ':
        cam.updatePosition(CameraMovement::UP);
        break;
    case 't':
        angulo_bracos += 2.0f;
        if (angulo_bracos >= 70.0f)angulo_bracos = 70.0f;
        break;
    case 'g':
        angulo_bracos -= 2.0f;
        if (angulo_bracos <= -70.0f)angulo_bracos = -70.0f;
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, GLfloat(sWidth) / GLfloat(sHeight), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam.updateCameraLookAt();

    glPushMatrix();

    Renderer::render_3D();

    glPopMatrix();
    glFlush();

    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCR_WIDTH, 0, SCR_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPopMatrix();
    Renderer::render_HUD();
    glPushMatrix();
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
}


void init(){
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    renderer.setActiveCamera(&cam);
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    

    glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-SW2, glutGet(GLUT_SCREEN_HEIGHT)/2-SH2);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
    glutCreateWindow("Big Yikes");
    
    GLenum err = glewInit();
    if (GLEW_OK != err){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    Input::initKeys(input_chars);
    Input::initSpcKeys(spc_chars);

    Environment::init();
    
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(SW2, SH2);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Bind dos Inputs de mouse
    
    glutMotionFunc(glMouse);
    glutPassiveMotionFunc(glMouse);

    glutMouseFunc(glMouseClick);
    glutMouseWheelFunc(glMouseWheel);

    // Bind de Teclado

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