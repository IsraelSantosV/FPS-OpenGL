//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_SCENARIO_H
#define FP_OPENGL_SCENARIO_H

#include <vector>
#include "../models/WorldObject.h"

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


#endif //FP_OPENGL_SCENARIO_H
