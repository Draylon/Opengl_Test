#ifndef GL_CASTLE
#define GL_CASTLE

#include <GL/freeglut.h>
#include "utils.h"

void castle() {
    //glDisable(GL_CULL_FACE);
    glPushMatrix();

    GLfloat w = 15, h = 3, d = 2, gate_gap = 4;

    create_rect(2 * w, h, d, -w, 0, -w);
    glRotatef(90, 0, 1, 0);
    create_rect(2 * w, h, d, -w, 0, -w);
    glRotatef(90, 0, 1, 0);

    create_rect(w - gate_gap / 2, h, d, -w, 0, -w);
    create_rect(w - gate_gap / 2, h, d, gate_gap / 2, 0, -w);

    glRotatef(90, 0, 1, 0);
    create_rect(2 * w, h, d, -w, 0, -w);



    glPopMatrix();
    //glEnable(GL_CULL_FACE);
}

#endif