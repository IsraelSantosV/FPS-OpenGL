//
// Created by Israel on 09/04/2022.
//

#ifndef VOXENGINE_TEXTURE_H
#define VOXENGINE_TEXTURE_H

#include <iostream>
#include <FreeImage.h>

#include "vox-engine/resources/OpenGL.h"
#include "vox-engine/util/Logger.h"

class Texture {
private:
    unsigned int m_RendererID;
    const char *m_FilePath;
    int m_Width, m_Height;
    void* m_ImgData;

    void loadTexture();
public:
    Texture(const std::string& path);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind();

    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }
};

#endif //VOXENGINE_TEXTURE_H
