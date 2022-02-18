//
// Created by Israel Santos Vieira on 18/02/2022.
//

#ifndef OPENGL_SCENARIO_H
#define OPENGL_SCENARIO_H
#include <vector>
#include "../../models/headers/WorldObject.h"

class Scenario {
private:
    vector<WorldObject*> m_RuntimeObjects;
    static Scenario* m_Instance;
    Scenario();
public:
    static Scenario* getInstance();
    void drawScenario();
    void registerObject(WorldObject* obj);
};


#endif //OPENGL_SCENARIO_H
