#include "grlpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Granola
{
	RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
