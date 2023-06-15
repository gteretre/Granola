/* EntryPoint.h */
#pragma once
#include "App.h"
#include "Granola/Core/Log.h"
#ifdef GRL_PLATFORM_WINDOWS

int main(int argc, char **argv)
{
	Granola::Log::Init();
	GRL_CORE_WARN("Initialized Log!");

	const auto app = Granola::CreateApp();
	app->Run();
	delete app;
}
#endif
