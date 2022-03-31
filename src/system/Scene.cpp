//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/Scene.h"

void Scene::unload() {
    OnUnload();
    for (auto & it : _entityList) {
        (*it)->destroyComponents();
        delete it;
    }

    _entityList.clear();
}

void Scene::OnUnload() {}

Entity* Scene::instantiate(std::string name) {
    auto *entity = new Entity(*this, name);
    addToList(entity);
    entity->parentScene = this;
    return entity;
}

Entity* Scene::getObjectByName(std::string name) {
    std::vector<Entity *> entitys = SceneManager::getCurrentScene()->_entityList;
    for (std::vector<Entity *>::iterator obj = entitys.begin(); obj != entitys.end(); ++obj) {
        if ((*obj)->name.find(name) != std::string::npos || (*obj)->name.compare(name) == 0) {
            return *obj;
        }
    }
    return nullptr;
}

void Scene::destroy(Entity* go) {
    go->destroy();
}

void Scene::addToList(Entity* go) {
    _entityList.push_back(go);
}

void Scene::removeFromList(Entity* go) {
    _entityList.erase(std::remove(_entityList.begin(), _entityList.end(), go), _entityList.end());
    delete go;
}

std::vector<Entity*>& Scene::getEntities() {
    return _entityList;
}