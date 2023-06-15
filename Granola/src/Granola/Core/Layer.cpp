#include "grlpch.h"
#include "Layer.h"

namespace Granola
{
	Layer::Layer(std::string debugName) : m_DebugName(std::move(debugName))
	{
	}

	Layer::~Layer() = default;
}
