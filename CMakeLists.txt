cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(OpenGlLinkers -lglut -lGLU -lGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(OpenGL
        src/core/main.cpp
        src/core/tools/Vector3.cpp
        src/core/tools/headers/Vector3.h
        src/core/input/InputKey.cpp
        src/core/input/headers/InputKey.h
        src/core/input/InputManager.cpp
        src/core/input/headers/InputManager.h
        src/core/controllers/Camera.cpp
        src/core/controllers/headers/Camera.h src/core/tools/Drawer.cpp src/core/tools/headers/Drawer.h src/core/controllers/Scenario.cpp src/core/controllers/headers/Scenario.h)
target_link_libraries(OpenGL ${OpenGlLinkers})
