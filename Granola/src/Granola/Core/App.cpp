﻿#include "grlpch.h"
#include "App.h"

#include "Granola/Core/Log.h"
#include "Granola/Core/Window.h"
#include "Granola/Events/ApplicationEvent.h"
#include "Granola/Events/Event.h"
#include "Granola/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

/*
 * to hunt openGL errors use:
 * if (const GLenum error = glGetError(); error != GL_NO_ERROR)
				GRL_CORE_ERROR("OpenGL Error: {0}", error);
 */

namespace Granola
{
	App *App::s_Instance = nullptr;

	App::App() : m_ImGuiLayer(new ImGuiLayer()) // may be better to use unique_ptr in the future to ImGuiLayer
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(GRL_BIND_EVENT_FN(OnEvent));
		//m_Window->SetVSync(false);
		PushOverlay(m_ImGuiLayer);
		Renderer::Init();
	}

	App::~App() = default;

	void App::PushLayer(Layer *layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer *overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void App::OnEvent(Event &currentEvent)
	{
		GRL_CORE_TRACE("{0}", currentEvent);
		EventDispatcher dispatcher(currentEvent);
		dispatcher.Dispatch<WindowCloseEvent>(GRL_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(GRL_BIND_EVENT_FN(OnWindowResize));

		for (const auto &it : std::ranges::reverse_view(m_LayerStack))
		{
			if (currentEvent.IsHandled())
				break;
			it->OnEvent(currentEvent);
		}
	}

	void App::Run()
	{
		if (!m_Minimized)
			while (m_IsRunning)
			{
				const auto time = static_cast<float>(glfwGetTime());
				// Platform::GetTime() eg. MacOS::GetTime() in the future
				const Timestep timestep = time - m_LastFrameTime;

				m_LastFrameTime = time;
				{
					for (const auto layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				ImGuiLayer::Begin();
				{
					for (const auto layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				ImGuiLayer::End();

				m_Window->OnUpdate();
			}
	}

	bool App::OnWindowClose([[maybe_unused]] const WindowCloseEvent &currentEvent)
	{
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); // to hunt memory leaks
		_CrtDumpMemoryLeaks(); // to hunt memory leaks
		m_IsRunning = false;
		return true;
	}

	bool App::OnWindowResize(const WindowResizeEvent &currentEvent)
	{
		if (currentEvent.GetWidth() == 0 || currentEvent.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		// in the future Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
