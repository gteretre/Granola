#pragma once
#include "grlpch.h"

// to manage dll
#ifdef GRL_PLATFORM_WINDOWS
#ifdef GRL_BUILD_DLL
#define GRANOLA_API __declspec(dllexport)
#else
			#define GRANOLA_API __declspec(dllimport)
#endif
#elif GRL_PLATFORM_UNIX
#ifdef GRL_BUILD_DLL
		#define GRANOLA_API __attribute__((visibility("default")))
#else
		#define GRANOLA_API
#endif

#else
#error Currently only Windows (UNIX is under devolopment) is supported!!!
#endif

// to manage logging
#ifdef GRL_ENABLE_ASSERTS
#define GRL_CORE_ASSERT(x, ...) { if(!(x)) { GRL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define GRL_ASSERT(x, ...) { if(!(x)) { GRL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define GRL_CORE_ASSERT(x, ...)
#define GRL_ASSERT(x, ...)
#endif

// to hunt memory leaks
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>


// to manage OpenGL logging
// TODO make openGL logging
#ifdef GRL_DEBUG
#define GRL_OPENGL_DEBUG
#else
#define GRL_OPENGL_DEBUG
#endif

#define BIT(x) (1 << (x))

// OpenGL Macros
