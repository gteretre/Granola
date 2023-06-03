#include "grlpch.h"
#include "ImGuiLayer.h"
#include "Granola/App.h"
#include "Granola/KeyCodes.h"
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
		ImGui_ImplOpenGL3_Init("#version 430");
	}

	void ImGuiLayer::OnDetach()
	{
		// to be implemented
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
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(GRL_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(const MouseButtonPressedEvent &mouseEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.MouseDown[mouseEvent.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent &mouseEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.MouseDown[mouseEvent.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(const MouseMovedEvent &mouseEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.MousePos = ImVec2(mouseEvent.GetX(), mouseEvent.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(const MouseScrolledEvent &mouseEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.MouseWheelH += mouseEvent.GetXOffset();
		imGuiIO.MouseWheel += mouseEvent.GetYOffset();
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(const KeyPressedEvent &keyEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.KeysDown[keyEvent.GetKeyCode()] = true;

		imGuiIO.KeyCtrl = imGuiIO.KeysDown[GRL_KEY_LEFT_CONTROL] || imGuiIO.KeysDown[GRL_KEY_RIGHT_CONTROL];
		imGuiIO.KeyShift = imGuiIO.KeysDown[GRL_KEY_LEFT_SHIFT] || imGuiIO.KeysDown[GRL_KEY_RIGHT_SHIFT];
		imGuiIO.KeyAlt = imGuiIO.KeysDown[GRL_KEY_LEFT_ALT] || imGuiIO.KeysDown[GRL_KEY_RIGHT_ALT];
		imGuiIO.KeySuper = imGuiIO.KeysDown[GRL_KEY_LEFT_SUPER] || imGuiIO.KeysDown[GRL_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(const KeyReleasedEvent &keyEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.KeysDown[keyEvent.GetKeyCode()] = false;

		imGuiIO.KeyCtrl = imGuiIO.KeysDown[GRL_KEY_LEFT_CONTROL] || imGuiIO.KeysDown[GRL_KEY_RIGHT_CONTROL];
		imGuiIO.KeyShift = imGuiIO.KeysDown[GRL_KEY_LEFT_SHIFT] || imGuiIO.KeysDown[GRL_KEY_RIGHT_SHIFT];
		imGuiIO.KeyAlt = imGuiIO.KeysDown[GRL_KEY_LEFT_ALT] || imGuiIO.KeysDown[GRL_KEY_RIGHT_ALT];
		imGuiIO.KeySuper = imGuiIO.KeysDown[GRL_KEY_LEFT_SUPER] || imGuiIO.KeysDown[GRL_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(const KeyTypedEvent &keyEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		if (keyEvent.GetKeyCode() > 0 && keyEvent.GetKeyCode() < 0x10000)
			imGuiIO.AddInputCharacter(keyEvent.GetKeyCode());
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(const WindowResizeEvent &windowResizeEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.DisplaySize = ImVec2(static_cast<float>(windowResizeEvent.GetWidth()),
									 static_cast<float>(windowResizeEvent.GetHeight()));
		setViewport(windowResizeEvent.GetWidth(), windowResizeEvent.GetHeight());
		return false;
	}

	void ImGuiLayer::setViewport(const unsigned int width, const unsigned int height)
	{
		/*todo make it resize properly etc.
		 *const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
		glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
		ImGui::GetIO().DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));
		ImGui::GetIO().DisplayFramebufferScale = ImVec2(aspectRatio, 1.0f);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1, 1);*/

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, -1, 1);
		glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	}
}
