//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_DISPLAY_H
#define VOXENGINE_DISPLAY_H

#include "ISystem.h"
#include "vox-engine/resources/OpenGL.h"
#include "vox-engine/resources/GUI.h"
typedef void ResizeCallback(int width, int height);

class Display : public ISystem {
public:
    static void setTitle(const std::string& title);
    static unsigned int getWidth() { return m_Width; }
    static unsigned int getHeight() { return m_Height; }
    int getWindow() { return m_CurrentWindow; }

    static void setRect(int width, int height){
        m_Width = width;
        m_Height = height;
    }

    static void registerResizeCallback(ResizeCallback callback){
        m_Callbacks.push_back(callback);
    }

    void init(Config::Profile profile) override;
    void start() override {}
    void destroy() override;
private:
    static std::vector<ResizeCallback*> m_Callbacks;
    static void reshapeDisplay(int width, int height);
    int m_CurrentWindow;
    static int m_Width;
    static int m_Height;
};


#endif //VOXENGINE_DISPLAY_H
