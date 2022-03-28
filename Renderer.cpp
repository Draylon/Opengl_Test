#include "Renderer.hpp"

#include "snowman.cpp"
#include "castle.cpp"
//#include "randomCube.cpp"
#include "Particles.hpp"
#include "Material.hpp"
#include "Boid.hpp"
#include "Aimlab.hpp"

#define SCR_WIDTH 1580
#define SCR_HEIGHT 1020
#define SW2 SCR_WIDTH/2
#define SH2 SCR_HEIGHT/2

//Material* Renderer::singular_material;

Renderer* Renderer::instance;
Camera* Renderer::activeCamera;
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
    //glEnable(GL_POINT_SMOOTH);

    //singular_material->setMaterial();

    glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
    glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do

    //GLfloat mat_ambient[] = { 0.24725f, 0.0745f,0.1995f,1.0 };
    //GLfloat mat_diffuse[] = { 0.75164f, 0.22648f,0.60648f,1.0 };
    //GLfloat mat_specular[] = { 0.228281f, 0.366065f,0.555802f,1.0 };
    
    //GLfloat mat_ambient[] = { 0.7f, 0.0f, 0.0f, 1.0f };
    //GLfloat mat_diffuse[] = { 0.0f, 0.4f, 0.0f, 1.0f };
    //GLfloat mat_specular[] = { 0.0f, 0.0f, 0.2f, 1.0f };
    
    //GLfloat mat_shininess[] = { 90.0 };

    //glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
    
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //Model::init_all();
}

// https://community.khronos.org/t/strange-behavoir-with-light-rotation/55735/14
// https://stackoverflow.com/questions/8627856/how-to-rotate-my-object-with-the-light-in-opengl

//unsigned char* draw_angles_str = (unsigned char*)malloc(27 * sizeof(char));
unsigned char* draw_fps_str = (unsigned char*)malloc(27 * sizeof(char));
unsigned char* draw_hits_str = (unsigned char*)malloc(27 * sizeof(char));
void Renderer::render_HUD(){
    
    //draw camera angles
    /*if (draw_angles_str != NULL) {
        glColor3f(2, 2, 2);
        glRasterPos2d(5, 5);
        float yaw, pitch, roll;
        activeCamera->drawAngles(&yaw, &pitch, &roll);
        sprintf_s((char*)draw_angles_str, 27 * sizeof(char), "Y:%.2f P:%.2f R:%.2f", yaw, pitch, roll);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, draw_angles_str);
    }*/
    //draw FPS
    if (draw_fps_str != NULL) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 1);
        glRasterPos2d(5, 700);
        float yaw, pitch, roll;
        sprintf_s((char*)draw_fps_str, 27 * sizeof(char), "%u fps", Renderer::fps);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, draw_fps_str);
        glEnable(GL_LIGHTING);
    }
    
    //draw FPS
    if (draw_hits_str != NULL) {
        glDisable(GL_LIGHTING);
        glColor3f(1, 1, 1);
        glRasterPos2d(400, 700);
        sprintf_s((char*)draw_hits_str, 27 * sizeof(char), "%u", Target::player_hits);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, draw_hits_str);
        glEnable(GL_LIGHTING);
    }
    
    //draw DOT
    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    glRasterPos2d(650, 360);
    sprintf_s((char*)draw_hits_str, 27 * sizeof(char), ".", "");
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, draw_hits_str);
    glEnable(GL_LIGHTING);
    
}

void Renderer::render_3D(){
    //glScalef(cam.Zoom, cam_zoom, cam_zoom);
    /*glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);*/

    glDisable(GL_LIGHTING);
    DirectedParticle::render_all();
    Boid::render_all();
    glEnable(GL_LIGHTING);
    

    Entity::render_all();
    //Model::render_all();
    
    //snowman();
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
    //glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(75.0, GLfloat(w) / GLfloat(h), 1.0, 100.0);
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
