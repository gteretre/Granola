// Granola - Granola - ImGuiLayer.h
// Created: 2023.05.26-8:52 PM
// Modified: 2023.05.26-8:52 PM
// 
// Copyright Michael Kowalski 2023
#include "Granola/Layer.h"
#pragma once
namespace Granola
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() override;

		virtual void OnUpdate() override;
		virtual void OnEvent(Event &event) override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

	private:
	};
}
