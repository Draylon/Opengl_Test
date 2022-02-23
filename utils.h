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

  /*{0, 1, 2, 3},
  {3, 2, 6, 7},
  {5, 4, 7, 6},
  {0, 4, 5, 1},
  {1, 5, 6, 2},
  {4, 0, 3, 7}*/
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
        glTexCoord2f(0, 0);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(0, 1);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(1, 0);
        glVertex3fv(&v[faces[i][3]][0]);
        glTexCoord2f(1, 1);
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

    if (type == GL_TRIANGLES||type==GL_TRIANGLE_STRIP) {
        for (i = 5; i >= 0; i--) {
            glBegin(type);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0, 0);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1, 1);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1, 0);
            glVertex3fv(&v[faces[i][2]][0]);
            glEnd();
            glBegin(type);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0, 0);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1, 1);
            glVertex3fv(&v[faces[i][3]][0]);
            glTexCoord2f(0, 1);
            glVertex3fv(&v[faces[i][2]][0]);
            glEnd();
        }
    }else{
        for (i = 5; i >= 0; i--) {
            glBegin(type);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0, 0);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1, 0);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1, 1);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0, 1);
            glVertex3fv(&v[faces[i][3]][0]);
            glEnd();
        }
    }
}

void getFragLen(GLfloat l, GLfloat lim_l, GLfloat* new_w, GLfloat* dim_c) {
    /*x=17
    lm = 2
    div = 8,5
    floor/ceil div = 8
    x - (lm*div) = mod?
    new_lm = lm + (mod / floor_div)
    2,125*/
    if (l <= lim_l) {
        *new_w = l;
        *dim_c = 1;
        return;// new GLfloat[]{ l,1 };
    }
    float div = l / lim_l;
    int floordiv = ceil(div);
    float m1 = l - (lim_l * floordiv);
    float new_lm = lim_l + (m1 / floordiv);
    *new_w = new_lm;
    *dim_c = floordiv;
    return;
    
    GLfloat r = 0,c=0;
    while (l >= lim_l) {
        r += lim_l;
        l -= lim_l; c++;
    }
    if (l > 0) {
        r += l / lim_l; c++;
    }
    *new_w = r - lim_l*c;
    *dim_c = c;
    //return new GLfloat[]{ r,c };
}

void drawRectFrag(GLfloat w, GLfloat h, GLfloat d,GLfloat lw,GLfloat lh,GLfloat ld, GLenum type=GL_QUADS) {
    GLfloat new_w, new_h, new_d;
    GLfloat dc_w, dc_h, dc_d;
    getFragLen(w,lw,&new_w,&dc_w);
    getFragLen(h, lh,&new_h,&dc_h);
    getFragLen(d, ld,&new_d,&dc_d);

    /*printf("%f %i\n", new_w, dc_w);
    printf("%f %i\n", new_h, dc_h);
    printf("%f %i\n", new_d, dc_d);*/
    
    /*{-1.0, 0.0, 0.0},
      {0.0, 1.0, 0.0},
      {1.0, 0.0, 0.0},
      {0.0, -1.0, 0.0},
      {0.0, 0.0, 1.0},
      {0.0, 0.0, -1.0}*/

    GLfloat dx = 0;
    GLfloat dy = 0;
    GLfloat dz = 0;
    GLfloat x0 = -w/2;
    GLfloat y0 = -h/2;
    GLfloat z0 = -d/2;
    GLfloat x1 = -w/2 + new_w;
    GLfloat y1 = -h/2 + new_h;
    GLfloat z1 = -d/2 + new_d;
    GLfloat tx0=0,ty0=0,tx1=1/dc_d, ty1= 1 / dc_h;
    //printf("%f %f %f %f\n", tx0, ty0, tx1, ty1);
    //face esq
    while (dy < dc_h){
        dz = 0;
        z0 = -d / 2;
        z1 = -d / 2 + new_d;
        tx0 = 0, tx1 = 1 / dc_d;
        while (dz < dc_d){
            glBegin(type);
            glNormal3f(-1.0f,0,0);
            glTexCoord2f(tx0, ty0);
            glVertex3f(x0,y0,z0);
            glTexCoord2f(tx1, ty0);
            glVertex3f(x0,y0,z1);
            glTexCoord2f(tx1, ty1);
            glVertex3f(x0,y1,z1);
            glTexCoord2f(tx0, ty1);
            glVertex3f(x0,y1,z0);
            glEnd();
            dz++;
            z0 += new_d;
            z1 += new_d;
            tx0 = tx1, tx1 += 1 / dc_d; 
            
        }
        dy++;
        y0 += new_h;
        y1 += new_h;
        ty0 = ty1, ty1 += 1 / dc_h;
    }
    //===========================================
    //===========================================
    //===========================================
    dz = 0;
    y0 = h / 2,z0 = -d / 2;
    z1 = -d / 2 + new_d;
    tx0 = 0, ty0 = 0, tx1 = 1 / dc_d, ty1 = 1 / dc_w;
    //face cima
    while (dx < dc_w){
        dz = 0;
        z0 = -d / 2;
        z1 = -d / 2 + new_d;
        tx0 = 0, tx1 = 1 / dc_d;
        while (dz < dc_d) {
            glBegin(type);
            glNormal3f(0, 1, 0);
            glTexCoord2f(tx0, ty0);
            glVertex3f(x0, y0, z0);
            glTexCoord2f(tx1, ty0);
            glVertex3f(x0, y0, z1);
            glTexCoord2f(tx1, ty1);
            glVertex3f(x1, y0, z1);
            glTexCoord2f(tx0, ty1);
            glVertex3f(x1, y0, z0);
            glEnd();
            dz++;
            z0 += new_d;
            z1 += new_d;
            tx0 = tx1, tx1 += 1 / dc_d; 
        }
        dx++;
        x0 += new_w;
        x1 += new_w;
        ty0 = ty1, ty1 += 1 / dc_w;
    }
    //===========================================
    //===========================================
    //===========================================
    dy = 0,dz = 0;
    x0 = w / 2,y0 = -h / 2,z0 = -d / 2;
    y1 = -h / 2 + new_h,z1 = -d / 2 + new_d;
    tx0 = 0, ty0 = 0, tx1 = 1 / dc_d, ty1 = 1 / dc_h;
    //face direita
    while (dy < dc_h){
        dz = 0;
        z0 = -d / 2;
        z1 = -d / 2 + new_d;
        tx0 = 0, tx1 = 1 / dc_d;
        while (dz < dc_d){
            glBegin(type);
            glNormal3f(1.0f, 0, 0);
            glTexCoord2f(tx1, ty0);
            glVertex3f(x0, y0, z1);
            glTexCoord2f(tx0, ty0);
            glVertex3f(x0, y0, z0);
            glTexCoord2f(tx0, ty1);
            glVertex3f(x0, y1, z0);
            glTexCoord2f(tx1, ty1);
            glVertex3f(x0, y1, z1);
            glEnd();
            dz++;
            z0 += new_d;
            z1 += new_d;
            tx0 = tx1, tx1 += 1 / dc_d;

        }
        dy++;
        y0 += new_h;
        y1 += new_h;
        ty0 = ty1, ty1 += 1 / dc_h;
    }
    //============================================
    //============================================
    //============================================
    dx = 0, dy = 0, dz = 0;
    x0 = -w / 2, y0 = -h / 2, z0 = -d / 2;
    x1 = -w / 2 + new_w, y1 = -h / 2 + new_h, z1 = -d / 2 + new_d;
    tx0 = 0, ty0 = 0, tx1 = 1 / dc_d, ty1 = 1 / dc_w;
    //face baixo
    while (dx < dc_w) {
        dz = 0;
        z0 = -d / 2;
        z1 = -d / 2 + new_d;
        tx0 = 0, tx1 = 1 / dc_d;
        while (dz < dc_d) {
            glBegin(type);
            glNormal3f(0, -1, 0);
            glTexCoord2f(tx1, ty0);
            glVertex3f(x0, y0, z1);
            glTexCoord2f(tx0, ty0);
            glVertex3f(x0, y0, z0);
            glTexCoord2f(tx0, ty1);
            glVertex3f(x1, y0, z0);
            glTexCoord2f(tx1, ty1);
            glVertex3f(x1, y0, z1);
            glEnd();
            dz++;
            z0 += new_d;
            z1 += new_d;
            tx0 = tx1, tx1 += 1 / dc_d;
        }
        dx++;
        x0 += new_w;
        x1 += new_w;
        ty0 = ty1, ty1 += 1 / dc_w;
    }

    //=================================================
    //=================================================
    //=================================================
    dx = 0, dz = 0;
    x0 = -w / 2, y0 = -h / 2, z0 = -d / 2;
    x1 = -w / 2 + new_w;
    tx0 = 0, ty0 = 0, tx1 = 1 / dc_h, ty1 = 1 / dc_w;
    //face frente
    while (dx < dc_w) {
        dy = 0;
        y0 = -h / 2;
        y1 = -h / 2 + new_h;
        tx0 = 0, tx1 = 1 / dc_h;
        while (dy < dc_h) {
            glBegin(type);
            glNormal3f(0, 0, -1);
            glTexCoord2f(tx0, ty0);
            glVertex3f(x0, y0, z0);
            glTexCoord2f(tx1, ty0);
            glVertex3f(x0, y1, z0);
            glTexCoord2f(tx1, ty1);
            glVertex3f(x1, y1, z0);
            glTexCoord2f(tx0, ty1);
            glVertex3f(x1, y0, z0);
            glEnd();
            dy++;
            y0 += new_h;
            y1 += new_h;
            tx0 = tx1, tx1 += 1 / dc_h;
        }
        dx++;
        x0 += new_w;
        x1 += new_w;
        ty0 = ty1, ty1 += 1 / dc_w;
    }
    
    dx = 0, dz = 0;
    z0 = d / 2;
    x0 = -w / 2,x1 = -w / 2 + new_w;
    tx0 = 0, ty0 = 0, tx1 = 1 / dc_h, ty1 = 1 / dc_w;
    //face tras
    while (dx < dc_w){
        dy = 0;
        y0 = -h / 2;
        y1 = -h / 2 + new_h;
        tx0 = 0, tx1 = 1 / dc_h;
        while (dy < dc_h) {
            glBegin(type);
            glNormal3f(0, 0, 1);
            glTexCoord2f(tx1, ty0);
            glVertex3f(x0, y1, z0);
            glTexCoord2f(tx0, ty0);
            glVertex3f(x0, y0, z0);
            glTexCoord2f(tx0, ty1);
            glVertex3f(x1, y0, z0);
            glTexCoord2f(tx1, ty1);
            glVertex3f(x1, y1, z0);
            glEnd();
            dy++;
            y0 += new_h;
            y1 += new_h;
            tx0 = tx1, tx1 += 1 / dc_h;
        }
        dx++;
        x0 += new_w;
        x1 += new_w;
        ty0 = ty1, ty1 += 1 / dc_w;
    }
}

void APIENTRY
glutSolidCube(GLdouble size) {
    drawBox(size, GL_QUADS);
}

static float gr(int iv) {
    float r = (float)rand() / (RAND_MAX);
    if ((float)rand() / (RAND_MAX) < 0.5)
        r *= -1;
    return r * iv;
}

#endif