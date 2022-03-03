cmake_minimum_required(VERSION 3.21)
project(VoxEngine)

set(OpenGlLinkers -lglut -lGLU -lGL)
set(CMAKE_CXX_STANDARD 20)

add_executable(VoxEngine
        src/main.cpp
        src/InputManager.cpp
        src/Controllers.cpp
        src/Models.cpp
        src/Tools.cpp
        src/Debug.cpp
        src/Time.cpp
        src/Grid.cpp)

target_link_libraries(VoxEngine ${OpenGlLinkers})