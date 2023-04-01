#pragma once

#ifdef GRL_PLATFORM_WINDOWS
#ifdef GRL_BUILD_DLL
#define GRANOLA_API __declspec(dllexport)
#else
		#define GRANOLA_API __declspec(dllimport)
#endif
#else
	#error Currently only Windows is supported!!!
#endif
