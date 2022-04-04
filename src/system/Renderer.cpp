//
// Created by zetta on 01/04/2022.
//

#include "../../include/vox-engine/system/Renderer.h"

int Renderer::_debugMode;
unsigned int Renderer::_frameIndex;
std::vector<ObjectRenderer*> Renderer::_renderList;
int Renderer::_drawCalls;
Vector3f Renderer::_clearColor = Vector3f(0.3f, 0.3f, 0.3f);

void Renderer::init(Config::Profile profile){
    Logger::infoln("Initializing Renderer");

    // OpenGL config
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glClearColor(_clearColor.x(), _clearColor.y(), _clearColor.z(), 0);

    _debugMode = 0;
}

void Renderer::reset() {
    _frameIndex = 0;
    _renderList.clear();
}

void Renderer::start(){ }

void Renderer::newFrame() {
    ++_frameIndex;
    _renderList.clear();
}

void Renderer::prePass() {
    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::clearDrawCalls() {
    _drawCalls = 0;
}

void Renderer::populateShadowBuffer() {
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
}

void Renderer::renderObjects(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);

    for (auto & it : _renderList){
        if (it->getEnable() && Camera::getMainCamera()->frustumTest(it)){
            it->render();
        }
    }
}

void Renderer::render() {
    // Render objects
    renderObjects();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
}

void Renderer::renderGizmos() {
    if (_debugMode >= 1) {
        SceneManager::getCurrentScene()->getEntities();
        for (auto &it: SceneManager::getCurrentScene()->getEntities()) {
            if (it->getEnable()) {
                it->transform->renderHandels();
            }
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::setDebug(int debugMode) {
    _debugMode = debugMode;
}

unsigned long int Renderer::getFrameIndex() {
    return _frameIndex;
}

void Renderer::destroy() { }

void Renderer::setClearColor(Vector3f color) {
    _clearColor = color;
}

void Renderer::addDrawCall() {
    ++_drawCalls;
}