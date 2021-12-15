#include "Particles.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

std::list<DirectedParticle*> DirectedParticle::rendering_list;
std::list<Firework*> Firework::rendering_list;
std::thread DirectedParticle::particle_update;
std::thread Firework::firework_update;
bool DirectedParticle::particle_update_active;
bool Firework::firework_update_active;

void DirectedParticle::createParticleArray(){
    glm::vec3 vb = glm::vec3(0.71f, 0.71f, 0);
    normal = glm::cross(direction, vb);
    plane = glm::cross(direction, normal);
    ammount = default_ammount;
    if (emiter_radius==0){
        for (int i = 0; i < ammount; i++) {
            float r1 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r2 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r3 = ((double)rand() / (RAND_MAX / 2)) - 1;

            particles[i].velocity[0] = start_velocity * r1 * displacement;
            particles[i].velocity[1] = start_velocity * r2 * displacement;
            particles[i].velocity[2] = start_velocity * r3 * displacement;
            particles[i].position[0] = position[0];
            particles[i].position[1] = position[1];
            particles[i].position[2] = position[2];
            //particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
            particles[i].lifetime = lifetime * ((double)rand() / (RAND_MAX));
        }
    } else {
        for (int i = 0; i < ammount; i++) {
            float ag = rand() % 720;
            ag -= 360;
            float bg = 360 - abs(ag);

            glm::vec3 v = normal * ag + plane * bg;
            v = glm::normalize(v);
            if ((double)rand() / (RAND_MAX) < 0.5f)
                v = -v;

            float r1 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r2 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r3 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r4 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r5 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r6 = ((double)rand() / (RAND_MAX / 2)) - 1;

            particles[i].velocity[0] = start_velocity * direction[0] + r1 * displacement;
            particles[i].velocity[1] = start_velocity * direction[1] + r2 * displacement;
            particles[i].velocity[2] = start_velocity * direction[2] + r3 * displacement;
            particles[i].position[0] = position[0] + v[0] * r4 * emiter_radius;
            particles[i].position[1] = position[1] + v[1] * r5 * emiter_radius;
            particles[i].position[2] = position[2] + v[2] * r6 * emiter_radius;
            //particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
            particles[i].lifetime = lifetime * ((double)rand() / (RAND_MAX));
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
}

void DirectedParticle::animate() {
    particles = (SingularParticle*)malloc(sizeof(SingularParticle) * ammount);
    this->createParticleArray();
    rendering_list.push_back(this);
    if (!particle_update_active) {
        particle_update_active = true;
        particle_update = std::thread(updateParticles);
    }
}
void DirectedParticle::pre_animate() {
    particles = (SingularParticle*)malloc(sizeof(SingularParticle) * ammount);
    rendering_list.push_back(this);
    if (!particle_update_active) {
        particle_update_active = true;
        particle_update = std::thread(updateParticles);
    }
}

void DirectedParticle::resetParticle(int i){
    if (emiter_radius==0) {
        float r1 = ((double)rand() / (RAND_MAX / 2)) - 1,
            r2 = ((double)rand() / (RAND_MAX / 2)) - 1,
            r3 = ((double)rand() / (RAND_MAX / 2)) - 1;

        particles[i].velocity[0] = start_velocity * r1 * displacement;
        particles[i].velocity[1] = start_velocity * r2 * displacement;
        particles[i].velocity[2] = start_velocity * r3 * displacement;
        particles[i].position[0] = position[0];
        particles[i].position[1] = position[1];
        particles[i].position[2] = position[2];
        //particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
        particles[i].lifetime = lifetime * ((double)rand() / (RAND_MAX));
    }else{
        float ag = rand() % 720;
        ag -= 360;
        float bg = 360 - abs(ag);

        glm::vec3 v = normal * ag + plane * bg;
        v = glm::normalize(v);
        if ((double)rand() / (RAND_MAX) < 0.5f)
            v = -v;

        float r1 = ((float)rand() / (RAND_MAX / 2)) - 1,
            r2 = ((float)rand() / (RAND_MAX / 2)) - 1,
            r3 = ((float)rand() / (RAND_MAX / 2)) - 1,
            r4 = ((float)rand() / (RAND_MAX / 2)) - 1,
            r5 = ((float)rand() / (RAND_MAX / 2)) - 1,
            r6 = ((float)rand() / (RAND_MAX / 2)) - 1;

        particles[i].velocity[0] = start_velocity * direction[0] + r1 * displacement;
        particles[i].velocity[1] = start_velocity * direction[1] + r2 * displacement;
        particles[i].velocity[2] = start_velocity * direction[2] + r3 * displacement;
        particles[i].position[0] = position[0] + v[0] * r4 * emiter_radius;
        particles[i].position[1] = position[1] + v[1] * r5 * emiter_radius;
        particles[i].position[2] = position[2] + v[2] * r6 * emiter_radius;
        //particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
        particles[i].lifetime = lifetime * ((double)rand() / (RAND_MAX));
    }
}

void DirectedParticle::updateParticles(){
    std::list<DirectedParticle*>::iterator rp;
    while (particle_update_active){
        rp=rendering_list.begin();
        for (; rp != rendering_list.end();) {
            DirectedParticle* p = *rp++;
            if (p->swirl != 0){
                SingularParticle* particles = p->particles;
                if (p->ammount > 360){
                    for (int i = 0; i < p->ammount; i++) {
                        float ag = (((i+p->swirl_cycles) % 360) * PI180);
                        float bg = 6.2831853071 - abs(ag);
                        glm::vec3 swl = glm::normalize(p->normal * cos(ag) + p->plane * sin(bg)) * p->swirl;

                        particles[i].position += particles[i].velocity;
                        particles[i].velocity += (*p->gravity - particles[i].velocity) * p->weight * ((float)rand() / (RAND_MAX));
                        particles[i].velocity += swl;
                        particles[i].lifetime--;
                    }
                } else {
                    for (int i = 0; i < p->ammount; i++) {
                        float ag = ((i+p->swirl_cycles) * 360 / p->ammount) * PI180;
                        float bg = 6.2831853071 - abs(ag);
                        glm::vec3 swl = glm::normalize(p->normal * cos(ag) + p->plane * sin(bg)) * p->swirl;

                        particles[i].position += particles[i].velocity;
                        particles[i].velocity += (*p->gravity - particles[i].velocity) * p->weight * ((float)rand() / (RAND_MAX));
                        particles[i].velocity += swl;
                        particles[i].lifetime--;
                    }
                }
                p->swirl_cycles+=p->swirl_cycle;
                if (p->swirl_cycles > 360)
                    p->swirl_cycles = 0;
                //std::cout << std::endl << std::endl;
            }else {
                SingularParticle* particles = p->particles;
                for (int i = 0; i < p->ammount; i++) {
                    particles[i].position += particles[i].velocity;
                    particles[i].velocity += (*p->gravity - particles[i].velocity) * p->weight * ((float)rand() / (RAND_MAX));
                    particles[i].lifetime--;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    printf("Particle updater stopped\n");
}

void DirectedParticle::drawParticles(){
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    for (int i = 0; i < ammount; i++) {
        float r = (double)rand() / (RAND_MAX);
        glPointSize(r * 200 + 5);
        if (particles[i].lifetime<=0) {
            if(reset_particle)
                resetParticle(i);
            else {
                particles[i] = particles[ammount - 1];
                ammount--;
            }
        }else {
            glVertex3f(particles[i].position[0], particles[i].position[1], particles[i].position[2]); // draw pixel
        }
    }
    glEnd();
}

void DirectedParticle::render_all() {
    for (DirectedParticle* p : rendering_list) {
        p->drawParticles();
    }
}

//==========================================================
//==========================================================
//==========================================================


void Firework::animate(){
    //trail_particles = (DotParticle**)malloc(sizeof(DotParticle*) * ammount);
    //explosion_particles = (DotParticle**)malloc(sizeof(DotParticle*) * ammount);
    firework_particle = (FireworkParticle*)malloc(sizeof(FireworkParticle) * ammount);
    for (int i = 0; i < ammount; i++) {
        trail_particles[i] = trail_template->clone();
        explosion_particles[i] = explosion_template->clone();
    }
    this->createFireworkArray();
    rendering_list.push_back(this);
    if (!firework_update_active) {
        firework_update_active = true;
        firework_update = std::thread(updateFireworks);
    }
}

void Firework::createFireworkArray(){
    glm::vec3 vb = glm::vec3(0.71f, 0.71f, 0);
    normal = glm::cross(direction, vb);
    plane = glm::cross(direction, normal);

    if (emiter_radius == 0) {
        for (int i = 0; i < ammount; i++) {
            trail_particles[i]->stop_animation();
            explosion_particles[i]->stop_animation();

            float r1 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r2 = ((double)rand() / (RAND_MAX / 2)) - 1,
                r3 = ((double)rand() / (RAND_MAX / 2)) - 1;

            firework_particle[i].status = 0; // trailing
            firework_particle[i].velocity = start_velocity * direction;
            firework_particle[i].position = position;
            //firework_particle[i].lifetime = lifetime * ((double)rand() / (RAND_MAX));
            firework_particle[i].lifetime = (lifetime / 2) + ((lifetime / 2) * ((double)rand() / (RAND_MAX)));
            trail_particles[i]->position = firework_particle[i].position;
            trail_particles[i]->animate();
            explosion_particles[i]->pre_animate();
        }
    }else {
        for (int i = 0; i < ammount; i++) {
            trail_particles[i]->stop_animation();
            explosion_particles[i]->stop_animation();
            float ag = rand() % 720;
            ag -= 360;
            float bg = 360 - abs(ag);

            glm::vec3 v = normal * ag + plane * bg;
            v = glm::normalize(v);
            if ((double)rand() / (RAND_MAX) < 0.5f)
                v = -v;

            float r1 = ((double)rand() / (RAND_MAX / 2)) - 1;
            v = v * r1 * emiter_radius;

            firework_particle[i].status = 0; // trailing
            firework_particle[i].velocity = start_velocity * direction;
            firework_particle[i].position = position + v;
            //firework_particle[i].lifetime = lifetime * ((double)rand() / (RAND_MAX));
            firework_particle[i].lifetime = (lifetime / 2) + (( lifetime / 2) * ((double)rand() / (RAND_MAX)));
            trail_particles[i]->position = firework_particle[i].position;
            trail_particles[i]->animate();
            explosion_particles[i]->pre_animate();
        }
    }
}

void Firework::updateFireworks(){
    std::list<Firework*>::iterator rp;
    while (firework_update_active){
        rp = rendering_list.begin();
        for (; rp != rendering_list.end();){
            Firework* p = *rp++;
            //std::vector<DotParticle*>* firework_trail_element = &p->trail_particles;
            //std::vector<DotParticle*>* firework_expls_element = &p->explosion_particles;
            FireworkParticle* firework_particle = p->firework_particle;
            for (int i = 0; i < p->ammount; i++){
                firework_particle[i].position += firework_particle[i].velocity;
                //printf("%d %u %u\n",i, firework_particle[i].lifetime, firework_particle[i].status);
                if (firework_particle[i].status == 0) { // trailing
                    firework_particle[i].velocity += (*p->gravity - firework_particle[i].velocity) * 0.05f * ((float)rand() / (RAND_MAX));
                    firework_particle[i].lifetime--;

                    p->trail_particles[i]->position = firework_particle[i].position;
                    if (firework_particle[i].lifetime <= 0){
                        p->trail_particles[i]->reset_particle = !p->trail_particles[i]->reset_particle;
                        firework_particle[i].status = 1; // explode
                        firework_particle[i].lifetime += p->trail_particles[i]->lifetime + 5;
                        p->explosion_particles[i]->position = firework_particle[i].position;
                        p->explosion_particles[i]->createParticleArray();
                    }
                }else if (firework_particle[i].lifetime > 0){
                    firework_particle[i].velocity += (*p->gravity - firework_particle[i].velocity) * 0.005f * ((float)rand() / (RAND_MAX));
                    firework_particle[i].lifetime--;

                    p->explosion_particles[i]->position = firework_particle[i].position;
                } else if(p->reset_firework){
                    p->resetFirework(i);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    printf("Firework updater stopped\n");
}

void Firework::resetFirework(int i){
    //printf("resetting firework %d\n", i);
    if (emiter_radius == 0) {
        float r1 = ((double)rand() / (RAND_MAX / 2)) - 1;

        firework_particle[i].status = 0; // trailing
        firework_particle[i].velocity = start_velocity * direction;
        firework_particle[i].position = position;
        //particles[i].lifetime = lifetime / 2 + (lifetime / 2) * ((double)rand() / (RAND_MAX));
        firework_particle[i].lifetime = (lifetime / 2) + ((lifetime / 2) * ((double)rand() / (RAND_MAX)));

        trail_particles[i]->reset_particle = !trail_particles[i]->reset_particle;
        trail_particles[i]->position = firework_particle[i].position;
        trail_particles[i]->createParticleArray();
    } else {
        float ag = rand() % 720;
        ag -= 360;
        float bg = 360 - abs(ag);

        glm::vec3 v = normal * ag + plane * bg;
        v = glm::normalize(v);
        if ((double)rand() / (RAND_MAX) < 0.5f)
            v = -v;

        float r1 = ((double)rand() / (RAND_MAX / 2)) - 1;
        v = v * r1 * emiter_radius;

        firework_particle[i].status = 0; // trailing
        firework_particle[i].velocity = start_velocity * direction;
        firework_particle[i].position = position + v;
        //firework_particle[i].lifetime = lifetime * ((double)rand() / (RAND_MAX));
        firework_particle[i].lifetime = (lifetime / 2) + ((lifetime / 2) * ((double)rand() / (RAND_MAX)));

        trail_particles[i]->reset_particle = !trail_particles[i]->reset_particle;
        trail_particles[i]->position = firework_particle[i].position;
        trail_particles[i]->createParticleArray();
    }
}
