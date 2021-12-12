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
#include "Particles.hpp"


Environment* env = Environment::getInstance();
Input* ui_in = Input::getInstance();

EulerCamera cam = EulerCamera(75,true,false,glm::vec3(0.0f, 0.0f, 3.0f));
Renderer* renderer = Renderer::getInstance();

void glMouseWheel(int button, int dir, int x, int y){
    cam.ProcessMouseScroll(dir);
}

void glMouseClick(int button, int state, int x, int y) {
    //mouse click
}


void glMouse(int ox, int oy) {
    if (ox == SW2 && oy == SH2)return;
    cam.updatePerspective(ox-SW2, SH2-oy);
    glutWarpPointer(SW2, SH2);
    //glutPostRedisplay();
}

void glSpcDown(int key) {
    switch (key) {
        case GLUT_KEY_CTRL_L:
            cam.updatePosition(CameraMovement::DOWN);
            break;
        case GLUT_KEY_SHIFT_L:
            if(cam.MovementSpeed!=1.0f)
                cam.MovementSpeed = 1.0f;
            break;
        default:break;
    }
}

void glSpcUp(int key) {
    switch (key) {
    case GLUT_KEY_SHIFT_L:
        cam.MovementSpeed = 0.1f;
        break;
    default:break;
    }
}

void glKeyDown(unsigned char key) {
    switch (key) {
    case 'q':
        cam.updateOrientation(2);
        break;
    case 'e':
        cam.updateOrientation(-2);
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
    case 'r':
        angulo_bracos += 2.0f;
        if (angulo_bracos >= 70.0f) angulo_bracos = 70.0f;
        break;
    case 'f':
        angulo_bracos -= 2.0f;
        if (angulo_bracos <= -70.0f) angulo_bracos = -70.0f;
        break;
    case 'g':
        Environment::lightPos[0] -= 0.5f;
        break;
    case 'y':
        Environment::lightPos[2] -= 0.5f;
        break;
    case 'h':
        Environment::lightPos[2] += 0.5f;
        break;
    case 'j':
        Environment::lightPos[0] += 0.5f;
        break;
    case 't':
        Environment::lightPos[1] -= 0.5f;
        break;
    case 'u':
        Environment::lightPos[1] += 0.5f;
        break;
    default:break;
    }
    //glutPostRedisplay();
}

void glKeyUp(unsigned char key){
    switch (key) {
    case 'q':
        cam.updateOrientation(0);
        break;
    case 'e':
        cam.updateOrientation(0);
        break;
    default:break;
    }
    //glutPostRedisplay();
}


void display(){
    Renderer::frames++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Renderer::getActiveCamera()->fov, GLfloat(sWidth) / GLfloat(sHeight), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam.updateCameraLookAt();
    Environment::repositionLights();
    glPushMatrix();

    Renderer::render_3D();

    glPopMatrix();
    //glFlush();

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


void init(){
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);     // Do not calculate inside

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    renderer->setActiveCamera(&cam);
}


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

    DotParticle* snow_part = new DotParticle(1500, 500, 0.15f,35,
        glm::vec3(1,1,1),0.003f, 0.15f,
        glm::vec3(0,30,0),glm::vec3(0, -1, 0),
        0, 0.1f, 0.8f);
    snow_part->createParticleArray();

    DotParticle* flame = new DotParticle(300, 30, 0.15f,0.2f,
        glm::vec3(1,0.6,0.2),-0.00001f, 0.2f,
        glm::vec3(5,0,-4),glm::vec3(0, 1, 0),
        0, 0.08f, 0.8f);
    flame->createParticleArray();

    Environment::init();
    Renderer::init(&sWidth, &sHeight);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(SW2, SH2);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    // Bind dos Inputs de mouse

    glutMotionFunc(glMouse);
    glutPassiveMotionFunc(glMouse);

    glutMouseFunc(glMouseClick);
    glutMouseWheelFunc(glMouseWheel);

    // Bind de Teclado

    glutSpecialFunc(Input::spcDownReceiver);
    glutSpecialUpFunc(Input::spcUpReceiver);
    glutKeyboardFunc(Input::keyDownReceiver);
    glutKeyboardUpFunc(Input::keyUpReceiver);

    Input::keyDownCallback(glKeyDown);
    Input::keyUpCallback(glKeyUp);
    Input::spcDownCallback(glSpcDown);
    Input::spcUpCallback(glSpcUp);

    init();
    glutMainLoop();
    //glutMainLoopEvent(); // uma iteração só

    delete snow_part;
    delete flame;
    Input::Stop();
    Environment::Stop();
    Renderer::Stop();
}