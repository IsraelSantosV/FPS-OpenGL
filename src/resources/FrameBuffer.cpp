//
// Created by zetta on 04/04/2022.
//

#include "../../include/vox-engine/resources/FrameBuffer.h"

#include <iostream>
#include <algorithm>

const std::string DEFAULT_ATTACHMENT = "default";
GLuint FrameBuffer::_quadVAO = -1;
GLuint FrameBuffer::_quadVBO = -1;
std::vector<FrameBuffer*> FrameBuffer::_bufferList;

FrameBuffer::FrameBuffer(float screenFactor) {
    _screenFactor = screenFactor;
    _width = static_cast<int>(Display::getWidth() * screenFactor);
    _height = static_cast<int>(Display::getHeight() * screenFactor);
    initialize();
    _bufferList.push_back(this);
}

FrameBuffer::FrameBuffer(int width, int height) {
    _screenFactor = -1;
    _width = width;
    _height = height;
    initialize();
    _bufferList.push_back(this);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &_fbo);
    for (auto const &ent1: _colorAttachments) {
        glDeleteTextures(1, &ent1.second.id);
    }
    glDeleteRenderbuffers(1, &_depthAttachment);
    _bufferList.erase(std::remove(_bufferList.begin(), _bufferList.end(), this), _bufferList.end());
}

void FrameBuffer::addDepthBufferAttachment() {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glGenRenderbuffers(1, &_depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthAttachment);
}

FrameBuffer::BufferAttachment* FrameBuffer::getAttachment(std::string name) {
    return &_colorAttachments[name];
}

void FrameBuffer::enable() {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glViewport(0, 0, _width, _height);
}

void FrameBuffer::bind(unsigned int textureUnit, std::string name) {
    getAttachment(name)->bind(textureUnit);
}

void FrameBuffer::ready() {
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    if (_drawBuffers.size() > 0)
        glDrawBuffers(static_cast<GLsizei>(_drawBuffers.size()), &_drawBuffers[0]);
    else {
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE)
        Logger::warnln("Framebuffer not complete:", fboStatus);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void FrameBuffer::resize() {
    // Only recreate nonstatic buffers
    if (_screenFactor == -1) return;

    _width = static_cast<int>(Display::getWidth() * _screenFactor);
    _height = static_cast<int>(Display::getHeight() * _screenFactor);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    if (_depthAttachment != -1) {
        glDeleteRenderbuffers(1, &_depthAttachment);
        addDepthBufferAttachment();
    }

    ready();
}

void FrameBuffer::blit(FrameBuffer* target, std::string sourceAttachment, std::string targetAttachment) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
    glReadBuffer(getAttachment(sourceAttachment)->attachmentIndex);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target->getFBO());
    glDrawBuffer(target->getAttachment(targetAttachment)->attachmentIndex);

    glBlitFramebuffer(0, 0, _width, _height, 0, 0, target->getWidth(), target->getHeight(), GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);
}

void FrameBuffer::blitDepth(FrameBuffer* target) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target->getFBO());

    glBlitFramebuffer(0, 0, _width, _height, 0, 0, target->getWidth(), target->getHeight(), GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST);
}

void FrameBuffer::blitToScreen(std::string name) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo);
    glReadBuffer(getAttachment(name)->attachmentIndex);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glBlitFramebuffer(0, 0, _width, _height, 0, 0, Display::getWidth(), Display::getHeight(), GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);
}

void FrameBuffer::render(std::string name) {
    glBindVertexArray(_quadVAO);

    /*Shader *shader;
    if (material == nullptr) {
        shader = DefaultPostShader::getInstance();
    } else {
        shader = material->getShader();
    }*/

    //shader->bind();
    //shader->update(nullptr);
    //shader->updateTextures();
    bind(0, name);

    //shader->enableAttributes();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    //Renderer::addDrawCall();
    //shader->disableAttributes();

    glBindVertexArray(0);
}

void FrameBuffer::initialize() {
    _colorAttachmentIndex = GL_COLOR_ATTACHMENT0;

    // Create framebuffer
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);


    // Create mesh
    if (_quadVAO == -1) {
        // Quad Mesh
        static const GLfloat _quadVertices[] = {
                -1.0f, 1.0f,
                -1.0f, -1.0f,
                1.0f, 1.0f,
                1.0f, -1.0f,
        };

        glGenVertexArrays(1, &_quadVAO);
        glBindVertexArray(_quadVAO);

        glGenBuffers(1, &_quadVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_quadVertices), _quadVertices, GL_STATIC_DRAW);


        glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
        glVertexAttribPointer(Vertex::AttibLocation::POSITION, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    }
}

void FrameBuffer::resizeAll() {
    for (FrameBuffer *fbo: _bufferList) {
        fbo->resize();
    }
}

void FrameBuffer::destroy() {
    glDeleteBuffers(1, &_quadVBO);
    glDeleteVertexArrays(1, &_quadVAO);
}

void FrameBuffer::resetDefaultBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Display::getWidth(), Display::getHeight());
}

void FrameBuffer::clearDefaultBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Display::getWidth(), Display::getHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
