#include "Camera.hpp"

#include <GL/glut.h>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>

/*glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(Position, Position + Front, Up);
}*/

std::vector<Camera*> Camera::cam_list;

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}

void Camera::updateCameraLookAt(){
    gluLookAt(Position[0],Position[1], Position[2], (Position[0] + Front[0]), (Position[1] + Front[1]), (Position[2] + Front[2]), Up[0], Up[1], Up[2]);
}

void Camera::updateOrientation(float roll){
    Roll += roll;
    if (roll > 180.0f) roll = -180.0f;
    if (roll < -180.0f) roll = 180.0f;
}


void Camera::bindViewMatrix(Movement* m) {
    send_viewMatrix = true;
    objectsMatrixBound.emplace(m);
}


void Camera::bindMovementOrientations(Movement* m, bool yaw, bool pitch, bool roll, bool usef){
        send_to_movement = true;
        objectsOrientationBound.emplace(m, BoundObjects{ yaw,pitch,roll,usef });
        //bound_yaw=yaw, bound_pitch=pitch, bound_roll=roll;
}

void Camera::staticUpdatePosition() {
    //nothing?
    Position = *(objectPosition->getPositionVec()) - Front;//this->max_distance;
}

void Camera::updatePosition(MovementDirection direction){
    switch (direction){
    case FORWARD:  Position += Front * MovementSpeed; break;
    case BACKWARD: Position -= Front * MovementSpeed; break;
    case LEFT:     Position -= Right * MovementSpeed; break;
    case RIGHT:    Position += Right * MovementSpeed; break;
    case UP:       Position += Up * MovementSpeed;    break;
    case DOWN:     Position -= Up * MovementSpeed;    break;
    default:break;
    }
}

//WorldUpEuler
void Camera::updateCameraVectors() {
    glm::vec3 front;

    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::updatePerspective(float xoff,float yoff) {
    xoff *= MouseSensitivity;
    yoff *= MouseSensitivity;
    Yaw += xoff, Pitch += yoff;
    if (!allowUpsideDown) {
        if (Pitch > 89.8f) Pitch = 89.8f;
        if (Pitch < -89.8f) Pitch = -89.8f;
    }

    if (Yaw > 180.0f) Yaw = -180.0f;
    if (Yaw < -180.0f) Yaw = 180.0f;
    if (Pitch > 180.0f) Pitch = -180.0f;
    if (Pitch < -180.0f) Pitch = 180.0f;
    this->updateCameraVectors();

    if (send_to_movement){
        for (std::pair<Movement*, BoundObjects> pr : objectsOrientationBound){
            if (pr.second.useFrag) {
                if (pr.second.pitch)
                    pr.first->preSetVectors(1, Up);
                if (pr.second.yaw)
                    pr.first->preSetVectors(0, Right);
                if (pr.second.roll)
                    pr.first->preSetVectors(2, Front);
                pr.first->updateFromVector();
            }else {
                if (pr.second.pitch)
                    pr.first->preUpdateOrientation(0, pr.second.useFrag?xoff:Pitch, 0, pr.second.useFrag);
                if (pr.second.yaw)
                    pr.first->preUpdateOrientation(pr.second.useFrag?yoff:Yaw, 0, 0, pr.second.useFrag);
                if (pr.second.roll)
                    pr.first->preUpdateOrientation(0, 0, Roll, pr.second.useFrag);
                if (pr.second.useFrag)
                    pr.first->updateMatrix();
                else pr.first->updateVectors();
            }
            
        }
    }
    if (send_viewMatrix) {
        for (Movement* m : objectsMatrixBound) {
            m->preSetViewmatrix(this->viewMatrix);
        }
    }
}

//=======================================
//=======================================
//=======================================

void EulerCamera::updateOrientation(float roll){
    if (roll != 0){
        roll *= MouseSensitivity;
        Roll = roll;
    }else{
        Roll = 0;
    }
    this->updateCameraVectors();
}

void EulerCamera::updatePerspective(float xoffset, float yoffset){
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    Yaw = xoffset, Pitch = yoffset;
    this->updateCameraVectors();
}

/*
void EulerCamera::EulerLocked(){
    glm::vec3 a, b, c;

    float cosY = cosf(glm::radians(Yaw)), sinY = sinf(glm::radians(Yaw)),
        cosP = cosf(glm::radians(Pitch)), sinP = sinf(glm::radians(Pitch)),
        cosR = cosf(glm::radians(Roll)), sinR = sinf(glm::radians(Roll));

    a.x = cosY * cosR + sinY * sinP * sinR;
    a.y = cosR * sinY * sinP - sinR * cosY;
    a.z = cosP * sinY;

    b.x = cosP * sinR;
    b.y = cosR * cosP;
    b.z = -sinP;

    c.x = sinR * cosY * sinP - sinY * cosR;
    c.y = sinY * sinR + cosR * cosY * sinP;
    c.z = cosP * cosY;

    Front = glm::normalize(a);
    Right = glm::normalize(c);
    Up = glm::normalize(b);
}
*/


void EulerCamera::updateCameraVectors(){
    if(Yaw!=0)
        viewMatrix = glm::rotate(viewMatrix, glm::radians(Yaw), glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
    if(Pitch!=0)
        viewMatrix = glm::rotate(viewMatrix, glm::radians(Pitch), glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
    if(Roll!=0)
        viewMatrix = glm::rotate(viewMatrix, glm::radians(Roll), glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));

    /*
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Yaw), glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Pitch), glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Roll), glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));
    */
    
    /*
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Yaw), glm::vec3(0,1,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Pitch), glm::vec3(1,0,0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Roll), glm::vec3(0,0,1));
    */

    //printf("%f %f %f\n", Yaw, Pitch, Roll);
    //viewMatrix *= glm::eulerAngleXYZ(glm::radians(Pitch), glm::radians(Yaw), glm::radians(Roll));
    
    /*viewMatrix = glm::rotate(viewMatrix, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Pitch), glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(Roll), glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
    */

    //glm::quat rot = glm::angleAxis(glm::radians(Yaw), glm::vec3(1, 0, 0));
    //glm::mat4 rotMatrix = glm::mat4_cast(rot);

    viewMatrix = glm::translate(viewMatrix, Position);

    Front = glm::normalize(glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));
    Up= glm::normalize(glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
    Right= glm::normalize(-glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
}



//=======================================================
//=======================================================
//=======================================================
//=======================================================

void OrbitCamera::ProcessMouseScroll(float scroll) {
    this->max_distance += scroll;
    if (max_distance < min_distance) max_distance = min_distance;
}

void OrbitCamera::staticUpdatePosition() {
    Position = *(objectPosition->getPositionVec()) - Front * this->max_distance;
}

void OrbitCamera::updatePosition(MovementDirection m) {
    // ?
    //printf("não chamar isso\nposition = entity->movement->Position");

    //objectPosition - distancia do objeto
    //objectPosition - Front?
    //ObjectMovement != trigger CameraMovement
}

void OrbitCamera::updatePerspective(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    Yaw = xoffset, Pitch = yoffset;
    this->updateCameraVectors();
    this->staticUpdatePosition();
}

void OrbitCamera::updateOrientation(float roll) {
    if (roll != 0) {
        roll *= MouseSensitivity;
        Roll = roll;
    }else {
        Roll = 0;
    }
    this->updateCameraVectors();
    this->staticUpdatePosition();
}

void OrbitCamera::updateCameraVectors(){
    if (Yaw != 0)
        viewMatrix = glm::rotate(viewMatrix, glm::radians(Yaw), glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
    if (Pitch != 0)
        viewMatrix = glm::rotate(viewMatrix, glm::radians(Pitch), glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
    if (Roll != 0)
        viewMatrix = glm::rotate(viewMatrix, glm::radians(Roll), glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));

    viewMatrix = glm::translate(viewMatrix, Position);

    Front = glm::normalize(glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]));
    Up = glm::normalize(glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
    Right = glm::normalize(-glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
}



//=======================================================
//=======================================================
//=======================================================
//=======================================================

/*
void matrixFromQuat(quaternion::Quaternion<float>quat,glm::mat4x4 *Matrix){
    float a = quat.a();
    float x = quat.b();
    float y = quat.c();
    float z = quat.d();
    //Column 1
    Matrix[0][0] = (a * a) + (x * x) - (y * y) - (z * z);
    Matrix[1] = (2 * x * y) + (2 * a * z);
    Matrix[2] = (2 * x * z) - (2 * a * y);
    Matrix[3] = 0;
    //Column 2
    Matrix[4] = (2 * x * y) - (2 * a * z);
    Matrix[5] = (a * a) - (x * x) + (y * y) - (z * z);
    Matrix[6] = (2 * y * z) + (2 * a * x);
    Matrix[7] = 0;
    //Column 3
    Matrix[8] = (2 * x * z) + (2 * a * y);
    Matrix[9] = (2 * y * z) - (2 * a * x);
    Matrix[10] = (a * a) - (x * x) - (y * y) + (z * z);
    Matrix[11] = 0;
    //Column 4
    Matrix[12] = 0;
    Matrix[13] = 0;
    Matrix[14] = 0;
    Matrix[15] = 1;
}
*/


void QuatCamera::updatePerspective(float xoffset, float yoffset){
    const glm::vec2 d(xoffset,yoffset);
    //retrieve camera matrix
    //const Mat4x4f& mat = _context.getCamMat();
    const glm::vec3 right(camMat[0][0], camMat[1][0], camMat[2][0]);
    const glm::vec3 up(camMat[0][1], camMat[1][1], camMat[2][1]);
    const glm::vec3 front(camMat[0][2], camMat[1][2], camMat[2][2]);
    // determine rotation axis for orbit navigation
    const glm::vec3 axis = glm::normalize(d.y * right + d.x * up);
    
    //glm::mat4x4 camMat()
    /*_context.setCamMat(
        Mat4x4f(InitTrans, _centerOrbit)
        * Mat4x4f(InitRot, axis, -2.0f * (float)Pi * length(d))
        * Mat4x4f(InitTrans, -_centerOrbit)
        * mat);*/
}

void QuatCamera::updateOrientation(float roll){

}

void QuatCamera::updateCameraVectors(){
    //glm::quat rot = glm::angleAxis(glm::radians(angle_in_degrees), glm::vec3(x, y, z));
    //glm::mat4 rotMatrix = glm::mat4_cast(rot);
    return;
    /*
    float a = orientation.a(),x = orientation.b(),y=orientation.c(),z=orientation.d();
    Right = glm::vec3(
        (a * a) + (x * x) - (y * y) - (z * z),
        (2 * x * y) + (2 * a * z),
        (2 * x * z) - (2 * a * y));

    Up = glm::vec3(
    (2 * x * y) - (2 * a * z),
    (a * a) - (x * x) + (y * y) - (z * z),
    (2 * y * z) + (2 * a * x));
    
    Front = glm::vec3((2 * x * z) + (2 * a * y),
        (2 * y * z) - (2 * a * x),
        (a * a) - (x * x) - (y * y) + (z * z));
    
    */
}