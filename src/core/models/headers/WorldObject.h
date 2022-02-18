//
// Created by Israel Santos Vieira on 18/02/2022.
//

#ifndef OPENGL_WORLDOBJECT_H
#define OPENGL_WORLDOBJECT_H

#include <vector>
#include <iostream>
#include "../../tools/headers/Vector3.h"
#include "Component.h"
#include "Mesh.h"

using namespace std;

class WorldObject {
private:
    string m_Name;
    string m_ID;
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;
    bool m_Active;
    vector<Component*> m_Components;
    static int getNextID();
    static int RANDOM_ID;
    WorldObject* m_Parent;
    Mesh* m_Mesh;
public:
    WorldObject(string name, WorldObject* parent = nullptr);
    ~WorldObject();
    string getName();
    string getID();
    bool isActive();
    void setActive(bool active);
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation);
    void setScale(Vector3 scale);
    void registerComponent(Component* component);
    void setParent(WorldObject* parent);
    void setMesh(Mesh* mesh);
    WorldObject* getParent();
    Mesh* getMesh();
    Component* getComponent(string name);
    Vector3 getPosition();
    Vector3 getRotation();
    Vector3 getScale();
};


#endif //OPENGL_WORLDOBJECT_H
