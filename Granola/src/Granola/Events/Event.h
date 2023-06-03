/*
 *INFO
 *
 **/
#pragma once

#include "Granola/Core.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Granola
{
	enum class EventType
	{
		None = 0,
		// Window Events
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		// App Events
		AppTick,
		AppUpdate,
		AppRender,
		// Key Events
		KeyPressed,
		KeyReleased,
		KeyTyped,
		// Mouse Events
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory // Events filter
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class GRANOLA_API Event
	{
		friend class EventDispatcher;

	public:
		Event() = default;
		virtual ~Event() = default;

		[[nodiscard]] virtual EventType GetEventType() const = 0;
		[[nodiscard]] virtual const char *GetName() const = 0;
		[[nodiscard]] virtual int GetCategoryFlags() const = 0;
		[[nodiscard]] virtual std::string ToString() const { return GetName(); }

		[[nodiscard]] bool IsInCategory(const EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

		[[nodiscard]] bool IsHandled() const { return m_Handled; }

		bool m_Handled = false; // TODO maybe just protected
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T &)>;

	public:
		explicit EventDispatcher(Event &event) : m_Event(event)
		{
		}

		template <typename T, typename F>
		bool Dispatch(const F &func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event &m_Event;
	};

	//---Operator overloads---
	inline std::ostream &operator<<(std::ostream &os, const Event &currentEvent)
	{
		return os << currentEvent.ToString();
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::vec2 &vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::mat4 &mat)
	{
		return os << "(" << mat[0] << ", " << mat[1] << ", " << mat[2] << ", " << mat[3] << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::mat3 &mat)
	{
		return os << "(" << mat[0] << ", " << mat[1] << ", " << mat[2] << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::mat2 &mat)
	{
		return os << "(" << mat[0] << ", " << mat[1] << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::quat &quat)
	{
		return os << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")";
	}
}
