cmake_minimum_required(VERSION 3.21)
project(OpenGL)

set(OpenGlLinkers -lglut -lGLU -lGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(OpenGL
        src/core/main.cpp
        src/core/tools/vector3.cpp
        src/core/tools/headers/vector3.h
        src/core/input/inputKey.cpp
        src/core/input/headers/inputKey.h
        src/core/input/inputManager.cpp
        src/core/input/headers/inputManager.h
        src/core/camera.cpp
        src/core/headers/camera.h)
target_link_libraries(OpenGL ${OpenGlLinkers})
