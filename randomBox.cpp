#ifndef BOX_ENTITY
#define BOX_ENTITY

#include "Entity.hpp"
#include "utils.h"
#include "Material.hpp"

//class RandomBox : public Entity {
//public:
//	RandomBox(glm::vec3 box_color) :Entity() {
//		this->color = box_color;
//	}
//
//	void render() {
//		glTranslatef(
//			this->movement->getPosition(0),
//			this->movement->getPosition(1),
//			this->movement->getPosition(2));
//		glColor3f(1, 0, 0);
//		drawBox(2, GL_QUADS);
//	}
//
//private:
//	glm::vec3 color;
//};

class RandomBox : public Model {

    GLfloat v[8][3];
    glm::vec3* color;
    GLfloat w, h, d;
    GLenum type;
    Texture* texture;
    Material* mat;

public:
    RandomBox(GLfloat width, GLfloat height, GLfloat depth, GLenum type = GL_QUADS)
        : Model() {
        this->w = width;
        this->h = height;
        this->d = depth;
        this->type = type;

        v[0][0] = v[1][0] = v[2][0] = v[3][0] = -w / 2;
        v[4][0] = v[5][0] = v[6][0] = v[7][0] = w / 2;
        v[0][1] = v[1][1] = v[4][1] = v[5][1] = -h / 2;
        v[2][1] = v[3][1] = v[6][1] = v[7][1] = h / 2;
        v[0][2] = v[3][2] = v[4][2] = v[7][2] = -d / 2;
        v[1][2] = v[2][2] = v[5][2] = v[6][2] = d / 2;
    }
    RandomBox(Material* default_,Texture* tex, GLfloat width, GLfloat height, GLfloat depth, GLenum type = GL_QUADS)
        :RandomBox(width,height,depth,type) {
        //this->color = color;
        this->texture = tex;
        this->mat = default_;
    }
    void setTexture(Texture* tex) {
        this->texture = tex;
    }
    void setMat(Material* tex) {
        this->mat = tex;
    }
    virtual void render(){
        //glColor3f((*color)[0], (*color)[1], (*color)[2]);
        glColor3f(1, 1, 1);
        
        mat->apply();

        if (texture != NULL && texture != nullptr)
            texture->Bind();
        GLint i;

        for (i = 5; i >= 0; i--) {
            glBegin(this->type);
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
        if (texture != NULL && texture != nullptr)
            texture->Unbind();

    }

};

#endif