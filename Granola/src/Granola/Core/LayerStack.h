﻿// Granola - Granola - LayerStack.h
// Created: 2023.05.21-9:48 PM
// Modified: 2023.05.21-9:48 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "grlpch.h"
#include "Layer.h"

namespace Granola
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();
		void PushLayer(Layer *layer);
		void PushOverlay(Layer *overlay);
		void PopLayer(Layer *layer);
		void PopOverlay(Layer *overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		[[nodiscard]] std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		[[nodiscard]] std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		[[nodiscard]] std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		[[nodiscard]] std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers{};
		unsigned int m_LayerInsertIndex = 0;
	};
}
