/*
#include "Environment.hpp"

Environment* Environment::instance;

std::vector<Entity*> Environment::entity_list;
std::vector<GenericLight*> Environment::light_list;
std::vector<Physics*> Environment::physics_actuators;
std::vector<GenericParticle*> Environment::particle_list;

int Environment::elc, Environment::llc,
Environment::pha, Environment::plc;

Environment* Environment::getInstance() {
    if (!Environment::instance) {
        instance = new Environment();
    }
    return instance;
}

void Environment::Stop() {
    delete instance;
}

void Environment::init(){
    //gluLookAt(0, 2, 5, 0, 0, 0, 0, 1, 0);
    //Environment::enable_lighting();
}

void Environment::addLighting(GenericLight* l) {
    light_list.push_back(l);
    llc++;
}

void Environment::addEntity(Entity* e) {
    entity_list.push_back(e);
    elc++;
}

void Environment::setPhysics(Physics* p) {
    physics_actuators.push_back(p);
    pha++;
}

void Environment::addParticle(GenericParticle* p) {
    particle_list.push_back(p);
    plc++;
}

*/

/*

void Environment::enable_lighting(){
        // Light values and coordinates
        GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
        GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
        GLfloat  sourceLight2[] = { 0.0f, 0.0f, 1.0f, 1.0f };

        GLfloat  ambient[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat  diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
        GLfloat  specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 1.0 };
        //GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };
        //GLfloat  lightPos[] = { -5.0f, 10.0f, -5.0f, 1.0f };
        //GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

        // Enable lighting
        glEnable(GL_LIGHTING);

        // Setup and enable light 0
        //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_LIGHT_MODEL_AMBIENT, whiteLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sourceLight2);
        glLightfv(GL_LIGHT0, GL_SHININESS, mat_shininess);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
        //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 25.f);
        //glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.2f);
        //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 5);
        glEnable(GL_LIGHT0);

        // Enable color tracking
        glEnable(GL_COLOR_MATERIAL);

        //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

        // Set Material properties to follow glColor values  
        glColorMaterial(GL_FRONT, GL_DIFFUSE);

        // Black blue background  
        glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
    }

void Environment::terrain() {

}
*/ 

