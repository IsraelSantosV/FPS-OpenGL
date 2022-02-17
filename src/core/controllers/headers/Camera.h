//
// Created by zetta on 17/02/2022.
//

#ifndef OPENGL_CAMERA_H
#define OPENGL_CAMERA_H

#include "../../tools/headers/Vector3.h"
#include "../../input/headers/InputManager.h"

class Camera {
private:
    int m_ScreenWidth;
    int m_ScreenHeight;
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_VerticalLimit;
    float m_Speed;
    float m_Sensibility;
    bool m_CursorLocked;
    static Camera* m_Instance;
    Camera();
public:
    static Camera* getInstance();
    void setScreenSize(int width, int height);
    void initialize(float speed, float sensibility);
    void updateMovement();
    void setVerticalLimit(Vector3 limit);
    void setMovement(Vector3 position);
    void setRotation(Vector3 rotation);
    Vector3 getPosition();
    Vector3 getRotation();
    float getSpeed();
    float getSensibility();
    void setCursorLockState(bool locked);
    bool cursorIsLocked();
};


#endif //OPENGL_CAMERA_H
