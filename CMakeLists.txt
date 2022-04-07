cmake_minimum_required(VERSION 3.21)
project(VoxEngine)

set(OpenGlLinkers -lglut -lGLU -lGL)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/system/InputManager.cpp
        src/util/Tools.cpp
        src/util/Time.cpp
        include/vox-engine/util/Logger.h
        include/vox-engine/math/Constants.h
        src/math/Vector3.cpp
        include/vox-engine/math/Vector3.h
        src/math/Matrix3.cpp
        include/vox-engine/math/Matrix3.h
        src/math/Quaternion.cpp
        include/vox-engine/math/Quaternion.h
        src/core/Application.cpp
        include/vox-engine/core/Application.h
        src/system/Scene.cpp
        include/vox-engine/system/Scene.h
        src/component/Camera.cpp
        include/vox-engine/component/Camera.h
        src/system/Logic.cpp
        include/vox-engine/system/Logic.h
        src/component/Component.cpp
        include/vox-engine/component/Component.h
        src/component/Transform.cpp
        include/vox-engine/component/Transform.h
        src/system/Entity.cpp
        include/vox-engine/system/Entity.h
        src/component/Mesh.cpp
        include/vox-engine/component/Mesh.h
        src/component/primitives/CubeMesh.cpp
        include/vox-engine/component/primitives/CubeMesh.h
        include/vox-engine/core/Config.h
        include/vox-engine/core/ApplicationVersion.h
        include/vox-engine/system/ISystem.h
        src/system/Display.cpp
        include/vox-engine/system/Display.h
        include/vox-engine/system/InputManager.h
        include/vox-engine/util/Time.h
        include/vox-engine/resources/OpenGL.h
        src/core/Config.cpp
        include/vox-engine/util/Tools.h
        src/system/SceneManager.cpp
        include/vox-engine/system/SceneManager.h include/vox-engine/core.h build/Sandbox/Sandbox.cpp build/Sandbox/Scenes/MainScene.cpp build/Sandbox/Scripts/Health.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenGlLinkers})
target_include_directories(${PROJECT_NAME} PRIVATE include)