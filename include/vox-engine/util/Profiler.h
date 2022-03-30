//
// Created by zetta on 30/03/2022.
//

#ifndef VOXENGINE_PROFILER_H
#define VOXENGINE_PROFILER_H

#include "MaxQueue.h"
#include <limits>
#include <iostream>
#include <string>

#define FRAME_WINDOW_SIZE 30

class Profiler {
public:
    static const int WARMUP_SECONDS = 6;

    static void addFps(int fps);
    static int getMinFps() { return _minFPS; }
    static int getMaxFps() { return _maxFPS; }
    static int getAvgFps() { return (int) _avgFPS; }

    void reset();
    void nextFrame();
    static void drawGraph();
private:
    static int _minFPS;
    static int _maxFPS;
    static float _avgFPS;
    static unsigned long int _allFrames;
    static unsigned long int _allSeconds;
    static MaxQueue<float> _frames;

    static void startProfiling();
};


#endif //VOXENGINE_PROFILER_H
