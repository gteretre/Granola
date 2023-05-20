#include "grlpch.h"
#include <GL/gl.h>

#include "App.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Granola
{
	App::App()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	App::~App() = default;

	void App::Run()
	{
		GRL_CORE_INFO("Starting Granola Engine");
		// TODO GLR_OPENGL_DEBUG; should be here
		while (m_IsRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
		//TODO add GRL_OPENGL_DEBUG
		while (true);
	}
}
