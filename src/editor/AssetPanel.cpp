#include <editor/AssetPanel.h>
#include <onyx/core/AssetManager.h>
#include <onyx/renderer/Texture.h>

#include <imgui/imgui.h>

#include <filesystem>

namespace Onyx
{

void AssetPanel::setupAssets()
{

}

void AssetPanel::drawAssetPanel()
{
    ImGui::Begin("Assets");

    if (ImGui::BeginCombo("Asset View", m_assetView.c_str()))
    {
        if (ImGui::Selectable("Texture View"))
        {
            m_assetView = "Texture View";
        }
        if (ImGui::Selectable("Audio View"))
        {
            m_assetView = "Audio View";
        }

        ImGui::EndCombo();
    }

    for (auto& asset : std::filesystem::directory_iterator("assets"))
    {
        auto ext = asset.path().extension();

        if (m_assetView == "Texture View" && (ext == ".png" || ext == ".jpeg" || ext == ".jpg"))
        {
            ImGui::Image(reinterpret_cast<void*>(AssetManager::getInstance()->getTexture(asset.path())->getId()), ImVec2{80, 80}, ImVec2{0, 1}, ImVec2{1, 0});

            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
            {
                ImGui::SetDragDropPayload("TextureAsset", asset.path().c_str(), asset.path().string().size() + 1);

                ImGui::Image(reinterpret_cast<void*>(AssetManager::getInstance()->getTexture(asset.path())->getId()), ImVec2{80, 80}, ImVec2{0, 1}, ImVec2{1, 0});
                ImGui::SameLine();
                ImGui::Text(asset.path().c_str());

                ImGui::EndDragDropSource();
            }

            ImGui::SameLine();
        }

        if (m_assetView == "Audio View" && (ext == ".mp3" || ext == ".wav" || ext == ".flac"))
        {
            ImGui::Image(reinterpret_cast<void*>(AssetManager::getInstance()->getTexture("assets/audio_preview.png")->getId()), ImVec2{80, 80}, ImVec2{0, 1}, ImVec2{1, 0});

            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
            {
                ImGui::SetDragDropPayload("AudioAsset", asset.path().c_str(), asset.path().string().size() + 1);

                ImGui::Image(reinterpret_cast<void*>(AssetManager::getInstance()->getTexture("assets/audio_preview.png")->getId()), ImVec2{80, 80}, ImVec2{0, 1}, ImVec2{1, 0});
                ImGui::Text(asset.path().c_str());

                ImGui::EndDragDropSource();
            }

            ImGui::SameLine();
        }
    }

    ImGui::End();
}

}