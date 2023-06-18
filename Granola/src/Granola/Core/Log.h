/* Log.h */
#pragma once
#include "grlpch.h"
#include "Base.h"
#include "Granola/Events/Event.h"

#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

//#define GRL_LOGGING_WITH_SPDLOG
// ignore all spdlog warnings
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Granola
{
#define RESET   "\033[0m"
#define RED     "\033[38;2;160;47;31m"
#define GREEN   "\033[38;2;87;102;43m"
#define YELLOW  "\033[38;2;185;163;140m"
#define BLUE    "\033[38;2;72;120;140m"
#define MAGENTA "\033[38;2;161;88;151m"
#define CYAN    "\033[36m"
#define WHITE   "\033[38;2;250;250;250m"
#define GREY    "\033[38;2;121;131;121m"
#pragma warning(disable : 4858) // until multithreading is made good
	class Log
	{
	public:
		static void Init()
		{
			std::cout << "Granola Engine Log\n";
		}

		template <typename... Args>
		class GetCoreLogger
		{
		public:
			template <typename... TraceArgs>
			static void trace(TraceArgs &&... args)
			{
				std::stringstream ss;
				((ss << std::forward<TraceArgs>(args)), ...);
				const std::string message = ss.str();
				std::jthread(log,BLUE, "TRACE", message);
			}

			template <typename... TraceArgs>
			static void info(TraceArgs &&... args)
			{
				std::stringstream ss;
				((ss << std::forward<TraceArgs>(args)), ...);
				const std::string message = ss.str();
				std::jthread(log,GREEN, "INFO", message);
			}

			template <typename... TraceArgs>
			static void warn(TraceArgs &&... args)
			{
				std::stringstream ss;
				((ss << std::forward<TraceArgs>(args)), ...);
				const std::string message = ss.str();
				std::jthread(log,YELLOW, "WARNING", message);
			}

			template <typename... TraceArgs>
			static void error(TraceArgs &&... args)
			{
				std::stringstream ss;
				((ss << std::forward<TraceArgs>(args)), ...);
				const std::string message = ss.str();
				std::jthread(log,RED, "ERROR", message);
			}

			template <typename... TraceArgs>
			static void critical(TraceArgs &&... args)
			{
				std::stringstream ss;
				((ss << std::forward<TraceArgs>(args)), ...);
				const std::string message = ss.str();
				std::jthread(log,MAGENTA, "FATAL", message);
			}
		};

	private:
		inline static std::mutex m_mutex{};
		static void log(const std::string &color, const std::string &type, const std::string &message);
	};

#ifdef GRL_LOGGING_WITH_SPDLOG
	class Logspd
	{
	public:
		static void Init();

		static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
#endif


	//---Operator overloads---
	inline std::ostream &operator<<(std::ostream &os, const Event &currentEvent)
	{
		return os << currentEvent.ToString();
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::vec2 &vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::vec4 &vec)
	{
		return os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::mat4 &mat)
	{
		return os << "(" << mat[0] << ", " << mat[1] << ", " << mat[2] << ", " << mat[3] << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::mat3 &mat)
	{
		return os << "(" << mat[0] << ", " << mat[1] << ", " << mat[2] << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::mat2 &mat)
	{
		return os << "(" << mat[0] << ", " << mat[1] << ")";
	}

	inline std::ostream &operator<<(std::ostream &os, const glm::quat &quat)
	{
		return os << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")";
	}

	template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
	OStream &operator<<(OStream &os, const glm::vec<L, T, Q> &vector)
	{
		return os << glm::to_string(vector);
	}

	template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
	OStream &operator<<(OStream &os, const glm::mat<C, R, T, Q> &matrix)
	{
		return os << glm::to_string(matrix);
	}

	template <typename OStream, typename T, glm::qualifier Q>
	OStream &operator<<(OStream &os, glm::qua<T, Q> quaternion)
	{
		return os << glm::to_string(quaternion);
	}
}

#ifdef GRL_DEBUG
#define GRL_LOGGING
#endif

// Core Log macros
#ifdef GRL_LOGGING
#ifdef GRL_LOGGING_WITH_SPDLOG
#define GRL_CORE_TRACE(...) ::Granola::Logspd::GetCoreLogger()->trace(__VA_ARGS__)
#define GRL_CORE_INFO(...)  ::Granola::Logspd::GetCoreLogger()->info(__VA_ARGS__)
#define GRL_CORE_WARN(...)  ::Granola::Logspd::GetCoreLogger()->warn(__VA_ARGS__)
#define GRL_CORE_ERROR(...) ::Granola::Logspd::GetCoreLogger()->error(__VA_ARGS__)
#define GRL_CORE_FATAL(...) ::Granola::Logspd::GetCoreLogger()->critical(__VA_ARGS__)
#define GRL_CORE_CRITICAL GRL_CORE_FATAL
#else
#define GRL_CORE_TRACE(...) ::Granola::Log::GetCoreLogger<>::trace(__VA_ARGS__)
#define GRL_CORE_INFO(...)  ::Granola::Log::GetCoreLogger<>::info(__VA_ARGS__)
#define GRL_CORE_WARN(...)  ::Granola::Log::GetCoreLogger<>::warn(__VA_ARGS__)
#define GRL_CORE_ERROR(...) ::Granola::Log::GetCoreLogger<>::error(__VA_ARGS__)
#define GRL_CORE_FATAL(...) ::Granola::Log::GetCoreLogger<>::critical(__VA_ARGS__)
#define GRL_CORE_CRITICAL GRL_CORE_FATAL
#endif
#else
#define GRL_CORE_TRACE(...) 
#define GRL_CORE_INFO(...)
#define GRL_CORE_WARN(...)
#define GRL_CORE_ERROR(...)
#define GRL_CORE_FATAL(...)
#define GRL_CORE_CRITICAL GRL_CORE_FATAL
#endif

// Client Log Macros
#ifdef GRL_LOGGING
#ifdef GRL_LOGGING_WITH_SPDLOG
#define GRL_TRACE(...) ::Granola::Logspd::GetClientLogger()->trace(__VA_ARGS__)
#define GRL_INFO(...)  ::Granola::Logspd::GetClientLogger()->info(__VA_ARGS__)
#define GRL_WARN(...)  ::Granola::Logspd::GetClientLogger()->warn(__VA_ARGS__)
#define GRL_ERROR(...) ::Granola::Logspd::GetClientLogger()->error(__VA_ARGS__)
#define GRL_FATAL(...) ::Granola::Logspd::GetClientLogger()->critical(__VA_ARGS__)
#define GRL_CRITICAL GRL_CORE_FATAL
#else
#define GRL_TRACE(...) ::Granola::Log::GetCoreLogger<>::trace(__VA_ARGS__)
#define GRL_INFO(...)  ::Granola::Log::GetCoreLogger<>::info(__VA_ARGS__)
#define GRL_WARN(...)  ::Granola::Log::GetCoreLogger<>::warn(__VA_ARGS__)
#define GRL_ERROR(...) ::Granola::Log::GetCoreLogger<>::error(__VA_ARGS__)
#define GRL_FATAL(...) ::Granola::Log::GetCoreLogger<>::critical(__VA_ARGS__)
#define GRL_CRITICAL GRL_FATAL
#endif
#else
#define GRL_TRACE(...)
#define GRL_INFO(...)
#define GRL_WARN(...)
#define GRL_ERROR(...)
#define GRL_FATAL(...)
#define GRL_CRITICAL GRL_FATAL
#endif
