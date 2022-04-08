//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/system/Display.h"

int Display::m_Width;
int Display::m_Height;
std::vector<ResizeCallback*> Display::m_Callbacks;

void Display::init(Config::Profile profile) {
    Logger::infoln("Initializing Display");

    m_Width = profile.width;
    m_Height = profile.height;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(profile.width, profile.height);
    glutCreateWindow(profile.appName.c_str());

    glutReshapeFunc(Display::reshapeDisplay);
    m_CurrentWindow = glutGetWindow();
}

void Display::reshapeDisplay(int width, int height) {
    if(width == 0 || height == 0) return;
    setRect(width, height);

    for(auto& callback : m_Callbacks){
        callback(width, height);
    }
}

void Display::destroy() {
    Logger::warnln("Closing window: " + std::to_string(m_CurrentWindow));
}

void Display::setTitle(const std::string& title) {
    glutSetWindowTitle(title.c_str());
}
