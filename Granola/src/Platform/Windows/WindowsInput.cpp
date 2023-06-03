#include "grlpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Granola/App.h"

namespace Granola
{
	Input *Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(const int keycode)
	{
		const auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		const auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(const int button)
	{
		const auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		const auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		const auto window = static_cast<GLFWwindow*>(App::Get().GetWindow().GetNativeWindow());
		double xPos{}, yPos{};
		glfwGetCursorPos(window, &xPos, &yPos);
		return {static_cast<float>(xPos), static_cast<float>(yPos)};
	}

	float WindowsInput::GetMouseXImpl()
	{
		const auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		const auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
