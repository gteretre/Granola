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

		//TODO: Set Granola key map for all keys
		imGuiIO.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		imGuiIO.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		imGuiIO.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		imGuiIO.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		imGuiIO.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		imGuiIO.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		imGuiIO.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		imGuiIO.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		imGuiIO.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		imGuiIO.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		imGuiIO.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		imGuiIO.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		imGuiIO.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		imGuiIO.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		imGuiIO.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		imGuiIO.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		imGuiIO.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		imGuiIO.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		imGuiIO.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		imGuiIO.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		imGuiIO.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		imGuiIO.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;


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

		imGuiIO.KeyCtrl = imGuiIO.KeysDown[GLFW_KEY_LEFT_CONTROL] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		imGuiIO.KeyShift = imGuiIO.KeysDown[GLFW_KEY_LEFT_SHIFT] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		imGuiIO.KeyAlt = imGuiIO.KeysDown[GLFW_KEY_LEFT_ALT] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_ALT];
		imGuiIO.KeySuper = imGuiIO.KeysDown[GLFW_KEY_LEFT_SUPER] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(const KeyReleasedEvent &keyEvent)
	{
		ImGuiIO &imGuiIO = ImGui::GetIO();
		imGuiIO.KeysDown[keyEvent.GetKeyCode()] = false;

		imGuiIO.KeyCtrl = imGuiIO.KeysDown[GLFW_KEY_LEFT_CONTROL] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		imGuiIO.KeyShift = imGuiIO.KeysDown[GLFW_KEY_LEFT_SHIFT] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		imGuiIO.KeyAlt = imGuiIO.KeysDown[GLFW_KEY_LEFT_ALT] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_ALT];
		imGuiIO.KeySuper = imGuiIO.KeysDown[GLFW_KEY_LEFT_SUPER] || imGuiIO.KeysDown[GLFW_KEY_RIGHT_SUPER];

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
