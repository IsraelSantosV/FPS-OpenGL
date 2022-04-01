//
// Created by Israel on 22/03/2022.
//
#pragma once

#ifndef VOXENGINE_SCENE_H
#define VOXENGINE_SCENE_H

#include <iostream>
#include <vector>
#include "Entity.h"

class Scene {
public:
    virtual void Load() = 0;
    virtual void OnUnload();
    void unload();

    Entity *instantiate(std::string name);
    void destroy(Entity *go);
    void removeFromList(Entity *go);
    Entity *getObjectByName(std::string name);
    std::vector<Entity *> &getEntities();
private:
    std::vector<Entity *> _entityList;
    void addToList(Entity *go);
};


#endif //VOXENGINE_SCENE_H
