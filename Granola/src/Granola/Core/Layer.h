// Granola - Granola - Layer.h
// Created: 2023.05.21-9:48 PM
// Modified: 2023.05.21-9:48 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

#include "Granola/Events/Event.h"

namespace Granola
{
	class Layer // TODO declspec may be unnecessary here
	{
	public:
		explicit Layer(std::string debugName = "Layer");

		virtual ~Layer();


		virtual void OnAttach()
		{
			// temporary empty, to be implemented
		}

		virtual void OnDetach()
		{
			// temporary empty, to be implemented
		}

		virtual void OnUpdate()
		{
			// temporary empty, to be implemented
		}

		virtual void OnImGuiRender()
		{
			// temporary empty, to be implemented
		}

		virtual void OnEvent([[maybe_unused]] Event &event)
		{
			// temporary empty, to be implemented
		}

		[[nodiscard]] const std::string &GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
