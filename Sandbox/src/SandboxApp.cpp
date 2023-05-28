#include <Granola.h>
#include <Granola/Log.h>

/* BUG access violation 0xC0000005 or 0x0000... (nullptr) means problems with GLFW or glad initialization check:
 * 1. Check status and success variables in WindowsWindow.cpp
 * 2. Check if gladLoadGLLoader is called after glfwMakeContextCurrent, glfwInit etc.
 * 3. Check if glad is initialized before any OpenGL call
 */
class ExampleLayer final : public Granola::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{
	}

	virtual void OnEvent(Granola::Event &event) override
	{
	}
};

class Sandbox final : public Granola::App
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Granola::ImGuiLayer());
	}

	virtual ~Sandbox() override = default;
};

Granola::App *Granola::CreateApp()
{
	return new Sandbox();
}
