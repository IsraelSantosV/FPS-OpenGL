//
// Created by Israel Santos Vieira on 18/02/2022.
//

#include "headers/Scenario.h"
#include "../models/meshes/CubeMesh.h"

Scenario* Scenario::m_Instance = nullptr;
Scenario *Scenario::getInstance() {
    if(m_Instance == nullptr){
        m_Instance = new Scenario();
    }

    return m_Instance;
}

Scenario::Scenario() {
    WorldObject* cubeObj = new WorldObject("Cube");
    cubeObj->setMesh(new CubeMesh(false));
}

void Scenario::registerObject(WorldObject *obj) {
    if(obj == nullptr) return;
    m_RuntimeObjects.push_back(obj);
}

void Scenario::drawScenario() {
    for(auto i = m_RuntimeObjects.begin(); i != m_RuntimeObjects.end(); ++i){
        auto obj = *i;
        if(obj == nullptr || !obj->isActive()) continue;
        if(obj->getMesh() == nullptr) continue;
        obj->getMesh()->draw();
    }
}
