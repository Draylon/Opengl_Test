/*
#ifndef ENV_ENTITY
#define ENV_ENTITY
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "LightSource.hpp"
#include "Physics.hpp"
#include "Particles.hpp"

class Environment {
private:
    static Environment* instance;
    static std::thread env_proc;
    Environment(){
        env_proc = std::thread(env_calc);
    }
    ~Environment() {
        input_stop_all = true;
        if (env_proc.joinable())
            env_proc.join();
        printf("Environment thread has been stopped\n");
    }

    static void env_calc();
public:
    
    static Environment* getInstance();
    static void init();
    static void Stop();
    ~Environment() {}
    
};

#endif
*/