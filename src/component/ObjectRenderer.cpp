//
// Created by zetta on 01/04/2022.
//

#include "../../include/vox-engine/component/ObjectRenderer.h"

void ObjectRenderer::init() {
    //Renderer::addToRenderQueue(this, _type);
}

void ObjectRenderer::onDestroy() {}

BoundingSphere ObjectRenderer::getBoundingSphere() {
    return BoundingSphere(Vector3f::ZERO, 0.001f);
}

void ObjectRenderer::destroy() {
    onDestroy();
    //Renderer::removeFromRenderQueue(this);
}

void ObjectRenderer::setRenderType(RenderType type) {
    //Renderer::removeFromRenderQueue(this);
    //Renderer::addToRenderQueue(this, type);
    _type = type;
}