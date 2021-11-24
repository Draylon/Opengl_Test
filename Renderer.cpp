#include "Renderer.hpp"

#include "snowman.cpp"
#include "castle.cpp"

#define SCR_WIDTH 1580
#define SCR_HEIGHT 1020
#define SW2 SCR_WIDTH/2
#define SH2 SCR_HEIGHT/2

Renderer* Renderer::instance;
EulerCamera* Renderer::activeCamera;
GLint Renderer::width, Renderer::height;

Renderer& Renderer::getInstance(){
    if (!instance)
        instance = new Renderer();
    return *instance;
}

void Renderer::init(GLint w,GLint h) {
    Renderer::width = w;
    Renderer::height = h;
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
}

unsigned char* draw_angles_str = (unsigned char*)malloc(27 * sizeof(char));
void Renderer::render_HUD(){
    if (draw_angles_str != NULL) {
        glColor3f(2, 2, 2);
        glRasterPos2d(5, 5);
        float yaw, pitch, roll;
        activeCamera->drawAngles(&yaw, &pitch, &roll);
        sprintf_s((char*)draw_angles_str, 27 * sizeof(char), "Y:%.2f P:%.2f R:%.2f", yaw, pitch, roll);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, draw_angles_str);
    }
}

void Renderer::render_3D(){
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



void Renderer::reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, GLfloat(w) / GLfloat(h), 1.0, 100.0);
    Renderer::height = h;
    Renderer::width= w;
}


void Renderer::display() {

    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    activeCamera->updateCameraLookAt();

    glPushMatrix();

    glPopMatrix();
    glFlush();
    */


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-aspect * near / lens, aspect * near / lens, -near / lens, near / lens, near, far);
    gluPerspective(75, GLfloat(Renderer::width) / GLfloat(Renderer::height), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    activeCamera->updateCameraLookAt();
    
    glPushMatrix();
    render_3D();
    glPopMatrix();

    glFlush();

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    */

    // just clear the depth buffer, so that everything that's
    // drawn next will overlay the previously rendered scene.
    /*glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-aspect * scale, aspect * scale, -scale, scale, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    render_ortho_scene();*/

    // Same for the HUD, only that we render
    // that one in pixel coordinates.
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCR_WIDTH, 0, SCR_HEIGHT, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    render_HUD();

    glFlush();
}