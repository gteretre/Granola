#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"


namespace Granola
{
	class GRANOLA_API App
	{
	public:
		App();
		virtual ~App();

		void Run() const;
		void OnEvent(Event &currentEvent);

	private:
		bool OnWindowClose(WindowCloseEvent &currentEvent);

		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	// To be defined in client
	App *CreateApp();
}
