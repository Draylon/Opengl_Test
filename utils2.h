#ifndef UTILS2
#define UTILS2

#include<GL/freeglut.h>

static float gr(int iv) {
    float r = (float)rand() / (RAND_MAX);
    if ((float)rand() / (RAND_MAX) < 0.5)
        r *= -1;
    return r * iv;
}

#endif