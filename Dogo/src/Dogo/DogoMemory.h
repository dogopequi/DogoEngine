#pragma once
#include "Logger.h"
namespace Dogo
{
	struct MemoryUsage
	{
		static uint32_t TotalAllocated;
		static uint32_t TotalFreed;
		static uint32_t GetUsage() { return TotalAllocated - TotalFreed; }
		static void PrintUsage() { DG_INFO("Total Usage: %i", GetUsage()); }
	};

	static MemoryUsage MemoryMetrics;
}
	void* operator new(size_t size);
	void operator delete(void* memory, size_t size);