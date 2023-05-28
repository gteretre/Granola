#pragma once
#include "grlpch.h"


//---Platform Specific----------------
// platform windows
#ifdef GRL_PLATFORM_WINDOWS
#define GRL_BREAK() __debugbreak()
#ifdef GRL_BUILD_DLL
#define GRANOLA_API __declspec(dllexport)
#else
			#define GRANOLA_API __declspec(dllimport)
#endif

// platform linux

#elif GRL_PLATFORM_LINUX
#define GRL_BREAK() __builtin_trap()
#ifdef GRL_BUILD_DLL
		#define GRANOLA_API __attribute__((visibility("default")))
#else
		#define GRANOLA_API
#endif

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
#define GRL_CORE_ASSERT(x, ...) { if(!(x)) { GRL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define GRL_ASSERT(x, ...) { if(!(x)) { GRL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
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
// TODO add Linux support and make changes in src\Granola\EntryPoint.h and src\Granola\App.cpp
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
//------------------------------------


//---External Libraries---------------
// OpenGL Macros
//------------------------------------
