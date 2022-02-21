//
// Created by zetta on 21/02/2022.
//

#include "Transform.h"

Transform::Transform(WorldObject *wo) : Component(wo) {
    setPosition(Vector3());
    setRotation(Vector3());
    setScale(Vector3(1,1,1));
}

void Transform::setPosition(Vector3 position) {
    m_Position.set(position.X(), position.Y(), position.Z());
}

void Transform::setRotation(Vector3 rotation) {
    m_Position.set(rotation.X(), rotation.Y(), rotation.Z());
}

void Transform::setScale(Vector3 scale) {
    m_Position.set(scale.X(), scale.Y(), scale.Z());
}

Vector3 Transform::getPosition() {
    return m_Position;
}

Vector3 Transform::getRotation() {
    return m_Rotation;
}

Vector3 Transform::getScale() {
    return m_Scale;
}
