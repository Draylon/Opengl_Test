#ifndef CAMERA_ENTITY
#define CAMERA_ENTITY

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>
//#include <Quaternions/quaternion.h>

enum CameraMovement {
    FORWARD,BACKWARD,
    LEFT,RIGHT, 
    UP,DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ROLL= 0.0f;
const float SPEED = 0.1f;//2.5f
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

__interface ICamera{
    void updatePosition(CameraMovement);
    void updatePerspective(float xoffset, float yoffset);
    void updateOrientation(float roll);
    void ProcessMouseScroll(float);
    void updateCameraLookAt();

};

class Camera :public ICamera{
protected:
    
    float MouseSensitivity;
    float Zoom;
    bool allowUpsideDown;
    bool boundVertical;

    glm::vec3 Position;
    glm::vec3 WorldUp;

    glm::vec3 Up;
    glm::vec3 Front;
    glm::vec3 Right;
public:
    GLfloat* getPosition(int i) { return &Position[i]; }
    float MovementSpeed;
    Camera() :MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {}
    void updatePosition(CameraMovement);
    void ProcessMouseScroll(float);
    void updateCameraLookAt();
};

class EulerCamera:public Camera{
public:
    float Yaw,YawC=0;
    float Pitch,PitchC=0;
    float Roll,RollC=0;
    GLfloat fov;

    EulerCamera(GLfloat fov,bool allowUpsideDown = false,bool boundVertical=false,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
        float yaw = YAW, float pitch = PITCH,float roll = ROLL ):Camera(){
            //Front = glm::vec3(0.0f, 0.0f, -1.0f);
            this->fov = fov;
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            Roll = roll;
            this->allowUpsideDown=allowUpsideDown;
            this->boundVertical=boundVertical;
            if (boundVertical)
                updateCameraVectors = &EulerCamera::worldUpEuler;
            else
                updateCameraVectors = &EulerCamera::EulerFull;
            (this->*updateCameraVectors)();
    }
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
    ~EulerCamera() {}
    //glm::mat4 GetViewMatrix();
    void updatePerspective(float xoffset, float yoffset);
    void updateOrientation(float roll);

    void drawAngles(float*,float*,float*);

private:
    glm::mat4 viewMatrix = glm::identity<glm::mat4>();
    void (EulerCamera::*updateCameraVectors)();
    void worldUpEuler();
    void EulerLocked();
    void EulerFull();
};

class OrbitCamera {
    //TO-DO
};

class QuatCamera :public Camera {
public:
    glm::vec3 Position;
    glm::vec3 WorldUp;

    QuatCamera(bool allowUpsideDown = false, bool boundVertical = false,
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH, float roll = ROLL
    ):Camera(){
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