//
// Created by Israel on 08/04/2022.
//

#include "vox-engine/system/GUIManager.h"

bool GUIManager::show_demo_window = true;
Entity* GUIManager::m_SelectedEntity = nullptr;

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

void GUIManager::displayGUICallback(std::vector<Entity*> sceneObjects) {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    renderGUI(std::move(sceneObjects));

    //Rendering
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void GUIManager::renderGUI(std::vector<Entity*> sceneObjects) {
    //ImGui::ShowDemoWindow();
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(Display::getWidth()/4,Display::getHeight()/2));
    GUIManager::renderInspector();
    ImGui::End();

    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowPos(ImVec2(0, Display::getHeight()/2));
    ImGui::SetWindowSize(ImVec2(Display::getWidth()/4,Display::getHeight()/2));
    GUIManager::renderHierarchy(std::move(sceneObjects));
    ImGui::End();
}

void GUIManager::renderInspector() {
    if(GUIManager::m_SelectedEntity){
        GUIManager::drawNodeComponents(m_SelectedEntity);
    }
}

void GUIManager::renderHierarchy(std::vector<Entity *> sceneObjects) {
    static ImGuiTreeNodeFlags base_flags =
            ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    static bool align_label_with_current_x_position = false;

    if (align_label_with_current_x_position)
        ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

    for (auto& sceneObject : sceneObjects) {
        GUIManager::drawHierarchyNode(sceneObject);
    }

    if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()){
        m_SelectedEntity = {};
    }

    if (align_label_with_current_x_position){
        ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
    }
}

void GUIManager::drawHierarchyNode(Entity* entity) {
    auto& tag = entity->name;
    bool isEnable = entity->getEnable();

    ImGuiTreeNodeFlags flags = ((GUIManager::isSelectedEntity(entity)) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    if(entity->transform->getChildren().empty()){
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    if(!isEnable){
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 0.5, 0.5, 0.4));
    }

    bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity->getId(), flags, "%s", tag.c_str());
    if(!isEnable){
        ImGui::PopStyleColor();
    }

    if(ImGui::IsItemClicked()){
        m_SelectedEntity = entity;
    }

    if(opened){
        ImGui::TreePop();
    }
}

bool GUIManager::isSelectedEntity(Entity *entity) {
    if(m_SelectedEntity == nullptr || entity == nullptr) return false;
    return m_SelectedEntity->getId() == entity->getId();
}

void GUIManager::drawNodeComponents(Entity* entity) {
    //Render entity name
    auto& tag = entity->name;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    Tools::strcpy_s(buffer, sizeof(buffer), tag.c_str());
    if(ImGui::InputText("Tag", buffer, sizeof(buffer))){
        tag = std::string(buffer);
    }

    bool isEnable = entity->getEnable();
    if(ImGui::Checkbox("Enable", &isEnable)){
        entity->setEnable(isEnable);
    }

    if(ImGui::TreeNodeEx((void*) typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")){
        //Render transform
        ImGui::DragFloat3("Position", value_ptr(entity->transform->m_Position), 0.1f);
        ImGui::DragFloat3("Rotation", value_ptr(entity->transform->m_Rotation), 0.1f);
        ImGui::DragFloat3("Scale", value_ptr(entity->transform->m_Scale), 0.1f);

        ImGui::TreePop();
    }

    if(entity->getComponent<Camera>()){
        if(ImGui::TreeNodeEx((void*) typeid(Camera).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")){
            auto* currentCamera = entity->getComponent<Camera>();

            const char* projectionTypeStrings[] = { "Orthographic", "Perspective" };
            const char* currentProjectionTypeString = projectionTypeStrings[(int)currentCamera->getMode()];
            if(ImGui::BeginCombo("Projection", currentProjectionTypeString)){
                for(int i = 0; i < 2; i++){
                    bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                    if(ImGui::Selectable(projectionTypeStrings[i], isSelected)){
                        currentProjectionTypeString = projectionTypeStrings[i];
                        currentCamera->setMode((CameraType)i);
                    }

                    if(isSelected){
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }

            if(currentCamera->getMode() == CameraType::FREE){
                float fov = currentCamera->field_of_view;
                if(ImGui::DragFloat("FOV", &fov)){
                    currentCamera->setFOV(fov);
                }

                float orthoNear = currentCamera->near_clip;
                if(ImGui::DragFloat("Near", &orthoNear)){
                    currentCamera->setClipping(orthoNear, currentCamera->far_clip);
                }

                float orthoFar = currentCamera->far_clip;
                if(ImGui::DragFloat("Far", &orthoFar)){
                    currentCamera->setClipping(currentCamera->near_clip, orthoFar);
                }

                float sensibility = currentCamera->sensibility;
                if(ImGui::DragFloat("Sensibility", &sensibility, 0.01f)){
                    currentCamera->setSensibility(sensibility);
                }
            }
            if(currentCamera->getMode() == CameraType::ORTHO){
                float fov = currentCamera->field_of_view;
                if(ImGui::DragFloat("FOV", &fov)){
                    currentCamera->setFOV(fov);
                }

                float orthoNear = currentCamera->near_clip;
                if(ImGui::DragFloat("Near", &orthoNear)){
                    currentCamera->setClipping(orthoNear, currentCamera->far_clip);
                }

                float orthoFar = currentCamera->far_clip;
                if(ImGui::DragFloat("Far", &orthoFar)){
                    currentCamera->setClipping(currentCamera->near_clip, orthoFar);
                }
            }

            ImGui::TreePop();
        }
    }
}
