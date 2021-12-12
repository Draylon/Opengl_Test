#ifndef GL_SNOWMAN
#define GL_SNOWMAN

#include <gl/freeglut.h>

#include "Gambiarra.hpp"

void snowman(){

    glPushMatrix();
    
    GLUquadricObj* pObj;
    // Move object back and do in place rotation  
    //glTranslatef(0.0f, -1.0f, -3.0f);
    //glPopMatrix();
    // Draw something  
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    
    glTranslatef(0.0f, 4.5f, 0.0f);
    // white
    glColor3f(1.0f, 1.0f, 1.0f);

    //Main Body
    glPushMatrix();
    glTranslatef(0.0f, -2.5f, 0.0f);
    gluSphere(pObj, 2.0f, 26, 13);  // Bottom
    glPopMatrix();

    //Mid section
    glPushMatrix();
    //glTranslatef(0.0f,0.0f,0.0f); 
    gluSphere(pObj, 1.2f, 26, 13);
    glPopMatrix();

    //Scarf
    glColor3f(1.0f, 0.2f, 0.2f);
    glPushMatrix();
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, -0.6f);
    gluDisk(pObj, 0, 1.2f, 26, 13);
    glRotatef(180, 1.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 1.2f, 0.9f, 0.7f, 26, 13);
    glTranslatef(0.0f, 0.0f, 0.7f);
    gluDisk(pObj, 0, 0.9f, 26, 13);
    glPopMatrix();

    // Head
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix(); // save transform matrix state
    glTranslatef(0.0f, 2.0f, 0.0f);
    gluSphere(pObj, 0.95f, 26, 13);
    glPopMatrix(); // restore transform matrix state

    // Nose (orange)
    glColor3f(1.0f, 0.4f, 0.51f);
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.95f);
    gluCylinder(pObj, 0.1f, 0.0f, 1.6f, 26, 13);
    glPopMatrix();



    // Eyes (black)
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-0.4f, 2.3f, 0.80f);
    gluSphere(pObj, 0.1f, 26, 13);
    glTranslatef(0.8f, 0.0f, 0.0f);
    gluSphere(pObj, 0.1f, 26, 13);
    glPopMatrix();
    // glColor, glPushMatrix,...

        // Hat

    glPushMatrix();
    glTranslatef(-0.2f, 2.6f, 0.0f);
    glRotatef(90, 1.0f, 0.4f, 0.0f);

    gluDisk(pObj, 0, 1.4f, 26, 13);
    glRotatef(180, 1.0f, 0.0f, 0.0f);

    gluCylinder(pObj, 1.4f, 1.4f, 0.3f, 26, 13);
    //glDisable(GL_CULL_FACE);

    glTranslatef(0.0f, 0.0f, 0.3f);
    gluDisk(pObj, 1.0f, 1.4f, 26, 13);
    gluCylinder(pObj, 1.0f, 1.0f, 1.0f, 26, 13);
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluDisk(pObj, 0, 1.0f, 26, 13);
    //glEnable(GL_CULL_FACE);
    glPopMatrix();

    // ARMS

    glPushMatrix();
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.19f);
    glRotatef(angulo_bracos, 1, 0, 0);
    gluCylinder(pObj, 0.1f, 0.0f, 2.3f, 26, 13);
    glPopMatrix();
    glRotatef(180, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 1.19f);
    glRotatef(angulo_bracos, 1, 0, 0);
    gluCylinder(pObj, 0.1f, 0.0f, 2.3f, 26, 13);
    glPopMatrix();


    glPopMatrix();
}

#endif