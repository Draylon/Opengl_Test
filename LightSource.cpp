#include "LightSource.hpp"

std::map<int, GenericLight*> GenericLight::light_list;

void GenericLight::reposition_light(GLenum lnum) {
    glLightfv(lnum, GL_POSITION, light_list[lnum]->light_position);
}

void GenericLight::bind_light(GLenum light_number){
    light_list.insert_or_assign(light_number, this);
    glLightfv(light_number, GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(light_number, GL_DIFFUSE, diffuse);
    glLightfv(light_number, GL_SPECULAR, specular);
    glLightf(light_number, GL_SHININESS, shininess);
    glLightfv(light_number, GL_POSITION, light_position);
    glEnable(light_number);
}

void GenericLight::enable_lighting() {
    // Enable lighting
    glEnable(GL_LIGHTING);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
}