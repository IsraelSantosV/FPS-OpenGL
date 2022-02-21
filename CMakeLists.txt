cmake_minimum_required(VERSION 3.21)
project(FP_OpenGL)

set(OpenGlLinkers -lglut -lGLU -lGL)
set(CMAKE_CXX_STANDARD 20)

add_executable(FP_OpenGL
        src/main.cpp
        src/controllers/Camera.cpp
        src/controllers/Camera.h
        src/controllers/Scenario.cpp
        src/controllers/Scenario.h
        src/input/InputKey.cpp
        src/input/InputKey.h
        src/input/InputManager.cpp
        src/input/InputManager.h
        src/models/WorldObject.cpp
        src/models/WorldObject.h
        src/models/Component.cpp
        src/models/Component.h
        src/models/Mesh.cpp
        src/models/Mesh.h
        src/tools/Vector3.cpp
        src/tools/Vector3.h src/tools/Transform.cpp src/tools/Transform.h)

target_link_libraries(FP_OpenGL ${OpenGlLinkers})