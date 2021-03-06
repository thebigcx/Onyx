#include <editor/InspectorPanel.h>
#include <onyx/audio/AudioSource.h>
#include <onyx/scene/Sprite.h>
#include <onyx/renderer/Texture.h>
#include <onyx/audio/AudioBuffer.h>
#include <onyx/core/AssetManager.h>

#include <imgui/imgui.h>

namespace Onyx
{

template<typename T>
void InspectorPanel::addComponent(const WeakPtr<GameObject>& go, const std::string& name)
{
    if (!go->hasComponent<T>())
    {
        if (ImGui::Selectable(name.c_str()))
        {
            go->addComponent(new T());
        }
    }
}

void InspectorPanel::drawInspectorPanel(const WeakPtr<GameObject>& go)
{
    ImGui::Begin("Inspector");

    if (go)
    {
        drawComponents(go);

        if (ImGui::BeginCombo("##addComponent", "+ Add Component", ImGuiComboFlags_NoArrowButton))
        {
            addComponent<Sprite>(go, "Sprite");
            addComponent<AudioSource>(go, "Audio Source");

            ImGui::EndCombo();
        }
    }

    ImGui::End();
}

template<typename T, typename F>
void InspectorPanel::drawComponent(const std::string& name, const WeakPtr<GameObject>& object, const F& fn)
{
    if (!object->hasComponent<T>())
    {
        return;
    }

    ImGui::PushID(name.c_str());

    if (ImGui::CollapsingHeader(name.c_str()))
    {
        fn();
    }
    if (ImGui::BeginPopupContextItem("Delete"))
    {
        if (ImGui::MenuItem("Delete"))
        {
            object->removeComponent<T>();
        }

        ImGui::EndPopup();
    }

    ImGui::PopID();
}

void InspectorPanel::drawComponents(const WeakPtr<GameObject>& object)
{
    if (ImGui::CollapsingHeader("Transform"))
    {
        ImGui::Columns(2);

        ImGui::Text("Translation");
        ImGui::NextColumn();
        ImGui::DragFloat2("##Translation", &object->getTransform()->translation.x, 0.1f);
        ImGui::NextColumn();

        ImGui::Text("Scale");
        ImGui::NextColumn();
        ImGui::DragFloat2("##Scale", &object->getTransform()->scale.x, 0.1f);
        ImGui::NextColumn();

        ImGui::Text("Rotation");
        ImGui::NextColumn();
        ImGui::DragFloat("##Rotation", &object->getTransform()->rotation, 0.1f);
        ImGui::NextColumn();

        ImGui::Columns(1);
    }

    drawComponent<Sprite>("Sprite", object, [&object]
    {
        ImGui::Columns(2);

        // Display the path to the texture
        ImGui::Text("Texture");
        ImGui::NextColumn();

        char buffer[128];

        auto& texture = object->getComponent<Sprite>()->getTexture();

        if (texture)
        {
            strcpy(buffer, texture->getPath().c_str());
        }
        
        ImGui::InputText("", buffer, 128, ImGuiInputTextFlags_ReadOnly);

        // Drag and drop from AssetPanel
        if (ImGui::BeginDragDropTarget())
        {
            auto payload = ImGui::AcceptDragDropPayload("TextureAsset");

            if (payload)
            {
                std::string path = (const char*)payload->Data;
                object->getComponent<Sprite>()->setTexture(AssetManager::getInstance()->getTexture(path));
            }
        }

        ImGui::NextColumn();
        ImGui::Columns(1);
    });

    drawComponent<AudioSource>("Audio Source", object, [&object]
    {
        ImGui::Columns(2);

        // Display the path to the audio clip
        ImGui::Text("Audio Clip");
        ImGui::NextColumn();

        char buffer[128];

        auto& audio = object->getComponent<AudioSource>()->getAudio();

        if (audio)
        {
            strcpy(buffer, audio->getPath().c_str());
        }
        
        ImGui::InputText("", buffer, 128, ImGuiInputTextFlags_ReadOnly);

        // Drag and drop from AssetPanel
        if (ImGui::BeginDragDropTarget())
        {
            auto payload = ImGui::AcceptDragDropPayload("AudioAsset");

            if (payload)
            {
                std::string path = (const char*)payload->Data;
                object->getComponent<AudioSource>()->setBuffer(AssetManager::getInstance()->getAudio(path));
            }
        }

        ImGui::NextColumn();
        ImGui::Columns(1);
    });
}

}