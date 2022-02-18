//
// Created by Israel Santos Vieira on 18/02/2022.
//

#include "headers/Scenario.h"
#include "../tools/headers/Drawer.h"

Scenario* Scenario::m_Instance = nullptr;
Scenario *Scenario::getInstance() {
    if(m_Instance == nullptr){
        m_Instance = new Scenario();
    }

    return m_Instance;
}

Scenario::Scenario() { }

void Scenario::drawScenario() {
    Drawer::drawSolidCube(Vector3(), Vector3(1,1,1), Vector3(1, 0, 0));
}
