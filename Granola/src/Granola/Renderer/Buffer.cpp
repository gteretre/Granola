#include "grlpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>


namespace Granola
{
	VertexBuffer *VertexBuffer::Create(const float *vertices, const uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer *IndexBuffer::Create(const uint32_t *indices, const uint32_t count)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
