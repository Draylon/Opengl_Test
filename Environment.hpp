#ifndef ENV_ENTITY
#define ENV_ENTITY
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Environment {
private:
    static Environment* instance;
    Environment(){
        lightPos[0] = 5.0f;
        lightPos[1] = 0.3f;
        lightPos[2] = -4.0f;
        lightPos[3] = 1.0f;
        lightDir[0] = 0;
        lightDir[1] = -1;
        lightDir[2] = 0;
    }
    //int gravity = 1;

    static void enable_lighting();
    static void terrain();

    //anotar pra fazer depois em uma classe separada
    float specular;
    float difuse;
    float global;
    float fog_depth;
public:
    static GLfloat lightPos[4];
    static GLfloat lightDir[3];
    static Environment* getInstance();
    static void init();
    static void Stop();
    ~Environment() {}
    static void repositionLights();
};

#endif