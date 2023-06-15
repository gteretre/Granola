// Granola - Granola - OpenGLRendererAPI.h
// Created: 2023.06.15-11:22 PM
// Modified: 2023.06.15-11:22 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "Granola/Renderer/RendererAPI.h"

namespace Granola
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4 &color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
	};
}
