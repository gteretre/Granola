#include <Granola.h>
#include <Granola/Log.h>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* BUG access violation 0xC0000005 or 0x0000... (nullptr) means problems with GLFW or glad initialization check:
 * 1. Check status and success variables in WindowsWindow.cpp
 * 2. Check if gladLoadGLLoader is called after glfwMakeContextCurrent, glfwInit etc.
 * 3. Check if glad is initialized before any OpenGL call
 */

glm::mat4 camera(const float Translate, const glm::vec2 &Rotate)
{
	const glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.f, -Translate));
	View = rotate(View, Rotate.y, glm::vec3(-1.f, 0.f, 0.f));
	View = rotate(View, Rotate.x, glm::vec3(0.f, 1.f, 0.f));
	const glm::mat4 Model = scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}


class ExampleLayer final : public Granola::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		auto camPos = camera(5.0f, {0.5f, 0.5f});
		GRL_TRACE("camPos: ", camPos);
	}

	virtual void OnUpdate() override
	{
		/*	EXAMPLE
		 *if (Granola::Input::IsMouseButtonPressed(GRL_MOUSE_BUTTON_LEFT))
			GRL_WARN("mouse left pressed");*/
	}

	virtual void OnEvent(Granola::Event &event) override
	{
		/*	EXAMPLE
		 *if (event.GetEventType() == Granola::EventType::KeyPressed)
		{
			const auto &e = dynamic_cast<Granola::KeyPressedEvent&>(event);
			GRL_TRACE("typed: ", static_cast<char>(e.GetKeyCode()));
		}*/
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
