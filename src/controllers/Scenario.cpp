//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#include "Scenario.h"

Scenario* Scenario::m_Instance = nullptr;
Scenario *Scenario::getInstance() {
    if(m_Instance == nullptr){
        m_Instance = new Scenario();
    }

    return m_Instance;
}

Scenario::Scenario() {

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
