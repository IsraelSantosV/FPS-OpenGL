//
// Created by Israel on 22/03/2022.
//
#pragma once

#ifndef VOXENGINE_SCENE_H
#define VOXENGINE_SCENE_H

#include <iostream>
#include <vector>
#include "SceneManager.h"

class Entity;

class Scene {
public:
    virtual void Load() = 0;
    virtual void OnUnload();
    void unload();

    void addToList(Entity* go);
    void removeFromList(Entity* go);

    std::vector<Entity*>& getEntities();
private:
    std::vector<Entity*> _entityList;
};


#endif //VOXENGINE_SCENE_H
