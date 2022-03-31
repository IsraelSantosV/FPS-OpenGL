//
// Created by Israel on 30/03/2022.
//

#ifndef VOXENGINE_DEBUGGUI_H
#define VOXENGINE_DEBUGGUI_H

#include "../../../imgui/imgui_impl_glfw.h"
#include "../../../imgui/imgui_impl_glut.h"
#include "../../../imgui/imgui_impl_opengl3.h"

#include "Display.h"
#include "ISystem.h"
#include "../util/Logger.h"

class DebugGUI : public ISystem {
public:
    void init(Config::Profile profile) override;
    void start() override;
    void reset() override;
    void destroy() override;

    void newFrame();
    void render();
};


#endif //VOXENGINE_DEBUGGUI_H
