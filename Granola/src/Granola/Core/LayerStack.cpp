#include "grlpch.h"
#include "LayerStack.h"

namespace Granola
{
	LayerStack::~LayerStack()
	{
		for (Layer *layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer *layer)
	{
		if (!layer)
			throw std::invalid_argument("Null pointer provided!");

		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		++m_LayerInsertIndex;
	}

	void LayerStack::PushOverlay(Layer *overlay)
	{
		if (!overlay)
			throw std::invalid_argument("Null pointer provided!");

		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer *layer)
	{
		if (!layer)
			throw std::invalid_argument("Null pointer provided!");

		if (const auto it = std::ranges::find(m_Layers, layer); it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);

			--m_LayerInsertIndex;
		}
	}

	void LayerStack::PopOverlay(Layer *overlay)
	{
		if (!overlay)
			throw std::invalid_argument("Null pointer provided!");

		if (const auto it = std::ranges::find(m_Layers, overlay); it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}
