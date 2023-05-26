/* Log.h */
#pragma once
#include "grlpch.h"
#include "Core.h"

// ignore all spdlog warnings
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)


namespace Granola
{
	class GRANOLA_API Log
	{
	public:
		static void Init()
		{
		}

		// TODO make it threadsafe, use mutex, if the same command multiple times create counter eg Event bla bla (3)
		template <typename... Args>
		class GetCoreLogger
		{
		public:
			template <typename... TraceArgs>
			static void trace(TraceArgs &&... args)
			{
				std::cout << "[TRACE]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void info(TraceArgs &&... args)
			{
				std::cout << "[INFO]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void warn(TraceArgs &&... args)
			{
				std::cout << "[WARNING]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void error(TraceArgs &&... args)
			{
				std::cout << "[ERROR]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void critical(TraceArgs &&... args)
			{
				std::cout << "[FATAL]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}
		};

		template <typename... Args>
		class GetClientLogger
		{
		public:
			template <typename... TraceArgs>
			static void trace(TraceArgs &&... args)
			{
				std::cout << "[TRACE]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void info(TraceArgs &&... args)
			{
				std::cout << "[INFO]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void warn(TraceArgs &&... args)
			{
				std::cout << "[WARNING]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void error(TraceArgs &&... args)
			{
				std::cout << "[ERROR]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}

			template <typename... TraceArgs>
			static void critical(TraceArgs &&... args)
			{
				std::cout << "[FATAL]: ";
				[[maybe_unused]] const int table[] = {0, ((std::cout << std::forward<TraceArgs>(args) << "\n"), 0)...};
			}
		};
	};

	// TODO repair spdlog or get rid of it; make possibility to toggle mine own log and spdlog
	/*class GRANOLA_API Logspd
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};*/
}

//TODO layer update log
#ifdef GRL_DEBUG
#define GRL_LOGGING
#endif

//#define GRL_LOGGING_WITH_SPDLOG

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
#define GRL_TRACE(...) ::Granola::Log::GetClientLogger<>::trace(__VA_ARGS__)
#define GRL_INFO(...)  ::Granola::Log::GetClientLogger<>::info(__VA_ARGS__)
#define GRL_WARN(...)  ::Granola::Log::GetClientLogger<>::warn(__VA_ARGS__)
#define GRL_ERROR(...) ::Granola::Log::GetClientLogger<>::error(__VA_ARGS__)
#define GRL_FATAL(...) ::Granola::Log::GetClientLogger<>::critical(__VA_ARGS__)
#define GRL_CRITICAL GRL_FATAL
#else
#define GRL_TRACE(...)
#define GRL_INFO(...)
#define GRL_WARN(...)
#define GRL_ERROR(...)
#define GRL_FATAL(...)
#define GRL_CRITICAL GRL_FATAL
#endif
