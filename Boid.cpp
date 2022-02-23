#include "Boid.hpp"
#include "utils.h"

std::vector<Boid*> Boid::boids_list;
std::list<Boid*> Boid::rendering_list;
std::thread Boid::boids_update;
bool Boid::boids_update_active;

void Boid::updateGeneralTrajectory(){
    while (boids_update_active) {
        for (Boid* p : rendering_list) {
            if (p == NULL)continue;
            if (!boids_update_active) break;

            p->updateTrajectory();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    printf("Boid updater stopped\n");
}

void Boid::updateTrajectory() {
    
    if (this->seek.size() == 0 && this->flee.size() == 0)
        return;//temporário enquanto não implementa physics global
    glm::vec3 avg = *this->Front;

    //if (this->seek.size() == 0)
        for (Boid* ib : this->seek) {
            glm::vec3 vec = *ib->Position - *this->Position;
            float dist = glm::length(vec);
            if (dist < ib->seek_range) {
                avg += ib->seek_strength * glm::vec3(vec);
            }
        }
    //if (this->flee.size() == 0)
        for (Boid* ib : this->flee) {
            glm::vec3 vec = *ib->Position - *this->Position;
            float dist = glm::length(vec);
            if (dist < ib->flee_range) {
                avg -= ib->flee_strength * glm::vec3(vec);
            }
        }

    avg = glm::normalize(avg);
    *this->Position += *this->Front * 0.2f;
    *this->Front = avg;
    /* trajectory:
    interpolate all seek with their range and radius
        product: seek vector
    interpolate all flee with their range and radius
        product: flee vector
    sum seek_vector and flee vector */
}

void Boid::animate() {
    if (!boids_update_active){
        for (Boid* p : boids_list) rendering_list.push_back(p);
        boids_update_active = true;
        boids_update = std::thread(updateGeneralTrajectory);
    }
}

void Boid::stop_animate() {
    boids_update_active = false;
    if (boids_update.joinable()) boids_update.join();
    rendering_list.clear();
}

void Boid::render() {
    //printf("%f %f %f - %f %f %p\n", p->Position[0], p->Position[1], p->Position[2], p->seek_range, p->seek_strength,p);
    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_POINTS);

    //float r = (double)rand() / (RAND_MAX);
    //glPointSize(r * 2 + 5);
    glm::vec3 p = *this->Position;
    glVertex3f(p[0], p[1], p[2]); // draw pixel
    //glVertex3f(this->Position[0], this->Position[1], this->Position[2]); // draw pixel
    glEnd();
}

void Boid::render_all() {
    for (Boid* p : rendering_list) {
        p->render();
    }
    //printf("\n");
}


//==============================
//==============================
//==============================


std::list<Boid*> Boid::generate_boid_swarm(unsigned int ammount) {
    std::list<Boid*> ret;
    for (int i = 0; i < ammount; i++){
        glm::vec3 rpos(*this->Position);
        glm::vec3 rfrt(*this->Front);
        rpos[0] += gr(1);
        rpos[1] += gr(1);
        rpos[2] += gr(1);
        rfrt = glm::normalize(glm::vec3(
            rfrt[0] + gr(7),
            rfrt[1] + gr(7),
            rfrt[2] + gr(7)
        ));
        Boid* bb=new Boid(rpos,rfrt, glm::vec3(1, 1, 1), this->model, this->physics, this->seek_strength, this->flee_strength, this->seek_range, this->flee_range, this->auto_avoid_collision);
        
        //bb->Front = glm::normalize(bb->Front);
        bb->add_seeker(this);
        bb->add_fleeing(this);
        ret.push_back(bb);
    }
    return ret;
}

void Boid::set_swarm_behaviour(std::list<Boid*> list, BoidSwarmBehaviour behaviour) {
    if (behaviour == BoidSwarmBehaviour::FLEE_EACHOTHER) {
        for (Boid* b : list) {
            for (Boid* b2: list) {
                if (b != b2)
                    b->add_fleeing(b2);
            }
        }
    }
}


//==========================================
//==========================================
//==========================================
//==========================================

void ControlBoid::render() {
    //printf("%f %f %f - %f %f %p\n", p->Position[0], p->Position[1], p->Position[2], p->seek_range, p->seek_strength,p);
    glColor3f(this->color[0], this->color[1], this->color[2]);
    glBegin(GL_POINTS);
    //float r = (double)rand() / (RAND_MAX);
    //glPointSize(r * 2 + 5);
    //glVertex3fv(*this->Position)
    glm::vec3 p = *this->Position;
    glVertex3f(p[0], p[1], p[2]); // draw pixel
    //glVertex3f(p[0], p[1], p[2]); // draw pixel
    glEnd();
}

void ControlBoid::updateTrajectory() {

    if (this->seek.size() == 0 && this->flee.size() == 0)
        return;//temporário enquanto não implementa physics global
    glm::vec3 avg = *this->Front;

    //if (this->seek.size() == 0)
    for (Boid* ib : this->seek) {
        glm::vec3 vec = *ib->Position - *this->Position;
        float dist = glm::length(vec);
        if (dist < ib->seek_range) {
            avg += ib->seek_strength * glm::vec3(vec);
        }
    }
    //if (this->flee.size() == 0)
    for (Boid* ib : this->flee) {
        glm::vec3 vec = *ib->Position - *this->Position;
        float dist = glm::length(vec);
        if (dist < ib->flee_range) {
            avg -= ib->flee_strength * glm::vec3(vec);
        }
    }

    avg = glm::normalize(avg);
    *this->Position += *this->Front * 0.2f;
    *this->Front = avg;
    /* trajectory:
    interpolate all seek with their range and radius
        product: seek vector
    interpolate all flee with their range and radius
        product: flee vector
    sum seek_vector and flee vector */
}