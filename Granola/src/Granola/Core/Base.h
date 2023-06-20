#pragma once
#include "grlpch.h"


//---Temporary Solution For Warning---
#pragma warning(disable : 4514)
#pragma warning(disable : 4201)
//-------------------------------------


//---Platform Specific----------------
// platform windows
#ifdef GRL_PLATFORM_WINDOWS
#define GRL_BREAK() __debugbreak()

// platform linux
#elif GRL_PLATFORM_LINUX
#define GRL_BREAK() raise(SIGTRAP) // or __builtin_trap()

// other platforms
#else
#error Currently only Windows (Linux is under devolopment) is supported!!!
#endif
//------------------------------------


//---Own Macros-----------------------
// just to make it easier to read
#define BIT(x) (1 << (x))
#define GRL_BIND_EVENT_FN(fn) [this](auto&&... args) { return fn(std::forward<decltype(args)>(args)...); }

// to manage logging
#ifdef GRL_ENABLE_ASSERTS
#define GRL_CORE_ASSERT(x, ...) { if(!(x)) { GRL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); GRL_BREAK(); } }
#define GRL_ASSERT(x, ...) { if(!(x)) { GRL_ERROR("Assertion Failed: {0}", __VA_ARGS__); GRL_BREAK(); } }
#else
	#define GRL_CORE_ASSERT(x, ...)
	#define GRL_ASSERT(x, ...)
#endif

// to manage OpenGL logging
#ifdef GRL_DEBUG
#define GRL_OPENGL_DEBUG glDebugMessageCallback(GRL::OpenGLDebugMessageCallback, nullptr);\
glEnable(GL_DEBUG_OUTPUT); glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#else
	#define GRL_OPENGL_DEBUG
#endif
//------------------------------------


//---Compiler Specific-----------------
// basic functionality
#ifdef _MSC_VER
#define GRL_FUN_INFO __FUNCSIG__
#elif defined(__clang__)
	#define GRL_FUN_INFO __PRETTY_FUNCTION__
#elif defined(__GNUC__)
	#define GRL_FUN_INFO __PRETTY_FUNCTION__
#else
#define GRL_FUN_INFO __func__
#endif

// to hunt memory leaks (Windows only!!!)
// TODO add Linux support and make changes in src\Granola\EntryPoint.h and src\Granola\App.cpp for Linux
#define _CRTDBG_MAP_ALLOC
//------------------------------------


//---In Namespace---------------------

//Granola Engine Michal Kowalski 2023
namespace Granola
{
	// Granola memory management system based on unique_ptr
	template <typename T>
	using Scope = std::unique_ptr<T>;

	// Granola memory management system based on unique_ptr
	template <typename T, typename... Args>
	constexpr Scope<T> CreateScope(Args &&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// Granola memory management system based on shared_ptr
	template <typename T>
	using Ref = std::shared_ptr<T>;

	// Granola memory management system based on shared_ptr
	template <typename T, typename... Args>
	constexpr Ref<T> CreateRef(Args &&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

//------------------------------------


//---External Libraries---------------
// OpenGL Macros
//------------------------------------
