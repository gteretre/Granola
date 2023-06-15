#include "grlpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace Granola
{
	Ref<VertexBuffer> VertexBuffer::Create(const float *vertices, const uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case Renderer::API::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case Renderer::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(const uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case Renderer::API::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case Renderer::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(const uint32_t *indices, const uint32_t count)
	{
		switch (Renderer::GetRendererAPI())
		{
		case Renderer::API::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case Renderer::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
