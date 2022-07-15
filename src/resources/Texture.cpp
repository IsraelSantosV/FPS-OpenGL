//
// Created by Israel on 09/04/2022.
//

#include "vox-engine/resources/Texture.h"

static GLuint textureIDS[32];

Texture::Texture(const std::string &path) {
    m_RendererID = 0;
    m_FilePath = path.c_str();
    m_Width = 0;
    m_Height = 0;

    loadTexture();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);
}

void Texture::bind(unsigned int slot) const {
    glEnable(GL_TEXTURE_2D);
    glColor4f(1,1,1,1);
    GLuint texture;
    glGenTextures(1,&texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,m_ImgData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadTexture() {
    glGenTextures(32, textureIDS);  // Get the texture object IDs.

    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(m_FilePath);
    if (format == FIF_UNKNOWN) {
        Logger::errorln("Unknown file type for texture image file: \n", m_FilePath);
        return;
    }

    FIBITMAP* bitmap = FreeImage_Load(format, m_FilePath, 0);  // Read image from file.
    if (!bitmap) {
        Logger::errorln("Failed to load image: \n", m_FilePath);
        return;
    }

    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convert to RGB or BGR format
    FreeImage_Unload(bitmap);
    m_ImgData = FreeImage_GetBits(bitmap2);     // Grab the data we need from the bitmap.
    m_Width = FreeImage_GetWidth(bitmap2);
    m_Height = FreeImage_GetHeight(bitmap2);

    if (m_ImgData) {
        Logger::infoln("Texture image loaded from file: \n", m_FilePath, "\nImage size:", m_Width, "x", m_Height);
        int format; // The format of the color data in memory, depends on platform.
        if (FI_RGBA_RED == 0){
            format = GL_RGB;
        }
        else {
            format = GL_BGR;
        }

        glBindTexture( GL_TEXTURE_2D, m_RendererID);  // Will load image data into texture object #i
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, format,
                     GL_UNSIGNED_BYTE, m_ImgData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Required since there are no mipmaps.
    }
    else {
        Logger::errorln("Failed to get texture data from: \n", m_FilePath);
    }
}
