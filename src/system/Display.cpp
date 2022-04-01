//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/system/Display.h"

bool Display::_isRunning;
int Display::_width, Display::_height;
GLFWwindow* Display::_window;
bool Display::_isVSync;

void window_size_callback(GLFWwindow*, int, int);

void Display::init(Config::Profile profile) {
    Logger::infoln("Initializing Display");

    _width = profile.width;
    _height = profile.height;

    if (!glfwInit()) {
        Logger::errorln("Failed to initialize GLFW!");
        exit(EXIT_FAILURE);
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 32);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    _window = glfwCreateWindow(profile.width, profile.height, profile.appName.c_str(),
                               profile.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (!_window) {
        const char *errorText = nullptr;
        glfwGetError(&errorText);
        Logger::errorln(errorText);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_window);

    // Set Icon
    GLFWimage icon[1];
    icon[0].pixels = Utils::loadIcon(Resources::ENGINE_RESOURCES + "/logo.png", icon[0].width, icon[0].height);
    glfwSetWindowIcon(_window, 1, icon);
    Utils::freeIcon(icon[0].pixels);

    setVSync(profile.vsync);
    _isRunning = true;

    Logger::infoln("OpenGL Version", glGetString(GL_VERSION));
    glfwSetWindowSizeCallback(_window, window_size_callback);
}

void Display::destroy() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Display::setVSync(bool vsync) {
    glfwSwapInterval((int) vsync);
    _isVSync = vsync;
}

void Display::setTitle(const std::string& title) {
    glfwSetWindowTitle(_window, title.c_str());
}

void Display::swapBuffer() {
    glfwSwapBuffers(_window);
    _isRunning = !glfwWindowShouldClose(_window);
}

unsigned int Display::getWidth() {
    return _width;
}

unsigned int Display::getHeight() {
    return _height;
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    if (width == 0 || height == 0) return;

    Display::setRect(width, height);
    //Camera::getMainCamera()->updateAspect();
}