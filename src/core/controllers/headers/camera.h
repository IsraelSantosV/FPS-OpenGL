//
// Created by zetta on 17/02/2022.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include "../../tools/headers/vector3.h"
#include "../../input/headers/inputManager.h"

class camera {
private:
    int m_ScreenWidth;
    int m_ScreenHeight;
    vector3 m_Position;
    vector3 m_Rotation;
    vector3 m_ClampedAngle;
    float m_Speed;
    bool m_CursorLocked;
    camera();
public:
    static camera& getInstance();
    void setScreenSize(int width, int height);
    void updateMovement();
    void setMovement(vector3 position);
    void setRotation(vector3 rotation);
    vector3 getRotation();
    vector3 getPosition();
    void setCursorLockState(bool locked);
    bool cursorIsLocked();
};


#endif //OPENGL_CAMERA_H
