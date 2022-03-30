//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/core/Application.h"
#include "../../include/vox-engine/util/GLError.h"

const double Application::FIXED_TIME_INTERVAL = 1.0f / 60.0f;

bool Application::_isRunning;

void Application::init() {
    _logger = new Logger();

    Logger::logln(VOX_ENGINE_VERSION);
    Logger::hr();
    Logger::logln("               INITIALIZING SYSTEMS\n");

    // Load Config
    _config = new Config();
    _config->readConfig();

    // Core Systems
    _display = new Display();
    _inputManager = new InputManager();
    _logic = new Logic();
    _lighting = new LightManager();
    _sceneManager = new SceneManager();
    //_sceneManager->setSceneMap(sceneMap);

    // Helper
    _profiler = new Profiler();
    _time = new Time();

    _systems.push_back(_display);
    _systems.push_back(_sceneManager);
    _systems.push_back(_inputManager);
    _systems.push_back(_logic);
    _systems.push_back(_lighting);

    for (auto & _system : _systems) {
        _system->init(Config::profile);
    }

    Logger::logln("\n                   SYSTEMS READY");
    Logger::hr();
    Logger::br();

    // Start Subsystems
    start();
}

void Application::start() {
    Logger::hr();
    Logger::logln("            LOADING SCENE ", SceneManager::getQueuedName(), "\n");

    for (auto & _system : _systems) {
        _system->start();
    }

    Logger::logln("\n                   SCENE READY");
    Logger::hr();
}

void Application::run() {
    double lastTime = Time::now();
    int nbFrames = 0;
    double lastSecond = 0;
    _isRunning = true;
    static int flop = -1;

    std::string statPrint;

    while (_isRunning && Display::isRunning()) {
        // Measure time
        double currentTime = Time::now();
        _time->setDeltaTime(currentTime - lastTime);

        if (Time::deltaTime < 1.0 / 999.0) {
            continue;
        }

        lastTime = currentTime;
        lastSecond += Time::deltaTime;

        if (lastSecond >= 1.0) {
            statPrint = std::to_string(nbFrames) + " FPS  -  " + std::to_string(1000.0f /
                    double(nbFrames)).substr(0, 4) + "ms";

            Profiler::addFps(nbFrames);
            nbFrames = 0;
            lastSecond = 0;
        }

        _inputManager->pollEvents();

        // Update Physics
        _accumulatedTime += Time::deltaTime;
        if (_accumulatedTime > FIXED_TIME_INTERVAL) {
            _logic->fixedUpdate();
            _accumulatedTime = 0;
        }

        // Update Logic
        _logic->update();

        // Late update Logic
        _logic->lateUpdate();

        // Update input
        _inputManager->update();

        // Start Rendering
        _check_gl_error("Pre Frame", 0);
        //TODO -> CLEAR DEFAULT BUFFER
        _check_gl_error("First Clear", 0);

        // Render Scene
        //Renderer::render();
        nbFrames++;
        _check_gl_error("Main Render", 0);

        // Refeed position updates to physics system
        //_physics->refeed();

        // Stop Rendering
        Display::swapBuffer();
        //_renderer->clearDrawCalls();

        /*
        *	After Render events
        */

        _check_gl_error("End of frame", 0);

        if (flop == -1) {
            Logger::infoln("Generate Lighting!");
            LightManager::generate();
            //_renderer->_shadowsAreDirty = true;
        }

        ++flop;

        _logic->tick();

        // End of Frame
        if (_sceneManager->sceneQueued()) {
            //_sceneManager->unloadScene(SceneManager::getCurrentScene());
            reset();
            start();

            // reset timing
            _accumulatedTime = 0;
            flop = -1;
            lastTime = Time::now();
        }
    }
}

void Application::stop() {
    _isRunning = false;
}

void Application::reset() {
    for (auto & _system : _systems) {
        _system->reset();
    }

    _profiler->reset();
}

void Application::destroy() {
    for (auto & _system : std::ranges::reverse_view(_systems)) {
        _system->destroy();
    }

    delete _time;
    delete _display;
    delete _inputManager;
    delete _sceneManager;
    delete _logic;
    delete _lighting;
    delete _profiler;
    delete _config;
    delete _logger;
}