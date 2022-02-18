//
// Created by Israel Santos Vieira on 18/02/2022.
//

#ifndef OPENGL_COMPONENT_H
#define OPENGL_COMPONENT_H
using namespace std;
#include <iostream>
#include "WorldObject.h"

class Component {
private:
    string m_Name;
    WorldObject* m_Object;
public:
    Component(WorldObject* wo);
    string getName();
    WorldObject* getObject();
};


#endif //OPENGL_COMPONENT_H
