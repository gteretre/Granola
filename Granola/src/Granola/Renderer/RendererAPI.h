// Granola - Granola - RendererAPI.h
// Created: 2023.06.15-10:59 PM
// Modified: 2023.06.15-10:59 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Granola
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4 &color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) = 0;
		static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}
