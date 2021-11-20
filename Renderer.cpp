#include "Renderer.hpp"

#include "snowman.cpp"
#include "castle.cpp"

void Renderer::render() {
    //glScalef(cam.Zoom, cam_zoom, cam_zoom);
    /*glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);*/

    snowman();
    glColor3f(1, 1, 1);
    castle();
    glTranslatef(3, 0, 0);
    //blender_snowman();


    //draw_arm(shoulderAngle);
    //glTranslatef(0.0, 0.0, 0.0);
    //draw_arm(elbowAngle);

    /*GLUquadricObj* pObj;
    pObj = gluNewQuadric();

    gluSphere(pObj, 2, 25, 15);

    gluQuadricDrawStyle(pObj, GLU_POINT);
    gluQuadricNormals(pObj, GLU_SMOOTH);
    gluQuadricOrientation(pObj, GLU_OUTSIDE);*/
}