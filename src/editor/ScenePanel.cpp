#include <editor/ScenePanel.h>
#include <editor/Editor.h>
#include <onyx/scene/GameObject.h>

#include <imgui/imgui.h>

namespace Onyx
{

void ScenePanel::drawScenePanel(const std::shared_ptr<Scene>& scene)
{
    ImGui::Begin("Scene");

    for (auto& go : scene->getObjects())
    {
        ImGui::PushID(go.get());

        if (ImGui::TreeNode(go->name.c_str()))
        {
            ImGui::TreePop();
        }

        if (ImGui::IsItemClicked())
        {
            static_cast<Editor*>(Game::getInstance())->setSelectedObject(go);
        }

        ImGui::PopID();
    }

    if (ImGui::BeginPopupContextWindow("CreateObject"))
    {
        if (ImGui::BeginMenu("Create"))
        {
            if (ImGui::MenuItem("Empty Game Object"))
            {
                auto object = scene->createGameObject("Game Object");
                static_cast<Editor*>(Game::getInstance())->setSelectedObject(object);
            }

            ImGui::EndMenu();
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}

}