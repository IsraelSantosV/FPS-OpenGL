//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/Component.h"

void Component::setEnable(bool enable) {
    if (enable){
        OnEnable();
    }
    else{
        OnDisable();
    }

    _isEnabled = enable;
}

std::string Component::getName() {
    std::string s = typeid(*this).name();
    return s.substr(6);
}

bool Component::getEnable() {
    return _isEnabled;
}

Transform * Component::getTransform() {
    return transform;
}

Entity * Component::getEntity() {
    return entity;
}

void Component::OnEnable() {}
void Component::OnDisable() {}
void Component::destroy() {}

std::type_index Component::getBaseType() {
    return typeid(Component);
}

Component::~Component() {}