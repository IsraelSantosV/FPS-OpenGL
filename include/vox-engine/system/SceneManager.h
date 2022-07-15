//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_SCENEMANAGER_H
#define VOXENGINE_SCENEMANAGER_H

#include "vox-engine/system/ISystem.h"
#include "vox-engine/system/Scene.h"
#include "vox-engine/resources/OpenGL.h"
#include "vox-engine/component/Camera.h"
#include "vox-engine/system/GUIManager.h"
#include "vox-engine/system/LightManager.h"
#include <map>

class SceneManager : public ISystem {
public:
    static void addScene(const std::string name, Scene* scene);
    static void loadScene(const std::string &name);
    static void unloadScene(Scene* scene);
    static void unloadScene(const std::string &name);
    static std::string getCurrentName();
    static std::string getQueuedName();
    static Scene* getCurrentScene();
    static void setSceneMap(std::map<std::string, Scene*>& sceneMap);

    static void clearDefaultBuffer();

    void start() override;
    void destroy() override;

    void loadSceneImmediately(const std::string &name);
    void loadQueuedScene();
    bool sceneQueued() { return _inQueue; }
    void drawSceneList();
private:
    static std::string _newScene;
    static std::string _currentSceneName;
    static bool _inQueue;
    static Scene* _currentScene;
    static std::map<std::string, Scene*> _sceneMap;
    static void renderSceneCallback();
    static void drawCurrentSceneRenders();
};


#endif //VOXENGINE_SCENEMANAGER_H
