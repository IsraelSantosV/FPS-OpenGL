//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_DISPLAY_H
#define VOXENGINE_DISPLAY_H

#include "ISystem.h"

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

    void init(Config::Profile profile) override;
    void start() override {}
    void destroy() override;
private:
    static void reshapeDisplay(int width, int height);
    int m_CurrentWindow;
    static int m_Width;
    static int m_Height;
};


#endif //VOXENGINE_DISPLAY_H
