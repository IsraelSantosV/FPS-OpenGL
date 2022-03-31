//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_COMPONENT_H
#define VOXENGINE_COMPONENT_H

#include <iostream>
#include <typeindex>
#include "Entity.h"

class Component {
public:
    void setEnable(bool enable);
    std::string getName();
    bool getEnable();
    Entity* getEntity();

    void setup(Entity* entity){
        this->entity = entity;
        init();
    }

    virtual ~Component() = 0;
    virtual void init() {}
    virtual void OnEnable();
    virtual void OnDisable();
    virtual void destroy();
    virtual std::type_index getBaseType();
protected:
    Entity* entity;
private:
    bool _isEnabled = true;
};

#endif //VOXENGINE_COMPONENT_H
