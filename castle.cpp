#ifndef GL_CASTLE
#define GL_CASTLE

#include <GL/freeglut.h>
#include "utils.h"
#include <cmath>


GLfloat w = 25, h = 10, d = 2, gate_gap = 6;
GLfloat tower_height = 20;
GLfloat top_height = 12;
GLfloat tower_diameter = sqrt(pow(d, 2) + pow(d, 2));

void drawPillar(GLUquadricObj* pObj) {
    glPushMatrix();
    glTranslatef(0, 0, tower_height);
    glRotatef(180, 1, 0, 0);
    gluDisk(pObj, 0, tower_diameter * 1.5, 26, 13);
    glRotatef(180, 1, 0, 0);
    gluCylinder(pObj, tower_diameter * 1.5, 2*tower_diameter / 3, top_height / 3, 26, 13);
    glTranslatef(0, 0, top_height / 3);
    gluCylinder(pObj, 2*tower_diameter / 3, 0,2* top_height / 3, 26, 13);
    glPopMatrix();
}

void castle() {
    //glDisable(GL_CULL_FACE);
    glPushMatrix();
    
    
    create_rect(2*w,d,2*w,-w,-d,w);
    
    create_rect(2 * w, h, d, -w, 0, -w);
    
    glRotatef(90, 0, 1, 0);
    create_rect(2 * w, h, d, -w, 0, -w);
    glRotatef(90, 0, 1, 0);

    create_rect(w - gate_gap / 2, h, d, -w, 0, -w);
    create_rect(w - gate_gap / 2, h, d, gate_gap / 2, 0, -w);

    glRotatef(90, 0, 1, 0);
    create_rect(2 * w, h, d, -w, 0, -w);

    glPopMatrix();
    GLUquadricObj* pObj = gluNewQuadric();
    glPushMatrix();

    glTranslatef(-w-d/2, 0,-w-d/2);
    glRotatef(90, -1, 0, 0);
    gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
    drawPillar(pObj);

    glTranslatef(2*w+d, 0,0);
    gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
    drawPillar(pObj);

    glTranslatef(0, -2 * w - d,0);
    gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
    drawPillar(pObj);
    
    glTranslatef(-2 * w - d, 0, 0);
    gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
    drawPillar(pObj);

    glPopMatrix();

    //glEnable(GL_CULL_FACE);
}

#endif