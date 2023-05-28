// Granola - Granola - ImGuiLayer.h
// Created: 2023.05.26-8:52 PM
// Modified: 2023.05.26-8:52 PM
// 
// Copyright Michael Kowalski 2023
#pragma once
#include "Granola/Layer.h"
#include "Granola/Events/ApplicationEvent.h"
#include "Granola/Events/Event.h"
#include "Granola/Events/KeyEvent.h"
#include "Granola/Events/MouseEvent.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"


namespace Granola
{
	class GRANOLA_API ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() override;

		virtual void OnUpdate() override;
		virtual void OnEvent(Event &event) override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

	private:
		static bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent &mouseEvent);
		static bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent &mouseEvent);
		static bool OnMouseMovedEvent(const MouseMovedEvent &mouseEvent);
		static bool OnMouseScrolledEvent(const MouseScrolledEvent &mouseEvent);
		static bool OnKeyPressedEvent(const KeyPressedEvent &keyEvent);
		static bool OnKeyReleasedEvent(const KeyReleasedEvent &keyEvent);
		static bool OnKeyTypedEvent(const KeyTypedEvent &keyEvent);
		static bool OnWindowResizeEvent(const WindowResizeEvent &windowResizeEvent);

		static void setViewport(unsigned int width, unsigned int height);

		float m_Time = 0.0f;
	};
}
