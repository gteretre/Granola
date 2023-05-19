#include <Granola.h>
// TODO spdlog may not work (linker problem)
// D:\Cpp\Granola\vendor\spdlog\include;

class Sandbox final : public Granola::App
{
public:
	Sandbox()
	{
	}

	virtual ~Sandbox() override
	{
	}
};

Granola::App *Granola::CreateApp()
{
	return new Sandbox();
	// TODO use smart pointers
}
