/* EntryPoint.h */
#pragma once
#ifdef GRL_PLATFORM_WINDOWS

extern Granola::App *Granola::CreateApp();


int main(int argc, char **argv)
{
	Granola::Log::Init();
	GRL_CORE_WARN("Initialized Log!");
	int a = 7;
	GRL_INFO("Hi! Test Var={0}(7)", a);

	printf("\nWelcome in Granola!\n");


	const auto app = Granola::CreateApp();
	app->Run();
	delete app;
}
#endif
