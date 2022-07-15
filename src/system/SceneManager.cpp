//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/system/SceneManager.h"

bool SceneManager::_inQueue = false;
Scene* SceneManager::_currentScene;
std::string SceneManager::_newScene;
std::map<std::string, Scene*> SceneManager::_sceneMap;
std::string SceneManager::_currentSceneName;

void SceneManager::setSceneMap(std::map<std::string, Scene*>& sceneMap) {
    _sceneMap = sceneMap;
    loadScene(_sceneMap.begin()->first);
}

void SceneManager::start() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    float whiteColor[4] = { 1, 1, 1, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, whiteColor);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(SceneManager::renderSceneCallback);
    loadQueuedScene();
}

void SceneManager::addScene(const std::string name, Scene* scene) {
    _sceneMap[name] = scene;
}

void SceneManager::loadScene(const std::string & name) {
    _newScene = name;
    _inQueue = true;
}

void SceneManager::loadSceneImmediately(const std::string& name) {
    if (_sceneMap[name] == nullptr) return;

    Scene *oldScene = _currentScene;
    _currentScene = _sceneMap[name];
    _currentSceneName = name;

    _currentScene->Load();

    if (oldScene != nullptr) oldScene->unload();

    Display::setTitle(Config::profile.appName + " - " + name);
    _inQueue = false;
}

void SceneManager::loadQueuedScene() {
    loadSceneImmediately(_newScene);
    _newScene = "";
}

void SceneManager::unloadScene(Scene * scene) {
    if (scene == nullptr) return;

    scene->unload();
    _currentScene = nullptr;
}

void SceneManager::unloadScene(const std::string & name) {
    unloadScene(_sceneMap[name]);
}

std::string SceneManager::getCurrentName() {
    return _currentSceneName;
}

std::string SceneManager::getQueuedName() {
    return _newScene;
}

Scene* SceneManager::getCurrentScene() {
    return _currentScene;
}

void SceneManager::destroy() {
    _currentScene->unload();
    for (auto const &scene: _sceneMap) {
        delete scene.second;
    }
    _sceneMap.clear();
}

void SceneManager::renderSceneCallback() {
    clearDefaultBuffer();
    LightManager::setupLights();
    GUIManager::displayGUICallback(SceneManager::getCurrentScene()->getEntities());

    if(Camera::main != nullptr){
        mat4 model, view, projection;
        Camera::main->Update();
        Camera::main->getMatrices(projection, view, model);

        mat4 mvp = projection * view * model;
        glLoadMatrixf(value_ptr(mvp));
    }
    else {
        glMatrixMode(GL_MODELVIEW);
    }

    drawCurrentSceneRenders();
    glutSwapBuffers();
}

void SceneManager::clearDefaultBuffer() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0, Display::getWidth(), Display::getHeight());
    glLoadIdentity();
}

void SceneManager::drawCurrentSceneRenders() {
    Scene* currentScene = SceneManager::getCurrentScene();
    for(auto& entity : currentScene->getEntities()){
        if(!entity->getEnable()) continue;
        Transform* transform = entity->transform;

        vec3 position = transform->getLocalPosition();
        vec3 rotation = transform->getLocalEulerAngles();
        vec3 scale = transform->getLocalScale();

        if(entity->mesh != nullptr){
            entity->mesh->drawTexture();
        }

        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glRotatef(0, rotation.x, rotation.y, rotation.z);
            glScalef(scale.x, scale.y, scale.z);

            if(entity->mesh != nullptr){
                entity->mesh->draw();
            }
        glPopMatrix();
    }
}
