//
// Created by Israel on 30/03/2022.
//

#include "../../include/vox-engine/system/DebugGUI.h"

void DebugGUI::init(Config::Profile profile) {
    Logger::infoln("Initializing DebugGUI");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Display::getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiIO &io = ImGui::GetIO();
    (void) io;
}

void DebugGUI::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void DebugGUI::render() {
    static const float identityMatrix[16] =
            {1.f, 0.f, 0.f, 0.f,
             0.f, 1.f, 0.f, 0.f,
             0.f, 0.f, 1.f, 0.f,
             0.f, 0.f, 0.f, 1.f};

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugGUI::start() {
    newFrame();
}

void DebugGUI::reset() {
    ImGui::EndFrame();
}

void DebugGUI::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}