// Granola - Granola - WindowsWindow.h
// Created: 2023.05.19-9:21 PM
// Modified: 2023.05.19-9:21 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

#include "Granola/Core/Window.h"
#include "Granola/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

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

		[[nodiscard]] virtual void *GetNativeWindow() const override { return m_Window; }
		static void openNewTerminalWindow(); // Not implemented yet terminal inside app

	private:
		void Init(const WindowProps &props);
		void Shutdown();

		GLFWwindow *m_Window{};
		GraphicsContext *m_Context{};

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
