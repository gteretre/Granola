#pragma once
#include "Core.h"

namespace Granola
{
	class GRANOLA_API App
	{
	public:
		App();
		virtual ~App();

		void Run();
	};

	// To be defined in client
	App *CreateApp();
}
