//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/Scene.h"

void Scene::unload() {
    OnUnload();
    for (auto & it : _entityList) {
        SceneManager::destroyComponentsFromEntity(it);
        //(*it)->destroyComponents();
        delete it;
    }

    _entityList.clear();
}

void Scene::OnUnload() {}

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