#include "dgpch.h"
#include "Dogo/Utils/Logger.h"

const char* DG_COLOR_FORMAT[6] =
{
	"\033[1;31m", "\033[0;31m", "\033[0;33m", "\033[0;32m", "\033[1;36m", "\033[0;36m"
};
bool InitLogger()
{
	return true;
}

void EndLogger()
{
}

void LogOutput(DG_LOG_LEVEL level, const char* msg, ...)
{
	const char* stringLevel[6] = { "[FATAL]: ", "[ERROR]: " , "[WARN]: " , "[INFO]: " , "[DEBUG]: " , "[TRACE]: " };
	bool isError = level < 2;

	char outMessage[3200] = { 0 };

	va_list arg_ptr;
	va_start(arg_ptr, msg);
	vsnprintf(outMessage, 3200, msg, arg_ptr);
	va_end(arg_ptr);

	char outMessage2[32000] = { 0 };
	sprintf_s(outMessage2, "%s%s\n", stringLevel[level], outMessage);

	printf(DG_COLOR_FORMAT[level]);
	printf("%s", outMessage2);
	printf("\033[0m");
}

void assertionFailure(const char* expression, const char* message, const char* file, int32_t line)
{
	LogOutput(FATAL, "Assertion: %s, message: %s, in file: %s, line: %d\n", expression, message, file, line);
}
