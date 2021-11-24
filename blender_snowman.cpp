#ifndef BLENDER_SNOWMAN
#define BLENDER_SNOWMAN

#include <fstream>
#include <vector>

#include "Texture.hpp"
#include "ObjLoader.cpp"
#include <GL/glut.h>


static std::vector<Vertex> model;
static Texture texture;


void load_snowman() {
    std::ifstream ifile("blender_snowman.obj");
    model = LoadOBJ(ifile);
    texture = Texture("blender_snowman.png");
}

void blender_snowman() {

    glPushMatrix();

    //glTranslatef(0.0f, -1.0f, -3.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &model[0].position);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &model[0].texcoord);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &model[0].normal);
    glDrawArrays(GL_TRIANGLES, 0, model.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    texture.Bind();

    glPopMatrix();
}

#endif