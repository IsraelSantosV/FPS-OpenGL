//
// Created by Israel Santos Vieira on 18/02/2022.
//

#include "headers/Component.h"

string Component::getName() {
    return m_Name;
}

WorldObject *Component::getObject() {
    return m_Object;
}

Component::Component(WorldObject *wo) {
    m_Object = wo;
}
