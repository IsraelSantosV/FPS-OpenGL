//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_ENTITY_H
#define VOXENGINE_ENTITY_H

#include <iostream>
#include <unordered_map>
#include <typeindex>
#include "vox-engine/component/Transform.h"
#include "vox-engine/component/Mesh.h"

class Entity {
public:
    Transform* transform;
    Mesh* mesh;
    std::string name;

    Entity() = default;
    Entity(std::string _name);

    template <class T>
    T* addComponent() {
        if (_componentMap.find(typeid(T)) != _componentMap.end()) {
            Logger::warnln(name, "Entity already contains Component");
            return nullptr;
        }

        T *c = new T();
        c->setup(this);

        _componentMap.insert(std::pair<std::type_index, Component *>(typeid(T), c));
        return c;
    }

    template<class T>
    T* getComponent() {
        if (_componentMap.find(typeid(T)) == _componentMap.end()) {
            for (auto & it : _componentMap) {
                if (typeid(T).hash_code() == it.second->getBaseType().hash_code()) {
                    return (T *) it.second;
                }
            }

            //Logger::warnln("Component", typeid(T).name(), "could not be found!");
            return nullptr;
        }

        return (T *) _componentMap[typeid(T)];
    }

    template <class T>
    void removeComponent() {
        T *c = getComponent<T>();
        _componentMap.erase(typeid(T));
        delete c;
    }

    void removeComponent(std::type_index ti) {
        Component *c = _componentMap[ti];
        c->destroy();
        _componentMap.erase(ti);
        delete c;
    }

    void setMesh(Mesh* targetMesh){
        mesh = targetMesh;
        targetMesh->setup(this);
        _componentMap.insert(std::pair<std::type_index, Component *>(typeid(Mesh), targetMesh));
    }

    std::vector<Component*> getAllComponents(){
        std::vector<Component*> components;
        for(auto& pair : _componentMap){
            components.push_back(pair.second);
        }

        return components;
    }

    void destroyComponents();
    void destroy();
    int getId();
    void setEnable(bool enable);
    bool getEnable() { return _isEnabled; }
    void setStatic(bool _static);
    bool getStatic() { return _isStatic; }
private:
    static int _idCnt;
    bool _isEnabled;
    bool _isStatic;
    int _id;
    std::unordered_map<std::type_index, Component*> _componentMap;
};


#endif //VOXENGINE_ENTITY_H
