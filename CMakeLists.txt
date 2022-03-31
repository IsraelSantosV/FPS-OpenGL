cmake_minimum_required(VERSION 3.21)
project(VoxEngine)

add_definitions("-std=c++11")

set(OpenGlLinkers -lglut -lGLU -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor)
set(CMAKE_CXX_STANDARD 11)

find_package(ZLIB)
file(GLOB SRC CONFIGURE_DEPENDS "imgui/*.hpp" "imgui/*.cpp")

add_executable(VoxEngine src/Main.cpp ${SRC} imgui/imgui.cpp
        src/core/Application.cpp
        include/vox-engine/core/Application.h
        src/system/Display.cpp
        include/vox-engine/system/Display.h
        src/system/InputManager.cpp
        include/vox-engine/system/InputManager.h
        src/core/Config.cpp
        include/vox-engine/core/Config.h
        src/system/Entity.cpp
        include/vox-engine/system/Entity.h
        src/system/LightManager.cpp
        include/vox-engine/system/LightManager.h
        src/system/Logic.cpp
        include/vox-engine/system/Logic.h
        src/system/SceneManager.cpp
        include/vox-engine/system/SceneManager.h
        src/system/Component.cpp
        include/vox-engine/system/Component.h
        src/util/Time.cpp
        include/vox-engine/util/Time.h
        src/component/Light.cpp
        include/vox-engine/component/Light.h
        src/component/Camera.cpp
        include/vox-engine/component/Camera.h
        src/system/Transform.cpp
        include/vox-engine/system/Transform.h
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
        src/system/Scene.cpp
        include/vox-engine/system/Scene.h
        src/resources/Texture.cpp
        include/vox-engine/resources/Texture.h
        include/vox-engine/util/Logger.h
        src/util/GLError.cpp
        include/vox-engine/util/GLError.h
        src/resources/FilePath.cpp
        include/vox-engine/resources/FilePath.h
        src/util/Utils.cpp
        include/vox-engine/util/Utils.h
        src/util/Profiler.cpp
        include/vox-engine/util/Profiler.h
        src/util/MaxQueue.cpp
        include/vox-engine/util/MaxQueue.h
        include/vox-engine/system/ISystem.h
        include/vox-engine/core/ApplicationVersion.h
        include/vox-engine/util/Resources.h
        include/vox-engine/math/Math.h
        src/system/DebugGUI.cpp
        include/vox-engine/system/DebugGUI.h
        include/vox-engine/system/IBehaviour.h
        src/math/Math.cpp src/system/Models.cpp include/vox-engine/system/Models.h)

target_link_libraries(VoxEngine ${OpenGlLinkers} ZLIB::ZLIB)