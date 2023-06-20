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
	/**
	 * \brief Here rendering is handled.
	 */
	class Renderer
	{
	public:
		/**
		 * \brief Function to initialize the renderer.
		 * \param camera Camera to be used for rendering. From OrthographicCamera class.
		 */
		static void BeginScene(const OrthographicCamera &camera);
		static void EndScene();

		static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray,
						   const glm::mat4 &transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData *m_SceneData;
	};
}
