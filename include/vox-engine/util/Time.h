//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_TIME_H
#define VOXENGINE_TIME_H

#include "vox-engine/resources/OpenGL.h"

class Time {
public:
    static double deltaTime;
    static float deltaTimeF;
    static double time;
    static float timeScale;

    void setDeltaTime(double deltaTime);
    void setTime(double time);
    void setTimeScale(float timeScale);
    static double now();
};

#endif //VOXENGINE_TIME_H
