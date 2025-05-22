#pragma once

#ifdef DG_PLATFORM_WINDOWS
	#define DEBUG_BREAK() __debugbreak();
	#ifdef DG_BUILD_DLL
		#define DG_API _declspec(dllexport)
	#else
		#define DG_API 
	#endif
	#ifdef DG_BUILD_STATIC
		#define DG_API
	#endif
#endif
#ifdef DG_PLATFORM_LINUX
	#define DEBUG_BREAK() __builtin_trap();
	#ifdef DG_BUILD_SO
		#define DG_API __attribute__((visibility("default")))
	#else
		#define DG_API 
	#endif
#endif
#define DG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIT(x) (1 << x)
