//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/Scene.h"

void Scene::unload() {
    OnUnload();
    for (auto & it : _entityList) {
        it->destroyComponents();
        delete it;
    }

    _entityList.clear();
}

void Scene::OnUnload() {}

Entity* Scene::instantiate(std::string name) {
    Entity *entity = new Entity(name);
    addToList(entity);
    return entity;
}

Entity* Scene::getObjectByName(std::string name) {
    std::vector<Entity *> entities = _entityList;
    for (auto & entity : entities) {
        if (entity->name.find(name) != std::string::npos || entity->name == name) {
            return entity;
        }
    }

    return nullptr;
}

void Scene::destroy(Entity* go) {
    go->destroy();
    removeFromList(go);
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