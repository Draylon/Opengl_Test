#include "Environment.hpp"

#include <GL/glut.h>

Environment* Environment::instance;

Environment& Environment::getInstance() {
    if (!Environment::instance) {
        instance = new Environment();
    }
    return *instance;
}

void Environment::init(){
    //gluLookAt(0, 2, 5, 0, 0, 0, 0, 1, 0);
    Environment::enable_lighting();
}

void Environment::enable_lighting() {
        // Light values and coordinates
        GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
        GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
        //GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };
        GLfloat  lightPos[] = { 0, 10.0f, -1, 0.0f };

        glEnable(GL_DEPTH_TEST);    // Hidden surface removal
        glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
        glEnable(GL_CULL_FACE);     // Do not calculate inside

        // Enable lighting
        glEnable(GL_LIGHTING);

        // Setup and enable light 0
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
        glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glEnable(GL_LIGHT0);

        // Enable color tracking
        glEnable(GL_COLOR_MATERIAL);

        // Set Material properties to follow glColor values  
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

        // Black blue background  
        glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
    }

void Environment::terrain() {

}
