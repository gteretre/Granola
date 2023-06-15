// Granola - Granola - Renderer.h
// Created: 2023.06.14-4:50 PM
// Modified: 2023.06.14-4:50 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "RenderCommand.h"

namespace Granola
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray> &vertexArray);


		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
