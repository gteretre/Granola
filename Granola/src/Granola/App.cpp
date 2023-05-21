#include "grlpch.h"
#include <GL/gl.h>

#include "App.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"

namespace Granola
{
	//#define GRL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define GRL_BIND_EVENT_FN(fn) [this](auto&&... args) { return fn(std::forward<decltype(args)>(args)...); }


	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(GRL_BIND_EVENT_FN(OnEvent));
	}

	App::~App() = default;

	void App::OnEvent(Event &currentEvent)
	{
		EventDispatcher dispatcher(currentEvent);
		dispatcher.Dispatch<WindowCloseEvent>(GRL_BIND_EVENT_FN(OnWindowClose));
		GRL_CORE_TRACE("{0}", currentEvent);
	}

	void App::Run() const
	{
		GRL_CORE_INFO("Starting Granola Engine");
		// TODO GLR_OPENGL_DEBUG; should be here
		while (m_IsRunning)
		{
			glClearColor(0.1f, 0.3f, 0.6f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent &currentEvent)
	{
		m_IsRunning = false;
		return true;
	}
}
