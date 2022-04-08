//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_APPLICATION_H
#define VOXENGINE_APPLICATION_H

#include <iostream>
#include <map>
#include <vector>

#include "vox-engine/system/Display.h"
#include "vox-engine/system/Logic.h"
#include "vox-engine/system/Scene.h"
#include "vox-engine/system/InputManager.h"
#include "vox-engine/system/SceneManager.h"
#include "vox-engine/util/Time.h"
#include "vox-engine/core/Config.h"
#include "vox-engine/core/ApplicationVersion.h"
#include "vox-engine/util/Logger.h"
#include "vox-engine/resources/OpenGL.h"
#include "vox-engine/component/Camera.h"

class Application {
public:
    static const double FIXED_TIME_INTERVAL;

    void init(std::map<std::string, Scene*>& sceneMap, int argc, char* argv[]);
    void start();
    void reset();

    static bool isRunning() { return m_IsRunning; }
    static void stop();
private:
    static Application* m_CurrentRunningApp;
    Time* m_Time;
    Display* m_Display;
    InputManager* m_InputManager;
    SceneManager* m_SceneManager;
    Logic* m_Logic;

    Config* m_Config;
    Logger* m_Logger;

    double m_AccumulatedTime;
    double m_LastSecond;

    static void runApplicationCallback(int);
    static void closeApplicationCallback();

    void destroy();
    void tick();

    std::vector<ISystem*> m_Systems;
    static bool m_IsRunning;
};


#endif //VOXENGINE_APPLICATION_H
