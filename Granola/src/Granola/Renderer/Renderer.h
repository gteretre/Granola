// Granola - Granola - Renderer.h
// Created: 2023.06.14-4:50 PM
// Modified: 2023.06.14-4:50 PM
// 
// Copyright Michael Kowalski 2023

#pragma once
#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Granola
{
	class Renderer
	{
	public:
		static void BeginScene(const OrthographicCamera &camera);
		static void EndScene();

		static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData *m_SceneData;
	};
}
