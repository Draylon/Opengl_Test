#ifndef GL_CASTLE
#define GL_CASTLE

#include <GL/freeglut.h>
#include <cmath>
#include "utils.h"
#include "Material.hpp"

class Castle : public Model{
public:
    Castle(GLfloat width, GLfloat height, GLfloat depth,
        glm::vec3 castle_base_color,
        GLfloat gate_gap,GLfloat tower_height,
        GLfloat top_height):Model() {
    
        this->color = castle_base_color;
        this->w = width;
        this->h = height;
        this->d = depth;
        this->gate_gap = gate_gap;
        this->tower_height = tower_height;
        this->top_height = top_height;

        this->tower_diameter = sqrt(pow(d, 2) + pow(d, 2));
    }

    void setTexture(Texture* tex) {
        this->texture = tex;
    }
    void setMat(Material* tex) {
        this->mat = tex;
    }

    virtual void render() {
        if (texture != NULL && texture != nullptr)
            texture->Bind();
        //glDisable(GL_CULL_FACE);
        
        glPushMatrix();
        
        //glColor3f(1, 0, 1);
        glColor3f(color[0], color[1], color[2]);
        GLfloat xx, yy, zz;


        //yy = h / 2;

        //glTranslatef(0,yy, 0);
        //glTranslatef(0, h / 2, 0);
        
        yy = h/2;
        yy += -h / 2 - d / 2;
        
        //glPushMatrix();
        glTranslatef(0, yy, 0);
        drawRectFrag(2 * w, d, 2 * w,3,3,3);
        //glPopMatrix();

        yy = h/2 + d/2;
        xx = -w - d / 2;

        //glPushMatrix();
        glTranslatef(xx, yy, 0);
        drawRectFrag(d, h, 2 * w,3,3,3);
        //glPopMatrix();

        xx = -xx;
        zz = -w - d / 2;

        //glPushMatrix();
        glTranslatef(xx, 0, zz);
        drawRectFrag(2 * w, h, d,3,3,3);
        //glPopMatrix();

        xx = w + d / 2;
        zz = -zz;

        //glPushMatrix();
        glTranslatef(xx, 0, zz);
        drawRectFrag(d, h, 2 * w, 3, 3, 3);
        //glPopMatrix();

        xx = -xx;
        zz = w + d / 2;
        xx += -w / 2 - gate_gap / 4;

        //glPushMatrix();
        glTranslatef(xx, 0,zz);
        drawRectFrag(w - gate_gap / 2, h, d, 3, 3, 3);
        //glPopMatrix();

        //xx = -xx;
        xx = w + gate_gap/2;
        //xx += w / 2 + d/4;
        zz = 0;

        //glPushMatrix();
        glTranslatef(xx, 0, zz);
        drawRectFrag(w - gate_gap / 2, h, d, 3, 3, 3);
        //glPopMatrix();

        glPopMatrix();
        //glRotatef(90, 0, 1, 0);
        //create_rect(2 * w, h, d, -w, 0, -w);

        //glPopMatrix();

        GLUquadricObj* pObj = gluNewQuadric();
        glPushMatrix();

        glTranslatef(-w - d / 2, 0, -w - d / 2);
        glRotatef(90, -1, 0, 0);
        //gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
        //drawPillar(pObj);

        glTranslatef(2 * w + d, 0, 0);
        //gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
        //drawPillar(pObj);

        glTranslatef(0, -2 * w - d, 0);
        //gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
        //drawPillar(pObj);

        glTranslatef(-2 * w - d, 0, 0);
        //gluCylinder(pObj, tower_diameter, tower_diameter, tower_height, 26, 13);
        //drawPillar(pObj);

        glPopMatrix();
        
        if (texture != NULL && texture != nullptr)
            texture->Unbind();

        //glEnable(GL_CULL_FACE);
    }
private:
    void drawPillar(GLUquadricObj* pObj) {
        glPushMatrix();
        glTranslatef(0, 0, tower_height);
        glRotatef(180, 1, 0, 0);
        gluDisk(pObj, 0, tower_diameter * 1.5, 26, 13);
        glRotatef(180, 1, 0, 0);
        gluCylinder(pObj, tower_diameter * 1.5, 2 * tower_diameter / 3, top_height / 3, 26, 13);
        glTranslatef(0, 0, top_height / 3);
        gluCylinder(pObj, 2 * tower_diameter / 3, 0, 2 * top_height / 3, 26, 13);
        glPopMatrix();
    }

    GLfloat w, h, d, gate_gap,tower_height,top_height;
    GLfloat tower_diameter;
    glm::vec3 color;

    Texture* texture;
    Material* mat;
};




/*void castle() {
    
}*/

#endif