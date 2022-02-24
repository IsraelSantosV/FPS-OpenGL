cmake_minimum_required(VERSION 3.21)
project(FP_OpenGL)

set(OpenGlLinkers -lglut -lGLU -lGL)
set(CMAKE_CXX_STANDARD 20)

add_executable(FP_OpenGL
        src/main.cpp
        src/InputManager.cpp
        src/Controllers.cpp
        src/Models.cpp
        src/Tools.cpp src/Debug.cpp)

target_link_libraries(FP_OpenGL ${OpenGlLinkers})