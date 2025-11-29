#pragma once

#include "Dogo/Core.h"
#define DG_WARN_ENABLE 1
#define DG_INFO_ENABLE 1
#define DG_DEBUG_ENABLE 1
#define DG_TRACE_ENABLE 1
#define DG_ASSERT_ENABLE 1

#if DG_BUILD_RELEASE == 1
#define DG_DEBUG_ENABLE 0
#define DG_TRACE_ENABLE 0
#define DG_ASSERT_ENABLE 0
#endif

enum DG_LOG_LEVEL
{
	FATAL = 0,
	ERRORR,
	WARN,
	INFO,
	DEBUG,
	TRACE
};


DG_API void LogOutput(DG_LOG_LEVEL level, const char* msg, ...);

DG_API void assertionFailure(const char* expression, const char* message, const char* file, int32_t line);

#define DG_FATAL(msg, ...) LogOutput(FATAL, msg, ##__VA_ARGS__);
#define DG_ERROR(msg, ...) LogOutput(ERRORR, msg, ##__VA_ARGS__);

#if DG_ASSERT_ENABLE == 1
#define DG_ASSERT(expr) 											 \
{																	 \
	if (expr)														 \
	{																 \
	}																 \
	else															 \
	{																 \
		assertionFailure(#expr, "", __FILE__, __LINE__);			 \
		DEBUG_BREAK();												 \
	}																 \
}
#define DG_ASSERT_MSG(expr, msg) 									 \
{																	 \
	if (expr)														 \
	{																 \
	}																 \
	else															 \
	{																 \
		assertionFailure(#expr, msg, __FILE__, __LINE__);			 \
		DEBUG_BREAK();												 \
	}																 \
}
#else
#define DG_ASSERT(msg, ...)
#define DG_ASSERT_MSG(expr, msg)
#endif


#if DG_WARN_ENABLE == 1
#define DG_WARN(msg, ...) LogOutput(WARN, msg, ##__VA_ARGS__);
#else
#define DG_WARN(msg, ...)
#endif

#if DG_INFO_ENABLE == 1
#define DG_INFO(msg, ...) LogOutput(INFO, msg, ##__VA_ARGS__);
#else
#define DG_INFO(msg, ...)
#endif

#if DG_DEBUG_ENABLE == 1
#define DG_DEBUG(msg, ...) LogOutput(DEBUG, msg, ##__VA_ARGS__);
#else
#define DG_DEBUG(msg, ...)
#endif

#if DG_TRACE_ENABLE == 1
#define DG_TRACE(msg, ...) LogOutput(TRACE, msg, ##__VA_ARGS__);
#else
#define DG_TRACE(msg, ...)
#endif