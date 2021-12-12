#ifndef PROJ_UTILS
#define PROJ_UTILS

#include<GL/freeglut.h>

static GLfloat n[6][3] = {
      {-1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, -1.0}
};
static GLint faces[6][4] = {
  {0, 1, 2, 3},
  {3, 2, 6, 7},
  {7, 6, 5, 4},
  {4, 5, 1, 0},
  {5, 6, 2, 1},
  {7, 4, 0, 3}
};

static void
drawBox(GLfloat size, GLenum type){
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(type);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void drawRect(GLfloat w, GLfloat h, GLfloat d, GLenum type=GL_QUADS) {
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -w / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = w / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -h / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = h / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -d / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = d / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(type);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void APIENTRY
glutSolidCube(GLdouble size) {
    drawBox(size, GL_QUADS);
}


#endif