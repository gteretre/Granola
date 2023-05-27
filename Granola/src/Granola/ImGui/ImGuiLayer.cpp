#include "grlpch.h"
#include "ImGuiLayer.h"
#include "Granola/App.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include <imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Granola
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer() = default;

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO &imGuiIO = ImGui::GetIO();

		imGuiIO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		imGuiIO.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TODO : Set Granola Keymap
		imGuiIO.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		imGuiIO.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		const App &app = App::Get();
		imGuiIO.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()),
									 static_cast<float>(app.GetWindow().GetHeight()));

		const auto time = static_cast<float>(glfwGetTime());
		imGuiIO.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event &event)
	{
	}
}
