/* Log.cpp */
#include "grlpch.h"

#include <glad/glad.h>
#pragma warning(push, 0)
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

#include "Log.h"


namespace Granola
{
	// OpenGL Log
	void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, const GLenum severity,
								[[maybe_unused]] GLsizei length,
								const GLchar *message, [[maybe_unused]] const void *userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			GRL_CORE_FATAL("OpenGL Error ({0}): Source={1}, Type={2}, Message={3}", id, source, type, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			GRL_CORE_ERROR("OpenGL Error ({0}): Source={1}, Type={2}, Message={3}", id, source, type, message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			GRL_CORE_WARN("OpenGL Error ({0}): Source={1}, Type={2}, Message={3}", id, source, type, message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			GRL_CORE_TRACE("OpenGL Message ({0}): Source={1}, Type={2}, Message={3}", id, source, type, message);
			break;
		default:
			GRL_CORE_INFO("OpenGL Message ({0}): Source={1}, Type={2}, Message={3}", id, source, type, message);
			break;
		}
	}
}
