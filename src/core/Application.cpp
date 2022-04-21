//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/core/Application.h"

Application* Application::m_CurrentRunningApp = nullptr;
const double Application::FIXED_TIME_INTERVAL = 1.0f / 60.0f;
bool Application::m_IsRunning;

void Application::init(std::map<std::string, Scene*>& sceneMap, int argc, char* argv[]) {
    if(m_CurrentRunningApp != nullptr){
        Application::stop();
        m_CurrentRunningApp->destroy();
    }

    m_CurrentRunningApp = this;
    m_Logger = new Logger();

    Logger::logln(VOX_ENGINE_VERSION);
    Logger::logln("GLUT [v" + std::to_string(GLUT_VERSION) + "]");
    Logger::hr();

    Logger::logln("INITIALIZING SYSTEMS\n");

    m_Config = new Config();
    m_Config->readConfig();

    m_Display = new Display();
    m_InputManager = new InputManager();
    m_Logic = new Logic();
    m_Time = new Time();
    m_SceneManager = new SceneManager();
    m_GUIManager = new GUIManager();
    m_LightManager = new LightManager();
    SceneManager::setSceneMap(sceneMap);

    m_Systems.push_back(m_Display);
    m_Systems.push_back(m_SceneManager);
    m_Systems.push_back(m_InputManager);
    m_Systems.push_back(m_Logic);
    m_Systems.push_back(m_GUIManager);
    m_Systems.push_back(m_LightManager);

    //Initialize glut and imGui
    glutInit(&argc, argv);

    for(auto& _system : m_Systems){
        _system->init(Config::profile);
    }

    Display::registerResizeCallback([](int width, int height){
        if(Camera::main != nullptr){
            Camera::main->setViewport(width/4,0, width, height);
        }
    });

    Logger::logln("\nSYSTEMS READY");
    Logger::hr();
    Logger::br();

    // Start Subsystems
    start();
}

void Application::start() {
    Logger::hr();
    Logger::logln("LOADING SCENE ", SceneManager::getQueuedName(), "\n");

    for (auto & _system : m_Systems) {
        _system->start();
    }

    Logger::logln("\nSCENE READY");
    Logger::hr();

    m_LastSecond = 0;
    m_AccumulatedTime = 0;
    m_IsRunning = true;

    glutTimerFunc(1000 / Config::profile.frameRate, runApplicationCallback, 0);
    glutCloseFunc(closeApplicationCallback);
    glutMainLoop();
}

void Application::runApplicationCallback(int) {
    glutPostRedisplay();

    if(Application::isRunning()){
        Application::m_CurrentRunningApp->tick();
        glutTimerFunc(1000 / Config::profile.frameRate, runApplicationCallback, 0);
    }
}

void Application::tick() {
    m_Time->setDeltaTime((1000 / Config::profile.frameRate) / 1000);

    if(Time::deltaTime < 1.0 / 999.0){
        return;
    }

    m_LastSecond += Time::deltaTime;

    if(m_LastSecond >= 1.0){
        //Register FPS
        m_LastSecond = 0;
    }

    m_AccumulatedTime += Time::deltaTime;
    if(m_AccumulatedTime > FIXED_TIME_INTERVAL){
        Logic::fixedUpdate();
        m_AccumulatedTime = 0;
    }

    Logic::update();
    Logic::lateUpdate();

    m_InputManager->update();

    Logic::tick();

    if(m_SceneManager->sceneQueued()){
        reset();
        start();

        m_AccumulatedTime = 0;
    }
}

void Application::stop() {
    if(m_CurrentRunningApp == nullptr) return;
    if(m_CurrentRunningApp->m_Display != nullptr){
        glutDestroyWindow(m_CurrentRunningApp->m_Display->getWindow());
    }

    m_IsRunning = false;
}

void Application::reset() {
    for(auto& _system : m_Systems){
        _system->reset();
    }
}

void Application::closeApplicationCallback() {
    m_CurrentRunningApp->destroy();

    m_IsRunning = false;
    Logger::hr();
    Logger::logln("CLOSING APPLICATION!", "\n");
}

void Application::destroy() {
    for(auto& _system : m_Systems){
        _system->destroy();
    }

    delete m_Time;
    delete m_Display;
    delete m_InputManager;
    delete m_SceneManager;
    delete m_LightManager;
    delete m_Logic;
    delete m_Config;
    delete m_Logger;
}
