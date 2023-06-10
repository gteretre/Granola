// Granola - Granola - MouseEvent.h
// Created: 2023.05.19-5:13 PM
// Modified: 2023.05.19-5:13 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Event.h"

namespace Granola
{
	class  WindowResizeEvent final : public Event
	{
	public:
		WindowResizeEvent(const unsigned int width, const unsigned int height) : m_Width(width), m_Height(height)
		{
		}

		[[nodiscard]] unsigned int GetWidth() const { return m_Width; }
		[[nodiscard]] unsigned int GetHeight() const { return m_Height; }

		[[nodiscard]] virtual std::string ToString() const override
		{
			std::stringstream ssWindowSize;
			ssWindowSize << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ssWindowSize.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class  WindowCloseEvent final : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  AppTickEvent final : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  AppUpdateEvent final : public Event
	{
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  AppRenderEvent final : public Event
	{
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
