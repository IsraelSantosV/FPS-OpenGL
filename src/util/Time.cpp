//
// Created by israel on 28/02/2022.
//

#ifndef FP_OPENGL_TIME_CPP
#define FP_OPENGL_TIME_CPP

#include "vox-engine/util/Time.h"

double Time::deltaTime = 0.001;
float Time::deltaTimeF = 0.001f;
double Time::time = 0.0;
float Time::timeScale = 1.0f;

void Time::setDeltaTime(double deltaTime) {
    Time::deltaTime = deltaTime * timeScale;
    Time::deltaTimeF = (float) deltaTime * timeScale;
    time += deltaTime;
}

void Time::setTime(double time) {
    Time::time = time;
}

void Time::setTimeScale(float timeScale) {
    Time::timeScale = timeScale;
}

double Time::now() {
    return glutGet(GLUT_ELAPSED_TIME);
}

#endif //FP_OPENGL_TIME_CPP