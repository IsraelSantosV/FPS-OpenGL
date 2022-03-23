cmake_minimum_required(VERSION 3.21)
project(VoxEngine)

add_definitions("-std=c++11")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(OpenGlLinkers -lglut -lGLU -lGL)
set(CMAKE_CXX_STANDARD 20)

add_executable(VoxEngine src/core/Application.cpp
        include/vox-engine/core/Application.h
        src/core/Display.cpp
        include/vox-engine/core/Display.h
        src/core/InputManager.cpp
        include/vox-engine/core/InputManager.h
        src/core/Config.cpp
        include/vox-engine/core/Config.h
        src/core/Entity.cpp
        include/vox-engine/core/Entity.h
        src/system/LightManager.cpp
        include/vox-engine/system/LightManager.h
        src/system/Logic.cpp
        include/vox-engine/system/Logic.h
        src/system/SceneManager.cpp
        include/vox-engine/system/SceneManager.h
        src/system/Component.cpp
        include/vox-engine/system/Component.h
        src/component/Time.cpp
        include/vox-engine/component/Time.h
        src/component/Light.cpp
        include/vox-engine/component/Light.h
        src/component/Camera.cpp
        include/vox-engine/component/Camera.h
        src/component/Transform.cpp
        include/vox-engine/component/Transform.h
        src/component/Behaviour.cpp
        include/vox-engine/component/Behaviour.h
        src/math/Matrix4f.cpp
        include/vox-engine/math/Matrix4f.h
        src/math/Quaternion.cpp
        include/vox-engine/math/Quaternion.h
        src/math/Vector3f.cpp
        include/vox-engine/math/Vector3f.h
        src/math/Vector2f.cpp
        include/vox-engine/math/Vector2f.h
        src/math/Vector4f.cpp
        include/vox-engine/math/Vector4f.h
        src/resources/Animator.cpp
        include/vox-engine/resources/Animator.h
        src/resources/Scene.cpp
        include/vox-engine/resources/Scene.h
        src/resources/Texture.cpp
        include/vox-engine/resources/Texture.h)

target_link_libraries(VoxEngine ${OpenGlLinkers} ${CONAN_LIBS})