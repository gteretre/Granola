// Granola - Granola - MouseEvent.h
// Created: 2023.05.19-5:13 PM
// Modified: 2023.05.19-5:13 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Event.h"

namespace Granola
{
	class MouseMovedEvent final : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y)
		{
		}

		[[nodiscard]] float GetX() const { return m_MouseX; }
		[[nodiscard]] float GetY() const { return m_MouseY; }

		[[nodiscard]] virtual std::string ToString() const override
		{
			std::stringstream ssMousePos;
			ssMousePos << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ssMousePos.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent final : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset)
		{
		}

		[[nodiscard]] float GetXOffset() const { return m_XOffset; }
		[[nodiscard]] float GetYOffset() const { return m_YOffset; }

		[[nodiscard]] virtual std::string ToString() const override
		{
			std::stringstream ssMouseScroll;
			ssMouseScroll << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ssMouseScroll.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		[[nodiscard]] int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		explicit MouseButtonEvent(const int button) : m_Button(button)
		{
		}

		int m_Button;
	};

	class MouseButtonPressedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonPressedEvent(const int button) : MouseButtonEvent(button)
		{
		}

		[[nodiscard]] virtual std::string ToString() const override
		{
			std::stringstream ssMouseButtonPressed;
			ssMouseButtonPressed << "MouseButtonPressedEvent: " << m_Button;
			return ssMouseButtonPressed.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button)
		{
		}

		[[nodiscard]] virtual std::string ToString() const override
		{
			std::stringstream ssMouseButtonReleased;
			ssMouseButtonReleased << "MouseButtonReleasedEvent: " << m_Button;
			return ssMouseButtonReleased.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
