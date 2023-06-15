// Granola - Granola - ImGuiLayer.h
// Created: 2023.05.26-8:52 PM
// Modified: 2023.05.26-8:52 PM
// 
// Copyright Michael Kowalski 2023
#pragma once
#include "Granola/Core/Layer.h"
#include "Granola/Events/Event.h"


namespace Granola
{
	class ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		static void Begin();
		static void End();

	private:
		float m_Time = 0.0f;
	};
}
