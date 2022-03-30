//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/util/Time.h"

double Time::deltaTime = 0.001;
float Time::deltaTimef = 0.001f;
double Time::time = 0.0;
float Time::timeScale = 1.0f;

void Time::setDeltaTime(double deltaTime) {
    Time::deltaTime = deltaTime * timeScale;
    Time::deltaTimef = (float) deltaTime * timeScale;
    time += deltaTime;
}

void Time::setTime(double time) {
    Time::time = time;
}

void Time::setTimeScale(float timeScale) {
    Time::timeScale = timeScale;
}

double Time::now() {
    return glfwGetTime();
}