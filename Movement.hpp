#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>


//#include "Camera.hpp"

class Camera;

/*
// euler: se mover com direction normal
// vect:  se mover na direção de um vetor
*/

enum MovementDirection {
    FORWARD, BACKWARD,
    LEFT, RIGHT,
    UP, DOWN
};

/*const float YAW = 180.0f;
const float PITCH = 0.0f;
const float ROLL= 0.0f;
const float SPEED = 0.1f;//2.5f
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;*/

const float YAW = 0.0f;
const float PITCH = 0.0f;
const float ROLL = 0.0f;
const float SPEED = 0.1f;//2.5f
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Movement{
protected:

    GLfloat fov;

    float MoveSensitivity;
    bool allowUpsideDown;

    glm::vec3 Position;

    glm::vec3 Up;
    glm::vec3 Front;
    glm::vec3 Right;
    
    bool cameraOrientationDriven;
    Camera *attached_camera;
    Movement* attachToFollow;

public:
    float Yaw = 0;
    float Pitch = 0;
    float Roll = 0;

    static Movement* defaultBuild() {
        return new Movement(glm::vec3(0, 0, 0), 1.0f);
    }

    virtual void translate() {
        if (attachToFollow != NULL)
            attachToFollow->translate();
        glTranslatef(Position[0], Position[1], Position[2]);
    }
    virtual void translate(GLfloat x, GLfloat y, GLfloat z);
    virtual void rotate();

    void attachCamera(Camera* c) {
        this->attached_camera = c;
    }
    void detachCamera() { this->attached_camera = nullptr; }
    void attachMovement(Movement* m) {attachToFollow = m;}
    void detachMovement() {attachToFollow = nullptr;}
    void attachCameraOrientation() { cameraOrientationDriven = true; }
    void detachCameraOrientation() { cameraOrientationDriven = false; }

    glm::vec3* getPositionVec() { return &Position; }
    GLfloat getPosition(int i) { return (Position)[i]; }
    glm::vec3* getOrientationVector(int);

    float MovementSpeed;
    Movement(glm::vec3 position, GLfloat speed,GLfloat movement_attenuation=0.0f,
        float yaw = YAW, float pitch = PITCH, float roll = ROLL)
        :MovementSpeed(speed), MoveSensitivity(SENSITIVITY) {

        Yaw = yaw;
        Pitch = pitch;
        Roll = roll;

        //Front = glm::vec3(0.0f, 0.0f, -1.0f);
        Position = position;
        this->allowUpsideDown = allowUpsideDown;

        //updateVectors();
        updateMatrix();

        movement_list.push_back(this);
    }
    ~Movement() {
        printf("movement destructor called\n");
    }
    virtual void updateVectors();
    virtual void updateMatrix();
    virtual void updatePosition(MovementDirection);
    virtual void updateOrientation(float xoffset, float yoffset, float zoffset);
    virtual void updateOrientation(float xoffset, float yoffset);
    virtual void updateOrientation(float zoffset);
    inline void GetRotation(float& Yaw, float& Pitch, float& Roll) const;
    

    static void End() {
        for (int i = 0; i < movement_list.size(); i++)
            delete movement_list[i];
    }

private:
    glm::mat4 viewMatrix = glm::identity<glm::mat4>();
    static std::vector<Movement*> movement_list;
};



class PositionMovement : public Movement{
protected:
public:
    static PositionMovement* defaultBuild() {
        return new PositionMovement(glm::vec3(0, 0, 0), 1.0f);
    }
    PositionMovement(glm::vec3 position, GLfloat speed, GLfloat movement_attenuation = 0.0f,
        float yaw = YAW, float pitch = PITCH, float roll = ROLL)
        :Movement(position,speed,movement_attenuation,yaw,pitch,roll) {

        
    }
    virtual void updatePosition(MovementDirection);
    //virtual void updateOrientation(float xoffset, float yoffset, float zoffset);
    //virtual void updateOrientation(float xoffset, float yoffset);
    //virtual void updateOrientation(float zoffset);
    //inline void GetRotation(float& Yaw, float& Pitch, float& Roll) const;

private:
    glm::mat4 viewMatrix = glm::identity<glm::mat4>();
};

class OrientationMovement : public Movement{
protected:
public:
    static OrientationMovement* defaultBuild() {
        return new OrientationMovement(glm::vec3(0, 0, 0), 1.0f);
    }
    OrientationMovement(glm::vec3 position, GLfloat speed, GLfloat movement_attenuation = 0.0f)
        :Movement(position,speed,movement_attenuation) {

        
    }
    virtual void updatePosition(MovementDirection);
    virtual void updateOrientation(float xoffset, float yoffset, float zoffset);
    //inline void GetRotation(float& Yaw, float& Pitch, float& Roll) const;

private:
    glm::mat4 viewMatrix = glm::identity<glm::mat4>();
};



#endif