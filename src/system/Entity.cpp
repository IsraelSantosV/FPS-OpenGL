//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/Entity.h"

int Entity::_idCnt = 0;

Entity::Entity(std::string _name) {
    _componentMap = std::unordered_map<std::type_index, Component *>();
    name = _name;
    _id = Entity::_idCnt++;
    _isEnabled = true;
    _isStatic = true;
    transform = addComponent<Transform>();
    transform->setup(this);
}

void Entity::destroyComponents() {
    for (auto it = _componentMap.begin(); it != _componentMap.end();) {
        Component *c = _componentMap[(it->first)];
        c->destroy();
        it = _componentMap.erase(it);
        delete c;
    }
}

void Entity::destroy() {
    std::vector<Transform *> children = transform->getChildren();
    for (auto & it : children) {
        it->getEntity()->destroy();
    }

    destroyComponents();
}

int Entity::getId() {
    return _id;
}

void Entity::setEnable(bool enable) {
    for (auto it : _componentMap) {
        it.second->setEnable(enable);
    }

    std::vector<Transform *> children = transform->getChildren();
    for (auto & it : children) {
        it->getEntity()->setEnable(enable);
    }

    _isEnabled = enable;
}

void Entity::setStatic(bool _static) {
    _isStatic = _static;
}
