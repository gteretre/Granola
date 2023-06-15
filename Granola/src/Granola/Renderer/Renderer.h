// Granola - Granola - Renderer.h
// Created: 2023.06.14-4:50 PM
// Modified: 2023.06.14-4:50 PM
// 
// Copyright Michael Kowalski 2023

#pragma once

namespace Granola
{
	class Renderer
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		static API GetRendererAPI() { return s_RenderAPI; }

	private:
		inline static API s_RenderAPI = API::OpenGL;
	};
}
