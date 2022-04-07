//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/system/Display.h"
#include "vox-engine/resources/OpenGL.h"

int Display::m_Width;
int Display::m_Height;

void Display::init(Config::Profile profile) {
    Logger::infoln("Initializing Display");

    m_Width = profile.width;
    m_Height = profile.height;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(profile.width, profile.height);
    glutCreateWindow(profile.appName.c_str());

    glutReshapeFunc(Display::reshapeDisplay);
    m_CurrentWindow = glutGetWindow();
}

void Display::reshapeDisplay(int width, int height) {
    setRect(width, height);
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Change perspective
    gluPerspective(60, 16.0/9.0, 1, 75);
    glMatrixMode(GL_MODELVIEW);
}

void Display::destroy() {
    Logger::warnln("Closing window: " + std::to_string(m_CurrentWindow));
}

void Display::setTitle(const std::string& title) {
    glutSetWindowTitle(title.c_str());
}
