//
// Created by zetta on 17/02/2022.
//

#define TO_RADIANS 3.14/180.0
#include <GL/glut.h>
#include <math.h>
#include "headers/camera.h"

camera::camera() { }

void camera::updateMovement() {
    inputKey forward = inputManager.getInstance().getKey("Vertical", true);
    inputKey backward = inputManager.getInstance().getKey("Vertical", false);
    inputKey right = inputManager.getInstance().getKey("Horizontal", true);
    inputKey left = inputManager.getInstance().getKey("Horizontal", false);

    float camX = getPosition().X();
    float camZ = getPosition().Z();
    float yaw = getRotation().X();
    float pitch = getRotation().Y();

    if(!manager.isInvalidKey(forward) && forward.getState() == PRESSED){
        setMovement(vector3(
                camX + cos((yaw+90)*TO_RADIANS/m_Speed), 0,
                camZ - sin((yaw+90)*TO_RADIANS/m_Speed)
        ));
    }
    if(!manager.isInvalidKey(backward) && backward.getState() == PRESSED){
        setMovement(vector3(
                camX + cos((yaw+90+180)*TO_RADIANS/m_Speed), 0,
                camZ - sin((yaw+90+180)*TO_RADIANS/m_Speed)
        ));
    }
    if(!manager.isInvalidKey(right) && right.getState() == PRESSED){
        setMovement(vector3(
                camX + cos((yaw+90+90)*TO_RADIANS/m_Speed), 0,
                camZ - sin((yaw+90+90)*TO_RADIANS/m_Speed)
        ));
    }
    if(!manager.isInvalidKey(left) && left.getState() == PRESSED){
        setMovement(vector3(
                camX + cos((yaw+90-90)*TO_RADIANS/m_Speed), 0,
                camZ - sin((yaw+90-90)*TO_RADIANS/m_Speed)
        ));
    }

    glRotatef(-pitch,1.0,0.0,0.0); // Along X axis
    glRotatef(-yaw,0.0,1.0,0.0);    //Along Y axis
    glTranslatef(-getPosition().X(),0.0,-getPosition().Z());
}

void camera::setMovement(vector3 position) {
    m_Position.set(position.X(), position.Y(), position.Z());
}

void camera::setScreenSize(int width, int height){
    m_ScreenWidth = width;
    m_ScreenHeight = height;
}

void camera::setRotation(vector3 rotation) {
    float clampedPitch = rotation.Y();
    if(clampedPitch >= m_ClampedAngle.X()){
        clampedPitch = m_ClampedAngle.X();
    }
    if(clampedPitch <= -m_ClampedAngle.Y()){
        clampedPitch = -m_ClampedAngle.Y();
    }

    m_Rotation.set(rotation.X(), clampedPitch, rotation.Z());
}

vector3 camera::getRotation() {
    return m_Rotation;
}

vector3 camera::getPosition() {
    return m_Position;
}

bool camera::cursorIsLocked() {
    return m_CursorLocked;
}

void camera::setCursorLockState(bool locked) {
    m_CursorLocked = locked;
    if(m_CursorLocked){
        glutWarpPointer(m_ScreenWidth/2,m_ScreenHeight/2);
        glutSetCursor(GLUT_CURSOR_NONE);
    }
    else {
        glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    }
}
