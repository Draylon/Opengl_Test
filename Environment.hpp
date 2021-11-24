#ifndef ENV_ENTITY
#define ENV_ENTITY

class Environment {
private:
    static Environment* instance;
    Environment(){}
    //int gravity = 1;

    static void enable_lighting();
    static void terrain();

    //anotar pra fazer depois em uma classe separada
    float specular;
    float difuse;
    float global;
    float fog_depth;

public:
    static Environment& getInstance();
    static void init();

};

#endif