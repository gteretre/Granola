#include "grlpch.h"
#include "VertexArray.h"

#include "Renderer.h"

namespace Granola
{
	VertexArray *VertexArray::Create()
	{
		switch (Renderer::GetRendererAPI())
		{
		case Renderer::API::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case Renderer::API::OpenGL:
			//return CreateRef<OpenGLVertexArray>();
			return nullptr;
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
