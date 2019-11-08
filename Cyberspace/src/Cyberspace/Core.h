#pragma once

#ifdef CSPACE_PLATFORM_WINDOWS
	#ifdef CSPACE_BUILD_DLL
		#define CSPACE_API __declspec(dllexport)
	#else
		#define CSPACE_API __declspec(dllimport)
	#endif
#else
	#error Cyberspace only supports Windows!
#endif