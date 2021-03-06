#include <editor/ImGuiLayer.h>
#include <onyx/core/Game.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Onyx
{

void ImGuiLayer::init()
{
    ImGui::CreateContext();

    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF("assets/font.ttf", 18.0f);

    ImGui_ImplGlfw_InitForOpenGL(Game::getInstance()->getWindow()->getNative(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiLayer::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiLayer::endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

void ImGuiLayer::destroy()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();

    ImGui::DestroyContext();
}

}