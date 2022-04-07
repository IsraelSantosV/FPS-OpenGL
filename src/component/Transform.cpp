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

Quaternion Transform::getRotation() {
    return m_Rotation;
}

Vector3 Transform::getPosition() {
    return m_Position;
}

Vector3 Transform::getScale() {
    return m_Scale;
}

void Transform::setPosition(Vector3 position) {
    if (position != m_Position) {
        m_Position = position;
        setChanged();
    }
}

void Transform::setRotation(Vector3 rotation) {
    setRotation(Quaternion(0, rotation));
}

void Transform::setRotation(Quaternion rotation) {
    if (rotation != m_Rotation) {
        m_Rotation = rotation;
        setChanged();
    }
}

void Transform::setScale(Vector3 scale) {
    if (scale != m_Scale) {
        m_Scale = scale;
        setChanged();
    }
}

void Transform::rotate(Quaternion quaternion) {
    m_Rotation = (quaternion * m_Rotation);
    m_Rotation.normalize();
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
