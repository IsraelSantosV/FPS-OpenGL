//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_WORLDOBJECT_H
#define FP_OPENGL_WORLDOBJECT_H
#include <vector>
#include <iostream>
#include "../tools/Vector3.h"
#include "Component.h"
#include "Mesh.h"
using namespace std;

class WorldObject {
private:
    string m_Name;
    string m_ID;
    Transform* m_Transform;
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
    void registerComponent(Component* component);
    void setParent(WorldObject* parent);
    void setMesh(Mesh *mesh);
    WorldObject* getParent();
    Mesh* getMesh();
    Component* getComponent(string name);
};


#endif //FP_OPENGL_WORLDOBJECT_H
