/* Log.cpp */
#include "grlpch.h"
#include "Log.h"

#include <glad/glad.h>
#pragma warning(push, 0)
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#pragma warning(pop)


namespace Granola
{
	void Log::log(const std::string &color, const std::string &type, const std::string &message)
	{
		std::scoped_lock lock(m_mutex);

		const auto now = std::chrono::system_clock::now();
		const std::time_t time = std::chrono::system_clock::to_time_t(now);
		std::tm tm{};
#ifdef _MSC_VER
		if (localtime_s(&tm, &time))
			throw std::runtime_error("Failed to get localtime");
#else
	if (localtime_r(&time, &tm));
			throw std::runtime_error("Failed to get localtime");
#endif
		std::cout << color << '[' << std::put_time(&tm, "%T") << "] " << '[' << type << "]: " << message << RESET <<
			'\n';
	}

#ifdef GRL_LOGGING_WITH_SPDLOG
	std::shared_ptr<spdlog::logger> Logspd::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logspd::s_ClientLogger;

	void Logspd::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}
#endif

	// OpenGL Log
	void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, const GLenum severity,
								[[maybe_unused]] GLsizei length,
								const GLchar *message, [[maybe_unused]] const void *userParam)
	{
		id = static_cast<int>(id);
		source = static_cast<int>(source);
		type = static_cast<int>(type);
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
