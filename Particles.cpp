#include "Particles.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

std::list<DotParticle*> DotParticle::rendering_list;
std::thread DotParticle::particle_update;
bool DotParticle::particle_update_active;

void DotParticle::createParticleArray(){
    direction = glm::normalize(direction);
    glm::vec3 vb = glm::vec3(0.71f, 0.71f, 0);
    normal = glm::cross(direction, vb);
    plane = glm::cross(direction, normal);

    for (int i = 0; i < ammount; i++) {
        float ag = rand() % 720;
        ag -= 360;
        float bg = 360 - abs(ag);

        glm::vec3 v = normal * ag + plane * bg;
        v=glm::normalize(v);
        if ((double)rand() / (RAND_MAX) < 0.5f)
            v = -v;

        float r1 = ((double)rand() / (RAND_MAX / 2)) - 1,
            r2 = ((double)rand() / (RAND_MAX)),
            r3 = ((double)rand() / (RAND_MAX / 2)) - 1,
            r4 = ((double)rand() / (RAND_MAX / 2)) - 1,
            r5 = ((double)rand() / (RAND_MAX / 2)) - 1,
            r6 = ((double)rand() / (RAND_MAX / 2)) - 1;
        particles[i].vx = start_velocity * r1 * direction[0] + r5 * displacement;
        particles[i].vy = start_velocity * r2 * direction[1];
        particles[i].vz = start_velocity * r3 * direction[2] + r6 * displacement;
        particles[i].x = position[0] + v[0] * r1 * emiter_radius;
        particles[i].y = position[1] + v[1] * r3 * emiter_radius;
        particles[i].z = position[2] + v[2] * r4 * emiter_radius;
        particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
        /*int angle = rand() % 360;
        int angle2= rand() % 360;
        float r = ((double)rand() / (RAND_MAX));
        particles[i].vx = cos((M_PI * angle / 180.0)) * r * start_velocity;
        particles[i].vy = 0;
        particles[i].vz = sin((M_PI * angle / 180.0)) * r * start_velocity;
        particles[i].x = position[0]+cos((M_PI * angle2 / 180.0))*r*emiter_radius;
        particles[i].y = position[1];
        particles[i].z = position[2]+sin((M_PI * angle2 / 180.0))* r* emiter_radius;
        particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
        */
    }
}

void DotParticle::resetParticle(int i){
    float ag = rand() % 720;
    ag -= 360;
    float bg = 360 - abs(ag);

    glm::vec3 v = normal * ag + plane * bg;
    v = glm::normalize(v);
    if ((double)rand() / (RAND_MAX) < 0.5f)
        v = -v;

    float r1 = ((double)rand() / (RAND_MAX / 2)) - 1,
        r2 = ((double)rand() / (RAND_MAX)),
        r3 = ((double)rand() / (RAND_MAX / 2)) - 1,
        r4 = ((double)rand() / (RAND_MAX / 2)) - 1,
        r5 = ((double)rand() / (RAND_MAX / 2)) - 1,
        r6 = ((double)rand() / (RAND_MAX / 2)) - 1;
    particles[i].vx = start_velocity * r1 * direction[0] + r5 * displacement;
    particles[i].vy = start_velocity * r2 * direction[1];
    particles[i].vz = start_velocity * r3 * direction[2] + r6 * displacement;
    particles[i].x = position[0] + v[0] * r1 * emiter_radius;
    particles[i].y = position[1] + v[1] * r3 * emiter_radius;
    particles[i].z = position[2] + v[2] * r4 * emiter_radius;
    particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
}

void DotParticle::updateParticles(){
    while (particle_update_active){
        for (DotParticle* p : rendering_list){
            SingularParticle* particles = p->particles;
            for (int i = 0; i < p->ammount; i++){
                particles[i].x += particles[i].vx;
                particles[i].y += particles[i].vy;
                particles[i].z += particles[i].vz;
                /*if(particles[i].vx > 0)
                    particles[i].vx -= 0.3f;
                if(particles[i].vz > 0)
                    particles[i].vz -= 0.3f;*/
                //particles[i].vx = particles[i].vx * p->weight * ((double)rand() / (RAND_MAX));
                //particles[i].vz = particles[i].vz * p->weight * ((double)rand() / (RAND_MAX));
                particles[i].vy-= p->weight*0.04f * ((double)rand() / (RAND_MAX));
                particles[i].lifetime--;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    printf("Particle updater stopped\n");
}

void DotParticle::drawParticles(){
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    for (int i = 0; i < ammount; i++) {
        float r = (double)rand() / (RAND_MAX);
        glPointSize(r * 200 + 5);
        if (particles[i].lifetime<=0) {
            resetParticle(i);
        }else {
            glVertex3f(particles[i].x, particles[i].y, particles[i].z); // draw pixel
        }
    }
    glEnd();
}

void DotParticle::render_all() {
    for (DotParticle* p : rendering_list) {
        p->drawParticles();
    }
}

/*
#define NUM_PARTICLES 3000
#define GRAVITY 0.0003

struct s_pf {
    float x, y, veloc_x, veloc_y;
    unsigned lifetime;
} particles[NUM_PARTICLES];

void InitParticle(int pause){
    int i;

    if (pause) usleep(200000 + rand() % 2000000);

    for (i = 0; i < NUM_PARTICLES; i++) {
        float velocity = 0.005;
        int angle = rand() % 360;
        particles[i].veloc_x = cos((M_PI * angle / 180.0)) * velocity;
        particles[i].veloc_y = sin((M_PI * angle / 180.0)) * velocity;
        particles[i].x = 0.0;
        particles[i].y = 0.0;
        particles[i].lifetime = 200;
    }
}


*/