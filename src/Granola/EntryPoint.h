#pragma once

#ifdef GRL_PLATFORM_WINDOWS

extern Granola::App *Granola::CreateApp();

int main(int argc, char **argv)
{
	printf("Welcome in Granola!");
	const auto app = Granola::CreateApp();
	app->Run();
	delete app;
}
#endif
