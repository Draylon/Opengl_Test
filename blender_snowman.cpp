#ifndef BLENDER_SNOWMAN
#define BLENDER_SNOWMAN

#include <fstream>
#include <vector>

#include "Texture.hpp"
#include "Model.hpp"
#include <GL/glut.h>


static Model model;
static Texture texture;


void load_snowman() {
    std::ifstream ifile("ganyu.obj");
    model = Model();
    model.loadOBJ(ifile);
    texture = Texture("ganyu.png");
}

void blender_snowman() {

    glPushMatrix();

    //glTranslatef(0.0f, -1.0f, -3.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &model.verts[0].position);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &model.verts[0].texcoord);
    glNormalPointer(GL_FLOAT, sizeof(Vertex), &model.verts[0].normal);
    glDrawArrays(GL_TRIANGLES, 0, model.verts.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    texture.Bind();

    glPopMatrix();
}

#endif