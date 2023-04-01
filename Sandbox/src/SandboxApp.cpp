#include <Granola.h>

class Sandbox : public Granola::App
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
	// use smart pointers
}
