//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_TIME_H
#define VOXENGINE_TIME_H

#include <GLFW/glfw3.h>

class Time {
public:
    static double deltaTime;
    static float deltaTimef;
    static double time;
    static float timeScale;

    void setDeltaTime(double deltaTime);
    void setTime(double time);
    void setTimeScale(float timeScale);
    static double now();
};


#endif //VOXENGINE_TIME_H
