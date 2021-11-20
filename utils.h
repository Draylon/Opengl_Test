#ifndef PROJ_UTILS
#define PROJ_UTILS

#include<GL/freeglut.h>

void create_rect(GLfloat w, GLfloat h, GLfloat d, GLfloat x, GLfloat y, GLfloat z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    // w = 3 | h = 1 | d = 2

    glRectf(0, 0, w, h);

    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -d, 0.0f);

    glRectf(0, 0, w, d);

    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    glTranslatef(-h, 0.0f, 0.0f);

    glRectf(0, 0, h, d);

    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    glTranslatef(-w, 0, 0);

    glRectf(0.0, 0.0f, w, d);

    glRotatef(-90, 0, 1, 0);
    glTranslatef(-h, 0, 0);

    glRectf(0.0, 0.0f, h, d);

    glRotatef(90, 1, 0, 0);
    glTranslatef(0, -w, 0);

    glRectf(0.0, 0.0f, h, w);

    glPopMatrix();
}
#endif