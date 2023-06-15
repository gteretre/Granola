#include "grlpch.h"
#include "ImGuiLayer.h"
#include "Granola/Core/App.h"
#include "Granola/Core/KeyCodes.h"

//BUG problems with linking imgui, some locations are hardcoded in files:
//D:\Cpp\Granola\Granola\vendor\imgui\backends\imgui_impl_glfw.cpp
//D:\Cpp\Granola\Granola\vendor\imgui\backends\imgui_impl_opengl3.cpp
//D:\Cpp\Granola\Granola\vendor\imgui\backends\imgui_impl_glfw.h
//D:\Cpp\Granola\Granola\vendor\imgui\backends\imgui_impl_opengl3.h
//D:\Cpp\Granola\Granola\vendor\imgui\backends\imgui_impl_win32.cpp
//D:\Cpp\Granola\Granola\vendor\imgui\backends\imgui_impl_win32.h
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
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
		ImGui::StyleColorsDark(); // or ImGui::StyleColorsClassic();
		ImGuiIO &imGuiIO = ImGui::GetIO();

		imGuiIO.BackendFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		imGuiIO.BackendFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
		imGuiIO.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
		imGuiIO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
		//imGuiIO.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//imGuiIO.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImGuiStyle &imGuiStyle = ImGui::GetStyle();
		if (imGuiIO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			imGuiStyle.WindowRounding = 0.0f;
			imGuiStyle.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		const App &app = App::Get();
		auto *window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		const App &app = App::Get();
		imGuiIO.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()),
									 static_cast<float>(app.GetWindow().GetHeight()));

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (imGuiIO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}
