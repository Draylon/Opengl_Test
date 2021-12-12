#include "Renderer.hpp"

#include "snowman.cpp"
#include "castle.cpp"
#include "randomCube.cpp"
#include "Particles.hpp"

#define SCR_WIDTH 1580
#define SCR_HEIGHT 1020
#define SW2 SCR_WIDTH/2
#define SH2 SCR_HEIGHT/2

Renderer* Renderer::instance;
EulerCamera* Renderer::activeCamera;
GLint* Renderer::width;
GLint* Renderer::height;

unsigned int Renderer::fps;
unsigned int Renderer::frames;
std::thread Renderer::fps_thread;
bool Renderer::fps_stop;

void Renderer::fps_function() {
    while(!fps_stop){
        fps = frames;
        frames = 0;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

Renderer* Renderer::getInstance(){
    if (!instance)
        instance = new Renderer();
    return instance;
}

void Renderer::Stop(){
    delete instance;
    instance = NULL;
}

void Renderer::init(GLint* w,GLint* h){
    Renderer::width = w;
    Renderer::height = h;
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    //glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    //glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do

    GLfloat mat_ambient[] = { 0.3,0.3,0.3,1.0 };
    GLfloat mat_diffuse[] = { 0.1,0.1,0.7,1.0 };
    GLfloat mat_specular[] = { 0.7,0.1,0.1,1.0 };
    GLfloat mat_shininess[] = { 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //Model::init_all();
}

// https://community.khronos.org/t/strange-behavoir-with-light-rotation/55735/14
// https://stackoverflow.com/questions/8627856/how-to-rotate-my-object-with-the-light-in-opengl

//unsigned char* draw_angles_str = (unsigned char*)malloc(27 * sizeof(char));
unsigned char* draw_fps_str = (unsigned char*)malloc(27 * sizeof(char));
void Renderer::render_HUD(){
    
    //draw FPS
    /*if (draw_angles_str != NULL) {
        glColor3f(2, 2, 2);
        glRasterPos2d(5, 5);
        float yaw, pitch, roll;
        activeCamera->drawAngles(&yaw, &pitch, &roll);
        sprintf_s((char*)draw_angles_str, 27 * sizeof(char), "Y:%.2f P:%.2f R:%.2f", yaw, pitch, roll);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, draw_angles_str);
    }*/
    if (draw_fps_str != NULL) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 1);
        glRasterPos2d(5, 700);
        float yaw, pitch, roll;
        activeCamera->drawAngles(&yaw, &pitch, &roll);
        sprintf_s((char*)draw_fps_str, 27 * sizeof(char), "%u fps", Renderer::fps);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, draw_fps_str);
        glEnable(GL_LIGHTING);
    }
}

void Renderer::render_3D(){
    //glScalef(cam.Zoom, cam_zoom, cam_zoom);
    /*glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);*/

    //Model::render_all();
    glDisable(GL_LIGHTING);
    DotParticle::render_all();
    glEnable(GL_LIGHTING);
    glPushMatrix();
    snowman();
    glColor3f(0.4f, 0.2f, 0.6f);
    castle();
    glTranslatef(6, 2, 0);
    glColor3f(1, 0, 0);
    drawBox(2, GL_QUADS);
    glTranslatef(0, 1.80f, 0);
    glutSolidTeapot(1);
    glPopMatrix();
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


// NÃO TÁ SENDO USADO
void Renderer::reshape() {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75.0, GLfloat(w) / GLfloat(h), 1.0, 100.0);
    //Renderer::height = h;
    //Renderer::width= w;
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
    gluPerspective(75, GLfloat(*Renderer::width) / GLfloat(*Renderer::height), 1.0, 100.0);
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
