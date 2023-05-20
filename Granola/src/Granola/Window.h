// Granola - Granola - Window.h
// Created: 2023.05.19-8:50 PM
// Modified: 2023.05.19-8:50 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Core.h"
#include "Granola/Events/Event.h"

namespace Granola
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		explicit WindowProps(std::string title = "Granola Engine",
							 const unsigned int width = 1280,
							 const unsigned int height = 720)
			: Title(std::move(title)), Width(width), Height(height)
		{
		}
	};

	// depending on what platform it will be runned (Windows Window, MacOS Window, ...)
	class GRANOLA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event &)>;
		virtual ~Window() = default;
		virtual void OnUpdate() = 0;
		[[nodiscard]] virtual unsigned int GetWidth() const = 0;
		[[nodiscard]] virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		[[nodiscard]] virtual bool IsVSync() const = 0;

		static Window *Create(const WindowProps &props = WindowProps());
	};
}
