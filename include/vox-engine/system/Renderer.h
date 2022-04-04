//
// Created by zetta on 01/04/2022.
//

#ifndef VOXENGINE_RENDERER_H
#define VOXENGINE_RENDERER_H

#define GL_GLEXT_PROTOTYPES
#define GLEW_STATIC

#include <GL/freeglut.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>
#include "../math/Vector3f.h"
#include "../component/ObjectRenderer.h"
#include "ISystem.h"
#include "../component/Camera.h"
#include "../resources/FrameBuffer.h"

class Renderer : public ISystem {
public:
    const static int MAX_DEBUG = 2;
    static int getDebugMode() { return _debugMode; }
    static void setDebug(int debugMode);
    static void setClearColor(Vector3f color);
    static Vector3f getClearColor() { return _clearColor; }
    static void addDrawCall();
    static int getDrawCalls() { return _drawCalls; }
    static FrameBuffer* getMainFrameBuffer() { return _mainFrameBuffer; }
    static FrameBuffer* getGBuffer() { return _gBuffer; }
    static FrameBuffer* getDebugBuffer() { return _gizmoBuffer; }
    static void addToRenderQueue(ObjectRenderer* renderer);
    static void removeFromRenderQueue(ObjectRenderer* renderer);

    static void render();
    static unsigned long int getFrameIndex();

    void init(Config::Profile profile) override;
    void start() override;
    void reset() override;
    void destroy() override;

    void newFrame();
    void prePass();
    void clearDrawCalls();
    void renderGizmos();
private:
    static int _drawCalls;
    static unsigned int _frameIndex;
    static int _debugMode;
    static std::vector<ObjectRenderer*> _renderList;
    static Vector3f _clearColor;

    static FrameBuffer* _mainFrameBuffer;
    static FrameBuffer* _gBuffer;
    static FrameBuffer* _gizmoBuffer;

    static void renderObjects();
};


#endif //VOXENGINE_RENDERER_H
