#include "grlpch.h"
#include "WindowsWindow.h"

#include "Granola/Log.h" // TODO take it to core
#include "Granola/Events/ApplicationEvent.h"
#include "Granola/Events/KeyEvent.h"
#include "Granola/Events/MouseEvent.h"

#include <glad/glad.h>

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
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		GRL_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
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

		m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(),
									nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		GRL_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
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
										const int action,
										[[maybe_unused]] const int mods)
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
		glfwSwapBuffers(m_Window);
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
}
