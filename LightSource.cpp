#include "LightSource.hpp"

std::map<unsigned int,GenericLight*> GenericLight::light_list;

void GenericLight::enable_lighting() {
    //glEnable(GL_AUTO_NORMAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values  
    //glColorMaterial(GL_FRONT, GL_DIFFUSE);
    
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);
}

GenericLight* GenericLight::get_light(GLenum light_nmber) {
    return light_list[light_nmber];
}


void GenericLight::bind_light() {

    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //light_list.insert_or_assign(light_number, this);
    //printf("%f %f %f %f\n", this->ambient[0], this->ambient[1], this->ambient[2], this->ambient[3]);
    //printf("%f %f %f %f\n", this->light_position[0], this->light_position[1], this->light_position[2], this->light_position[3]);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->ambient);
    //glLightfv(this->id, GL_AMBIENT, this->ambient);
    glLightfv(this->id, GL_DIFFUSE, this->diffuse);
    glLightfv(this->id, GL_SPECULAR, this->specular);
    //glLightf(this->id, GL_SHININESS, this->shininess);
    glLightfv(this->id, GL_POSITION, this->light_position);

    glEnable(this->id);
}


void GenericLight::reposition_light() {
    glLightfv(this->id, GL_POSITION, this->light_position);
}

void GenericLight::reposition_lights() {
    for (std::pair<unsigned int, GenericLight*> pair : light_list) {
        pair.second->reposition_light();
    }
}