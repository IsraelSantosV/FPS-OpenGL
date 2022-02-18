//
// Created by Israel Santos Vieira on 18/02/2022.
//

#ifndef OPENGL_SCENARIO_H
#define OPENGL_SCENARIO_H


class Scenario {
private:
    static Scenario* m_Instance;
    Scenario();
public:
    static Scenario* getInstance();
    void drawScenario();
};


#endif //OPENGL_SCENARIO_H
