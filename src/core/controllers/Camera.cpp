//
// Created by Israel Santos Vieira on 17/02/2022.
//

#define TO_RADIANS 3.14/180.0
#include <GL/glut.h>
#include <math.h>
#include "headers/Camera.h"

Camera::Camera() { }

void Camera::receiveMousePosition(int x, int y) {
    float sensibility = getSensibility();
    Vector3 currentRot = getRotation();
    float currentYaw = currentRot.X();
    float currentPitch = currentRot.Y();

    float targetYaw = isFreeze() ? currentYaw : currentYaw + (float)x/sensibility;
    float targetPitch = isFreeze() ? currentPitch : currentPitch + (float)y/sensibility;
    setRotation(Vector3(targetYaw, targetPitch));
}

void Camera::updateMovement() {
    InputKey* forward = InputManager::getInstance()->getKey("Vertical", true);
    InputKey* backward = InputManager::getInstance()->getKey("Vertical", false);
    InputKey* right = InputManager::getInstance()->getKey("Horizontal", true);
    InputKey* left = InputManager::getInstance()->getKey("Horizontal", false);

    float yaw = getRotation().X();
    float pitch = getRotation().Y();

    if(forward != nullptr && forward->isPressed()){
        setMovement(Vector3(
                getPosition().X() + cos((yaw+90)*TO_RADIANS)/getSpeed(), 0,
                getPosition().Z() - sin((yaw+90)*TO_RADIANS)/getSpeed()
        ));
    }
    if(backward != nullptr && backward->isPressed()){
        setMovement(Vector3(
                getPosition().X() + cos((yaw+90+180)*TO_RADIANS)/getSpeed(), 0,
                getPosition().Z() - sin((yaw+90+180)*TO_RADIANS)/getSpeed()
        ));
    }
    if(right != nullptr && right->isPressed()){
        setMovement(Vector3(
                getPosition().X() + cos((yaw+90-90)*TO_RADIANS)/getSpeed(), 0,
                getPosition().Z() - sin((yaw+90-90)*TO_RADIANS)/getSpeed()
        ));
    }
    if(left != nullptr && left->isPressed()){
        setMovement(Vector3(
                getPosition().X() + cos((yaw+90+90)*TO_RADIANS)/getSpeed(), 0,
                getPosition().Z() - sin((yaw+90+90)*TO_RADIANS)/getSpeed()
        ));
    }

    glRotatef(-pitch,1.0,0.0,0.0); // Along X axis
    glRotatef(-yaw,0.0,1.0,0.0);    //Along Y axis
    glTranslatef(-getPosition().X(),0.0,-getPosition().Z());
}

void Camera::setMovement(Vector3 position) {
    m_Position = Vector3(position.X(), position.Y(), position.Z());
}

void Camera::setScreenSize(int width, int height){
    m_ScreenWidth = width;
    m_ScreenHeight = height;
}

void Camera::setRotation(Vector3 rotation) {
    float clampedPitch = rotation.Y();
    if(clampedPitch >= m_VerticalLimit.X()){
        clampedPitch = m_VerticalLimit.X();
    }
    if(clampedPitch <= -m_VerticalLimit.Y()){
        clampedPitch = -m_VerticalLimit.Y();
    }

    m_Rotation.set(rotation.X(), clampedPitch, rotation.Z());
}

Vector3 Camera::getRotation() {
    return m_Rotation;
}

Vector3 Camera::getPosition() {
    return m_Position;
}

bool Camera::cursorIsLocked() {
    return m_CursorLocked;
}

void Camera::setCursorLockState(bool locked) {
    m_CursorLocked = locked;
    if(m_CursorLocked){
        glutWarpPointer(m_ScreenWidth/2,m_ScreenHeight/2);
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    else {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
}

void Camera::setVerticalLimit(Vector3 limit) {
    m_VerticalLimit.set(limit.X(), limit.Y(), limit.Z());
}

Camera* Camera::m_Instance = nullptr;
Camera *Camera::getInstance() {
    if(m_Instance == nullptr){
        m_Instance = new Camera();
    }

    return m_Instance;
}

void Camera::initialize(float speed, float sensibility) {
    m_Speed = speed;
    m_Sensibility = sensibility;
}

float Camera::getSpeed() {
    return m_Speed;
}

float Camera::getSensibility() {
    return m_Sensibility;
}

void TriggerEscapeKey(){
    Camera* currentCamera = Camera::getInstance();
    currentCamera->setCursorLockState(!currentCamera->cursorIsLocked());
    cout << "Using Escape Key!" << endl;
}

void Camera::registerActionTriggers() {
    InputKey *escapeKey = InputManager::getInstance()->getKey(ESCAPE);
    if (escapeKey != nullptr) {
        escapeKey->registerAction(TriggerEscapeKey, ONE_TIME);
    }
}

bool Camera::isFreeze() {
    return !cursorIsLocked();
}



