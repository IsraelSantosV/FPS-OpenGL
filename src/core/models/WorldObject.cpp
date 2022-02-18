//
// Created by Israel Santos Vieira on 18/02/2022.
//

#include "headers/WorldObject.h"

WorldObject::WorldObject(string name, WorldObject* parent) {
    m_ID = "WO_" + getNextID();
    m_Name = name;
    setParent(parent);
}

WorldObject::~WorldObject() {
    for(auto i = m_Components.begin(); i != m_Components.end(); ++i){
        delete *i;
    }
}

int WorldObject::getNextID() {
    if(RANDOM_ID < 0){
        RANDOM_ID = 0;
    }
    return ++RANDOM_ID;
}

string WorldObject::getName() {
    return m_Name;
}

string WorldObject::getID() {
    return m_ID;
}

bool WorldObject::isActive() {
    return m_Active;
}

void WorldObject::setActive(bool active) {
    m_Active = active;
}

void WorldObject::setPosition(Vector3 position) {
    m_Position.set(position.X(), position.Y(), position.Z());
}

void WorldObject::setRotation(Vector3 rotation) {
    m_Rotation.set(rotation.X(), rotation.Y(), rotation.Z());
}

void WorldObject::setScale(Vector3 scale) {
    m_Scale.set(scale.X(), scale.Y(), scale.Z());
}

void WorldObject::registerComponent(Component *component) {
    m_Components.push_back(component);
}

Component *WorldObject::getComponent(string name) {
    for(auto i = m_Components.begin(); i != m_Components.end(); ++i){
        auto element = *i;
        if(element->getName() == name){
            return element;
        }
    }

    return nullptr;
}

void WorldObject::setParent(WorldObject *parent) {
    m_Parent = parent;
}

WorldObject *WorldObject::getParent() {
    return m_Parent;
}

Mesh *WorldObject::getMesh() {
    return m_Mesh;
}

void WorldObject::setMesh(Mesh* mesh) {
    m_Mesh = mesh;
}

Vector3 WorldObject::getPosition() {
    return m_Position;
}

Vector3 WorldObject::getRotation() {
    return m_Rotation;
}

Vector3 WorldObject::getScale(){
    return m_Scale;
}
