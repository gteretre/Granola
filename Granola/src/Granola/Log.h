/* Log.h */
#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "grlpch.h"
#include "Core.h"

namespace Granola
{
	class GRANOLA_API Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define GRL_CORE_TRACE(...) ::Granola::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GRL_CORE_INFO(...)  ::Granola::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GRL_CORE_WARN(...)  ::Granola::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GRL_CORE_ERROR(...) ::Granola::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GRL_CORE_FATAL(...) ::Granola::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define GRL_TRACE(...) ::Granola::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GRL_INFO(...)  ::Granola::Log::GetClientLogger()->info(__VA_ARGS__)
#define GRL_WARN(...)  ::Granola::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GRL_ERROR(...) ::Granola::Log::GetClientLogger()->error(__VA_ARGS__)
#define GRL_FATAL(...) ::Granola::Log::GetClientLogger()->fatal(__VA_ARGS__)
