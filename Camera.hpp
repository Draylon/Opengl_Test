#ifndef CAMERA_ENTITY
#define CAMERA_ENTITY

#include "Entity.hpp"
#include "Movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
//#include <Quaternions/quaternion.h



__interface ICamera{
    virtual void staticUpdatePosition();
    virtual void updatePosition(MovementDirection);
    virtual void updatePerspective(float xoffset, float yoffset);
    virtual void updateOrientation(float roll);
    virtual void ProcessMouseScroll(float);
    virtual void updateCameraLookAt();

};

class Camera :public ICamera{
private:
    static std::vector<Camera*> cam_list;
protected:

    float MouseSensitivity;
    float Zoom;
    bool allowUpsideDown;

    glm::vec3 Position;
    glm::vec3 WorldUp;

    glm::vec3 Up;
    glm::vec3 Front;
    glm::vec3 Right;
public:
    static void End() {
        for (int i = 0; i < cam_list.size(); i++)
            delete cam_list[i];
    }

    GLfloat fov;
    float Yaw = 180;
    float Pitch = 0;
    float Roll = 0;

    GLfloat* getPosition(int i) { return &(Position[i]); }
    float MovementSpeed;
    Camera(GLfloat fov, float sensitivity = SENSITIVITY,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        bool allowUpsideDown = false,
        float yaw = YAW, float pitch = PITCH, float roll = ROLL)
        :MovementSpeed(SPEED), MouseSensitivity(sensitivity), Zoom(ZOOM) {
    
        this->fov = fov;
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        Roll = roll;
        this->allowUpsideDown = allowUpsideDown;
        updateCameraVectors();

        Camera::cam_list.push_back(this);
    }

    Movement* objectPosition;

    Camera(GLfloat fov, Entity* followEntity,
        float sensitivity = SENSITIVITY,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        bool allowUpsideDown = false,
        float yaw = YAW, float pitch = PITCH, float roll = ROLL)
    :Camera(fov,sensitivity,position,up,allowUpsideDown,yaw,pitch,roll) {
        objectPosition = followEntity->movement;

        objectPosition->attachCamera(this);

        this->updateCameraVectors();
        Position = *(objectPosition->getPositionVec()) - Front;
    }
    
    Camera(GLfloat fov, PositionMovement* followMovement,
        float sensitivity = SENSITIVITY,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        bool allowUpsideDown = false,
        float yaw = YAW, float pitch = PITCH, float roll = ROLL)
    :Camera(fov,sensitivity,position,up,allowUpsideDown,yaw,pitch,roll) {
        objectPosition = followMovement;

        objectPosition->attachCamera(this);

        this->updateCameraVectors();
        Position = *(objectPosition->getPositionVec()) - Front;
    }
    
    virtual void staticUpdatePosition();
    virtual void updatePerspective(float xoffset, float yoffset);
    virtual void updateOrientation(float roll);
    virtual void updatePosition(MovementDirection);
    virtual void ProcessMouseScroll(float);
    virtual void updateCameraLookAt();
    virtual void updateCameraVectors();
};

class EulerCamera:public Camera{
public:

    EulerCamera(GLfloat fov,glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
        float yaw = YAW, float pitch = PITCH,float roll = ROLL )
        :Camera(fov,false,position,up,yaw,pitch,roll) {
            //Front = glm::vec3(0.0f, 0.0f, -1.0f);
            
            /*if (boundVertical)
                updateCameraVectors = &EulerCamera::worldUpEuler;
            else
                updateCameraVectors = &EulerCamera::EulerFull;
            (this->*updateCameraVectors)();*/
        yaw = 0; pitch = 0; roll = 0;
    }
    ~EulerCamera() {}
    //glm::mat4 GetViewMatrix();
    virtual void updatePerspective(float xoffset, float yoffset);
    virtual void updateOrientation(float roll);
    virtual void updateCameraVectors();

private:
    glm::mat4 viewMatrix = glm::identity<glm::mat4>();
};

class OrbitCamera:public Camera{
protected:
    GLfloat min_distance, max_distance;

public:
    OrbitCamera(GLfloat fov, Entity* position, GLfloat min_distance,
        GLfloat max_distance, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
        :Camera(fov) {

        this->max_distance = max_distance;
        this->min_distance = min_distance;

        objectPosition = position->movement;

        objectPosition->attachCamera(this);

        this->updateCameraVectors();
        Position = *(objectPosition->getPositionVec()) - Front;
        //Position = position->movement->getPosition();
        //yaw = 0; pitch = 0; roll = 0;
    }

    virtual void staticUpdatePosition();
    virtual void updatePosition(MovementDirection);
    virtual void updatePerspective(float xoffset, float yoffset);
    virtual void updateOrientation(float roll);
    virtual void ProcessMouseScroll(float);
    virtual void updateCameraVectors();
private:
    //glm::vec3* orbitPosition;
    glm::mat4 viewMatrix = glm::identity<glm::mat4>();
};

class SimpleOrbitCamera:public Camera{
protected:
    GLfloat min_distance, max_distance;

public:
    SimpleOrbitCamera(GLfloat fov, Entity* position, GLfloat min_distance,
        GLfloat max_distance, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
        :Camera(fov) {

        this->max_distance = max_distance;
        this->min_distance = min_distance;

        objectPosition = position->movement;

        objectPosition->attachCamera(this);

        this->updateCameraVectors();
        Position = *(objectPosition->getPositionVec()) - Front;
        //Position = position->movement->getPosition();
        //yaw = 0; pitch = 0; roll = 0;
    }

    virtual void staticUpdatePosition();
    virtual void updatePosition(MovementDirection);
    virtual void updatePerspective(float xoffset, float yoffset);
    virtual void updateOrientation(float roll);
    virtual void ProcessMouseScroll(float);
    virtual void updateCameraVectors();
private:
    //glm::vec3* orbitPosition;
    Movement* objectPosition;
    glm::mat4 viewMatrix = glm::identity<glm::mat4>();
};

//===================================
//===================================
//===================================
//===================================

class QuatCamera :public Camera {
public:
    glm::vec3 Position;
    glm::vec3 WorldUp;

    QuatCamera(bool allowUpsideDown = false, bool boundVertical = false,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH, float roll = ROLL
    ):Camera(fov,false,position,up,yaw,pitch,roll) {
        //Front = glm::vec3(0.0f, 0.0f, -1.0f);
        Position = position;
        WorldUp = up;
    }

    void updatePerspective(float xoffset, float yoffset);
    void updateOrientation(float roll);
    void updateCameraLookAt();

private:
    glm::mat4x4 camMat = glm::identity<glm::mat4x4>();
    //quaternion::Quaternion<float> orientation;
    void updateCameraVectors();
};

#endif





// constructor with scalar values
/*Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch,float roll)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        Roll= roll;
        (this->*updateCameraVectors)();
    }*/