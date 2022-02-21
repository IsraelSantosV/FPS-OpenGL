//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#include "WorldObject.h"
#include "Mesh.h"
#include "../tools/Transform.h"

WorldObject::WorldObject(string name, WorldObject* parent) {
    m_ID = "WO_" + getNextID();
    m_Name = name;
    setParent(parent);
    m_Transform = new Transform(this);
    registerComponent(m_Transform);
}

WorldObject::~WorldObject() {
    for(auto i = m_Components.begin(); i != m_Components.end(); ++i){
        delete *i;
    }
}

int WorldObject::getNextID() {
    if(WorldObject::RANDOM_ID < 0){
        WorldObject::RANDOM_ID = 0;
    }
    return ++WorldObject::RANDOM_ID;
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

void WorldObject::setMesh(Mesh *mesh) {
    m_Mesh = mesh;
}
