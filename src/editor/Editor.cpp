#include <editor/Editor.h>
#include <editor/ImGuiLayer.h>
#include <editor/InspectorPanel.h>
#include <editor/ScenePanel.h>
#include <editor/AssetPanel.h>

// TEMPORARY
#include <onyx/scene/GameObject.h>

#include <GL/glew.h>
#include <imgui/imgui.h>

namespace Onyx
{

Editor::Editor()
{
    auto scene = std::make_shared<Scene>("Scene 1");
    m_scenes.push_back(scene);
    m_currentScene = scene;
    scene->start();
}

void Editor::onStart()
{
    getWindow()->setSize(Vector2u(1920, 1080));

    ImGuiLayer::init();

    createFramebuffer();
}

void Editor::onUpdate(float dt)
{
    
}

void Editor::onRender()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_currentScene->render();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGuiLayer::beginFrame();

    auto viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
    | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
	| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("Window", nullptr, windowFlags);
    ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(0.f, 0.f), ImGuiDockNodeFlags_None);

    ScenePanel::drawScenePanel(m_currentScene);
    InspectorPanel::drawInspectorPanel(m_selected);
    AssetPanel::drawAssetPanel();

    ImGui::Begin("Viewport");

    ImVec2 size = ImGui::GetContentRegionAvail();

    if (size.x != m_viewportSize.x || size.y != m_viewportSize.y)
    {
        m_viewportSize = Vector2u(size.x, size.y);
        createFramebuffer();
    }

    ImGui::Image(reinterpret_cast<void*>(m_fboColor), size, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::End();

    ImGui::End();
    ImGui::PopStyleVar();

    ImGuiLayer::endFrame();
}

void Editor::onDestroy()
{

}

void Editor::createFramebuffer()
{
    if (m_framebuffer != 0)
    {
        glDeleteFramebuffers(1, &m_framebuffer);
        glDeleteTextures(1, &m_fboColor);
    }

    glCreateFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_fboColor);
    glTextureStorage2D(m_fboColor, 1, GL_RGB8, m_viewportSize.x, m_viewportSize.y);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fboColor, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Editor::setSelectedObject(const WeakPtr<GameObject>& selected)
{
    m_selected = selected;
}

}