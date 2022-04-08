//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_COMPONENT_H
#define VOXENGINE_COMPONENT_H

#include <iostream>
#include <typeindex>
class Entity;

class Component {
public:
    Entity* getEntity() { return _entity; }
    void setEnable(bool enable);
    std::string getName();
    bool getEnable();

    void setup(Entity* entity){
        _entity = entity;
        init();
    }

    virtual ~Component() = 0;
    virtual void init() {}
    virtual void OnEnable();
    virtual void OnDisable();
    virtual void destroy();
    virtual std::type_index getBaseType();
private:
    Entity* _entity;
    bool _isEnabled = true;
};

#endif //VOXENGINE_COMPONENT_H
