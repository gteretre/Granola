#include "grlpch.h"
#include "WindowsWindow.h"
#include "Granola/Core/Log.h"
#include "Granola/Events/ApplicationEvent.h"
#include "Granola/Events/KeyEvent.h"
#include "Granola/Events/MouseEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Granola
{
	static bool s_isGLFWInitialized = false;

	Window *Window::Create(const WindowProps &props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps &props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps &props)
	{
		// copy window properties
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		GRL_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		// initialize GLFW
		if (!s_isGLFWInitialized)
		{
			// glfw terminate on system shutdown
			if (GetSystemMetrics(SM_SHUTTINGDOWN))
				glfwTerminate();

			const int success = glfwInit();
			GRL_CORE_ASSERT(success, "Could not initialize GLFW!")

			glfwSetErrorCallback([](const int error, const char *description)
			{
				GRL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
			});

			s_isGLFWInitialized = true;
		}

		// create window and render context
		m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(),
									nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks (event handling)
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, const int width, const int height)
		{
			auto &[Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(
				glfwGetWindowUserPointer(window));
			Width = width;
			Height = height;
			WindowResizeEvent event(width, height);
			EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
		{
			auto &[Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(
				glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow *window, const int key, [[maybe_unused]] const int scancode,
										const int action, [[maybe_unused]] const int mods)
		{
			auto &[Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(
				glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					EventCallback(event);
					break;
				}
			default:
				{
					GRL_CORE_ERROR("Unknown key action {0}", action);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow *window, const unsigned int keycode)
		{
			auto &[Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(
				glfwGetWindowUserPointer(window));
			KeyTypedEvent event(static_cast<int>(keycode));
			EventCallback(event);
		});

		glfwSetMouseButtonCallback(
			m_Window, [](GLFWwindow *window, const int button, const int action, [[maybe_unused]] const int mods)
			{
				auto &[Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(
					glfwGetWindowUserPointer(window));
				switch (action)
				{
				case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						EventCallback(event);
						break;
					}
				case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						EventCallback(event);
						break;
					}
				default:
					{
						GRL_CORE_ERROR("Unknown mouse button action {0}", action);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *window, const double xOffset, const double yOffset)
		{
			auto &[Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(
				glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, const double xPos, const double yPos)
		{
			auto &[Title, Width, Height, VSync, EventCallback] = *static_cast<WindowData*>(
				glfwGetWindowUserPointer(window));
			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		GRL_CORE_INFO("Destroying window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(const bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::openNewTerminalWindow()
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

		// Modify the command below according to your preferred terminal program

		if (const auto command = "cmd.exe"; !CreateProcess(nullptr, LPWSTR(command), nullptr, nullptr,
														   FALSE, 0, nullptr, nullptr, &si, &pi))
			std::cerr << "Failed to create new terminal window" << std::endl;

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}
