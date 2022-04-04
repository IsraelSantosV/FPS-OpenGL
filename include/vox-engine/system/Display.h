//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_DISPLAY_H
#define VOXENGINE_DISPLAY_H
typedef void DisplayAction(unsigned int, unsigned int);

#include "ISystem.h"
#include "../util/Resources.h"
#include <GLFW/glfw3.h>
#include "GL/glut.h"

class Display : public ISystem {
public:
    static bool isRunning() { return _isRunning; }
    static GLFWwindow* getWindow() { return _window; }
    static void setVSync(bool vsync);
    static void setTitle(const std::string& title);
    static void swapBuffer();
    static void setDisplayIcon();
    static void triggerDisplayActions();
    static void addDisplayAction(DisplayAction action);

    static unsigned int getWidth();
    static unsigned int getHeight();

    void init(Config::Profile profile) override;
    void start() override {}
    void destroy() override;

    static void setRect(int width, int height){
        _width = width;
        _height = height;
    }
private:
    static std::vector<DisplayAction*> _displayActions;
    static bool _isRunning;
    static int _width;
    static int _height;
    static GLFWwindow* _window;
    static bool _isVSync;
};


#endif //VOXENGINE_DISPLAY_H
