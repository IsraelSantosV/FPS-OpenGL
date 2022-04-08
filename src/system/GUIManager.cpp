//
// Created by Israel on 08/04/2022.
//

#include "vox-engine/system/GUIManager.h"

bool GUIManager::show_demo_window = true;

void GUIManager::start() {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsClassic();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL2_Init();
}

void GUIManager::reset() {
    ISystem::reset();
}

void GUIManager::destroy() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void GUIManager::displayGUICallback() {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    renderGUI();

    //Rendering
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::renderGUI() {
    ImGui::ShowDemoWindow(&show_demo_window);
}
