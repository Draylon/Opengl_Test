#include "Movement.hpp"
#include "Camera.hpp"

#include <GL/glut.h>
#include <glm/gtx/euler_angles.hpp>

/*glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(Position, Position + Front, Up);
}*/

std::vector<Movement*> Movement::movement_list;

void Movement::updatePosition(MovementDirection m) {
    printf("Método default!!!");
    if (attached_camera!=NULL)
        attached_camera->staticUpdatePosition();
}

void Movement::attachMovement(Movement* m, glm::vec3 translateDirection){
    attachToFollow = m;
    this->translateDirection = translateDirection;
}

void Movement::attachCameraOrientation(bool yaw, bool pitch, bool roll,bool usef){
    attached_camera->bindMovementOrientations(this,yaw, pitch, roll,usef); 
}

void Movement::updateMatrix(){
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
    
    if (attached_camera != NULL)
        attached_camera->updateCameraLookAt();
}

void Movement::updateFromVector() {
    Front = glm::normalize(glm::cross(Up,Right) );
    viewMatrix = glm::translate(viewMatrix, Position);
    
}

void Movement::updateVectors(){
    glm::vec3 front;

    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, glm::vec3(0.0f, 1.0f, 0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
    if (attached_camera != NULL)
        attached_camera->updateCameraLookAt();
}

void Movement::GetRotation(float& Yaw, float& Pitch, float& Roll) const {
    if (viewMatrix[0][0] == 1.0f) {
        Yaw = atan2f(viewMatrix[0][2], viewMatrix[2][3]);
        Pitch = 0;
        Roll = 0;
    }
    else if (viewMatrix[0][0] == -1.0f) {
        Yaw = atan2f(viewMatrix[0][2], viewMatrix[2][3]);
        Pitch = 0;
        Roll = 0;
    }
    else {
        Yaw = atan2(-viewMatrix[2][0], viewMatrix[0][0]);
        Pitch = asin(viewMatrix[1][0]);
        Roll = atan2(-viewMatrix[1][2], viewMatrix[1][1]);
    }
}

void Movement::translate(GLfloat x,GLfloat y,GLfloat z) {
    glTranslatef(x, y, z);
}

void Movement::rotate() {
    glRotatef(this->Pitch, 1, 0, 0);
    glRotatef(this->Yaw, 0, -1, 0);
    glRotatef(this->Roll, 0, 0, 1);
}

glm::vec3* Movement::getOrientationVector(int i){
    switch(i){
        case 0:return &Front;
        case 1:return &Right;
        case 2:return &Up;
        default:return NULL;
    }
}

void Movement::preUpdateOrientation(float xoffset, float yoffset, float zoffset,bool useFrag) {
    if (useFrag) {
        Yaw += xoffset;
        Pitch += yoffset;
        Roll += zoffset;
        return;
    }
    Yaw = xoffset!=0?xoffset:Yaw;
    Pitch= yoffset!=0?yoffset:Pitch;
    Roll= zoffset!=0?zoffset:Roll;
}

void Movement::preSetVectors(int i, glm::vec3 v) {
    switch (i) {
    case 0:Front=v;
    case 1:Right=v;
    case 2:Up=v;
    default:return;
    }
}

void Movement::preSetViewmatrix(glm::mat4 vm) {
    viewMatrix = vm;
}

void Movement::updateOrientation(float xoffset, float yoffset, float zoffset) {
    Yaw += xoffset*MoveSensitivity, Pitch += yoffset*MoveSensitivity;
    Roll += zoffset * MoveSensitivity;
    
    if (Yaw > 180.0f) Yaw = -180.0f;
    if (Yaw < -180.0f) Yaw = 180.0f;
    if (Pitch > 180.0f) Pitch = -180.0f;
    if (Pitch < -180.0f) Pitch = 180.0f;
    if (Roll > 180.0f) Roll = -180.0f;
    if (Roll < -180.0f) Roll = 180.0f;
    if (useMatrix) updateMatrix();
    else updateVectors();
    return;
    if (xoffset != 0 || yoffset != 0) {
        xoffset *= MoveSensitivity;
        yoffset *= MoveSensitivity;
        Yaw += xoffset, Pitch += yoffset;
    }
    if (zoffset != 0) {
        zoffset *= MoveSensitivity;
        Roll += zoffset;
    }
    else {
        Roll = 0;
    }
    
}

void Movement::updateOrientation(float xoffset, float yoffset) {
    Yaw += xoffset * MoveSensitivity, Pitch += yoffset * MoveSensitivity;
    if (Yaw > 180.0f) Yaw = -180.0f;
    if (Yaw < -180.0f) Yaw = 180.0f;
    if (Pitch > 180.0f) Pitch = -180.0f;
    if (Pitch < -180.0f) Pitch = 180.0f;

    if (useMatrix) updateMatrix();
    else updateVectors();
    return;
    if (xoffset != 0 || yoffset != 0) {
        xoffset *= MoveSensitivity*MoveSensitivity;
        yoffset *= MoveSensitivity;
        Yaw = xoffset, Pitch = yoffset;
    }
}

void Movement::updateOrientation(float zoffset) {
    Roll += zoffset * MoveSensitivity;

    if (Roll > 180.0f) Roll = -180.0f;
    if (Roll < -180.0f) Roll = 180.0f;

    if (useMatrix) updateMatrix();
    else updateVectors();
    return;
    if (zoffset != 0) {
        zoffset *= MoveSensitivity;
        Roll = zoffset;
    }
    else {
        Roll = 0;
    }
}

//=======================================
//=======================================
//=======================================


void OrientationMovement::updatePosition(MovementDirection d) {

}


//=======================================
//=======================================
//=======================================


void PositionMovement::updatePosition(MovementDirection direction) {
    switch (direction) {
        case FORWARD: Position += Front * MovementSpeed;  break;
        case BACKWARD: Position -= Front * MovementSpeed; break;
        case LEFT: Position -= Right * MovementSpeed;     break;
        case RIGHT: Position += Right * MovementSpeed;    break;
        case UP: Position += Up * MovementSpeed;          break;
        case DOWN: Position -= Up * MovementSpeed;        break;
        default:break;
    }
    if (attached_camera != NULL)
        attached_camera->staticUpdatePosition();
}