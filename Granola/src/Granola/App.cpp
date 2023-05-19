#include "grlpch.h"
#include "App.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Granola
{
	App::App() = default;

	App::~App() = default;

	void App::Run()
	{
		//TODO this is just a test event and should be removed
		const WindowResizeEvent someTestEvent(1200, 720);
		if (someTestEvent.IsInCategory(EventCategoryApplication))
			GRL_INFO(EventCategoryApplication);
		GRL_TRACE(someTestEvent);
		while (true);
	}
}
