#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"

namespace Granola
{
	class GRANOLA_API App
	{
	public:
		App();
		virtual ~App();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	// To be defined in client
	App *CreateApp();
}
