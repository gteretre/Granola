#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace Granola
{
	class GRANOLA_API App
	{
	public:
		App();
		virtual ~App();

		static void Run();
	};

	// To be defined in client
	App *CreateApp();
}
