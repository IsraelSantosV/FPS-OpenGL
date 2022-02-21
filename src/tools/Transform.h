//
// Created by zetta on 21/02/2022.
//

#ifndef FP_OPENGL_TRANSFORM_H
#define FP_OPENGL_TRANSFORM_H


#include "Vector3.h"
#include "../models/Component.h"

class Transform : public Component {
private:
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;
public:
    Transform(WorldObject *wo);
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation);
    void setScale(Vector3 scale);
    Vector3 getPosition();
    Vector3 getRotation();
    Vector3 getScale();
};

#endif //FP_OPENGL_TRANSFORM_H
