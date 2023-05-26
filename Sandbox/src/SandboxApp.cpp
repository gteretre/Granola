#include <Granola.h>
#include <Granola/Log.h>

class ExampleLayer final : public Granola::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{
		//GRL_INFO("ExampleLayer::Update");
	}

	virtual void OnEvent(Granola::Event &event) override
	{
		//GRL_TRACE("{0}", event);
	}
};

class Sandbox final : public Granola::App
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox() override = default;
};

Granola::App *Granola::CreateApp()
{
	return new Sandbox();
}
