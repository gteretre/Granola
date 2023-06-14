// Granola - Granola - Renderer.h
// Created: 2023.06.14-4:50 PM
// Modified: 2023.06.14-4:50 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

namespace Granola
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		static RendererAPI GetRendererAPI() { return s_RenderAPI; }

	private:
		inline static RendererAPI s_RenderAPI = RendererAPI::OpenGL;
	};
}
