// Granola - Granola - WindowsWindow.h
// Created: 2023.05.19-9:21 PM
// Modified: 2023.05.19-9:21 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include <GLFW/glfw3.h>

#include "Granola/Window.h"


namespace Granola
{
	class WindowsWindow final : public Window
	{
	public:
		explicit WindowsWindow(const WindowProps &props);
		virtual ~WindowsWindow() override;

		virtual void OnUpdate() override;
		[[nodiscard]] virtual unsigned int GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] virtual unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		[[nodiscard]] virtual bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps &props);
		virtual void Shutdown();

		GLFWwindow *m_Window{};

		struct WindowData
		{
			std::string Title;
			unsigned int Width{}, Height{};
			bool VSync{};
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
