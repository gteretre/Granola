// Granola - Granola - RenderCommand.h
// Created: 2023.06.15-11:07 PM
// Modified: 2023.06.15-11:07 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "RendererAPI.h"

namespace Granola
{
	class RenderCommand
	{
	public:
		static void Init() { s_RendererAPI->Init(); }
		static void SetClearColor(const glm::vec4 &color) { s_RendererAPI->SetClearColor(color); }

		static void SetClearColor(const float r, const float g, const float b, const float a)
		{
			s_RendererAPI->SetClearColor(glm::vec4(r, g, b, a));
		}

		static void Clear() { s_RendererAPI->Clear(); }
		static void DrawIndexed(const Ref<VertexArray> &vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI *s_RendererAPI;
	};
}
