//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/component/Transform.h"

Transform * Transform::getParent() {
    return m_Parent;
}

std::vector<Transform*> Transform::getChildren() {
    return m_Children;
}

void Transform::removeChild(Transform * child) {
    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
}

quat Transform::getRotation() {
    return m_Rotation;
}

vec3 Transform::getPosition() {
    return m_Position;
}

vec3 Transform::getScale() {
    return m_Scale;
}

void Transform::setPosition(vec3 position) {
    if (position != m_Position) {
        m_Position = position;
        setChanged();
    }
}

void Transform::setRotation(vec3 rotation) {
    setRotation(quat(0, rotation));
}

void Transform::setRotation(quat rotation) {
    if (rotation != m_Rotation) {
        m_Rotation = rotation;
        setChanged();
    }
}

void Transform::setScale(vec3 scale) {
    if (scale != m_Scale) {
        m_Scale = scale;
        setChanged();
    }
}

void Transform::rotate(quat quaternion) {
    m_Rotation = (quaternion * m_Rotation);
    m_Rotation = normalize(m_Rotation);
    setChanged();
}

void Transform::setParent(Transform *parent) {
    if (m_Parent == parent) return;

    if (m_Parent != nullptr) {
        m_Parent->removeChild(this);
    }

    m_Parent = parent;

    if (parent != nullptr)
        parent->m_Children.push_back(this);

    setChanged();
}

void Transform::setChanged() { }
