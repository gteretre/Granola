// Granola - Granola - GraphicsContext.h
// Created: 2023.06.10-8:38 PM
// Modified: 2023.06.10-8:38 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

namespace Granola
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
