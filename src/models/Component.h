//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_COMPONENT_H
#define FP_OPENGL_COMPONENT_H

#include <iostream>
#include "WorldObject.h"
using namespace std;

class Component {
private:
    string m_Name;
    WorldObject* m_Object;
public:
    Component(WorldObject* wo) { m_Object = wo; };
    string getName(){ return m_Name; };
    WorldObject* getObject(){ return m_Object; };
};


#endif //FP_OPENGL_COMPONENT_H
