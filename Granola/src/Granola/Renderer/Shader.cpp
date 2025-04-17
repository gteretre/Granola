#include "grlpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Granola
{
	Shader *Shader::Create(const std::string &filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader *Shader::Create(const std::string &vertexSource, const std::string &fragmentSource)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			GRL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		GRL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
